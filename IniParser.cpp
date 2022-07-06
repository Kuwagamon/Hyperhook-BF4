#include "IniParser.h"
#include "xorstr.hpp"
#include "Cfg.h"
#include "Globals.h"

//Here is the most awful code I've ever wrote. 
//More about that you will find in cfg.h

void IniParser::SetSection(const std::string& section)
{
	this->currSection = section;
}

bool IniParser::GetBool(const std::string& key)
{
	if (!this->configData.size() || this->currSection.empty()) return false;
	return (!this->configData.get(this->currSection).get(key).compare("true") ? true : false);
}

float IniParser::GetFloat(const std::string& key)
{
	if (!this->configData.size() || this->currSection.empty()) return -1.f;
	return std::stof(this->configData.get(this->currSection).get(key));
}

int IniParser::GetInt(const std::string& key)
{
	if (!this->configData.size() || this->currSection.empty()) return -1;
	return std::stoi(this->configData.get(this->currSection).get(key));
}

std::string IniParser::GetString(bool _bool)
{
	return (_bool ? "true" : "false");
}

std::string IniParser::GetString(int _int)
{
	return std::to_string(_int);
}

std::string IniParser::GetString(float _float)
{
	return std::to_string(_float);
}

void IniParser::Read()
{
	if (this->configData.size())
	{
		SetSection(xorstr_("AimBot"));
		Cfg::AimBot::enable						= GetBool(xorstr_("Enable"));
		Cfg::ESP::aimbotFov						= GetBool(xorstr_("Show_FOV"));
		Cfg::AimBot::autoTrigger				= GetBool(xorstr_("Auto_shot"));
		Cfg::AimBot::teslaAutoPilot				= GetBool(xorstr_("Auto_pilot"));
		Cfg::AimBot::autoBombs					= GetBool(xorstr_("Auto_bombs"));
		Cfg::DBG::jetSpeedCtrl					= GetBool(xorstr_("Auto_jet_speed"));
		Cfg::AimBot::radius						= GetFloat(xorstr_("FoV_radius"));
		Cfg::AimBot::smoothSoldier				= GetFloat(xorstr_("Smooth_soldier"));
		Cfg::AimBot::smoothVehicle				= GetFloat(xorstr_("smooth_vehicle"));
		
		SetSection(xorstr_("ESP"));
		Cfg::ESP::enable						= GetBool(xorstr_("Enable"));
		Cfg::ESP::use3DplayerBox				= GetBool(xorstr_("Player_3D_box"));
		Cfg::ESP::team							= GetBool(xorstr_("Team"));
		Cfg::ESP::lines							= GetBool(xorstr_("Lines"));
		Cfg::ESP::vehicles						= GetBool(xorstr_("Vehicles"));
		Cfg::DBG::vehicleCross					= GetBool(xorstr_("Vehicle_cross"));
		Cfg::ESP::use3DvehicleBox				= GetBool(xorstr_("Vehicles_3D_box"));
		Cfg::ESP::vehicleCenter					= GetBool(xorstr_("Vehicles_center"));
		Cfg::ESP::vehicleIndicator				= GetBool(xorstr_("Vehicles_Indicator"));
		Cfg::ESP::explosives					= GetBool(xorstr_("Explosives"));
		Cfg::ESP::ownMissile					= GetBool(xorstr_("Guided_missile"));
		Cfg::ESP::prediction					= GetBool(xorstr_("Prediction"));
		Cfg::ESP::predictionImpactData			= GetBool(xorstr_("Impact_data"));
		Cfg::ESP::predictionUseAngularVelocity	= GetBool(xorstr_("Use_angular_velocity"));
		Cfg::ESP::predictionBombImpact			= GetBool(xorstr_("Bomb_impact"));
		Cfg::DBG::spectators					= GetBool(xorstr_("Spectators"));

		SetSection(xorstr_("Radar"));
		Cfg::ESP::Radar::enable = GetBool(xorstr_("Enable"));
		Cfg::ESP::Radar::onlyInVehicle = GetBool(xorstr_("Only_in_vehicles"));
		Cfg::ESP::Radar::showVehicles = GetBool(xorstr_("Show_vehicles"));
		Cfg::ESP::Radar::posX = GetInt(xorstr_("PosX"));
		Cfg::ESP::Radar::posY = GetInt(xorstr_("PosY"));
		Cfg::ESP::Radar::zoom = GetFloat(xorstr_("Zoom"));
		Cfg::ESP::Radar::iconScale = GetInt(xorstr_("Icon_scale"));

		SetSection(xorstr_("Misc"));
		Cfg::DBG::watermark						= GetBool(xorstr_("Watermark"));
		Cfg::DBG::debugOutput					= GetBool(xorstr_("Debug_output"));
		Cfg::DBG::debugEntities					= GetBool(xorstr_("Debug_Entities"));
	}
}

