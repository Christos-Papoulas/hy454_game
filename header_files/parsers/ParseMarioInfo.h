#ifndef _PARSE_MARIO_INFO_H_
#define _PARSE_MARIO_INFO_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string>


#define MARIO_SPRITES_INFO "./data/mario.info"

typedef struct moves {
		unsigned short x;
		unsigned short y;
		unsigned short lengthX;
		unsigned short lengthY;
} Moves_t;

typedef struct marioInfo {
		unsigned short iid;
		char cid[20];
		unsigned short numOfmoves;
		Moves_t* moves;
} MarioInfo_t;

class ParseMarioInfo {
		private:
				unsigned short totalFrames;
				static ParseMarioInfo* marioInfo; //singleton
				MarioInfo_t* mariodetails;
				ParseMarioInfo();
				~ParseMarioInfo();

		public:
				static void Create();
				static void ParseFile(const char* f);
				static void PrintDataToLogFile();
				static MarioInfo_t GetNetMarioInfo(unsigned short i);
				static char* GetNetMarioInfoId(unsigned short i);
				static unsigned short GetTotalFrames();
};

#endif