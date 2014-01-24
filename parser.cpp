#include "header_files\conf\parser.h"

using namespace std;

ConfigItems* iniItem[1024];
int i = 0;

Configurator::Configurator(char *f) {
		parseFile(f);
		Dim moregoumbas = getOptionToInt(MORE_GOUBLAS);
		PutGoumbasOnMap(moregoumbas);
		
}

void Configurator::PutGoumbasOnMap(Dim n) {
		Dim x;
		Dim y;
		int tries = 0;
		srand((unsigned)time(0)); 

		for(int i = 0; i < n; ++i){
				tries = 0;
				while(1) {
						x = rand() % MAX_HEIGHT;
						y = 15 + (rand() % (MAX_WIDTH - 15));
						if( Enemies::GetFromMap(x, y) == 0 && Items::GetFromBricks(x, y) == 0 
								&& Terrain::GetTileLayer()->GetExactTile(x, y) ==282){
								Enemies::SetOnMap(161, x, y);
								Enemies::IncreaseEnemies();
								break;
						}
						
						if(++tries > 1000) 
								break;
				}
				
		}
}

bool parseFile(char *fileName) {
		std::string optionValue;
		ifstream infile;
		infile.open(fileName);

		if (infile.is_open() != true)
				return false;

		std::string key;

		while (!infile.eof()) {
				getline(infile, optionValue);

				if (optionValue.substr(0, 1) == "#")
						continue;

				key = parseOptionName(optionValue);

				if (key.length() > 0) {
						iniItem[i] = new ConfigItems;
						iniItem[i]->key = key;
						iniItem[i]->value = parseOptionValue(optionValue);
						i++;
				}
		}

		//i--;
		infile.close();
		return true;
}

void cleanupIniReader() {
        for (int x = 0; x <= i; x++)
						delete iniItem[x];
        
        i = 0;
}

string getOptionToString(std::string key) {
        if (i == 0)
            return "";

        for (int x = 0; x < i; x++)
						if (key == iniItem[x]->key)
								return iniItem[x]->value;
  
				return "";
}

const char *getOptionToChar(std::string key) {
		if (i == 0)
				return "";
    
		for (int x = 0; x <= i; x++)
				if (key == iniItem[x]->key)
						return iniItem[x]->value.c_str();
        
		return "";
}

int getOptionToInt(std::string key) {
        if (i == 0)
						return 0;

        for (int x = 0; x <= i; x++)
						if (key == iniItem[x]->key)
								return atoi(iniItem[x]->value.c_str());

        return 0;
}

string parseOptionName(std::string value){
        size_t found;

        found = value.find('=');

        if (found > 100)
						return "";

        std::string key = value.substr(0, (found-1));
        key = trim(key);

        return key;
}

string parseOptionValue(std::string value) {
        size_t found;

        found = value.find('=');

        if (found > 100)
						return "";


        std::string keyValue = value.substr((found+1));
        keyValue = trim(keyValue);

        return keyValue;
}

string trim(std::string s) {
        return ltrim(rtrim(s));
}

string ltrim(std::string s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

string rtrim(std::string s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}