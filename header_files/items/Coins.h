#ifndef _COINS_H_
#define _COINS_H_

#include "Objects.h"

class Coins{
	public:
		static Dim coins;
		static void SetCoins(Dim num){coins = num;}
		static Dim GetCoins(){return coins;}
		static void CheckCoins();
		static Dim lifes;
		static void SetLife(Dim num) {lifes = num;}
		static Dim GetLife(){return lifes;}
		static void AddLife(){lifes += 1;}
		static void RemoveLife(){lifes -= 1;}
};

#endif