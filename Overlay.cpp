#include "stdafx.h"
#include "Overlay.h"
#include "Globals.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <dwmapi.h>
#include <thread>
#include "Cfg.h"
#include "xorstr.hpp"
#include "Misc.h"
#include "Menu.h"
#pragma comment(lib, "dwmapi.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK Overlay::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (DX::pOverlay->pDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            DX::pOverlay->DXParams.BackBufferWidth = LOWORD(lParam);
            DX::pOverlay->DXParams.BackBufferHeight = HIWORD(lParam);
            DX::pOverlay->ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

bool Overlay::RepositionWindow()
{
    if (gameHandle)
    {
        RECT WinRect;
        GetWindowRect(gameHandle, &WinRect);
        ImVec2 pos = { (float)WinRect.left, (float)WinRect.top };

        static bool _switch = true;
        if (!G::isMenuVisible)
        {
            if (!_switch)
            {
                SetWindowLong(handle, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT);
                _switch = !_switch;
            }
        }
        else if (_switch)
        {
            SetWindowLong(handle, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST);
            _switch = !_switch;
        }

#ifndef GUI_TEST
        CheckGameBounds();
#endif // !GUI_TEST

#ifdef GUI_TEST
        G::overlaySize = { 1920, 1080 };
#endif

        G::scrnCenter = { G::overlaySize.x * 0.5f, G::overlaySize.y * 0.5f };

        int sum = pos.x + pos.y + G::overlaySize.x + G::overlaySize.y;
        static int prev = 0;
        bool shouldReposition = false;
        if (prev != sum)
        {
            prev = sum;
            shouldReposition = true;
        }

        if (handle)
        {
            if (shouldReposition)
            {
                DWORD dwStyle = GetWindowLong(gameHandle, GWL_STYLE);
                if (dwStyle & WS_BORDER)
                {
                    pos.x += 8;
                    pos.y += 31;
                }
                MoveWindow(handle, pos.x, pos.y, G::overlaySize.x, G::overlaySize.y, true);
            }
            return true;
        }
        return false;
    }
    return false;
}

void Overlay::FakeDumpOffsets()
{
    DX::pConsole->AddLog(xorstr_("----- Start of memory dump -----"));
    DX::pConsole->AddLog(xorstr_("MAIN                               = 0x%X"), 0x142364b78);
    DX::pConsole->AddLog(xorstr_("DX_RENDERER                 = 0x%X"), 0x142738080);
    DX::pConsole->AddLog(xorstr_("CLIENT_GAME_CONTEXT   = 0x%X"), 0x142670d80);
    DX::pConsole->AddLog(xorstr_("GAME_RENDERER             = 0x%X"), 0x142672378);
    DX::pConsole->AddLog(xorstr_("----- End of memory dump -----"));
}

bool Overlay::SetupOverlay()
{
    FakeDumpOffsets();

    gameHandle = FindWindowW(G::gameName.c_str(), NULL);
    CheckGameBounds();

    ZeroMemory(&overlayWindowClass, sizeof(WNDCLASSEX)); // Initialises, sets all bits to 0 to remove garbage data
    overlayWindowClass.cbClsExtra = NULL;
    overlayWindowClass.cbWndExtra = NULL;
    overlayWindowClass.cbSize = sizeof(WNDCLASSEX);
    overlayWindowClass.style = CS_HREDRAW | CS_VREDRAW;
    overlayWindowClass.lpfnWndProc = WndProc; // Function that will be executed when the window receives a "message" (input). Required! (crashes if set to NULL)
    overlayWindowClass.hInstance = NULL;
    overlayWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    overlayWindowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
    overlayWindowClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
    overlayWindowClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
    overlayWindowClass.lpszClassName = G::overlayName.c_str(); // Class name to use with the Windows API function CreateWindow(Ex) to create the window
    overlayWindowClass.lpszMenuName = G::overlayName.c_str();
    RegisterClassEx(&overlayWindowClass);

    DX::pConsole->AddLog(xorstr_("Creating overlay window..."));

    handle = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, 
        overlayWindowClass.lpszClassName, overlayWindowClass.lpszClassName, 
        WS_POPUP, G::overlayPos.x, G::overlayPos.y, G::overlaySize.x, G::overlaySize.y, 
        0, 0, overlayWindowClass.hInstance, 0);

    
    DX::pConsole->AddLog(xorstr_("Overlay created!"));

    if (handle)
    {
        SetLayeredWindowAttributes(handle, NULL, NULL, NULL);
        DWM_BLURBEHIND bb = { DWM_BB_ENABLE | DWM_BB_BLURREGION, true, CreateRectRgn(0, 0, -1, -1), true };
        DwmEnableBlurBehindWindow(handle, &bb);

        if (!CreateDeviceD3D())
        {
            CleanupDeviceD3D();
            UnregisterClass(overlayWindowClass.lpszClassName, overlayWindowClass.hInstance);
            return false;
        }

        ShowWindow(handle, SW_SHOWDEFAULT);
        UpdateWindow(handle);

        if (!CreateImGuiContext()) return false;

        RunOverlay();

        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        CleanupDeviceD3D();
        ::DestroyWindow(handle);
        ::UnregisterClass(overlayWindowClass.lpszClassName, overlayWindowClass.hInstance);

        return false;
    }
    return false;
}

