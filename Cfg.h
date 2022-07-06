#pragma once
#include "imgui.h"
#include "Engine.h"
#include <array>
#include <vector>

//There is the most cancerous code from whole cheat. You could put all of this 
//into the array(and iterate it in iniparser in 5 lines instead of 50..) and use like this: 
//auto& aimbot = cfg->aimbot;
//aimbot[ENABLE] = false;

//There are variables here that I have never used .

enum class CfgSwitch
{
	ESP_ENABLE = 0,
	ESP_WATERMARK,
	//...
	MAX_COUNT
};

enum class CfgSlider_Float
{
	AIM_RADIUS = 0,
	AIM_SMOOTH_SOLDIER,
	AIM_SMOOTH_VEHICLE,
	//...
	MAX_COUNT
};

enum class CfgSlider_Int
{
	ESP_PRED_CROSS_RADIUS = 0,
	//...
	MAX_COUNT
};

enum class CfgColor
{
	ESP_TEAM,
	ESP_LINES,
	ESP_LINES_VEHICLE_AIR,
	ESP_LINES_VEHICLE_GROUND,
	//...
	MAX_COUNT
};

//I was trying to fix that, but didn't get time to finish it
template <typename T, typename S, size_t Size>
class ConfigType
{
private:
	std::array<T, Size> value;

public:
	ConfigType() {}
	T& operator[] (const S& idx) const { return value[(size_t)idx]; }
	T& Get(const S& idx) const { return value[idx]; }
};


namespace Cfg
{
	extern ConfigType<bool, CfgSwitch, (size_t)CfgSwitch::MAX_COUNT> Bool;
	extern ConfigType<float, CfgSlider_Float, (size_t)CfgSlider_Float::MAX_COUNT> Float;
	extern ConfigType<int, CfgSlider_Int, (size_t)CfgSlider_Int::MAX_COUNT> Int;
	extern ConfigType<ImColor, CfgColor, (size_t)CfgColor::MAX_COUNT> Color;

	namespace ESP
	{
		extern bool aimbotFov;
		extern bool watermark;
		extern bool enable;
		extern bool use3DplayerBox;
		extern bool team;
		extern bool name; //TODO
		extern bool vehicles;

		extern bool prediction;
		extern bool predictionImpactData;
		extern bool predictionBombImpact;
		extern int predictionCrossRadius;
		extern bool predictionUseAngularVelocity;

		extern bool lines;
		extern bool linesVehicles;
		extern bool use3DvehicleBox;
		extern bool vehicleCenter;
		extern bool vehicleIndicator;

		namespace Radar
		{
			extern bool enable;
			extern bool onlyInVehicle;
			extern int radius;
			extern bool showVehicles;
			extern float zoom;
			extern int posX;
			extern int posY;
			extern int iconScale;

			extern ImColor soldierColor;
		}

		extern bool explosives;
		extern bool ownMissile;

		extern int _internalCurveIterationCount;
		extern float _internalCurvePredTimeMultiplier;

		extern std::vector<unsigned int> _internalPlayerIDs;
		extern std::vector<unsigned int> _internalSelectedPlayerIDs;

		extern ImColor fovColor;
		extern ImColor teamColor;
		extern ImColor linesColor;
		extern ImColor linesVehicleAirColor;
		extern ImColor linesVehicleGroundColor;
		extern ImColor enemyColor;
		extern ImColor vehicleAirColor;
		extern ImColor vehicleGroundColor;
		extern ImColor missileColor;
		extern ImColor explosivesColor;

		extern ImColor predictionDataColor;
		extern ImColor predictionCrossColor;
		extern ImColor predictionCrossOverrideColor;
	}

	namespace AimBot
	{
		extern bool enable;
		extern bool autoTrigger;
		extern bool teslaAutoPilot;
		extern float _internalSens;
		extern float radius;
		extern float smoothSoldier;
		extern float smoothVehicle;

		extern float smoothTV;

		extern bool autoBombs;

		extern bool forceTVAimbot;
		extern bool useTVPrediction;

		extern float TEST;
	}

	namespace DBG
	{
		extern bool vehicleCross;
		extern bool spectators;
		extern bool overlayBorder;
		extern bool console;
		extern bool watermark;
		extern bool debugOutput;
		extern bool debugEntities;
		extern bool jetSpeedCtrl;

		extern bool dbgMode;
		extern float dbgPos[3];

		extern bool _internalSpoof;
		extern bool _internalRestore;
		extern char _internalName[16];

		extern std::array<Vector, 16> _internalPredictionCurve;
		extern Quaternion _internalPredictedOrientation;
		extern bool _internalUseCurve;

		extern unsigned int _internalFFSS;

		extern char spoofedName[16];
	}
}