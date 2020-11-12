//Game.cpp

#include "Game.h"

sf::RenderWindow* Game::window = NULL;
DrawQ* Game::drawQ = NULL;
std::list<Entity*>* Game::entityList = NULL;

int Game::fighter_ids[2] = {-1, -1};
int Game::stageID = -1;

void Game::quit(){
	Game::window->close();
}