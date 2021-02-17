//FighterModule.cpp

#include "FighterModule.h"

FighterModule::FighterModule(int fighterID){
	//set texture based on fighter ID
	switch(fighterID){
	case 0:
		fighterTexture.loadFromFile("Assets/blueManReeled.png");
		break;
	case 1:
		fighterTexture.loadFromFile("Assets/redManReeled.png");
		break;
	}
}

sf::Texture *FighterModule::getTexture(){
	return &fighterTexture;
}

struct Input

class StickMan : public FighterModule {
	bool movingLeft = false;
	bool movingRight = false;
	
	enum class Move { //standard: names are lowercase verbs. (not capitalized, not "-ing" nouns)
		idle,
		walk,
		run,
		punch,
		kick,
		flinch
	};
	Move currentMove = Move::idle;
	
	public:
	StickMan(int id):FighterModule(id){
		//extra init
	}
	
	FighterState getNextState(EventList &eventList) override {
		FighterState newState;
		newState.hitboxes = NULL;
		newState.movement.y = 0;
		newState.spriteIndex = lastState.spriteIndex;
		newState.spriteReel = lastState.spriteReel;
		
		//for combos like 1 1 1, it is ideal to be able to check Pressed events (using realtime would require state boolean and frames where the button was not held to register a "press" not a "hold")
		//though sequential input is difficult to handle. Do we assemble an Input state for each frame? perhaps one for buttons pressed this frame, and one for buttons held (or just use realtime for this case)
		//either way, how do we handle inputs such as a quarter circle? Assemble a list of past events with timestamps, then for the current state, check this list for "substrings" of inputs
		//example: if currentMove==Move::dragon_punch, check for a quarter circle in the last 0.5 seconds. if present, move towards dragon_uppercut or something.
		//only checks certain inputs as determined by the current move and state.
		//when the current state ends, check past events starting from the oldest. if an input was received in a proper time window, then move to an according move next.
		
		//I think every transition should use the list of recent events:
		//if move is idle, and past events include X negative and no attack, set move to walk. if past events include an attack, do that.
		//if current move is an attack, and its timer hasn't finished, continue (don't check input). if the timer is running out, check past events. if followup move has been input, transition to that move.
		
		//TODO
		//to assemble this list: we want a linked list of (input, timestamp) pairs. they're all in chronological order, and the timestamp is measured since... the start of the game, I guess.
		//List is good for this: doubly linked, has push/pop for back and front. Good for pushing stuff to one side and popping to the other.
		//Deque is also acceptable. It offers random access (wonderful for substring matching). List is better for random insertion, which is NOT something we need. 
		//should I convert entity list to a Deque? maybe not, since things are frequently being removed from it at arbitrary locations. the iterator is fine, we don't really need random access either.
		//do I need to create a struct for input entries? I think I do... I can define an enum for the inputs (1-4, 8 directions) and have the entry be an enum value and a float timestamp.
		//should reinstate the game clock for this time stuff
		
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
		
		//punch
		if (currentMove == Move::idle || currentMove == Move::walk){
			
			
		}
		
		//movement
		if (movingLeft^movingRight){
			if (currentMove == Move::idle ){
				moveClock.restart();
				currentMove = Move::walk;
				newState.spriteIndex = 0;
				newState.spriteReel = 1;
			}
			if (currentMove == Move::walk){ //design decision: should this check be here, or when movingLeft/movingRight is set? depends on design of combat moves, I suppose...
				if (movingLeft) newState.movement.x = -2.5;
				if (movingRight)newState.movement.x =  2.5;
				if (moveClock.getElapsedTime().asSeconds() > 0.2f){
					moveClock.restart();
					newState.spriteIndex = (lastState.spriteIndex==0?1:0); //TODO mirror depending on direction
				}
			}
		}
		//idle
		else {
			if (currentMove != Move::idle){
				moveClock.restart();
				currentMove = Move::idle;
				newState.spriteIndex = 0;
				newState.spriteReel = 0;
			}
			if (moveClock.getElapsedTime().asSeconds() > 0.5f){
				moveClock.restart();
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