#include "gameWindow.h"
#include "Log.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Windows.h"
#include "Util.h"
#include "cardHeap.h"
#include "GraphicsUtil.h"
#include "AIPlayer.h"
#include <SFML/Audio.hpp>
#include "FileUtil.h"

sf::RenderWindow window(sf::VideoMode(920, 540), "ZZB Uno Games");

sf::Sprite bgSprite;
sf::Sprite backSprite;
sf::Sprite unoCallSprite;
sf::Sprite colorSprtie;
sf::Sprite saveSprite;
sf::Sprite turnSprite;
sf::Sprite animSprite;
sf::Sprite animDrawSprite;
sf::Sprite DialogSprite;
sf::Sprite RedSprite;
sf::Sprite YellowSprite;
sf::Sprite BlueSprite;
sf::Sprite GreenSprite;
sf::Sprite UnoBubbleSprite;

sf::Texture bgTexture;
sf::Texture backTexture;
sf::Texture unoCallTexture;
sf::Texture colorTexture;
sf::Texture saveTexture;
sf::Texture turnTexture;
sf::Texture animTexture;
sf::Texture animDrawTexture;
sf::Texture DialogTexture;
sf::Texture RedTexture;
sf::Texture YellowTexture;
sf::Texture BlueTexture;
sf::Texture GreenTexture;
sf::Texture UnoBubbleTexture;

std::vector<sf::Sprite> spriteRenderList;
std::vector<sf::Sprite> textSpriteList;
std::vector<sf::Sprite> cardRenderList;
std::vector<sf::Sprite> playerCardRenderList;
std::vector<sf::Texture> playerCardTextureList;

std::vector<std::string> playerCardList;

std::vector<sf::Sprite> Player1CardRenderList;
std::vector<sf::Sprite> Player2CardRenderList;
std::vector<sf::Sprite> Player3CardRenderList;

std::string lastCard;
sf::Sprite lastCardSprtie;
sf::Texture lastCardTexture;

sf::Sprite text;
sf::Sprite text2;
sf::Sprite text3;
sf::Sprite text4;

sf::Texture textT;
sf::Texture text2T;
sf::Texture text3T;
sf::Texture text4T;

sf::Font font;

int isInGame = 0;

sf::Sprite playerCardSprite;
sf::Texture playerTexture;


sf::Texture texture1;

AIPlayer player1;
AIPlayer player2;
AIPlayer player3;

sf::Clock clickTimer;

sf::SoundBuffer reverseBuffer;
sf::SoundBuffer stopBuffer;
sf::SoundBuffer drawBuffer;

sf::Sound reverseSound;
sf::Sound stopSound;
sf::Sound drawSound;

sf::Music music;

int isBanned = 0;
int isReversed = 0;
int isPlus4 = 0;
int plus2CardNum = 0;
int userPlus2Affordable = 0;
int isAnimated = 0;
int isAnimatedDrew = 0;
int isDialog = 0;
int proced = 0;
int callUnoTimes = 0;
void show() {
	LogInfo("开始展示窗口");
	
	initUtil();
	initSprite();
	
	spriteRenderList.push_back(bgSprite);
	
	initText();

	addmenuText();
	initMusic();
	music.play();

	while (window.isOpen())
	{
		if (isDialog == 0) {
			if (isBanned&& callUnoTimes==0) {
				playerBannedAction();
			}
			else if (isPlus4 && callUnoTimes==0) {
				playerPlus4Act();
			}
			else if (userPlus2Affordable == 1) {
				playerPlus2Act();
			}
		}
		
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (isInGame == 0) {
					
					if (text.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						aboutHandler();
					}
					else if (text2.getGlobalBounds().contains(mousePos.x, mousePos.y)){	
						startLocalGameHandler();

					}
					else if (text3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						introHandler();
					}
					else if (text4.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						readRecordHanlder();
					}
				}
				else {
					if (isDialog == 0) {
						if (backSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							backToMenu();
						}
						else if (unoCallSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)&& callUnoTimes) {
							unoCallHandler();
						}
						else if (saveSprite.getGlobalBounds().contains(mousePos.x, mousePos.y) ) {
							saveHanlder();
						}
						
						else {
							std::string clickedCard = playerClick(mousePos.x, mousePos.y);

							if (clickedCard != "NULL") {
								proced = 1;
								std::cout << "玩家出牌： " << clickedCard << std::endl;
								if (isThisOkay(lastCard, clickedCard) == 1) {

									playerProcHandler(clickedCard);
								}
							}
							else {
								if (cardRenderList.at(0).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
									playerNewCardHandler();
								}
							}
						}
					}
					else {
						playerColorSelectHandler(mousePos);
					}
				}
				
			}
				
		}
		render();
		
		
	}
}

void render() {
	window.clear();
	for (int i = 0; i < spriteRenderList.size(); i++) {
		window.draw(spriteRenderList.at(i));
	}
	
	for (int i = 0; i < textSpriteList.size(); i++) {
		window.draw(textSpriteList.at(i));
	}
	
	for (int i = 0; i < cardRenderList.size(); i++) {
		window.draw(cardRenderList.at(i));
	}

	for (int i = 0; i < Player1CardRenderList.size(); i++) {
		window.draw(Player1CardRenderList.at(i));
	}

	for (int i = 0; i < Player2CardRenderList.size(); i++) {
		window.draw(Player2CardRenderList.at(i));
	}

	for (int i = 0; i < Player3CardRenderList.size(); i++) {
		window.draw(Player3CardRenderList.at(i));
	}
	for (int i = 0; i < playerCardRenderList.size(); i++) {
		window.draw(playerCardRenderList.at(i));
	}
	if (isDialog) {
		window.draw(DialogSprite);
		window.draw(RedSprite);
		window.draw(BlueSprite);
		window.draw(GreenSprite);
		window.draw(YellowSprite);
	}
	if (isAnimated) {
		window.draw(animSprite);
	}
	if (isAnimatedDrew) {
		window.draw(animDrawSprite);
	}
	window.display();
}

