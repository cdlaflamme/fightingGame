//main.cpp

#include "Game.h"
#include "LoadScene.h" //for loading scenes :)
#include "DrawQ.h" //for drawing queue
#include "Entity.cpp" //for entity class; DO AT BOTTOM

int main(){
	
	//open the game window
	sf::RenderWindow window(sf::VideoMode(Game::SCREEN_X, Game::SCREEN_Y),\
			"Everybody was kung-fu fighting");
	
	window.setFramerateLimit(Game::FRAMERATE);
	
	std::list<Entity*> entityList;
	DrawQ drawQ;
	
	Game::window = &window;
	Game::drawQ = &drawQ;
	Game::entityList = &entityList;

	//#############################
	
	loadScene(SceneList::MainMenu);
	
	while (window.isOpen()){
		
		//entity logic
		for (std::list<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it){
			//for each entity:
			if ((*it)->isEnabled) (*it)->Update();
			if ((*it)->deleteThis) entityList.erase(it);
		}
		
		//process events
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}
		
		//draw things
		window.clear();
		drawQ.drawToWindow(window);
		window.display();
	}
	
	return 0;
}
