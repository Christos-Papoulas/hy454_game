#include "ParseMarioInfo.h"

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
		using namespace std;
		ifstream read(MARIO_SPRITES_INFO);
		unsigned short x = 0, y = 0, z = 0, k = 0;
		read >> marioInfo->totalFrames;
		marioInfo->mariodetails = (MarioInfo_t*) malloc(sizeof(MarioInfo_t)*marioInfo->totalFrames);
		for(unsigned short i = 0; i < marioInfo->totalFrames; ++i) {
				read >> marioInfo->mariodetails[i].iid;
				read >> marioInfo->mariodetails[i].cid;
				read >> marioInfo->mariodetails[i].numOfmoves;
				marioInfo->mariodetails[i].moves = (Moves_t*) malloc(sizeof(Moves_t)*marioInfo->mariodetails[i].numOfmoves);
				for(unsigned short j = 0; j < marioInfo->mariodetails[i].numOfmoves; ++j) {
						read >> x;
						marioInfo->mariodetails[i].moves[j].y = x;
						read >> y;
						marioInfo->mariodetails[i].moves[j].x = y;
						read >> z;
					  marioInfo->mariodetails[i].moves[j].lengthX = z;
						read >> k;
						marioInfo->mariodetails[i].moves[j].lengthY = k;
				}
		}
		read.close();
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

Dim ParseMarioInfo::GetIndexOf(const char* f) {
		for(Dim i = 0; i < marioInfo->totalFrames; i++)
				if(!strncmp(marioInfo->mariodetails[i].cid, f, 20))
						return i;
		assert(0);
		return 0;
}