void addmenuText() {
	textSpriteList.push_back(text);
	textSpriteList.push_back(text2);
	textSpriteList.push_back(text3);
	textSpriteList.push_back(text4);
}
void initMusic() {
	if (!music.openFromFile("./resources/bgm.ogg")) {
		LogError("无法加载bgm");
	}
	music.setLoop(true);

	if (!drawBuffer.loadFromFile("./resources/draw.ogg")) {
		LogError("无法加载摸牌声音");
	}
	drawSound.setBuffer(drawBuffer);
	if (!stopBuffer.loadFromFile("./resources/ban.ogg")) {
		LogError("无法加载ban声音");
	}
	stopSound.setBuffer(stopBuffer);
	if (!reverseBuffer.loadFromFile("./resources/reverse.ogg")) {
		LogError("无法加载reverse声音");
	}
	reverseSound.setBuffer(reverseBuffer);
}

void initSprite() {
	if (!bgTexture.loadFromFile("./resources/background.jpg")) {
		LogError("主页背景无法加载");
	}
	bgSprite.setTexture(bgTexture);
	


	if (!backTexture.loadFromFile("./resources/back.png")) {
		LogError("无法加载返回图标");
	}
	backSprite.setTexture(backTexture);
	backSprite.setPosition(10, 10);


	if (!unoCallTexture.loadFromFile("./resources/one.png")) {
		LogError("无法加载叫uno图标");
	}
	unoCallSprite.setTexture(unoCallTexture);
	unoCallSprite.setPosition(500, 250);

	if (!colorTexture.loadFromFile("./resources/blue.png")) {
		LogError("无法加载颜色图标");
	}
	colorSprtie.setTexture(colorTexture);
	colorSprtie.setPosition(500, 200);

	if (!saveTexture.loadFromFile("./resources/save.png")) {
		LogError("无法加载存档图标");
	}
	saveSprite.setTexture(saveTexture);
	saveSprite.setPosition(550, 200);

	if (!turnTexture.loadFromFile("./resources/down.png")) {
		LogError("无法加载turn图标");
	}
	turnSprite.setTexture(turnTexture);
	turnSprite.setPosition(180+36*3, 380);
	
	if (!animTexture.loadFromFile("./resources/animation/rotation/2.png")) {
		LogError("无法加载reverse动画");
	}
	isAnimated = 0;
	animSprite.setTexture(animTexture);
	animSprite.setPosition(360, 240);

	if (!RedTexture.loadFromFile("./resources/red.png")) {
		LogError("无法加载小红球");
	}
	RedSprite.setTexture(RedTexture);
	RedSprite.setPosition(280, 330);

	if (!BlueTexture.loadFromFile("./resources/blue.png")) {
		LogError("无法加载小蓝球");
	}
	BlueSprite.setTexture(BlueTexture);
	BlueSprite.setPosition(360, 330);

	if (!GreenTexture.loadFromFile("./resources/green.png")) {
		LogError("无法加载小蓝球");
	}
	GreenSprite.setTexture(GreenTexture);
	GreenSprite.setPosition(440, 330);

	if (!YellowTexture.loadFromFile("./resources/yellow.png")) {
		LogError("无法加载小蓝球");
	}
	YellowSprite.setTexture(YellowTexture);
	YellowSprite.setPosition(520, 330);

	if (!UnoBubbleTexture.loadFromFile("./resources/unoCall.png")) {
		LogError("无法加载uno气泡");
	}
	UnoBubbleSprite.setTexture(UnoBubbleTexture);
	UnoBubbleSprite.setScale(0.3, 0.3);
}

