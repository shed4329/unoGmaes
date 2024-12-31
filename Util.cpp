#include <string>

#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include "Util.h"
#include "Log.h"
/*
*这张牌能出吗？
*/
int isThisOkay(std::string lastCard,std::string card) {
	if (lastCard[0] == card[0]) {
		//同色纸牌
		return 1;
	}
	int lastCardNum = std::stoi(lastCard.substr(1));
	int cardNum = std::stoi(card.substr(1));
	if (cardNum == 13 || cardNum == 14) {
		//万能牌
		return 1;
	}

	if (cardNum == lastCardNum) {
		//换色
		return 1;
	}

	return -1;
}
/*
* 是否是万能牌
*/
int isWildCard(std::string card) {
	int cardNum = std::stoi(card.substr(1));
	if (cardNum == 13 || cardNum == 14) {
		return 1;
	}
	else {
		return -1;
	}
}

int getRandom() {
	srand(time(0));
	int result = rand();
	return result;
}

int isPlus2(std::string card) {
	int cardNum = std::stoi(card.substr(1));
	if (cardNum == 12) {
		return 1;
	}
	else {
		return -1;
	}
}

int isColorChange(std::string card) {
	int cardNum = std::stoi(card.substr(1));
	if (cardNum == 13||cardNum == 14) {
		return 1;
	}
	else {
		return -1;
	}
}






