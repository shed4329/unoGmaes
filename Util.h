#pragma once

#include <string>
#include <SFML/Graphics.hpp>


int isWildCard(std::string card);
int isThisOkay(std::string lastCard, std::string card);
int getRandom();
sf::Texture getTextureOfCard(std::string card);
int isPlus2(std::string card);
int isColorChange(std::string card);