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
	
	//TODO consider implementing a helpful pattern:
	//sf::Clock clock;
	//while (window.isOpen())
	//{
	//	sf::Time elapsed = clock.restart();
	//	updateGame(elapsed);
	//	...
	//}
	
	while (window.isOpen()){
		//list of entity iterator positions for entities that mark themselves for deletion.
		std::list<std::list<Entity*>::iterator> delList;
		//entity logic
		for (std::list<Entity*>::iterator it = entityList.begin(); it != entityList.end(); it++){
			//for each entity:
			if ((*it)->isEnabled) (*it)->Update();
			if ((*it)->deleteThis) delList.push_back(it);
		}
		//delete entities that marked themselves for deletion. doing this during the above loop corrupts the iterator. (holy type definitions, batman)
		for (std::list<std::list<Entity*>::iterator>::iterator it = delList.begin(); it != delList.end(); it++){
			entityList.erase((*it));
		}
		
		//process events
		//TODO consider having a global table maping keys/inputs to function pointers. Alternatively, have each entity process each event, with most entities ignoring most inputs
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				Game::quit();
			else if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Escape)
					Game::quit();
			}
		}
		
		//draw things
		window.clear();
		drawQ.drawToWindow(window);
		window.display();
	}
	
	return 0;
}
