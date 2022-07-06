#pragma once
#include "Engine.h"

class InputActions
{
public:
	static InputActions* Get() { static InputActions inst; return &inst; }
	void HandleInput(const Vector& pos, ClientPlayer* pLocal, const WeaponData_s& pVehData, const Vector& targetPos, VeniceClientMissileEntity* pMissile = nullptr);

private:
	bool isAboutToOverheat = false;
	bool isAutoPiloting = false;
	bool isJDAMBomb = false;
	Vector bombImpactPos = { 0.0f, 0.0f, 0.0f };

	float ReRange(float x, float inmin, float inmax, float outmin, float outmax);

	//TODO:
	void CountermeasuresControll();

	void JetSpeedControll(ClientVehicleEntity* pVeh, float* input);
	void JetBombControll(ClientVehicleEntity* pVeh, const Vector& targetPos, const WeaponData_s& pVehData, float* input);
	void JetWeaponsControll(ClientVehicleEntity* pVeh, const Vector& targetPos, float delta, float* input);
	void TVMissileControll(ClientVehicleEntity* pVeh, const Vector& targetPos, const Vector2D deltaVec, float delta, float* input);
	void VehicleTurretControll(const Vector2D& deltaVec, float delta, VeniceClientMissileEntity* pMissile);
	void SoldierWeaponControll(float delta, const Vector targetPos);
	void OverheatControll();
	void TriggerControll(const Vector& targetPos, float delta, float* input);
};

