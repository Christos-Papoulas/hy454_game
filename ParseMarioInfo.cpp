#include "header_files\parsers\ParseMarioInfo.h"

ParseMarioInfo* ParseMarioInfo::marioInfo = NULL;

ParseMarioInfo::ParseMarioInfo() {
		;
}

ParseMarioInfo::~ParseMarioInfo() {
		
}

void ParseMarioInfo::Create() {
		if(!marioInfo) marioInfo = new ParseMarioInfo;
}

void ParseMarioInfo::ParseFile(const char* f) {
		FILE* fp = fopen(MARIO_SPRITES_INFO, "r");
		unsigned short x = 0, y = 0, z = 0, k = 0;
		assert(fp);
		fscanf(fp, "%u", &marioInfo->totalFrames);
		marioInfo->mariodetails = (MarioInfo_t*) malloc(sizeof(MarioInfo_t)*marioInfo->totalFrames);
		unsigned short skata;
		for(unsigned short i = 0; i < marioInfo->totalFrames; ++i) {
				fscanf(fp, "%d", &marioInfo->mariodetails[i].iid);
				fscanf(fp, "%s", &marioInfo->mariodetails[i].cid);
				fscanf(fp, "%d", &marioInfo->mariodetails[i].numOfmoves);
				marioInfo->mariodetails[i].moves = (Moves_t*) malloc(sizeof(Moves_t)*marioInfo->mariodetails[i].numOfmoves);
				for(unsigned short j = 0; j < marioInfo->mariodetails[i].numOfmoves; ++j) {
						fscanf(fp, "%d", &x);
						marioInfo->mariodetails[i].moves[j].y = x;
						fscanf(fp, "%d", &y);
						marioInfo->mariodetails[i].moves[j].x = y;
						fscanf(fp, "%d", &z);
						marioInfo->mariodetails[i].moves[j].lengthX = z;
						fscanf(fp, "%d", &k);
						marioInfo->mariodetails[i].moves[j].lengthY = k;
				}
		}
		fclose(fp);
}

void ParseMarioInfo::PrintDataToLogFile() {
		
}

MarioInfo_t ParseMarioInfo::GetNetMarioInfo(unsigned short i) {
		return marioInfo->mariodetails[i];
}

char* ParseMarioInfo::GetNetMarioInfoId(unsigned short i) {
		return marioInfo->mariodetails[i].cid;
}

unsigned short ParseMarioInfo::GetTotalFrames() {
		return marioInfo->totalFrames;
}

unsigned short ParseMarioInfo::GetAnimationIdOf(unsigned short i) {
		return marioInfo->mariodetails[i].iid;
}