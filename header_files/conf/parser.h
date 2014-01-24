#ifndef INIREADER_H
#define INIREADER_H

#include <string>
#include <fstream>
#include <functional>
#include <cctype> 
#include <algorithm>


void parseIniFile(char *fileName);
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