#include "header_files\Objects.h"

unsigned int CurrTime() {
	SYSTEMTIME st;

	GetSystemTime(&st);
	return st.wMilliseconds + st.wSecond*1000 + st.wMinute*60*1000 + st.wHour*3600*1000 + st.wDay*24*3600*1000;
}