void IniParser::Write()
{
	if (!this->configData.size() || !this->config.get()) return;

	auto& c = this->configData;
	c[xorstr_("AimBot")][xorstr_("Enable")] = GetString(Cfg::AimBot::enable);
	c[xorstr_("AimBot")][xorstr_("Show_FOV")] = GetString(Cfg::ESP::aimbotFov);
	c[xorstr_("AimBot")][xorstr_("Auto_shot")] = GetString(Cfg::AimBot::autoTrigger);
	c[xorstr_("AimBot")][xorstr_("Auto_pilot")] = GetString(Cfg::AimBot::teslaAutoPilot);
	c[xorstr_("AimBot")][xorstr_("Auto_bombs")] = GetString(Cfg::AimBot::autoBombs);;
	c[xorstr_("AimBot")][xorstr_("Auto_jet_speed")] = GetString(Cfg::DBG::jetSpeedCtrl);
	c[xorstr_("AimBot")][xorstr_("FoV_radius")] = GetString(Cfg::AimBot::radius);
	c[xorstr_("AimBot")][xorstr_("Smooth_soldier")] = GetString(Cfg::AimBot::smoothSoldier);
	c[xorstr_("AimBot")][xorstr_("smooth_vehicle")] = GetString(Cfg::AimBot::smoothVehicle);

	c[xorstr_("ESP")][xorstr_("Enable")] = GetString(Cfg::ESP::enable);
	c[xorstr_("ESP")][xorstr_("Player_3D_box")] = GetString(Cfg::ESP::use3DplayerBox);
	c[xorstr_("ESP")][xorstr_("Team")] = GetString(Cfg::ESP::team);
	c[xorstr_("ESP")][xorstr_("Lines")] = GetString(Cfg::ESP::lines);
	c[xorstr_("ESP")][xorstr_("Vehicles")] = GetString(Cfg::ESP::vehicles);
	c[xorstr_("ESP")][xorstr_("Vehicle_cross")] = GetString(Cfg::DBG::vehicleCross);
	c[xorstr_("ESP")][xorstr_("Vehicles_3D_box")] = GetString(Cfg::ESP::use3DvehicleBox);
	c[xorstr_("ESP")][xorstr_("Vehicles_center")] = GetString(Cfg::ESP::vehicleCenter);
	c[xorstr_("ESP")][xorstr_("Vehicles_Indicator")] = GetString(Cfg::ESP::vehicleIndicator);
	c[xorstr_("ESP")][xorstr_("Explosives")] = GetString(Cfg::ESP::explosives);
	c[xorstr_("ESP")][xorstr_("Guided_missile")] = GetString(Cfg::ESP::ownMissile);
	c[xorstr_("ESP")][xorstr_("Prediction")] = GetString(Cfg::ESP::prediction);
	c[xorstr_("ESP")][xorstr_("Impact_data")] = GetString(Cfg::ESP::predictionImpactData);
	c[xorstr_("ESP")][xorstr_("Use_angular_velocity")] = GetString(Cfg::ESP::predictionUseAngularVelocity);
	c[xorstr_("ESP")][xorstr_("Bomb_impact")] = GetString(Cfg::ESP::predictionBombImpact);
	c[xorstr_("ESP")][xorstr_("Spectators")] = GetString(Cfg::DBG::spectators);

	c[xorstr_("Radar")][xorstr_("Enable")] = GetString(Cfg::ESP::Radar::enable);
	c[xorstr_("Radar")][xorstr_("Only_in_vehicles")] = GetString(Cfg::ESP::Radar::onlyInVehicle);
	c[xorstr_("Radar")][xorstr_("Radius")] = GetString(Cfg::ESP::Radar::radius);
	c[xorstr_("Radar")][xorstr_("Show_vehicles")] = GetString(Cfg::ESP::Radar::showVehicles);
	c[xorstr_("Radar")][xorstr_("Zoom")] = GetString(Cfg::ESP::Radar::zoom);
	c[xorstr_("Radar")][xorstr_("PosX")] = GetString(Cfg::ESP::Radar::posX);
	c[xorstr_("Radar")][xorstr_("PosY")] = GetString(Cfg::ESP::Radar::posY);
	c[xorstr_("Radar")][xorstr_("Icon_scale")] = GetString(Cfg::ESP::Radar::iconScale);

	c[xorstr_("Misc")][xorstr_("Watermark")] = GetString(Cfg::DBG::watermark);
	c[xorstr_("Misc")][xorstr_("Debug_output")] = GetString(Cfg::DBG::debugOutput);
	c[xorstr_("Misc")][xorstr_("Debug_Entities")] = GetString(Cfg::DBG::debugEntities);
	c[xorstr_("Misc")][xorstr_("Overlay_border")] = GetString(Cfg::DBG::overlayBorder);

	this->config->write(c, true);
}

