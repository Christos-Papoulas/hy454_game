#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <fstream>
#include <functional>
#include <cctype> 
#include <cstdlib> 
#include <ctime> 
#include <algorithm>
#include <string.h>

#include "../enemies/Goumba.h"
#include "../enemies/Enemies.h"
#include "..\enemies\GreenKoopaTroopa.h"
#include "../items/Items.h"
#include "../tiles/TileLayer.h"
#include "../terrain/terrain.h"
#include "../Objects.h"
#include "../mario/NumbersHolder.h"

#define MORE_GOUBLAS "number_of_additional_goumbas"
#define MORE_KOOPAS "number_of_additional_koopas"
#define TIME_PLAY "time_play"
#define SPEED_KOOPA "speed_of_green_koopa"
#define SPEED_GOUMBA "speed_of_goumba"

class Configurator {
		void PutGoumbasOnMap(Dim enemy, Dim n);
		void PutKoopasOnMap(Dim enemy, Dim n);
		
public:
		Configurator(char *f);
};

struct ConfigItems {
        std::string key;
        std::string value;
};

extern ConfigItems* iniItem[128];

bool parseFile(char *fileName);
void cleanupIniReader();
std::string getOptionToString(std::string key);
int getOptionToInt(std::string key);

const char *getOptionToChar(std::string key);

std::string parseOptionName(std::string value);
std::string parseOptionValue(std::string value);
std::string trim(std::string s);
std::string rtrim(std::string s);
std::string ltrim(std::string s);

#endif 