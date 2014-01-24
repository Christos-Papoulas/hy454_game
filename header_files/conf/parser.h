#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <fstream>
#include <functional>
#include <cctype> 
#include <cstdlib> 
#include <ctime> 
#include <algorithm>

#include "../enemies/Goumba.h"
#include "../enemies/Enemies.h"
#include "../items/Items.h"
#include "../tiles/TileLayer.h"
#include "../terrain/terrain.h"
#include "../Objects.h"

#define MORE_GOUBLAS "number_of_additional_goumbas"

class Configurator {
		void PutGoumbasOnMap(Dim n);
public:
		Configurator(char *f);
};

struct ConfigItems {
        std::string key;
        std::string value;
};

extern ConfigItems* iniItem[1024];

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