void initText() {
	if (!textT.loadFromFile("./resources/about.png")) {
		LogError("无法加载关于图片");
	}
	text.setTexture(textT);
	text.setScale(0.5, 0.5);
	text.setPosition(350, 300);

	if (!text2T.loadFromFile("./resources/startGame.png")) {
		LogError("无法加载开始图片");
	}
	text2.setTexture(text2T);
	text2.setScale(0.5, 0.5);
	text2.setPosition(350, 200);

	if (!text3T.loadFromFile("./resources/intro.png")) {
		LogError("无法加载介绍图片");
	}
	text3.setTexture(text3T);
	text3.setScale(0.5, 0.5);
	text3.setPosition(350, 100);

	if (!text4T.loadFromFile("./resources/readRecord.png")) {
		LogError("无法加载读档图片");
	}
	text4.setTexture(text4T);
	text4.setScale(0.5, 0.5);
	text4.setPosition(350, 400);


}
void initScene() {
	spriteRenderList.push_back(unoCallSprite);

	spriteRenderList.push_back(colorSprtie);

	spriteRenderList.push_back(saveSprite);

	spriteRenderList.push_back(turnSprite);
}
void initPlayerScene() {
	//player抽牌
	for (int i = 0; i < 7; i++) {
		playerCardList.push_back(getCard());
	}
	//player1渲染
	for (int i = 0; i < 7; i++) {
		cardBackSprite.setPosition(10, 100 + 24 * i);
		Player1CardRenderList.push_back(cardBackSprite);
		player1.addCard(getCard());
	}
	//player获取材质
	for (int i = 0; i < 7; i++) {
		playerCardTextureList.push_back(getTextureOfCard(playerCardList.at(i)));

	}
	//player渲染
	for (int i = 0; i < 7; i++) {
		playerCardSprite.setTexture(playerCardTextureList.at(i));
		playerCardSprite.setScale(0.3, 0.3);
		playerCardSprite.setPosition(180 + 36 * i, 420);
		playerCardRenderList.push_back(playerCardSprite);
	}
	//player2渲染
	for (int i = 0; i < 7; i++) {
		cardBackSprite.setPosition(180 + 36 * i, 10);
		Player2CardRenderList.push_back(cardBackSprite);
		player2.addCard(getCard());
	}
	//player3渲染
	for (int i = 0; i < 7; i++) {
		cardBackSprite.setPosition(830, 100 + 24 * i);
		Player3CardRenderList.push_back(cardBackSprite);
		player3.addCard(getCard());
	}

	cardBackSprite.setPosition(328, 200);
	cardRenderList.push_back(cardBackSprite);

	//抽第一张卡
	lastCard = getCard();
	lastCardTexture = getTextureOfCard(lastCard);
	lastCardSprtie.setTexture(lastCardTexture);
	lastCardSprtie.setScale(0.3, 0.3);
	lastCardSprtie.setPosition(400, 200);
	cardRenderList.push_back(lastCardSprtie);
	setColor(lastCard);
}

std::string playerClick(float x,float y) {
	for (int i = playerCardRenderList.size()-1; i >= 0  ; i--) {
		if (playerCardRenderList.at(i).getGlobalBounds().contains(x,y) ){
			return playerCardList.at(i);
		}
	}
	return "NULL";
}

void setColor(std::string card) {
	char ch = card[0];
	switch (ch) {
		case 'r':
			if (!colorTexture.loadFromFile("./resources/red.png")) {
				LogError("无法加载红色");
			}
			break;
		case 'g':
			if (!colorTexture.loadFromFile("./resources/green.png")) {
				LogError("无法加载绿色");
			}
			break;
		case 'b':
			if (!colorTexture.loadFromFile("./resources/blue.png")) {
				LogError("无法加载蓝色");
			}
			break;
		case 'y':
			if (!colorTexture.loadFromFile("./resources/yellow.png")) {
				LogError("无法加载黄色");
			}
			break;
	}
}
void reset() {
	spriteRenderList.pop_back();
	spriteRenderList.pop_back();
	spriteRenderList.pop_back();
	spriteRenderList.pop_back();
	spriteRenderList.pop_back();

	cardRenderList.clear();
	Player1CardRenderList.clear();
	Player2CardRenderList.clear();
	Player3CardRenderList.clear();
	player1.reset();
	player2.reset();
	player3.reset();
	
	playerCardList.clear();
	playerCardRenderList.clear();
	playerCardTextureList.clear();
	resetHeap();
	isInGame = 0;
	isBanned = 0;
	isReversed = 0;
	isPlus4 = 0;
	plus2CardNum = 0;
	userPlus2Affordable = 0;
	isAnimated = 0;
	isAnimatedDrew = 0;
	proced = 0;
	isDialog = 0;
	callUnoTimes = 0;
}
void AIPlayerTurn() {
	if (isReversed == 0) {
		AIPlayer1Play();
	}
	else {
		AIPlayer3Play();
	}
	
}

