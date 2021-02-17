//Entity.cpp
/*
not everything that moves or is drawn needs to be its own entity:
an entity can be responsible for any number of drawables, 
and can control the behavior of any number of things,
even things that a player might see as completely distinct.

Entity is an abstract class that should be inherited by classes
that wish to model objects or instances of systems.

Entity's Update function will be called every frame, if it is enabled. 
The entity is responsible for adding all its drawables to the drawing queue,
and is given access to the entity list so it may find/interact with other entities.
*/

#include "Game.h"
#include "Entity.h"
#include "FighterModule.h"

class Entity{
public:
	bool deleteThis = false;
	bool isEnabled = true;
	
	virtual void Update(EventList &eventList){
		//pass
	}
	
	virtual void LateUpdate(EventList &eventList){
		//pass
	}
};

//MenuController
class MainMenuController : public Entity{
	private:
		sf::Texture titleTexture;
		sf::Texture cursorTexture;
		
		sf::Sprite titleSprite;
		sf::Sprite cursorSprite;

		sf::Text playText;
		sf::Text quitText;
		sf::Font titleFont;
		int cursorPos = 0;
		
		const int playX = 200;
		const int quitX = 600;
		const int textY = 400;
		
	//load assets
	public:
		MainMenuController(){
			titleTexture.loadFromFile("Assets/Title.png");
			titleTexture.setSmooth(true);
			cursorTexture.loadFromFile("Assets/Cursor.png");
			
			if (!titleFont.loadFromFile("Assets/Titillium/Titillium-Regular.otf")){
				std::cout << "Error: Could not read font file.\n";
			}
			
			//title screen image
			titleSprite.setTexture(titleTexture);
			
			//play text
			playText.setFont(titleFont);
			playText.setString("Play");
			playText.setCharacterSize(35);
			playText.setFillColor(sf::Color::Blue);
			playText.setPosition(playX, textY);
			
			//quit text
			quitText.setFont(titleFont);
			quitText.setString("Quit");
			quitText.setCharacterSize(35);
			quitText.setFillColor(sf::Color::Blue);
			quitText.setPosition(quitX, textY);
			
			//menu cursor
			cursorSprite.setTexture(cursorTexture);
			cursorSprite.setOrigin(35, -6);
			cursorSprite.setPosition(playX, textY);
			
			Game::drawQ->add(titleSprite, DrawLayers::background);
			Game::drawQ->add(playText, DrawLayers::backstage);
			Game::drawQ->add(quitText, DrawLayers::backstage);
			Game::drawQ->add(cursorSprite, DrawLayers::stage);
		}
		
		void Update(EventList &eventList) override {
			for (EventList::iterator it = eventList.begin(); it != eventList.end(); it++){
				sf::Event event = *it;
				if (event.type == sf::Event::KeyPressed){
					if (event.key.code == sf::Keyboard::Left){
						cursorSprite.setPosition(playX, textY);
						cursorPos = 0;
					}
					else if (event.key.code == sf::Keyboard::Right){
						cursorSprite.setPosition(quitX, textY);
						cursorPos = 1;
					}
					else if (event.key.code == sf::Keyboard::Space){
						//play
						if (cursorPos == 0){
							deleteThis = true; //leave main menu
							loadScene(Scene::FightScene);
						}
						//quit
						if (cursorPos == 1){
							Game::quit();
						}
					}
				}
			}
		}
};

class FightStage : public Entity{
	sf::Texture stageTexture;
	sf::Sprite stageSprite;
public:	
	FightStage(int stageID){
		//TODO change stage image based on chosen stage
		//TODO how to handle boundaries?
		//scrolling can be handled by a SFML View
		stageTexture.loadFromFile("Assets/warrior_shrine.png");
		sf::Vector2u stageTextureSize = stageTexture.getSize();
		stageSprite.setTexture(stageTexture);
		//stageSprite.setTextureRect(sf::IntRect(stageTextureSize.x/2 - Game::SCREEN_X/2, 0, Game::SCREEN_X, Game::SCREEN_Y));
		stageSprite.setScale((float)Game::SCREEN_X/(float)stageTextureSize.x, (float)Game::SCREEN_Y/(float)stageTextureSize.y);
		
		Game::drawQ->add(stageSprite, DrawLayers::background);
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Fighter : public Entity{
	//class for all fighters; implements all common mechanics, leaving character-specific mechanics/state transitions to FighterModules
	sf::Sprite fighterSprite;
	sf::Vector2f fighterPos;
	FighterModule *fighterModule;
	FighterState currentState;
	int gamepadID;
	int playerID;
	
	int health = 100; //percentage; assumed max of 100
	
	static const int sprite_x = 210; //tile size of single sprites in sprite sheet. used to split sheet
	static const int sprite_y = 225;
	
	void setSpriteIndex(int reel, int index){ //reel r, index i
		fighterSprite.setTextureRect(sf::IntRect(sprite_x*index, reel*sprite_y, sprite_x, sprite_y)); //top left x, top left y, width, height
	}
	
	public:
	void takeDamage(int damage){
		health -= damage;
		//TODO animation, Iframes
	}
	int getHealth(){
		return health;
	}
	FighterState getState(){
		return currentState;
	}
	
	Fighter(int fighterID, bool left){
		fighterModule = createFighterModule(fighterID); ///XXX memory leak?
		fighterSprite.setTexture(*(fighterModule->getTexture()));
		gamepadID = (left?0:1); //may need to change
		playerID = (left?0:1);
		//set position
		fighterPos.y = Game::SCREEN_Y-sprite_y-95; //TODO make these less magical, maybe stage dependent?
		fighterPos.x = (left?100:Game::SCREEN_X-sprite_x-100);

		//set initial sprite rectangle
		setSpriteIndex(0,0);
		Game::drawQ->add(fighterSprite, DrawLayers::stage);
	}
	
	void Update(EventList &eventList) override {
		//update state based on recent input
		currentState = fighterModule->getNextState(eventList);
		//set sprite
		setSpriteIndex(currentState.spriteReel, currentState.spriteIndex);
		//move fighter
		fighterPos += currentState.movement;
		fighterSprite.setPosition(fighterPos);
	}
	
	void LateUpdate(EventList &eventList) override {
		//TODO hitbox logic; happens in lateupdate so every fighter has a chance to update their state before this occurs
	}
	
};
