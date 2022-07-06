#pragma once
#include <vector>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class Overlay
{
public:
	IDirect3D9* pDX;
	IDirect3DDevice9* pDevice;
	D3DPRESENT_PARAMETERS DXParams;

private:
	HWND gameHandle;
	HWND handle;
	WNDCLASSEX overlayWindowClass;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool RepositionWindow();

	void FakeDumpOffsets();

	bool CreateDeviceD3D();
	bool CreateImGuiContext();
	void CleanupDeviceD3D();
	void ResetDevice();
	void CheckGameBounds();
	void RunOverlay();

public:
	bool SetupOverlay();
	void RefreshOverlay();
};

class Console
{
private:
	friend class Visuals;
	std::string consoleOutput;

public:
	//Output -> [hh:mm:ss] format\n
	void AddLog(const char* format, ...);
};

