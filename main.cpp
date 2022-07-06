#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "Globals.h"
#include "Misc.h"
#include "xorstr.hpp"
#include "VMTHooking.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "DiscordHook.h"

int ExitThread()
{
	FreeLibraryAndExitThread(G::hInst, 0);
	return 1;
}

DWORD WINAPI OverlayThread(LPVOID lpParam)
{
	UNREFERENCED_PARAMETER(lpParam);

	if (!GetModuleHandleA(xorstr_("DiscordHook64.dll")))
	{
		ERROR(xorstr_("DiscordHook64.dll not found! \nHave You enabled Discord Overlay first?"));
		return ExitThread();
	}

	F::pVisuals = std::make_unique<Visuals>();
	F::pConfig = std::make_unique<IniParser>();

	F::pConfig->Init(xorstr_("HyperHook_Config.ini"));
	F::pConfig->Read();

	DiscordHook::Get()->InstallHook();
	HooksManager::Get()->Install();

	while (!G::shouldExit) Sleep(75);

	HooksManager::Get()->Uninstall();
	DiscordHook::Get()->UninstallHook();

	Sleep(500);

	return ExitThread();
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) 
{
	G::hInst = hinstDLL;
	if (fdwReason == DLL_PROCESS_ATTACH) 
	{
		DisableThreadLibraryCalls(hinstDLL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)OverlayThread, lpReserved, NULL, NULL);
	}
	

	return TRUE;
}