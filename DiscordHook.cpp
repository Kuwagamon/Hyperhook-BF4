#include "DiscordHook.h"
#include "Misc.h"
#include "xorstr.hpp"
#include "Engine.h"
#include "Globals.h"
#include <sstream>

typedef int(__stdcall* CreateHookFn)(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal);
typedef int(__stdcall* EnableHookFn)(LPVOID pTarget, BOOL enable);
typedef int(__stdcall* ApplyQueuedFn)(VOID);
typedef int(__stdcall* CreateHookApiExFn)(
	LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID* ppOriginal, LPVOID* ppTarget);

//If you wish to find Hooking sigs in IDA, 
//search for "Failed queueing enable for hook %s; 0x%x" or "Failed creating hook %s; 0x%x"

void DiscordHook::CreateHook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal)
{
	static auto MH_CreateHookFn = (CreateHookFn)(Misc::FindSignature(
		xorstr_("DiscordHook64.dll"), 
		xorstr_("41 57 41 56 56 57 55 53 48 83 EC 68 4D 89 C6 49 89 D7 48 89 CF 48 8B 05 ? ? ? ? 48 31 E0 48 89 44 24 ? BE ? ? ? ?")));

	MH_CreateHookFn(pTarget, pDetour, ppOriginal);
}

void DiscordHook::EnableHook(LPVOID pTarget)
{
	static auto MH_EnableHookFn = (EnableHookFn)(Misc::FindSignature(
		xorstr_("DiscordHook64.dll"), 
		xorstr_("41 57 41 56 41 55 41 54 56 57 55 53 48 83 EC 38 41 89 D6 48 89 CB 48 8B 05 ? ? ? ? 48 31 E0 48 89 44 24 ? BE ? ? ? ?")));

	MH_EnableHookFn(pTarget, TRUE);
}

void DiscordHook::DisableHook(LPVOID pTarget)
{
	static auto MH_EnableHookFn = (EnableHookFn)(Misc::FindSignature(
		xorstr_("DiscordHook64.dll"),
		xorstr_("41 57 41 56 41 55 41 54 56 57 55 53 48 83 EC 38 41 89 D6 48 89 CB 48 8B 05 ? ? ? ? 48 31 E0 48 89 44 24 ? BE ? ? ? ?")));

	MH_EnableHookFn(pTarget, FALSE);
}

void DiscordHook::ApplyQueued()
{
	static auto MH_ApplyQueuedFn = (ApplyQueuedFn)(Misc::FindSignature(
		xorstr_("DiscordHook64.dll"),
		xorstr_("41 57 41 56 41 55 41 54 56 57 55 53 48 83 EC 38 48 8B 05 ? ? ? ? 48 31 E0 48 89 44 24 ? BE ? ? ? ? 31 C0 F0 0F B1 35 ? ? ? ?")));

	MH_ApplyQueuedFn();
}

void DiscordHook::CreateHookApiEx(LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID* ppOriginal, LPVOID* ppTarget)
{
	static auto MH_CreateHookApiExFn = (CreateHookApiExFn)(Misc::FindSignature(
		xorstr_("DiscordHook64.dll"),
		xorstr_("41 56 56 57 53 48 83 EC 28 4D 89 CE 4C 89 C7 48 89 D3 48 8B 74 24 ? FF 15 ? ? ? ?")));

	MH_CreateHookApiExFn(pszModule, pszProcName, pDetour, ppOriginal, ppTarget);
}

DiscordHook::DiscordHook()
{
	auto presentAddrs = Misc::FindSignature(
		xorstr_("DiscordHook64.dll"), 
		xorstr_("FF 15 ? ? ? ? 89 C6 48 8D 4C 24 ? E8 ? ? ? ? 48 8B 4C 24 ? 48 31 E1 E8 ? ? ? ? 89 F0 48 83 C4 30"));

	if (!presentAddrs)
	{
		ERROR(xorstr_("Couldn't locate Discord Present()!"));
		FreeLibraryAndExitThread(G::hInst, 0);
	}

	auto finalAddr = presentAddrs + (*(ULONG32*)(presentAddrs + 2)) + 6;
	if (!finalAddr)
	{
		ERROR(xorstr_("Couldn't locate Discord Present()!"));
		FreeLibraryAndExitThread(G::hInst, 0);
	}

	//Magic
	oPresent = reinterpret_cast<Present_t>(*(DWORD64*)(finalAddr));
	ppOriginal = &(*(void**)(finalAddr)); 

	std::string modName = xorstr_("Gdi32.dll");
	std::wostringstream woss; woss << modName.c_str();

	//Api hook using Discord framework
	CreateHookApiEx(woss.str().c_str(), xorstr_("BitBlt"), (void*)BitBltHook, (void**)&oBitBlt, nullptr);
}

DiscordHook* DiscordHook::Get()
{
	static DiscordHook dscHook;
	return &dscHook;
}

void DiscordHook::InstallHook()
{
	*ppOriginal = PresentHook;
	EnableHook((void*)BitBlt);
	ApplyQueued();
}

void DiscordHook::UninstallHook()
{
	*ppOriginal = oPresent;
	DisableHook((void*)BitBlt);
}
