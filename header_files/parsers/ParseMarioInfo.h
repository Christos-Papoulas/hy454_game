#ifndef _PARSE_MARIO_INFO_H_
#define _PARSE_MARIO_INFO_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string>

#include "../Objects.h"

#define MARIO_SPRITES_INFO "./data/mario.info"

typedef struct moves {
		Dim x;
		Dim y;
		Dim lengthX;
		Dim lengthY;
} Moves_t;

typedef struct marioInfo {
		Dim iid;
		char cid[20];
		Dim numOfmoves;
		Moves_t* moves;
} MarioInfo_t;

class ParseMarioInfo {
		private:
				Dim totalFrames;
				static ParseMarioInfo* marioInfo; //singleton
				MarioInfo_t* mariodetails;
				ParseMarioInfo();
				~ParseMarioInfo();

		public:
				static void Create();
				static void ParseFile(const char* f);
				static void PrintDataToLogFile();
				static MarioInfo_t GetNetMarioInfo(Dim i);
				static char* GetNetMarioInfoId(Dim i);
				static unsigned short GetTotalFrames();

				static Dim GetAnimationIdOf(Dim i);
};

#endif