void AIPlayer1Play() {
	LogInfo("player1出牌");
	if (playerCardList.size() == 0){
		return;
	}
	if (!turnTexture.loadFromFile("./resources/left.png")) {
		LogError("无法加载左turn图标");
	}
	spriteRenderList.at(5).setPosition(108, 100+24*player1.getCardNum()/2);
	for (int j = 0; j < 4; j++) {
		render();
		sf::sleep(sf::milliseconds(50));
	}
	
	int procAble = 0;
	if (isBanned) {
		LogInfo("player1被ban了");
		isBanned = 0;
	}
	else if (isPlus4) {
		LogInfo("喜吃加四");
		isPlus4 = 0;
		for (int j = 0; j < 4; j++) {
			player1.addCard(getCard());
			cardBackSprite.setPosition(10, 100 + 24 * Player1CardRenderList.size());
			Player1CardRenderList.push_back(cardBackSprite);
		}
	}
	else if (plus2CardNum) {
		LogInfo("+2来了");
		std::string result = player1.Plus2affordAble();
		if (result != "NULL") {
			LogInfo("逃过一劫");
			plus2CardNum += 1;
			lastCard = result;
			lastCardTexture = getTextureOfCard(lastCard);
			Player1CardRenderList.pop_back();
			setColor(lastCard);
			recycleCard(lastCard);
		}
		else {
			std::cout << "吃+2 " << plus2CardNum << "张" << std::endl;
			Plus2Anim();
			int cardNum = plus2CardNum * 2;
			for (int i = 0; i < cardNum; i++) {
				player1.addCard(getCard());
				cardBackSprite.setPosition(10, 100 + 24 * Player1CardRenderList.size());
				Player1CardRenderList.push_back(cardBackSprite);
			}
			plus2CardNum = 0;
		}
	}
	else {
		std::string result = player1.proc(lastCard);
		std::cout << "p1出牌: " << result << std::endl;

		if (result == "pass") {
			//player1.addCard(getCard());
			cardBackSprite.setPosition(10, 100 + 24 * Player1CardRenderList.size());
			Player1CardRenderList.push_back(cardBackSprite);
			//player1.addCard(getCard());
		}
		else {
			procAble = 1;
			lastCard = result;
			lastCardTexture = getTextureOfCard(lastCard);
			Player1CardRenderList.pop_back();
			setColor(lastCard);
			recycleCard(lastCard);
			cardSkill(lastCard);
		}
	}

	
	for (int i = 0; i < 12; i++) {
		render();
		sf::sleep(sf::milliseconds(50));
	}
	
	if (player1.getCardNum() == 0) {
		failedAlert();
		return;
	}
	else if (player1.getCardNum() == 1&&procAble) {
		UnoBubbleSprite.setPosition(135, 150);
		spriteRenderList.push_back(UnoBubbleSprite);
		for (int i = 0; i < 16; i++) {
			render();
			sf::sleep(sf::milliseconds(50));
		}
		
		spriteRenderList.pop_back();
	}
	if (isReversed == 0) {
		AIPlayer2Play();
		
	}
	else {
		if (plus2CardNum) {
			playerPlus2Affodable();
		}
		if (!turnTexture.loadFromFile("./resources/down.png")) {
			LogError("无法加载down turn图标");
		}
		spriteRenderList.at(5).setPosition(180 + 36 * playerCardList.size() / 2, 380);
		for (int j = 0; j < 4; j++) {
			render();
			sf::sleep(sf::milliseconds(50));
		}
	}
}

void AIPlayer2Play() {
	LogInfo("player2出牌");
	if (!turnTexture.loadFromFile("./resources/up.png")) {
		LogError("无法加载上turn图标");
	}
	spriteRenderList.at(5).setPosition(180 + 36 * player2.getCardNum() / 2,144);
	for (int j = 0; j < 4; j++) {
		render();
		sf::sleep(sf::milliseconds(50));
	}
	int procAble = 0;
	if (isBanned) {
		LogInfo("player2被ban了");
		isBanned = 0;
	}
	else if (isPlus4) {
		LogInfo("喜吃加四");
		isPlus4 = 0;
		for (int i = 0; i < 4; i++) {
			player2.addCard(getCard());
			cardBackSprite.setPosition(180 + 36 * Player2CardRenderList.size(),10);
			Player2CardRenderList.push_back(cardBackSprite);
		}
	}
	else if (plus2CardNum) {
		LogInfo("+2来了");
		std::string result = player2.Plus2affordAble();
		if (result != "NULL") {
			LogInfo("逃过一劫");
			plus2CardNum += 1;
			lastCard = result;
			lastCardTexture = getTextureOfCard(lastCard);
			Player2CardRenderList.pop_back();
			setColor(lastCard);
			recycleCard(lastCard);
		}
		else {
			std::cout << "吃+2 " << plus2CardNum << "张" << std::endl;
			int cardNum = plus2CardNum * 2;
			Plus2Anim();
			for (int i = 0; i < cardNum; i++) {
				player2.addCard(getCard());
				cardBackSprite.setPosition(180 + 36 * Player2CardRenderList.size(),10);
				Player2CardRenderList.push_back(cardBackSprite);
			}
			plus2CardNum = 0;
		}
	}
	else {
		std::string result = player2.proc(lastCard);
		std::cout << "p2出牌: " << result << std::endl;

		if (result == "pass") {
			//player2.addCard(getCard());
			cardBackSprite.setPosition(180 + 36 * Player2CardRenderList.size(), 10);
			Player2CardRenderList.push_back(cardBackSprite);
		}
		else {
			procAble = 1;
			lastCard = result;
			lastCardTexture = getTextureOfCard(lastCard);
			Player2CardRenderList.pop_back();
			setColor(lastCard);
			//记得把牌放回牌堆哟
			recycleCard(lastCard);
			cardSkill(lastCard);
		}
	
	}
	for (int i = 0; i < 16; i++) {
		render();
		sf::sleep(sf::milliseconds(50));
	}
	if (player2.getCardNum() == 0) {
		failedAlert();
		return;
	}
	else if (player2.getCardNum() == 1&&procAble) {
		UnoBubbleSprite.setPosition(200, 150);
		spriteRenderList.push_back(UnoBubbleSprite);
		for (int i = 0; i < 16; i++) {
			render();
			sf::sleep(sf::milliseconds(50));
		}
		spriteRenderList.pop_back();
	}
	if (isReversed == 0) {
		AIPlayer3Play();
	}
	else {
		AIPlayer1Play();
	}
	
}

