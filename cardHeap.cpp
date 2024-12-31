#include <string>
#include <vector>

#include "Util.h"

std::vector<std::string> cardList = {
	"r0","r1","r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13",
	"y0","y1","y2","y3","y4","y5","y6","y7","y8","y9","y10","y11","y12","y13",
	"g0","g1","g2","g3","g4","g5","g6","g7","g8","g9","g10","g11","g12","g13",
	"b0","b1","b2","b3","b4","b5","b6","b7","b8","b9","b10","b11","b12","b13",
		 "r1","r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r14",
		 "y1","y2","y3","y4","y5","y6","y7","y8","y9","y10","y11","y12","y14",
		 "g1","g2","g3","g4","g5","g6","g7","g8","g9","g10","g11","g12","g14",
		 "b1","b2","b3","b4","b5","b6","b7","b8","b9","b10","b11","b12","b14",

};

std::string getCard() {
	int random = getRandom() % cardList.size();

	int index = 0;
	std::string result = cardList.at(random);
	//«Â≈∆
	for (auto it = cardList.begin(); it != cardList.end(); ++it) {
		if (index == random) {
			cardList.erase(it);
			break;
		}
		index++;
	}

	return result;
}

void recycleCard(std::string card) {
	cardList.push_back(card);
}

void removeCard(std::vector<std::string> cardList) {
	for (std::string card: cardList) {
		for (auto it = cardList.begin(); it != cardList.end(); ++it) {
			if (*it == card) {
				cardList.erase(it);
				break;
			}
		}
	}
}

void resetHeap() {
	cardList = {
   "r0","r1","r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13",
   "y0","y1","y2","y3","y4","y5","y6","y7","y8","y9","y10","y11","y12","y13",
   "g0","g1","g2","g3","g4","g5","g6","g7","g8","g9","g10","g11","g12","g13",
   "b0","b1","b2","b3","b4","b5","b6","b7","b8","b9","b10","b11","b12","b13",
		"r1","r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r14",
		"y1","y2","y3","y4","y5","y6","y7","y8","y9","y10","y11","y12","y14",
		"g1","g2","g3","g4","g5","g6","g7","g8","g9","g10","g11","g12","g14",
		"b1","b2","b3","b4","b5","b6","b7","b8","b9","b10","b11","b12","b14",

	};
}