// AIPlayer.h

#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <vector>
#include <string>

#include "Util.h"
#include "cardHeap.h"

class AIPlayer {
private:
    std::vector<std::string> cardList;
    std::string usedCard;
    std::string thinker(std::string lastCard);

public:
    std::string proc(std::string card);
    void addCard(std::string card);
    std::string Plus2affordAble();
    int getCardNum();
    void reset();
    std::vector<std::string> getCardList();
    std::vector<std::string>& getCardListReferance();
};

#endif // AIPLAYER_H
