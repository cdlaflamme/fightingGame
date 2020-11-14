//FighterModule.cpp

#include "FighterModule.h"

FighterModule::FighterModule(int fighterID){
	//set texture based on fighter ID
	switch(fighterID){
	case 0:
		fighterTexture.loadFromFile("Assets/blueMan.png");
		break;
	case 1:
		fighterTexture.loadFromFile("Assets/redMan.png");
		break;
	}
}

sf::Texture *FighterModule::getTexture(){
	return &fighterTexture;
}
	
class BlueMan : public FighterModule {
	public:
	BlueMan(int id):FighterModule(id){
		//extra init
	}
	
	//TODO make function for the shared stuff like movement. also, need bool for movement: shouldn't move only on presses.
	FighterState getNextState(EventList &eventList) override {
		FighterState newState;
		newState.hitboxes = NULL;
		newState.movement.y = 0;
		//input
		bool left  = false;
		bool right = false;
		
		for (EventList::iterator it = eventList.begin(); it != eventList.end(); it++){
			sf::Event event = *it;
			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Left){
					left = true;
				}
				else if (event.key.code == sf::Keyboard::Right){
					right = true;
				}
			}
		}
		
		//movement
		if (left^right){
			if (fighterState==0){
				stateClock.restart();
				fighterState = 1;
				newState.spriteIndex = 2;
			}
			if (left) newState.movement.x = -2.5;
			if (right)newState.movement.x =  2.5;
			if (stateClock.getElapsedTime().asSeconds() > 0.3f){
				stateClock.restart();
				newState.spriteIndex = (lastState.spriteIndex==2?3:2); //TODO mirror depending on direction
			}
		}
		//idle
		else {
			if (fighterState!=0){
				stateClock.restart();
				fighterState = 0;
				newState.spriteIndex = 0;				
			}
			if (stateClock.getElapsedTime().asSeconds() > 0.5f){
				stateClock.restart();
				newState.spriteIndex = (lastState.spriteIndex==0?1:0);
			}
		}
		lastState = newState;
		return newState;
	}
};

class RedMan : public FighterModule {
	public:
	RedMan(int id):FighterModule(id){
		//extra init
	}
	
	FighterState getNextState(EventList &eventList) override {
		FighterState newState;
		newState.hitboxes = NULL;
		newState.movement.y = 0;
		//input
		bool left  = false;
		bool right = false;
		
		for (EventList::iterator it = eventList.begin(); it != eventList.end(); it++){
			sf::Event event = *it;
			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Left){
					left = true;
				}
				else if (event.key.code == sf::Keyboard::Right){
					right = true;
				}
			}
		}
		
		//movement
		if (left^right){
			if (fighterState==0){
				stateClock.restart();
				fighterState = 1;
				newState.spriteIndex = 2;
			}
			if (left) newState.movement.x = -2.5;
			if (right)newState.movement.x =  2.5;
			if (stateClock.getElapsedTime().asSeconds() > 0.3f){
				stateClock.restart();
				newState.spriteIndex = (lastState.spriteIndex==2?3:2); //TODO mirror depending on direction
			}
		}
		//idle
		else {
			if (fighterState!=0){
				stateClock.restart();
				fighterState = 0;
				newState.spriteIndex = 0;				
			}
			if (stateClock.getElapsedTime().asSeconds() > 0.5f){
				stateClock.restart();
				newState.spriteIndex = (lastState.spriteIndex==0?1:0);
			}
		}
		lastState = newState;
		return newState;
	}
};

/////////////////////////////////////////

FighterModule *createFighterModule(int id){ //FighterModule is an abstract class; this function instantiates an implemented class and passes it back as a generic module
	//big switch case determining which class to instantiate based on the passed ID
	FighterModule * module = NULL;
	switch(id){
		case 0: //blue man
			module = new BlueMan(id);
			break;
		case 1: //red man
			module = new RedMan(id);
			break;
	}
	return module;
}