void AIPlayer3Play() {
	LogInfo("player3出牌");
	if (playerCardList.size() == 0) {
		return;
	}
	if (!turnTexture.loadFromFile("./resources/right.png")) {
		LogError("无法加载right turn图标");
	}
	spriteRenderList.at(5).setPosition(780,100+24*player3.getCardNum()/2 );
	for (int j = 0; j < 4; j++) {
		render();
		sf::sleep(sf::milliseconds(50));
	}
	int procAble = 0;
	if (isBanned) {
		LogInfo("Player3被ban了");
		isBanned = 0;
		
	}
	else if (isPlus4) {
		LogInfo("喜吃加四");
		isPlus4 = 0;
		for (int j = 0; j < 4; j++) {
			player3.addCard(getCard());
			cardBackSprite.setPosition(830, 100 + 24 * Player3CardRenderList.size());
			Player3CardRenderList.push_back(cardBackSprite);
		}
	}
	else if (plus2CardNum) {
		LogInfo("+2来了");
		std::string result = player3.Plus2affordAble();
		if (result != "NULL") {
			LogInfo("逃过一劫");
			plus2CardNum += 1;
			lastCard = result;
			lastCardTexture = getTextureOfCard(lastCard);
			Player3CardRenderList.pop_back();
			setColor(lastCard);
			recycleCard(lastCard);
		}
		else {
			procAble = 1;
			std::cout << "吃+2 " << plus2CardNum << "张" << std::endl;
			int cardNum = plus2CardNum * 2;
			Plus2Anim();
			for (int i = 0; i < cardNum; i++) {
				player3.addCard(getCard());
				cardBackSprite.setPosition(830,100 + 24 * Player3CardRenderList.size());
				Player3CardRenderList.push_back(cardBackSprite);
			}
			plus2CardNum = 0;
		}
	}
	else {
		std::string result = player3.proc(lastCard);
		std::cout << "p3出牌: " << result << std::endl;

		if (result == "pass") {
			//player3.addCard(getCard());
			cardBackSprite.setPosition(830, 100 + 24 * Player3CardRenderList.size());
			Player3CardRenderList.push_back(cardBackSprite);
		}
		else {
			procAble=1;
			lastCard = result;
			lastCardTexture = getTextureOfCard(lastCard);
			Player3CardRenderList.pop_back();
			setColor(lastCard);
			recycleCard(lastCard);
			cardSkill(lastCard);
		}
	}
	for (int i = 0; i < 16; i++) {
		render();
		sf::sleep(sf::milliseconds(50));
	}
	if (player3.getCardNum() == 0) {
		failedAlert();
		return;
	}
	else if (player3.getCardNum() == 1&&procAble) {
		UnoBubbleSprite.setPosition(700, 150);
		spriteRenderList.push_back(UnoBubbleSprite);
		for (int i = 0; i < 16; i++) {
			render();
			sf::sleep(sf::milliseconds(50));
		}
		spriteRenderList.pop_back();
	}
	if (isReversed) {
		AIPlayer2Play();
		
	}
	else {
		if (plus2CardNum) {
			playerPlus2Affodable();
		}
		if (!turnTexture.loadFromFile("./resources/down.png")) {
			LogError("无法加载down turn图标");
		}
		spriteRenderList.at(5).setPosition(180+36*playerCardList.size()/2, 380);
		for (int j = 0; j < 4; j++) {
			render();
			sf::sleep(sf::milliseconds(50));
		}
	}
	
}

void cardSkill(std::string card) {
	int cardNum = std::stoi(card.substr(1));
	if (cardNum == 10) {
		//ban
		isBanned = 1;
		banAnim();
	}
	else if (cardNum == 11) {
		//reverse
		isReversed = 1 - isReversed;
		LogInfo("REVERSE");
		reverseAnim();
	}
	else if (cardNum == 14) {
		//+4
		isPlus4 = 1;
		Plus4Anim();
	}
	else if (cardNum == 12) {
		plus2CardNum ++;
	}
	else if (cardNum == 13) {
		//any color
		changeColorAnim();
	}

}

void playerPlus2Affodable() {
	
	for (std::string card : playerCardList) {
		LogInfo("user card=" + card); 
		if (isPlus2(card)==1) {
			LogInfo("找到+2");
			userPlus2Affordable = 2;
			return;
		}
	}
	userPlus2Affordable = 1;
}

void reverseAnim() {
	animSprite.setPosition(300, 160);
	animSprite.setTexture(animTexture);
	isAnimated = 1;
	LogInfo("REVERSE动画");
	reverseSound.play();
	for (int i = 2; i <= 50; i++) {
		if (!animTexture.loadFromFile("./resources/animation/rotation/" + std::to_string(i) + ".png")) {
			LogError("无法加载reverse动画");
		}
		render();
		sf::sleep(sf::milliseconds(40));
		
		
	}
	isAnimated = 0;
}
void banAnim() {
	animSprite.setPosition(300, 160);
	animSprite.setTexture(animTexture);
	isAnimated = 1;
	LogInfo("BAN动画");
	stopSound.play();
	for (int j = 0; j < 5; j++) {
		for (int i = 1; i <= 2; i++) {
			if (!animTexture.loadFromFile("./resources/animation/ban/" + std::to_string(i) + ".png")) {
				LogError("无法加载reverse动画");
			}
			render();
			sf::sleep(sf::milliseconds(100));

		}
	}
	isAnimated = 0;
}

