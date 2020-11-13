//Game.cpp

#include "Game.h"

sf::RenderWindow* Game::window = NULL;
DrawQ* Game::drawQ = NULL;
EntityList* Game::entityList = NULL;

int Game::fighter_ids[2] = {-1, -1};
int Game::stageID = -1;

void Game::quit(){
	Game::window->close();
}