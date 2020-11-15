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

class StickMan : public FighterModule {
	bool movingLeft = false;
	bool movingRight = false;
	
	public:
	StickMan(int id):FighterModule(id){
		//extra init
	}
	
	FighterState getNextState(EventList &eventList) override {
		FighterState newState;
		newState.hitboxes = NULL;
		newState.movement.y = 0;
		newState.spriteIndex = lastState.spriteIndex;
		
		for (EventList::iterator it = eventList.begin(); it != eventList.end(); it++){
			sf::Event event = *it;
			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Left){
					movingLeft = true;
				}
				else if (event.key.code == sf::Keyboard::Right){
					movingRight = true;
				}
			}
			else if (event.type == sf::Event::KeyReleased){
				if (event.key.code == sf::Keyboard::Left){
					movingLeft = false;
				}
				if (event.key.code == sf::Keyboard::Right){
					movingRight = false;
				}
			}
		}
		
		//movement
		if (movingLeft^movingRight){
			if (fighterState==0){
				stateClock.restart();
				fighterState = 1;
				newState.spriteIndex = 2;
			}
			if (movingLeft) newState.movement.x = -2.5;
			if (movingRight)newState.movement.x =  2.5;
			if (stateClock.getElapsedTime().asSeconds() > 0.2f){
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
			module = new StickMan(id);
			break;
		case 1: //red man
			module = new StickMan(id);
			break;
	}
	return module;
}