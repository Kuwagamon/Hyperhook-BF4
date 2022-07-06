#pragma once
#include "ini.h"

class IniParser
{
private:
	std::unique_ptr<mINI::INIFile> config;
	mINI::INIStructure configData;
	std::string currSection;

	void SetSection(const std::string& section);

	bool GetBool(const std::string& key);
	float GetFloat(const std::string& key);
	int GetInt(const std::string& key);

	std::string GetString(bool _bool);
	std::string GetString(int _int);
	std::string GetString(float _float);

public:
	//Reading from file to Cfg (namespace)
	void Read();

	//Writing current Cfg (namespace) to file ind disc
	void Write();

	//True if new file has been generated
	bool Init(const std::string& configName);
};

