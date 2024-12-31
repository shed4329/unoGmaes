#pragma once
#include <string>
#include <SFML/Graphics.hpp>


void show();
void render();
void addmenuText();
void initSprite();
void initText();
void initScene();
std::string playerClick(float x, float y);
void setColor(std::string card);
void initPlayerScene();
void reset();
void AIPlayerTurn();
void AIPlayer1Play();
void AIPlayer2Play();
void AIPlayer3Play();
void cardSkill(std::string card);
void playerPlus2Affodable();
void reverseAnim();
void banAnim();
void Plus4Anim();
void Plus2Anim();
void changeColorAnim();
void failedAlert();
void precallUno();
void initMusic();
void playerBannedAction();
void playerDrawAction(int cardNum);
void playerPlus4Act();
void playerPlus2Act();
void backToMenu();
void unoCallHandler();
void playerWinhandler();
void playerColorChangeHandler();
void playerProcHandler(std::string clickedCard);
void playerNewCardAvaliableHandler();
void playerColorSelectHandler(sf::Vector2i mousePos);
void playerNewCardHandler();
void saveHanlder();
void introHandler();
void aboutHandler();
void startLocalGameHandler();
void readRecordHanlder();
void initPlayerSceneLoaded();