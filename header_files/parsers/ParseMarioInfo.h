#ifndef _PARSE_MARIO_INFO_H_
#define _PARSE_MARIO_INFO_H_

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <assert.h>
#include <string>

#define MARIO_SPRITES_INFO "./data/mario.info"

typedef struct moves {
		unsigned int x;
		unsigned int y;
		unsigned int lengthX;
		unsigned int lengthY;
} Moves_t;

typedef struct marioInfo {
		unsigned int iid;
		char cid[20];
		unsigned int numOfmoves;
		std::vector<Moves_t> moves;
} MarioInfo_t;

class ParseMarioInfo {
		private:
				unsigned int totalFrames;
				static ParseMarioInfo* marioInfo; //singleton
				std::vector<MarioInfo_t> mariodetails;
				ParseMarioInfo();
				~ParseMarioInfo();

		public:
				static void Create();
				static void ParseFile(const char* f);
				static void PrintDataToLogFile();
};

#endif