void Plus4Anim() {
	animDrawSprite.setPosition(300, 160);
	if (!animDrawTexture.loadFromFile("./resources/animation/draw4.png",sf::IntRect(0,0,292,322) ) ) {
		LogError("无法加载加4动画");
	}
	
	animDrawSprite.setTexture(animDrawTexture);
	isAnimatedDrew = 1;
	LogInfo("DRAW4动画");
	drawSound.play();
	for (int j = 0; j < 7; j++) {
		if (!animDrawTexture.loadFromFile("./resources/animation/draw4.png", sf::IntRect(0+292*j, 0, 292, 322) ) ) {
			LogError("无法加载Draw 4动画");
		}
		render();
		sf::sleep(sf::milliseconds(50));
		render();
		sf::sleep(sf::milliseconds(50));
	}
	for (int j = 0; j < 7; j++) {
		if (!animDrawTexture.loadFromFile("./resources/animation/draw4.png", sf::IntRect(0 + 292 * j, 322, 292, 322))) {
			LogError("无法加载Draw 4动画");
		}
		render();
		render();
		sf::sleep(sf::milliseconds(50));
		render();
		sf::sleep(sf::milliseconds(50));
	}

	isAnimatedDrew = 0;
}

void Plus2Anim() {
	animDrawSprite.setPosition(300, 160);
	if (!animDrawTexture.loadFromFile("./resources/animation/draw2.png", sf::IntRect(0, 0, 292, 322))) {
		LogError("无法加载加2动画");
	}

	animDrawSprite.setTexture(animDrawTexture);
	isAnimatedDrew = 1;
	LogInfo("DRAW2动画");
	drawSound.play();
	for (int j = 0; j < 7; j++) {
		if (!animDrawTexture.loadFromFile("./resources/animation/draw2.png", sf::IntRect(0 + 292 * j, 0, 292, 322))) {
			LogError("无法加载Draw 2动画");
		}
		render();
		sf::sleep(sf::milliseconds(50));
		render();
		sf::sleep(sf::milliseconds(50));
	}
	for (int j = 0; j < 7; j++) {
		if (!animDrawTexture.loadFromFile("./resources/animation/draw2.png", sf::IntRect(0 + 292 * j, 322, 292, 322))) {
			LogError("无法加载Draw 2动画");
		}
		render();
		sf::sleep(sf::milliseconds(50));
		render();
		sf::sleep(sf::milliseconds(50));
	}

	isAnimatedDrew = 0;
}
void changeColorAnim() {
	animSprite.setPosition(300, 160);
	animSprite.setTexture(animTexture);
	isAnimated = 1;
	LogInfo("换色动画");
	reverseSound.play();

	for (int i = 1; i <=11; i++) {
		if (!animTexture.loadFromFile("./resources/animation/colorChange/" + std::to_string(i) + ".png")) {
			LogError("无法加载换色动画");
		}
		render();
		sf::sleep(sf::milliseconds(50));

	}
	for (int i = 11; i > 0; i--) {
		if (!animTexture.loadFromFile("./resources/animation/colorChange/" + std::to_string(i) + ".png")) {
			LogError("无法加载换色动画");
		}
		render();
		sf::sleep(sf::milliseconds(50));
		render();
		sf::sleep(sf::milliseconds(50));

	}
	
	isAnimated = 0;
}

void failedAlert() {
	sf::WindowHandle handle = window.getSystemHandle();
	HWND winHandle = (HWND)handle;
	MessageBox(winHandle, L"应用程序发生异常 expected software exception\n位置:player\n原因:mission failed", L"mission failed", MB_OK | MB_ICONERROR);
	LogInfo("返回主菜单");


	if (!bgTexture.loadFromFile("./resources/background.jpg")) {
		LogError("无法加载游戏背景");
	}

	reset();
	addmenuText();

}

void precallUno() {
	LogInfo("玩家应该叫uno了");
	clickTimer.restart();
	callUnoTimes = 1;
}

void playerBannedAction() {
	isBanned = 0;
	LogInfo("ban掉玩家");
	for (int j = 0; j < 8; j++) {
		render();
		sf::sleep(sf::milliseconds(50));
	}
	AIPlayerTurn();
}

void playerDrawAction(int cardNum) {
	for (int i = 0; i < cardNum; i++) {
		std::string newCard = getCard();
		playerCardList.push_back(newCard);
		playerCardTextureList.push_back(getTextureOfCard(playerCardList.at(playerCardList.size() - 1)));
		playerCardSprite.setTexture(playerCardTextureList.at(playerCardTextureList.size() - 1));
		playerCardSprite.setScale(0.3, 0.3);
		playerCardSprite.setPosition(180 + 36 * playerCardRenderList.size(), 420);
		playerCardRenderList.push_back(playerCardSprite);
		for (int i = 0; i < playerCardRenderList.size(); i++) {
			playerCardRenderList.at(i).setTexture(playerCardTextureList.at(i));
		}

		for (int i = 0; i < playerCardRenderList.size(); i++) {
			playerCardRenderList.at(i).setPosition(180 + 36 * i, 420);
		}
		for (int j = 0; j < 4; j++) {
			render();
			sf::sleep(sf::milliseconds(50));
		}
		
	}
}

void playerPlus4Act() {
	isPlus4 = 0;
	LogInfo("玩家喜提加四");

	playerDrawAction(4);
	for (int j = 0; j < 6; j++) {
		render();
		sf::sleep(sf::milliseconds(50));
	}
	

	AIPlayerTurn();
}
void playerPlus2Act() {
	int cardNum = plus2CardNum * 2;
	LogInfo("player吃加2");
	Plus2Anim();
	playerDrawAction(cardNum);

	plus2CardNum = 0;
	userPlus2Affordable = 0;
	for (int j = 0; j < 16; j++) {
		render();
		sf::sleep(sf::milliseconds(50));
	}
	
	AIPlayerTurn();
}

