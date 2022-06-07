#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <vector>
#include <map>

class Settings
{
public:

	static Settings* getInstance()
	{

		if (instance == 0)
		{
			instance = new Settings;
		}

		return instance;
	}

	static std::string getProperties(const char* propertyStr)
	{

		return Settings::getInstance()->Properties.at(propertyStr);

	}

private:

	const std::map<const char*, const char*> Properties = {
		{"PATH", "C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/"},
		{"PATH_SHADER", "shader/"},
		{"PATH_TEXTURE", "textures/"},
		{"PATH_AUDIO", "audio/"},
		{"PATH_LEVELS", "levels/"}
	};
	
	static Settings* instance;

	Settings() {};

};

#endif SETTINGS_H