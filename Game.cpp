//Game.cpp

#include "Game.h"

sf::RenderWindow* Game::window = NULL;
DrawQ* Game::drawQ = NULL;
std::list<Entity*>* Game::entityList = NULL;	