void backToMenu() {
	LogInfo("返回主菜单");
	if (!bgTexture.loadFromFile("./resources/background.jpg")) {
		LogError("无法加载游戏背景");
	}
	reset();
	addmenuText();
}

void unoCallHandler() {
	LogInfo("玩家叫了uno");
	if (clickTimer.getElapsedTime().asSeconds() <= 3) {
		LogInfo("成功叫了uno");

		UnoBubbleSprite.setPosition(400, 370);
		spriteRenderList.push_back(UnoBubbleSprite);
		for (int i = 0; i < 40; i++) {
			render();
			sf::sleep(sf::milliseconds(50));
		}
		

		spriteRenderList.pop_back();
	}
	else {
		LogInfo("太慢罚你");
		playerDrawAction(2);

		for (int i = 0; i < 4; i++) {
			render();
			sf::sleep(sf::milliseconds(100));
		}
		
	}
	clickTimer.restart();
	proced = 0;
	callUnoTimes = 0;
	if (isDialog == 0) {
		LogInfo("AI启动");
		AIPlayerTurn();
	}
}

void playerWinhandler() {
	sf::WindowHandle handle = window.getSystemHandle();
	HWND winHandle = (HWND)handle;
	MessageBox(winHandle, L"为玩家献上礼花!!!!!", L"You Win", MB_OK | MB_ICONINFORMATION);
	ShellExecute(NULL, L"open", L"https://shed4329.cn/uno", NULL, NULL, SW_SHOWNORMAL);
	LogInfo("返回主菜单");


	if (!bgTexture.loadFromFile("./resources/background.jpg")) {
		LogError("无法加载游戏背景");
	}

	reset();
	addmenuText();
}

void playerColorChangeHandler() {
	isDialog = 1;
	if (!DialogTexture.loadFromFile("./resources/dialogBackground.png")) {
		LogError("无法加载对话框背景图片");
	}
	DialogSprite.setTexture(DialogTexture);
	DialogSprite.setPosition(200, 200);
	render();
}

void playerProcHandler(std::string clickedCard) {
	setColor(clickedCard);
	lastCard = clickedCard;
	lastCardTexture = getTextureOfCard(clickedCard);

	int clickedIndex = 0;
	for (int i = 0; i < playerCardList.size(); i++) {
		if (clickedCard == playerCardList.at(i)) {
			clickedIndex = i;
		}
	}

	//player出牌
	playerCardList.erase(playerCardList.begin() + clickedIndex);
	cardSkill(lastCard);//发动技能
	//从渲染列表中清除
	playerCardRenderList.erase(playerCardRenderList.begin() + clickedIndex);

	playerCardTextureList.erase(playerCardTextureList.begin() + clickedIndex);
	for (int i = 0; i < playerCardRenderList.size(); i++) {
		playerCardRenderList.at(i).setTexture(playerCardTextureList.at(i));
	}

	for (int i = 0; i < playerCardRenderList.size(); i++) {
		playerCardRenderList.at(i).setPosition(180 + 36 * i, 420);
	}
	recycleCard(lastCard);
	//playerCardTextureList.erase(playerCardTextureList.begin() + clickedIndex);
	if (isColorChange(lastCard) == 1) {
		playerColorChangeHandler();
	}
	for (int j = 0; j < 8; j++) {
		render();
		sf::sleep(sf::milliseconds(100));
	}
	
	if (playerCardList.size() == 0) {
		playerWinhandler();
	}
	if (playerCardList.size() == 1) {
		precallUno();
	}
	else {

		if (isDialog == 0) {
			LogInfo("AI启动");
			AIPlayerTurn();
		}
	}
}

void playerNewCardAvaliableHandler() {
	if (playerCardList.size() == 1) {
		precallUno();
	}
	else {

		if (isDialog == 0) {
			LogInfo("AI启动");
			AIPlayerTurn();
		}
	}
}

void playerColorSelectHandler(sf::Vector2i mousePos) {
	//换色uno todo
	if (RedSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		isDialog = 0;
		lastCard[0] = 'r';
		LogInfo("last card =" + lastCard);
		setColor(lastCard);
		if (playerCardList.size() == 1) {
			precallUno();
		}
		else {
			AIPlayerTurn();
		}

	}
	else if (BlueSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		isDialog = 0;

		lastCard[0] = 'b';
		LogInfo("last card =" + lastCard);

		setColor(lastCard);

		if (playerCardList.size() == 1) {
			precallUno();
		}
		else {
			AIPlayerTurn();
		}
	}
	else if (GreenSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		isDialog = 0;

		lastCard[0] = 'g';
		LogInfo("last card =" + lastCard);

		setColor(lastCard);

		if (playerCardList.size() == 1) {
			precallUno();
		}
		else {
			AIPlayerTurn();
		}
	}
	else if (YellowSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		isDialog = 0;

		lastCard[0] = 'y';
		LogInfo("last card =" + lastCard);

		setColor(lastCard);

		if (playerCardList.size() == 1) {
			precallUno();
		}
		else {
			AIPlayerTurn();
		}
	}
}

