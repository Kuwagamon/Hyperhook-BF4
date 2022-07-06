#include "stdafx.h"
#include "Misc.h"
#include "xorstr.hpp"
#include "imgui.h"
#include <random>
#include "Globals.h"
#include <D3dx9math.h>
#include <ctime>
#include <Psapi.h>
#define     EQN_EPS			 1e-9
#define	    IsZero(x)		 ((x) > -EQN_EPS && (x) < EQN_EPS)
#define		INRANGE(x,a,b)   (x >= a && x <= b)
#define		GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define		GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define PI       3.14159265358979323846
#define PI_2     1.57079632679489661923

void SinCos(float radians, float* sine, float* cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}

DWORD_PTR Misc::FindSignature(const char* szModule, const char* szSignature)
{
	MODULEINFO modInfo;
	auto mod = GetModuleHandleA(szModule);
	GetModuleInformation(GetCurrentProcess(), mod, &modInfo, sizeof(MODULEINFO));
	DWORD_PTR startAddress = (DWORD_PTR)mod;
	DWORD_PTR endAddress = (startAddress + (DWORD_PTR)modInfo.SizeOfImage);
	const char* pat = szSignature;
	DWORD_PTR firstMatch = 0;
	for (DWORD_PTR pCur = startAddress; pCur < endAddress; pCur++) {
		if (!*pat) return firstMatch;
		if (*(PBYTE)pat == ('\?') || *(BYTE*)pCur == GET_BYTE(pat)) {
			if (!firstMatch) firstMatch = pCur;
			if (!pat[2]) return firstMatch;
			if (*(PWORD)pat == ('\?\?') || *(PBYTE)pat != ('\?')) pat += 3;
			else pat += 2;
		}
		else {
			pat = szSignature;
			firstMatch = 0;
		}
	}
	return NULL;
}

void Misc::RotateTriangle(std::array<D3DXVECTOR2, 3>& points, float rotation)
{
	const auto points_center = (points.at(0) + points.at(1) + points.at(2)) / 3;
	for (auto& point : points)
	{
		point -= points_center;

		const auto temp_x = point.x;
		const auto temp_y = point.y;

		const auto theta = D3DXToDegree(rotation);
		const auto c = cosf(theta);
		const auto s = sinf(theta);

		point.x = temp_x * c - temp_y * s;
		point.y = temp_x * s + temp_y * c;

		point += points_center;
	}
}

void Misc::AngleVectors(const D3DXVECTOR3& angles, D3DXVECTOR3* forward)
{
	float sp, sy, cp, cy;

	SinCos(-(angles.y), &sy, &cy);
	SinCos(-(angles.x), &sp, &cp);

	forward->x = -cp * cy;
	forward->y = -cp * sy;
	forward->z = sp;
}

void Misc::VectorAngles(const D3DXVECTOR3& forward, D3DXVECTOR3* angles)
{
	static constexpr double deg = 180.0f / M_PI;
	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270.f;
		else
			pitch = 90.f;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * deg);
		if (yaw < 0)
			yaw += 360;
 
		tmp = sqrt (forward[0]*forward[0] + forward[1]*forward[1]);
		pitch = (atan2(-forward[2], tmp) * deg);
		if (pitch < 0.f)
			pitch += 360.f;
	}
	
	*angles[1] = pitch;
	*angles[0] = yaw;
	*angles[2] = 0;
}

D3DXVECTOR3 Misc::CalcAngles(const D3DXVECTOR3& src, const D3DXVECTOR3& dst)
{
	Vector angles;
	Vector delta = dst - src;
	D3DXVec3Normalize(&delta, &delta);
	auto hyp = D3DXVec3Length(&delta);
	angles.x = -atan2f(delta.x, delta.z);
	angles.y = atan2f(delta.y, hyp);
	angles.z = 0.0f;
	ClampAngles(&angles);
	return angles;
}

D3DXVECTOR2 Misc::CalcAngles2D(const D3DXVECTOR3& src, const D3DXVECTOR3& dst)
{
	auto space = dst - src;
	D3DXVec3Normalize(&space, &space);
	D3DXVECTOR2 angle;
	angle.x = -atan2(space.x, space.z);
	angle.y = atan2(space.y, sqrt((space.x * space.x) + (space.z * space.z)));
	ClampAngles(&angle);
	return angle;
}

void Misc::ClampAngles(D3DXVECTOR2* ang)
{
	if (ang->x <= -PI)
		ang->x += 2 * PI;
	if (ang->x > PI)
		ang->x -= 2 * PI;
	if (ang->y <= -PI_2)
		ang->y += PI;
	if (ang->y > PI_2)
		ang->y -= PI;
}

void Misc::ClampAngles(D3DXVECTOR3* ang)
{
	if (!ang) return;

	ang->y = std::clamp(ang->y, -70.0f, 85.0f);

	if (ang->x > 360.0f)
		ang->x -= 360.0f;

	ang->z = 0.0f;
}

D3DXVECTOR2 Misc::AngleDiff(const D3DXVECTOR2& src, const D3DXVECTOR2& dst)
{
	D3DXVECTOR2 delta = (dst - src);
	ClampAngles(&delta);
	return delta;
}

float Misc::AngleDiff(float src, float dst)
{
	float delta;

	delta = fmodf(dst - src, PI * 2.0f);
	if (dst > src)
	{
		if (delta >= PI)
			delta -= PI * 2.0f;
	}
	else
	{
		if (delta <= -PI)
			delta += PI * 2.0f;
	}
	return delta;
}

