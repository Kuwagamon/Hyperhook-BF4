#pragma once
#include <iostream>
#include <Windows.h>
#include "Engine.h"

//Extra free space above new vmt (EXTRA_SPACE * sizeof(std::uintptr_t))
#define EXTRA_SPACE 3

//Use virtual protect when needed
//#define USE_VIRTUAL_PROTECT


enum class Index
{
	PHYSICS_RAY_QUERY = 0,
	PRE_FRAME_UPDATE = 3,
};

class VMTHook
{
public:
	VMTHook()
		: ppClassBase(nullptr), pClassVmt(nullptr), pNewVmt(nullptr), vmtLenght(-1) {};
	VMTHook(void* pClassInstance)
		: ppClassBase(reinterpret_cast<uintptr_t**>(pClassInstance)), pClassVmt(nullptr),
		pNewVmt(nullptr), vmtLenght(-1) {};
	~VMTHook() { Release(); };

	void Hook(Index index, void* fnPointer);
	bool Release();
	bool Setup(void* pclass = nullptr);

	template <typename T>
	T GetOriginal(Index index) { return reinterpret_cast< T >(pClassVmt[(int)index]); }

private:

	//https://github.com/OneshotGH/CSGOSimple-master/blob/master/CSGOSimple/helpers/vfunc_hook.cpp
	std::uintptr_t*		SearchFreeDataPage(const char* moduleName, const size_t vmtSize);
	std::uintptr_t**	ppClassBase;
	std::uintptr_t*		pClassVmt;
	std::uintptr_t*		pNewVmt;
	std::size_t			vmtLenght;
};

class HooksManager
{
	explicit HooksManager() {}
	~HooksManager() {}

	WNDPROC oWndproc = NULL;
	HWND oHWnd = NULL;

public:
	static HooksManager* Get();

	std::unique_ptr<VMTHook> pPreFrameHook;
	std::unique_ptr<VMTHook> pRayCasterHook;
	typedef int(__fastcall* PreFrameUpdate_t) (void*, void*, float);
	typedef bool(__fastcall* PhysicsRayQuery_t) (void*, void*, const char*, D3DXVECTOR4*, D3DXVECTOR4*, RayCastHit*, int, void*);

	static int __fastcall PreFrameUpdate(void* pThis, void* EDX, float deltaTime);
	static LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static bool __fastcall PhysicsRayQuery(void* pThis, void* EDX, const char* identifier, D3DXVECTOR4* from, D3DXVECTOR4* to, RayCastHit* hit, int flag, void* PhysicsEntityList);

	void Install();
	void Uninstall();
};
