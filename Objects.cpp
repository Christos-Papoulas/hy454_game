#include "header_files\Objects.h"

void CalculateTilesPosition(){
	for (int i=0; i<TILES_COLUMNS*TILES_ROWS; ++i) {
		divIndex[i] = i / TILES_ROWS;
		modIndex[i] = i % TILES_ROWS;
	}
	//row = divIndex[index];
	//column = modIndex[index];
}

unsigned int CurrTime() {
	SYSTEMTIME st;

	GetSystemTime(&st);
	return st.wMilliseconds + st.wSecond*1000 + st.wMinute*60*1000 + st.wHour*3600*1000 + st.wDay*24*3600*1000;
}