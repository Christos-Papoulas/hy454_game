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
		assert(fp);
		fscanf(fp, "%u", &marioInfo->totalFrames);
		int lala = marioInfo->mariodetails.size();

		for(unsigned int i = 0; i < marioInfo->totalFrames; i++) {
				MarioInfo_t tmp;
				Moves_t moves_tmp;
				fscanf(fp, "%u", &tmp.iid);
				fscanf(fp, "%s", tmp.cid);
				fscanf(fp, "%u", &tmp.numOfmoves);
				
				for(unsigned int j = 0; j < tmp.numOfmoves; j++) {
						unsigned int x, y, z, k;
						fscanf(fp, "%u", &x);
						fscanf(fp, "%u", &y);
						fscanf(fp, "%u", &z);
						fscanf(fp, "%u", &k);
						//fscanf(fp, "%u %u %u %u", &x, &y, &z, &k);
						moves_tmp.x = x; moves_tmp.y = y; moves_tmp.lengthX = z; moves_tmp.lengthY = k;
						tmp.moves.push_back(moves_tmp);
				}
				marioInfo->mariodetails.push_back(tmp);
				
		}
		fclose(fp);
}

void ParseMarioInfo::PrintDataToLogFile() {
		using namespace std;
		fprintf(stdout, "%u\n",  marioInfo->totalFrames);
		for(vector<MarioInfo_t>::iterator it = marioInfo->mariodetails.begin(); it != marioInfo->mariodetails.end(); it++) {
				fprintf(stdout, "%u\n%s\n", it->iid, it->cid);
				for(std::vector<Moves_t>::iterator et = it->moves.begin(); et != it->moves.end(); et++)
						fprintf(stdout, "%u %u %u %u\n", et->x, et->y, et->lengthX, et->lengthY);  
		}
}
