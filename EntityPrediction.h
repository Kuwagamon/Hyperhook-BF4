#pragma once
#include "Engine.h"

//I've spent most of the time here. Hope you will find that useful :)

class ClientPlayer;
class VeniceClientMissileEntity;
struct WeaponData_s;

class Prediction
{
public:
	struct AngularPredictionData_s
	{
		Quaternion orientation;
		Vector angularVelocity;
		bool valid = false;
	};

	static void PredictLinearMove(
		const Vector& linearVelocity, const double predictionTime, 
		const Vector& curPosition, Vector* out);

	static void PredictRotation(
		const Vector& angularVelocity, const Quaternion& orientation,
		const double predictionTime, Quaternion* out);

	static void PredictFinalRotation(
		const Vector& linearVel, const Vector& angularVel, 
		const double predTime, const Quaternion& orientation, 
		const Vector& curPosition, Quaternion* predOrientationOut,
		Vector* predLinearVelOut);

	//Main function for computing future position of given object in 3D space
	static bool ComputePredictedPointInSpace(
		const Vector& src, const Vector& dst, const Vector& dstVel,
		const float bulletVel, const float bulletGravity,
		PredictionData_s* out = nullptr, const float overrideTravelTime = 0.0f, 
		const float zeroying = 0.0f, const AngularPredictionData_s* angularDataIn = nullptr);
	
	//Compute final missile velocity from given data
	static float ComputeMissileFinalVelocity(
		float initSpd, float maxSpd, float accel,
		float engIgnTime, float dist, float* travelTime = nullptr);

	//Collect all neccesary data for ComputePredictedPointInSpace() and return PredictionData_s
	static bool GetPredictedAimPoint(
		ClientPlayer* pLocal, ClientPlayer* pTarget, const Vector& aimPoint,
		PredictionData_s* dataOut = nullptr,
		VeniceClientMissileEntity* pDataIn = nullptr,
		WeaponData_s* pWeaponData = nullptr);
};

