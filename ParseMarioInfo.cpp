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
		Dim x = 0, y = 0, z = 0, k = 0;
		assert(fp);
		fscanf(fp, "%u", &marioInfo->totalFrames);
		marioInfo->mariodetails = (MarioInfo_t*) malloc(sizeof(MarioInfo_t)*marioInfo->totalFrames);

		for(int i = 0; i < marioInfo->totalFrames; ++i) {
				fscanf(fp, "%u", &marioInfo->mariodetails[i].iid);
				fscanf(fp, "%s", &marioInfo->mariodetails[i].cid);
				fscanf(fp, "%u", &marioInfo->mariodetails[i].numOfmoves);
				marioInfo->mariodetails[i].moves = (Moves_t*) malloc(sizeof(Moves_t)*marioInfo->mariodetails[i].numOfmoves);
				for(int j = 0; j < marioInfo->mariodetails[i].numOfmoves; ++j) {
						fscanf(fp, "%u", &x);
						marioInfo->mariodetails[i].moves[j].x = x;
						fscanf(fp, "%u", &y);
						marioInfo->mariodetails[i].moves[j].y = y;
						fscanf(fp, "%u", &z);
						marioInfo->mariodetails[i].moves[j].lengthX = z;
						fscanf(fp, "%u", &k);
						marioInfo->mariodetails[i].moves[j].lengthY = k;
				}
		}
		fclose(fp);
}

void ParseMarioInfo::PrintDataToLogFile() {
		
}

MarioInfo_t ParseMarioInfo::GetNetMarioInfo(Dim i) {
		return marioInfo->mariodetails[i];
}

char* ParseMarioInfo::GetNetMarioInfoId(Dim i) {
		return marioInfo->mariodetails[i].cid;
}

Dim ParseMarioInfo::GetTotalFrames() {
		return marioInfo->totalFrames;
}

Dim ParseMarioInfo::GetAnimationIdOf(Dim i) {
		return marioInfo->mariodetails[i].iid;
}