bool IniParser::Init(const std::string& configName)
{
	this->config = std::make_unique<mINI::INIFile>(configName);

	if (!this->config.get()) return false;

	if (!config->read(this->configData))
	{
		auto& c = this->configData;
		c[xorstr_("AimBot")][xorstr_("Enable")]				= xorstr_("true");
		c[xorstr_("AimBot")][xorstr_("Show_FOV")]			= xorstr_("false");
		c[xorstr_("AimBot")][xorstr_("Auto_shot")]			= xorstr_("false");
		c[xorstr_("AimBot")][xorstr_("Auto_pilot")]			= xorstr_("false");
		c[xorstr_("AimBot")][xorstr_("Auto_bombs")]			= xorstr_("true");
		c[xorstr_("AimBot")][xorstr_("Auto_jet_speed")]		= xorstr_("true");
		c[xorstr_("AimBot")][xorstr_("FoV_radius")]			= xorstr_("15.0");
		c[xorstr_("AimBot")][xorstr_("Smooth_soldier")]		= xorstr_("3.5");
		c[xorstr_("AimBot")][xorstr_("smooth_vehicle")]		= xorstr_("2.5");

		c[xorstr_("ESP")][xorstr_("Enable")]				= xorstr_("true");
		c[xorstr_("ESP")][xorstr_("Player_3D_box")]			= xorstr_("false");
		c[xorstr_("ESP")][xorstr_("Team")]					= xorstr_("false");
		c[xorstr_("ESP")][xorstr_("Lines")]					= xorstr_("false");
		c[xorstr_("ESP")][xorstr_("Vehicles")]				= xorstr_("true");
		c[xorstr_("ESP")][xorstr_("Vehicle_cross")]			= xorstr_("true");
		c[xorstr_("ESP")][xorstr_("Vehicles_3D_box")]		= xorstr_("true");
		c[xorstr_("ESP")][xorstr_("Vehicles_center")]		= xorstr_("true");
		c[xorstr_("ESP")][xorstr_("Vehicles_Indicator")]	= xorstr_("true");
		c[xorstr_("ESP")][xorstr_("Explosives")]			= xorstr_("true");
		c[xorstr_("ESP")][xorstr_("Guided_missile")]		= xorstr_("true");
		c[xorstr_("ESP")][xorstr_("Prediction")]			= xorstr_("true");
		c[xorstr_("ESP")][xorstr_("Impact_data")]			= xorstr_("true");
		c[xorstr_("ESP")][xorstr_("Use_angular_velocity")]	= xorstr_("false");
		c[xorstr_("ESP")][xorstr_("Bomb_impact")]			= xorstr_("true");
		c[xorstr_("ESP")][xorstr_("Spectators")]			= xorstr_("true");

		c[xorstr_("Radar")][xorstr_("Enable")]				= xorstr_("true");
		c[xorstr_("Radar")][xorstr_("Only_in_vehicles")]	= xorstr_("true");
		c[xorstr_("Radar")][xorstr_("Radius")]				= xorstr_("100");
		c[xorstr_("Radar")][xorstr_("Show_vehicles")]		= xorstr_("true");
		c[xorstr_("Radar")][xorstr_("Zoom")]				= xorstr_("1.0");
		c[xorstr_("Radar")][xorstr_("PosX")]				= xorstr_("300");
		c[xorstr_("Radar")][xorstr_("PosY")]				= xorstr_("300");
		c[xorstr_("Radar")][xorstr_("Icon_scale")]			= xorstr_("16");

		c[xorstr_("Misc")][xorstr_("Watermark")]			= xorstr_("true");
		c[xorstr_("Misc")][xorstr_("Debug_output")]			= xorstr_("true");
		c[xorstr_("Misc")][xorstr_("Debug_Entities")]		= xorstr_("false");
		c[xorstr_("Misc")][xorstr_("Overlay_border")]		= xorstr_("false");
		c[xorstr_("Misc")][xorstr_("Overlay_refresh")]		= xorstr_("15.0");

		return config->generate(this->configData, true);
	}

	return false;
}