void playerNewCardHandler() {
	LogInfo("玩家摸牌");
	int flag = 0;//假设没牌可出
	//check是不是符合条件
	for (int i = 0; i < playerCardList.size(); i++) {
		if (isThisOkay(lastCard, playerCardList.at(i)) == 1) {
			std::cout << lastCard << " " << playerCardList.at(i) << std::endl;
			flag = 1;
		}
	}
	if (flag == 0) {
		proced = 1;
		LogInfo("允许玩家摸牌");
		std::string newCard = getCard();
		playerCardList.push_back(newCard);
		playerCardTextureList.push_back(getTextureOfCard(playerCardList.at(playerCardList.size() - 1)));
		playerCardSprite.setTexture(playerCardTextureList.at(playerCardTextureList.size() - 1));
		playerCardSprite.setScale(0.3, 0.3);
		playerCardSprite.setPosition(180 + 36 * playerCardRenderList.size(), 420);
		playerCardRenderList.push_back(playerCardSprite);
		//摸了牌之后可以马上出新牌
		if (isThisOkay(lastCard, newCard) == -1) {
			playerNewCardAvaliableHandler();
		}
	}
}

void saveHanlder() {
	LogInfo("玩家存档");
	int result = showSaveDialog();
	if (result == -1) {
		return;
	}
	writer(playerCardList, player1.getCardList(), player2.getCardList(), player3.getCardList(), lastCard);
}

void introHandler() {
	sf::WindowHandle handle = window.getSystemHandle();
	HWND winHandle = (HWND)handle;
	MessageBox(winHandle, L"UNO是一种快速出牌游戏，目标是最先出完手中的牌。游戏使用一副108张牌，包括四种颜色的数字牌和特殊功能牌。玩家轮流出牌，必须出与上一张牌颜色或数字相同的牌。特殊牌可以改变游戏流程或让对手抽牌。当玩家只剩一张牌时，必须喊“UNO”。第一个出完牌的玩家获胜。\n特殊牌\n跳过（Skip）：打出后，下一个玩家跳过他的回合。\n反转（Reverse）：打出后，出牌的方向会反转。\n+ 2（Draw Two）：可以叠加，如果玩家不能叠加时，则摸牌。\n变色（Wild）：打出后，可以指定下一个玩家须出牌的颜色。\n + 4（Wild Draw Four）：打出后，可以指定下一个玩家必须出牌的颜色，并且该玩家需要从牌堆中抽四张牌，跳过他的回合。\n", L"玩法介绍", MB_OK | MB_ICONINFORMATION);
	MessageBox(winHandle, L"输了人家可是会报错的哟", L"警告Player", MB_OK | MB_ICONWARNING);
}

void aboutHandler() {
	LogInfo("点击了关于");
	//specialized for windows platform
	sf::WindowHandle handle = window.getSystemHandle();
	HWND winHandle = (HWND)handle;
	MessageBox(winHandle, L"Uno games\nspecialized for ZZB\nauthor:lxy\nversion 1.0.0\npowered by SFML\nlove from CS,at SCU", L"关于此游戏", MB_OK | MB_ICONINFORMATION);
}

void startLocalGameHandler() {
	isInGame = 1;
	textSpriteList.clear();
	LogInfo("开始游戏");
	if (!bgTexture.loadFromFile("./resources/game.png")) {
		LogError("无法加载游戏背景");
	}
	spriteRenderList.push_back(backSprite);


	initPlayerScene();
	initScene();
}

void readRecordHanlder() {
	int result = showOpenDialog();
	if (result == -1) {
		return;
	}
	reader(playerCardList, player1.getCardListReferance(), player2.getCardListReferance(), player3.getCardListReferance(), lastCard);
	removeCard(playerCardList);
	removeCard(player1.getCardList());
	removeCard(player2.getCardList());
	removeCard(player3.getCardList());

	isInGame = 1;
	textSpriteList.clear();
	LogInfo("开始游戏");
	if (!bgTexture.loadFromFile("./resources/game.png")) {
		LogError("无法加载游戏背景");
	}
	spriteRenderList.push_back(backSprite);
	initPlayerSceneLoaded();
	initScene();
}

void initPlayerSceneLoaded() {
	//player1渲染
	for (int i = 0; i < player1.getCardNum(); i++) {
		cardBackSprite.setPosition(10, 100 + 24 * i);
		Player1CardRenderList.push_back(cardBackSprite);
		
	}
	//player获取材质
	for (int i = 0; i < playerCardList.size(); i++) {
		playerCardTextureList.push_back(getTextureOfCard(playerCardList.at(i)));

	}
	//player渲染
	for (int i = 0; i < playerCardList.size(); i++) {
		playerCardSprite.setTexture(playerCardTextureList.at(i));
		playerCardSprite.setScale(0.3, 0.3);
		playerCardSprite.setPosition(180 + 36 * i, 420);
		playerCardRenderList.push_back(playerCardSprite);
	}
	//player2渲染
	for (int i = 0; i < player2.getCardNum(); i++) {
		cardBackSprite.setPosition(180 + 36 * i, 10);
		Player2CardRenderList.push_back(cardBackSprite);
		
	}
	//player3渲染
	for (int i = 0; i < player3.getCardNum(); i++) {
		cardBackSprite.setPosition(830, 100 + 24 * i);
		Player3CardRenderList.push_back(cardBackSprite);
		
	}

	cardBackSprite.setPosition(328, 200);
	cardRenderList.push_back(cardBackSprite);

	//抽第一张卡
	//lastCard = getCard();
	lastCardTexture = getTextureOfCard(lastCard);
	lastCardSprtie.setTexture(lastCardTexture);
	lastCardSprtie.setScale(0.3, 0.3);
	lastCardSprtie.setPosition(400, 200);
	cardRenderList.push_back(lastCardSprtie);
	setColor(lastCard);
}