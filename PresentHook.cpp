#include "DiscordHook.h"
#include "xorstr.hpp"
#include "Globals.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "Menu.h"
#include "Engine.h"
#include "VMTHooking.h"
#include "Cfg.h"
#include <d3d11.h>
#include "MenuBackground.h"

bool shouldDraw = true;
ID3D11DeviceContext* pD11DeviceContext = nullptr;
ID3D11RenderTargetView* pD11RenderTargetView = nullptr;

void BeginDraw(IDXGISwapChain* pSwapChain);
void EndDraw();

int DiscordHook::PresentHook(void* pThis, UINT SyncInterval, UINT Flags)
{
    static auto pSSmoduleClass = (uintptr_t*)OFFSET_SSMODULE;
    if (!IsValidPtr(pSSmoduleClass)) return DiscordHook::Get()->oPresent(pThis, SyncInterval, Flags);

    //Simple PBSS bypass
    auto ssRequest = (*(int*)(*pSSmoduleClass + 0x14) != -1);
    if (!shouldDraw || ssRequest) return DiscordHook::Get()->oPresent(pThis, SyncInterval, Flags);

    BeginDraw(reinterpret_cast<IDXGISwapChain*>(pThis));

    if (GetAsyncKeyState(VK_INSERT) & 0x1) G::isMenuVisible = !G::isMenuVisible;

    Menu::GetContext()->Render();
    F::pVisuals->RenderVisuals();

    EndDraw();
	return DiscordHook::Get()->oPresent(pThis, SyncInterval, Flags);
}

BOOL __stdcall DiscordHook::BitBltHook(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop)
{
    //Disable visuals for 15ms and call original BitBlt
    Cfg::DBG::_internalFFSS++;
    shouldDraw = false;
    Sleep(15);
    auto result = DiscordHook::Get()->oBitBlt(hdcDest, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, dwRop);
    shouldDraw = true;
    return result;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall HooksManager::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (G::isMenuVisible)
    {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

        switch (uMsg) {
        case WM_MOUSEMOVE: return false;
        default:
            break;
        }
        return true;
    }
    return CallWindowProc(HooksManager::Get()->oWndproc, hWnd, uMsg, wParam, lParam);
}

void BeginDraw(IDXGISwapChain* pSwapChain)
{
    DX::pSwapChain = pSwapChain;
    if (!DX::pDevice || !pD11DeviceContext)
    {
        // Create ImguiContext
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.Fonts->AddFontDefault();
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

        TCHAR windir[MAX_PATH];
        GetWindowsDirectory(windir, MAX_PATH);

        std::string fontDir = std::string(windir);
        fontDir += xorstr_("\\Fonts\\");

        auto LoadFontFromFile = [&io, &fontDir](const std::string& fontName, float size) -> ImFont*
        {
            return io.Fonts->AddFontFromFileTTF((fontDir + fontName + ".ttf").c_str(), size);
        };

        auto LoadFontFromMemory = [&io, &fontDir](void* fontData, float size) -> ImFont*
        {
            return io.Fonts->AddFontFromMemoryTTF(fontData, sizeof(fontData), size);
        };

        DX::Verdana8 = LoadFontFromFile(xorstr_("Verdana"), 8.f);
        DX::Verdana12 = LoadFontFromFile(xorstr_("Verdana"), 12.f);
        DX::Verdana18 = LoadFontFromFile(xorstr_("Verdana"), 18.f);
        DX::Verdana24 = LoadFontFromFile(xorstr_("Verdana"), 24.f);
        DX::Verdana48 = LoadFontFromFile(xorstr_("Verdana"), 48.f);

        DX::Digital10 = LoadFontFromMemory(Fonts::digital, 10.f);
        DX::Digital12 = LoadFontFromMemory(Fonts::digital, 12.f);
        DX::Digital24 = LoadFontFromMemory(Fonts::digital, 24.f);
        DX::Digital36 = LoadFontFromMemory(Fonts::digital, 36.f);

        io.FontDefault = DX::Verdana18;

        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&DX::pDevice)))
        {
            pSwapChain->GetDevice(__uuidof(DX::pDevice), (void**)&DX::pDevice);
            DX::pDevice->GetImmediateContext(&pD11DeviceContext);
        }

        ImGui_ImplWin32_Init(FindWindowA(xorstr_("Battlefield 4"), NULL));
        ImGui_ImplDX11_Init(DX::pDevice, pD11DeviceContext);
    }
    else
    {
        ID3D11Texture2D* renderTargetTexture = nullptr;
        if (!pD11RenderTargetView)
        {
            if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&renderTargetTexture))))
            {
                DX::pDevice->CreateRenderTargetView(renderTargetTexture, nullptr, &pD11RenderTargetView);
                renderTargetTexture->Release();
            }
        }
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void EndDraw()
{
    ImGui::Render();
    pD11DeviceContext->OMSetRenderTargets(1, &pD11RenderTargetView, nullptr);

    // Release and free resources to setup again on the next loop.
    if (pD11RenderTargetView)
    {
        pD11RenderTargetView->Release();
        pD11RenderTargetView = nullptr;
    }

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    shouldDraw = true;
}

