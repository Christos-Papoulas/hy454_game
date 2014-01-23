#ifndef _SCORE_H_
#define _SCORE_H_

#define POINTS_GOOMBA 100
#define POINTS_GREEN_KOOPA_TROOPA 100
#define POINTS_RED_KOOPA_TROOPA 100
#define PONITS_PIRANHA_PLANT 200
#define POINTS_COIN 200
#define POINTS_STAR 1000
#define POINTS_RED_MUSHROOM 1000
#define POINTS_GREEN_MUSHROOM 1000

class Score{
	public:
		static Dim score;
		static void SetScore(Dim num){score = num;}
		static Dim GetScore(){return score;}
		static void ScoreAdd(Dim num){score += num;}
};

#endif