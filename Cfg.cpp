#include "stdafx.h"
#include "Cfg.h"

namespace Cfg
{
	ConfigType<bool, CfgSwitch, (size_t)CfgSwitch::MAX_COUNT>				Bool;
	ConfigType<float, CfgSlider_Float, (size_t)CfgSlider_Float::MAX_COUNT>	Float;
	ConfigType<int, CfgSlider_Int, (size_t)CfgSlider_Int::MAX_COUNT>		Int;
	ConfigType<ImColor, CfgColor, (size_t)CfgColor::MAX_COUNT>				Color;

	namespace ESP
	{
		 bool aimbotFov = false;
		 bool watermark = true;

		 bool enable = false;
		 bool use3DplayerBox = false;
		 bool team = false;
		 bool name = false;

		 bool vehicles = true;
		 bool use3DvehicleBox = true;
		 bool vehicleCenter = true;

		 bool prediction = true;
		 bool predictionBombImpact = true;
		 bool predictionImpactData = true;
		 int predictionCrossRadius = 15;
		 bool predictionUseAngularVelocity = false;

		 int _internalCurveIterationCount = 16;
		 float _internalCurvePredTimeMultiplier = 69.0f;

		 bool lines = false;
		 bool linesVehicles = false;
		 bool vehicleIndicator = true;

		 namespace Radar
		 {
			 bool enable = true;
			 bool onlyInVehicle = false;
			 int radius = 100;
			 bool showVehicles = true;
			 float zoom = 1.f;
			 int posX = 300;
			 int posY = 300;
			 int iconScale = 32;

			 ImColor soldierColor = ImColor::Red();
		 }
		
		 bool explosives = true;
		 bool ownMissile = true;

		 std::vector<unsigned int> _internalPlayerIDs;
		 std::vector<unsigned int> _internalSelectedPlayerIDs;

		 ImColor fovColor = ImColor::White(130);
		 ImColor teamColor = ImColor(120, 255, 76);
		 ImColor linesColor = ImColor(252, 119, 3);
		 ImColor linesVehicleAirColor = ImColor(0, 142, 255, 90);
		 ImColor linesVehicleGroundColor = ImColor::Orange(90);
		 ImColor enemyColor = ImColor(255, 71, 102);
		 ImColor vehicleAirColor = ImColor(0, 142, 255, 90);
		 ImColor vehicleGroundColor = ImColor(255, 156, 56, 90);
		 ImColor missileColor = ImColor::Red();

		 ImColor explosivesColor = ImColor::Pink();

		 ImColor predictionCrossColor = ImColor(23, 206, 176);
		 ImColor predictionDataColor = ImColor(23, 206, 176);
		 ImColor predictionCrossOverrideColor = ImColor::Pink();
	}

	namespace AimBot
	{
		 bool enable = false;
		 bool autoTrigger = false;
		 bool teslaAutoPilot = false;
		 float _internalSens = 12.f;
		 float radius = (float)ESP::predictionCrossRadius;
		 float smoothSoldier = 6.f;
		 float smoothVehicle = 2.5f;

		 float smoothTV = 1.f;

		 bool autoBombs = true;

		 bool forceTVAimbot = false;
		 bool useTVPrediction = false;

		 float TEST = 0.7f;
	}

	namespace DBG
	{
		bool vehicleCross = true;
		bool spectators = false;
		bool overlayBorder = false;
		bool console = true;
		bool watermark = true;
		bool debugOutput = false;
		bool debugEntities = false;
		bool jetSpeedCtrl = true;

		bool dbgMode = false;
		float dbgPos[3] = { 0.0f, 0.0f, 0.0f };

		std::array<Vector, 16> _internalPredictionCurve;
		Quaternion _internalPredictedOrientation;
		bool _internalUseCurve = false;

		unsigned int _internalFFSS = 0;

		bool _internalSpoof = false;
		bool _internalRestore = false;
		char _internalName[16];
		char spoofedName[16];
	}
}


void lol()
{

}