#pragma once
#include "imgui.h"
#include "Renderer.h"
#include "Engine.h"
#include <array>
#include <chrono>

class ClientGameContext;
class ClientSoldierEntity;
class ClientControllableEntity;
class MissileEntityData;
class ClientVehicleEntity;
class PredictionData_s;

class Timer
{
	float m_Delay = -1.0f;
	double m_PrevTime = -1.0f;

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	double elapsedTime = -1.0f;
	bool hasStartedCounting = false;

public:
	Timer() {};
	Timer(float delay) : m_Delay(delay), m_PrevTime(GetTime()) {};

	void ResetCounter();
	void StartCounting();
	void StopCounting();
	double GetElapsedTime();
	void SetDelay(float delay) { m_Delay = delay; };
	bool IsReadyThisTick();
	double GetTime();
};

class Visuals
{
public:
	Visuals();

	class BoundingBox3D
	{
	public:
		Vector min, max;
		std::array<Vector, 8> points;
		BoundingBox3D() { min = points[0]; max = points[4]; }; 
		Vector GetCenter()
		{
			return Vector(
				min.x + ((max.x - min.x) * 0.5f),
				min.y + ((max.y - min.y) * 0.5f),
				min.z + ((max.z - min.z) * 0.5f)
			);
		}
	};

	static bool WorldToScreen(const Vector& origin, Vector& screen);
	static bool WorldToScreen(const Vector& origin, Vector2D& screen);
	static bool WorldToScreen(const Vector& origin, ImVec2& screen);
	static bool WorldToScreen(Vector& origin);
	static BoundingBox GetEntityAABB(ClientControllableEntity* pEntity, BoundingBox3D* pTransformed3D = nullptr);

private:

	bool IsValidTime(ClientPlayer* pLocal);
	void RenderPlayerNames(ClientPlayer* pPlayer);
	void RenderPlayerCorneredRect(const BoundingBox& bbEntity, const ImColor& color);
	void RenderPlayerHealth(const BoundingBox& bbEntity);
	void RenderExplosives(ClientGameContext* pCtx);

	//I was using that function only in Polygon as you dont have there any 'living' objects
	//so its isnt optimized or organized in any way. Just skip that.
	void RenderDebugEntities(ClientGameContext* pCtx, VeniceClientMissileEntity* pMissile, ClientPlayer* pLocal, WeaponData_s* pVehWeaponData = nullptr);
	void RenderVehicleInfo(ClientPlayer* pLocal, WeaponData_s* pData);

	//Thats modified radar from my CSGO post so maybe you would find that useful in other games too
	//https://www.unknowncheats.me/forum/counterstrike-global-offensive/416262-2d-radar-overlay.html
	void RenderRadar(ClientPlayer* pLocal, ClientPlayer* pPlayer, int i);

	void RenderAimPoint(const PredictionData_s& data, ClientPlayer* pTargetData = nullptr);
	void RenderBombImpact(const Vector& targetPos, WeaponData_s* pDataIn = nullptr);
	void RenderOffScreenTarget(ClientPlayer* pTarget, const Vector& viewPos);
	void RenderWatermark();

	void SpoofNameClientSided(ClientPlayer* pLocal);

	VeniceClientMissileEntity* GetMissileEntity(ClientGameContext* pCtx, ClientPlayer* pLocal);

	

public:
	void RenderVisuals();
};

