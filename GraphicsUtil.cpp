#include <string>

#include "Log.h"
#include "GraphicsUtil.h"
#include <SFML/Graphics.hpp>

sf::Sprite cardBackSprite;
sf::Texture cardBackTexture;
sf::Texture cardFrontTexture;

sf::Texture getTextureOfCard(std::string card) {
	
	int cardNum = std::stoi(card.substr(1));

	//wild
	if (cardNum == 13) {
		if (!cardFrontTexture.loadFromFile("./resources/deck.png", sf::IntRect(240 * 13, 0, 240, 360))) {
			LogError("�޷����ػ�ɫ��");
		}
	}
	else if (cardNum == 14) {
		if (!cardFrontTexture.loadFromFile("./resources/deck.png", sf::IntRect(240 * 13, 360 * 4, 240, 360))) {
			LogError("�޷�����+4��");
		}
	}
	else {
		char ch = card[0];
		int y = 0;
		switch (ch) {
		case 'r':
			break;
		case 'y':
			y = 360;
			break;
		case 'g':
			y = 360 * 2;
			break;
		case 'b':
			y = 360 * 3;
			break;
		}
		if (!cardFrontTexture.loadFromFile("./resources/deck.png", sf::IntRect(240 * cardNum, y, 240, 360))) {
			LogError("�޷�������ͨ��");
		}
	}
	return cardFrontTexture;
}

void initUtil() {
	LogInfo("ͼ�ι��߳�ʼ��");
	if (!cardBackTexture.loadFromFile("./resources/uno.png")) {
		LogError("�޷�����uno�Ʊ���");
	}
	cardBackSprite.setTexture(cardBackTexture);
	cardBackSprite.setScale(0.3, 0.3);
}