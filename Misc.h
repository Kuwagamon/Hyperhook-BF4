#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <Windows.h>
#include <math.h>
#include <d3dx9.h>
#ifndef M_PI
#define M_PI 3.14159265359
#endif
#ifndef RAD2DEG
#define RAD2DEG(a) a * 180.0f / M_PI;
#endif
#ifndef DEG2RAD
#define DEG2RAD(a) a * M_PI / 180.0f;
#endif

struct ImVec2;

class Misc
{
public:
	template<unsigned int IIdx, typename TRet, typename ... TArgs>
	static auto CallVirtualFn(void* thisptr, TArgs ... argList) -> TRet
	{
		using Fn = TRet(__thiscall*)(void*, decltype(argList)...);
		return (*static_cast<Fn**>(thisptr))[IIdx](thisptr, argList...);
	}

	//Use this when function is passing value by refference
	template<typename FuncType>
	__forceinline static FuncType CallVirtualFnEx(void* ppclass, int index)
	{
		int* pVTable = *(int**)ppclass;
		int dwAddress = pVTable[index];
		return (FuncType)(dwAddress);
	}

	static DWORD_PTR FindSignature(const char* szModule, const char* szSignature);

	static void RotateTriangle(std::array<D3DXVECTOR2, 3>& points, float rotation);

	static void AngleVectors(const D3DXVECTOR3& angles, D3DXVECTOR3* forward);

	static void VectorAngles(const D3DXVECTOR3& forward, D3DXVECTOR3* angles);

	static D3DXVECTOR3 CalcAngles(const D3DXVECTOR3& src, const D3DXVECTOR3& dst);

	static D3DXVECTOR2 CalcAngles2D(const D3DXVECTOR3& src, const D3DXVECTOR3& dst);

	static void ClampAngles(D3DXVECTOR2* ang);

	static void ClampAngles(D3DXVECTOR3* ang);

	static D3DXVECTOR2 AngleDiff(const D3DXVECTOR2& src, const D3DXVECTOR2& dst);

	static float AngleDiff(float src, float dst);

	static void SmoothAngle(const D3DXVECTOR2& from, D3DXVECTOR2& to, float perc);

	static float GetFovFraction(const D3DXVECTOR3& src, const D3DXVECTOR3& dst, const D3DXVECTOR2& angles);

	static std::string GetRandomString(int length, bool caseSensitive = true, bool numbers = false, bool specialSymbols = false);

	static void DebugMsg(const std::string& title, const std::string& msg, UINT type = MB_OK);

	static std::string GetSystemTime();

	static float GetAbsDeltaAtGivenPoints(const D3DXVECTOR2& src, const D3DXVECTOR2& dst);

	static void RotatePoint(ImVec2* point, const ImVec2& origin, float angle);

	static void RotateTriangle(std::array<ImVec2, 3>* points, float angle);

	static float Distance3D(const D3DXVECTOR3& src, const D3DXVECTOR3& dst);

	static float Distance2D(const D3DXVECTOR2& src, const D3DXVECTOR2& dst);
};