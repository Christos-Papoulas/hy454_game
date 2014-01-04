#include "header_files\Objects.h"

timestamp_t currTime;

Dim divIndex[TILES_COLUMNS*TILES_ROWS + 1];
Dim modIndex[TILES_COLUMNS*TILES_ROWS + 1];
Dim divIndex_start_screen[TILES_COLUMNS_START_SCREEN*TILES_ROWS_START_SCREEN + 1];
Dim modIndex_start_screen[TILES_COLUMNS_START_SCREEN*TILES_ROWS_START_SCREEN + 1];

void CalculateTilesPosition(){
	for (int i=0; i<TILES_COLUMNS*TILES_ROWS; ++i) {
		divIndex[i] = (i / TILES_COLUMNS);
		modIndex[i] = (i % TILES_COLUMNS) - 1;
	}
	//row = divIndex[index];
	//column = modIndex[index];
}

void CalculateTilesPositionStartScreen(){
	for (int i=0; i<TILES_COLUMNS_START_SCREEN*TILES_ROWS_START_SCREEN; ++i) {
		divIndex_start_screen[i] = (i / TILES_COLUMNS_START_SCREEN);
		modIndex_start_screen[i] = (i % TILES_COLUMNS_START_SCREEN) - 1;
	}
	//row = divIndex[index];
	//column = modIndex[index];
}

unsigned int CurrTime() {
	SYSTEMTIME st;

	GetSystemTime(&st);
	return st.wMilliseconds + st.wSecond*1000 + st.wMinute*60*1000 + st.wHour*3600*1000 + st.wDay*24*3600*1000;
}

timestamp_t GetCurrTime() {
		return currTime;
}