void Misc::SmoothAngle(const D3DXVECTOR2& from, D3DXVECTOR2& to, float perc)
{
	D3DXVECTOR2 VecDelta;
	D3DXVec2Subtract(&VecDelta, &from, &to);
	ClampAngles(&VecDelta);
	VecDelta.x *= perc;
	VecDelta.y *= perc;
	to = from - VecDelta;
}

float Misc::GetFovFraction(const D3DXVECTOR3& src, const D3DXVECTOR3& dst, const D3DXVECTOR2& angles)
{
	D3DXVECTOR2 qCalcAng = Misc::CalcAngles2D(src, dst);
	D3DXVECTOR2 qAngleDelta; D3DXVec2Subtract(&qAngleDelta, &qCalcAng, &angles);
	Misc::ClampAngles(&qAngleDelta);

	return sinf(D3DXVec2Length(&qAngleDelta) / 2.0f) * 180.0f;
}

std::string Misc::GetRandomString(int length, bool caseSensitive, bool numbers, bool specialSymbols)
{
	//Oh boi, I've made that yeeears ago, didnt used once and yet I still c+p that to my every cheat...
	static const std::string chars = "qwertyuiopasdfghjklzxcvbnm";
	static const std::string caseChars = "QWERTYUIOPASDFGHJKLZXCVBNM";
	static const std::string symbols = "!@#$%^&*()_+[]{};':,./<>?";
	static const std::string charNumbers = "0123456789";
	std::string randomString = chars;

	if (caseSensitive) randomString += caseChars;
	if (specialSymbols) randomString += symbols;
	if (numbers) randomString += charNumbers;

	auto GetRandomChar = [&]() -> char
	{
		static std::random_device dev;
		static std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, randomString.size() - 1);
		return randomString.at(dist(rng));
	};

	std::string outString;
	outString.resize(length);

	for (int i = 0; i < outString.size(); i++)
		outString[i] = GetRandomChar();

	return outString;
}

void Misc::DebugMsg(const std::string& title, const std::string& msg, UINT type)
{
#ifdef _DEBUG
	MessageBoxA(NULL, msg.c_str(), title.c_str(), type);
#endif
}

std::string Misc::GetSystemTime()
{
	static std::tm* now = nullptr;
	std::time_t t = std::time(NULL);
	now = std::localtime(&t);

	if (now == nullptr) return NULL;

	const auto H = now->tm_hour;
	const auto M = now->tm_min;
	const auto S = now->tm_sec;

	char Buff[32] = { '\0' };

	//Beautiful, isn't it ?
	if (H > 9 && M > 9 && S > 9) sprintf(Buff, "%d:%d:%d", H, M, S);
	if (H >= 0 && H < 10) sprintf(Buff, "0%d:%d:%d", H, M, S);
	if (M >= 0 && M < 10) sprintf(Buff, "%d:0%d:%d", H, M, S);
	if (S >= 0 && S < 10) sprintf(Buff, "%d:%d:0%d", H, M, S);
	if (H >= 0 && H < 10 && M >= 0 && M < 10) sprintf(Buff, "0%d:0%d:%d", H, M, S);
	if (M >= 0 && M < 10 && S >= 0 && S < 10) sprintf(Buff, "%d:0%d:0%d", H, M, S);
	if (H >= 0 && H < 10 && S >= 0 && S < 10) sprintf(Buff, "0%d:%d:0%d", H, M, S);
	if (H >= 0 && H < 10 && M >= 0 && M < 10 && S >= 0 && S < 10) sprintf(Buff, "0%d:0%d:0%d", H, M, S);

	return Buff;
}

float Misc::GetAbsDeltaAtGivenPoints(const D3DXVECTOR2& src, const D3DXVECTOR2& dst)
{
	D3DXVECTOR2 outVec = { src.x - dst.x, src.y - dst.y };
	return fabsf(D3DXVec2Length(&outVec));
}

void Misc::RotatePoint(ImVec2* point, const ImVec2& origin, float angle)
{
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	point->x -= origin.x;
	point->y -= origin.y;

	// rotate point
	float xnew = point->x * c - point->y * s;
	float ynew = point->x * s + point->y * c;

	// translate point back:
	point->x = xnew + origin.x;
	point->y = ynew + origin.y;
}

void Misc::RotateTriangle(std::array<ImVec2, 3>* points, float angle)
{
	/*const auto points_center = (points->at(0) + points->at(1) + points->at(2)) / 3;
	for (auto& point : *points)
	{
		point -= points_center;

		const auto temp_x = point.x;
		const auto temp_y = point.y;

		const auto theta = D3DXToRadian(angle);
		const auto c = cosf(theta);
		const auto s = sinf(theta);

		point.x = temp_x * c - temp_y * s;
		point.y = temp_x * s + temp_y * c;

		point += points_center;
	}*/
}

float Misc::Distance3D(const D3DXVECTOR3& src, const D3DXVECTOR3& dst)
{
	D3DXVECTOR3 ret;
	D3DXVec3Subtract(&ret, &src, &dst);
	return D3DXVec3Length(&ret);
}

float Misc::Distance2D(const D3DXVECTOR2& src, const D3DXVECTOR2& dst)
{
	D3DXVECTOR2 ret;
	D3DXVec2Subtract(&ret, &src, &dst);
	return D3DXVec2Length(&ret);
}
