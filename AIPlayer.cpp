#include "AIPlayer.h"

#include "Util.h"
#include "cardHeap.h"
#include "Log.h"

#include <iostream>

std::string AIPlayer::thinker(std::string lastCard) {
    // ��Щ���ܳ�
    std::vector<std::string> avaliableCardList;

    for (std::string card : cardList) {
        if (isThisOkay(lastCard, card) == 1) {
            avaliableCardList.push_back(card);
        }
    }

    if (avaliableCardList.size() == 0) {
        return "pass";
    }
    else {
        int random = getRandom();
        random = random % avaliableCardList.size();
        usedCard = avaliableCardList.at(random);

        if (isWildCard(avaliableCardList.at(random) )==1) {
            //������ָ����ɫ
            LogInfo("������");
            std::string result = avaliableCardList.at(random);
            LogInfo(result.c_str());
            char ch = cardList.at(0)[0];
            std::string info = "change color to ";
            info.push_back(ch);
            LogInfo(info);
            result[0] = ch;
            return result;
        }
        else {
            return avaliableCardList.at(random);
        }
        
    }
}

std::string AIPlayer::proc(std::string card) {
    std::string result = thinker(card);
    if (result == "pass") {
        // ����
        std::string newcard = getCard();
        cardList.push_back(newcard);
    }
    else {
        // ����


        for (std::string card0 : cardList) {
            std::cout<<card0<<" ";
        }
        std::cout << std::endl;
        // ���������������������
        for (auto it = cardList.begin(); it != cardList.end(); it++) {
          
            if (*it == usedCard) {
               
                cardList.erase(it);
                break;
            }
        }
        for (std::string card0 : cardList) {
            std::cout << card0 << " ";
        }
        
        std::cout << std::endl;
    }
    return result;
}
void AIPlayer::addCard(std::string card) {
    cardList.push_back(card);
}
std::string AIPlayer::Plus2affordAble() {
    
    for (int i = 0; i < cardList.size(); i++) {
        if (isPlus2(cardList.at(i)) == 1) {
            std::string result = cardList.at(i);
            //���ٿ�Ƭ
            for (auto it = cardList.begin(); it != cardList.end(); ++it) {
                if (*it == result) {
                    cardList.erase(it);
                    break;
                }
            }

            return result;
        }
    }
    return "NULL";
}
int AIPlayer::getCardNum() {
    return cardList.size();
}

void AIPlayer::reset() {
    cardList.clear();
}
std::vector<std::string> AIPlayer::getCardList() {
    return cardList;
}

std::vector<std::string>& AIPlayer::getCardListReferance() {
    return cardList;

}