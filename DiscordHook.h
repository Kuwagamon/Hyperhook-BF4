#pragma once
#include <Windows.h>

class DiscordHook
{
private:
	typedef int(__stdcall* Present_t)(void* thisptr, UINT SyncInterval, UINT Flags);
	static int __stdcall PresentHook(void* pThis, UINT SyncInterval, UINT Flags);
	typedef BOOL(__stdcall* BitBlt_t)(HDC hdcDest, int nXDest, int nYDest, int nWidth,
		int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop);
	static BOOL __stdcall BitBltHook(HDC hdcDest, int nXDest, int nYDest, int nWidth,
		int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop);
	
	BitBlt_t oBitBlt = NULL;
	Present_t oPresent = NULL;
	void** ppOriginal = nullptr;

	//Discord hooking methods 
	void CreateHook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal);
	void EnableHook(LPVOID pTarget);
	void DisableHook(LPVOID pTarget);
	void ApplyQueued();
	void CreateHookApiEx(LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID* ppOriginal, LPVOID* ppTarget);
	
	explicit DiscordHook();
	~DiscordHook() { UninstallHook(); }

public:
	static DiscordHook* Get();
	void InstallHook();
	void UninstallHook();
};

