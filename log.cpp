#include "header_files\logs\logs.h"

void log_write(char* file, int line, char *text) {
		using namespace std;
		ofstream myfile;
		myfile.open ("mariobros.log");
		myfile << file << ":" << line << ": " << text << "\n";
		myfile.close();

		return ;
}