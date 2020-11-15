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
	
	EntityList entityList;
	DrawQ drawQ;
	
	Game::window = &window;
	Game::drawQ = &drawQ;
	Game::entityList = &entityList;

	//#############################
	
	loadScene(SceneList::MainMenu);
	window.requestFocus();
	window.setKeyRepeatEnabled(false);
	//consider implementing the following pattern:
	//for now, anything that cares about the time will handle its own clocks
	//sf::Clock clock;
	//while (window.isOpen())
	//{
	//	sf::Time elapsed = clock.restart();
	//	updateGame(elapsed);
	//	...
	//}
	
	EventList inputEvents;
	
	while (window.isOpen()){
		//process events
		sf::Event event;
		inputEvents.clear();
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				Game::quit();
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
				Game::quit();
			}
			else{
				inputEvents.push_back(event); //is this a problem?
			}
		}
		
		//entity logic
		//list of entity iterator positions for entities that mark themselves for deletion.
		EntItList delList;
		//update entities
		for (EntityList::iterator it = entityList.begin(); it != entityList.end(); it++){
			//for each entity:
			if ((*it)->isEnabled) (*it)->Update(inputEvents);
			if ((*it)->deleteThis) delList.push_back(it);
		}
		//late update entities
		for (EntityList::iterator it = entityList.begin(); it != entityList.end(); it++){
			//for each entity:
			if (!(*it)->deleteThis){
				if ((*it)->isEnabled) (*it)->LateUpdate(inputEvents);
				if ((*it)->deleteThis) delList.push_back(it);
			}
		}
		//delete entities that marked themselves for deletion. doing this during the above loop corrupts the iterator. (holy type definitions, batman)
		for (EntItList::iterator it = delList.begin(); it != delList.end(); it++){
			entityList.erase((*it));
		}
		

		
		//draw things
		window.clear();
		drawQ.drawToWindow(window);
		window.display();
	}
	
	return 0;
}