bool Overlay::CreateDeviceD3D()
{
    if ((pDX = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    ZeroMemory(&DXParams, sizeof(DXParams));
    DXParams.Windowed = TRUE;
    DXParams.BackBufferFormat = D3DFMT_A8R8G8B8;
    DXParams.BackBufferWidth = G::overlaySize.x;
    DXParams.BackBufferHeight = G::overlaySize.y;
    DXParams.MultiSampleQuality = DEFAULT_QUALITY;
    DXParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    DXParams.EnableAutoDepthStencil = TRUE;
    DXParams.AutoDepthStencilFormat = D3DFMT_D16;
    DXParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    /*DXParams.Windowed = TRUE;
    DXParams.BackBufferFormat = D3DFMT_A8R8G8B8;
    DXParams.BackBufferWidth = size.x;
    DXParams.BackBufferHeight = size.y;
    DXParams.MultiSampleQuality = DEFAULT_QUALITY;
    DXParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    DXParams.EnableAutoDepthStencil = TRUE;
    DXParams.AutoDepthStencilFormat = D3DFMT_D16;
    DXParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;*/

    if (pDX->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, handle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &DXParams, &pDevice) < 0)
        return false;

    return true;
}

bool Overlay::CreateImGuiContext()
{
    DX::pConsole->AddLog(xorstr_("Initializing ImGui..."));

    if (!ImGui::CreateContext()) return false;

    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig fontCfg = ImFontConfig();
    io.DeltaTime = 1.0f / 60.0f;

    fontCfg.RasterizerFlags = 0x01;
    fontCfg.OversampleH = fontCfg.OversampleV = 1;
    fontCfg.PixelSnapH = true;

    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
    style.Colors[ImGuiCol_WindowBg] = ImGui::ColorConvertU32ToFloat4(ImColor(15, 15, 15, 255));
    style.Colors[ImGuiCol_ChildBg] = ImGui::ColorConvertU32ToFloat4(ImColor(10, 10, 10, 255));
    style.Colors[ImGuiCol_Border] = ImGui::ColorConvertU32ToFloat4(ImColor(15, 15, 15, 255));
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);

    style.WindowRounding = 0.f;
    style.FramePadding = ImVec2(4, 0);
    style.WindowPadding = ImVec2(0, 0);
    style.ItemSpacing = ImVec2(0, 12);
    style.ScrollbarSize = 10.f;
    style.ScrollbarRounding = 0.f;
    style.GrabMinSize = 5.f;

    DX::Verdana8 = io.Fonts->AddFontFromFileTTF(xorstr_("c:\\Windows\\Fonts\\Verdana.ttf"), 8.f);
    DX::Verdana12 = io.Fonts->AddFontFromFileTTF(xorstr_("c:\\Windows\\Fonts\\Verdana.ttf"), 12.f);
    DX::Verdana18 = io.Fonts->AddFontFromFileTTF(xorstr_("c:\\Windows\\Fonts\\Verdana.ttf"), 18.f);
    DX::Verdana24 = io.Fonts->AddFontFromFileTTF(xorstr_("c:\\Windows\\Fonts\\Verdana.ttf"), 24.f);
    io.FontDefault = DX::Verdana18;

    if(!ImGui_ImplWin32_Init(handle) || !ImGui_ImplDX9_Init(pDevice)) return false;

    DX::pConsole->AddLog(xorstr_("ImGui has been initialized!"));
    return true;
}

void Overlay::CleanupDeviceD3D()
{
    if (pDevice) { pDevice->Release(); pDevice = NULL; }
    if (pDX) { pDX->Release(); pDX = NULL; }
}

void Overlay::ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = pDevice->Reset(&DXParams);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

void Overlay::CheckGameBounds()
{
    static const auto pGameDx = *(uintptr_t**)(0x142738080);
    static const auto pScreen = *(uintptr_t**)(*(uintptr_t*)(&pGameDx) + 0x38);
    if (!pGameDx || !pScreen) G::overlaySize = { 1920, 1080 };

    G::overlaySize =
    {
        (float)*(int*)(*(uintptr_t*)(&pScreen) + 0x60),
        (float)*(int*)(*(uintptr_t*)(&pScreen) + 0x64)
    };
}

void Overlay::RunOverlay()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    std::thread refreshThread(&Overlay::RefreshOverlay, this);
    
    while (msg.message != WM_QUIT)
    {
        if (GetAsyncKeyState(VK_INSERT) & 0x1)
            G::isMenuVisible = !G::isMenuVisible;

        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        F::pVisuals->RenderVisuals();
        Menu::GetContext()->Render();

        ImGui::EndFrame();

        pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (pDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            pDevice->EndScene();
        }
        HRESULT result = pDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();

        if (G::shouldExit) break;

        std::this_thread::sleep_for(std::chrono::milliseconds(G::overlayRefresh));
    }

    //if (F::T::inputThread) { F::T::inputThread->detach(); delete F::T::inputThread; }
    refreshThread.detach();
}

void Overlay::RefreshOverlay()
{
    while (!G::shouldExit)
    {
        RepositionWindow();
        std::this_thread::sleep_for(std::chrono::milliseconds(G::overlayRefresh));
    }
}

void Console::AddLog(const char* format, ...)
{
    va_list va_alist;
    char buf[1024];
    va_start(va_alist, format);
    _vsnprintf(buf, sizeof(buf), format, va_alist);
    va_end(va_alist);

    const std::string& tmp = buf;

    consoleOutput += ("[" + Misc::GetSystemTime() + "] " + tmp + "\n");
}

