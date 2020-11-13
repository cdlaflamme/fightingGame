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
#include "FighterFunctions.cpp"

class Entity{
public:
	bool deleteThis = false;
	bool isEnabled = true;
	
	virtual void Update(EventList &eventList){
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
							loadScene(SceneList::FightScene);
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
	
	//abstract class for all fighters; provides health structure
	sf::Texture fighterTexture;
	sf::Sprite fighterSprite;
	sf::Clock stateClock; //time at which the current state started, used for animations
	sf::Vector2f fighterPos;
	int fighterState = 0;//0: idle, 1:moving, 2:damaged, 3:attacking
	int spriteIndex = 0;//0: idle, 1:moving, 2:damaged, 3:attacking
	int gamepadID;
	int playerNumber;
	
	int health = 100; //percentage; assumed max of 100
	
	static const int sprite_x = 210; //tile size of single sprites in sprite sheet. used to split sheet
	static const int sprite_y = 225;
	
	void setSpriteIndex(int i){
		fighterSprite.setTextureRect(sf::IntRect(0, sprite_y*i, sprite_x, sprite_y));
		spriteIndex = i;
	}
	
	public:
	void takeDamage(int damage){
		health -= damage;
		//TODO animation, Iframes
	}
	int getHealth(){
		return health;
	}
	
	Fighter(int fighterID, bool left){
		gamepadID = (left?0:1); //may need to change
		playerNumber = (left?0:1);
		//set position
		fighterPos.y = Game::SCREEN_Y-sprite_y-95; //TODO make these less magical, maybe stage dependent?
		fighterPos.x = (left?100:Game::SCREEN_X-sprite_x-100);
		//load sprite sheet. TODO: make this more sophisticated? table of fighter names/texture paths somewhere? or make the filenames based on ID?
		switch(fighterID){
			case 0:
				fighterTexture.loadFromFile("Assets/blueMan.png");
				break;
			case 1:
				fighterTexture.loadFromFile("Assets/redMan.png");
				break;
		}
		fighterSprite.setTexture(fighterTexture); //TODO scale everything based on window size...? do I even allow configurable window size?
		//set initial sprite rectangle
		setSpriteIndex(0);
		Game::drawQ->add(fighterSprite, DrawLayers::stage);
	}
	
	void Update(EventList &eventList) override {

		
		//input
		bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		
		//movement
		if (left^right){
			if (fighterState==0){
				stateClock.restart();
				fighterState = 1;
				setSpriteIndex(2);
			}
			if (left) fighterPos.x -= 2.5;
			if (right)fighterPos.x += 2.5;
			if (stateClock.getElapsedTime().asSeconds() > 0.3f){
				stateClock.restart();
				setSpriteIndex((spriteIndex==2?3:2)); //TODO mirror depending on direction
			}
		}
		//idle
		else {
			if (fighterState!=0){
				stateClock.restart();
				fighterState = 0;
				setSpriteIndex(0);				
			}
			if (stateClock.getElapsedTime().asSeconds() > 0.5f){
				stateClock.restart();
				setSpriteIndex(((spriteIndex==0)?1:0));
			}
		}
		//attacking
		/*
		create a class with internal state variables and a big ol list of potential input sequences.
		each fighter has an instance of this classs inside of it (or make the fighter class really fat?)
		it has functions to receive inputs as they occur. it stores inputs and their timestamps (or at least the time since the previous input) in member variables.
		when this class is instantiated, a pointer is pointed towards a function that should be used to update its state, either through a function pointer or a class instance with a function pointer member.
		this function will be unique for each fighter, and will define the fighter's abilities completely.
		based on the most recent N inputs, the times at which those inputs occured, and the curent time, it outputs a state and sprite index. probably also cares about whether an input or attack hit.
		the above logic should only check the returned state to alter the fighter's position.
		hitbox generation/calculation should also be based on the state. moves which have multiple hitbox stages, like sex kicks, will be represented with multiple fighter states.
		how do we generate/calculate hitboxes? how do we attach a hitbox/hurtbox to a state? the above function should probably return a list of hitboxes (objects or number representations?).
		perhaps the function should internalize all fighter-specific decisions: how much to move given a specific input, the sprite to change to, and the hitboxes to use this frame.
		
		overall: this class should effect the desired sprite, movement, and hitboxes output by the fighter-specific function which implements each fighter's specific mechanics.
		*/
		
		fighterSprite.setPosition(fighterPos);
	}
	
};
