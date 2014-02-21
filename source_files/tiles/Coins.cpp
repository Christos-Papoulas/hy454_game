#include "Coins.h"

void Coins::CheckCoins(){
	if(coins < 100){ 
		coins += 1;
	}else{
		Coins::AddLife();
		coins = 0;
	}
}