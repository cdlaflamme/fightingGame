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

class Entity {
public:
	
	bool deleteThis = false;
	bool isEnabled = true;
	virtual void Update(){
		//pass
	};
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
		}
		
		
		void Update() override {
			Game::drawQ->add(titleSprite, DrawLayers::background);
			Game::drawQ->add(playText, DrawLayers::backstage);
			Game::drawQ->add(quitText, DrawLayers::backstage);
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				cursorSprite.setPosition(playX, textY);
				cursorPos = 0;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				cursorSprite.setPosition(quitX, textY);
				cursorPos = 1;
			}
			Game::drawQ->add(cursorSprite, DrawLayers::stage);
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
				//play
				if (cursorPos == 0){
					deleteThis = true; //leave main menu
					loadScene(SceneList::FightScene);
				}
				//quit
				if (cursorPos == 1){
					//TODO: has no access to window
					//window.close();
				}
			}
		}
};


class Fighter : public Entity{
	//abstract class for all fighters; provides health structure
	public:
	
	int health = 100; //percentage; assumed max of 100
	
	
	
	/*
	void Update() override {
		//TODO logic, animation, drawing
		
	}
	*/
	
};

class FightStage : public Entity{
	
	sf::Texture stageTexture;
	sf::Sprite stageSprite;
	sf::Vector2u stageTextureSize;
	
	FightStage(int stageID = 0){
		//TODO change stage image based on chosen stage
		//TODO how to handle boundaries?
		//scrolling can be handled by a SFML View
		stageTexture.loadFromFile("Assets/warrior_shrine.png");
		stageTextureSize = stageTexture.getSize();
		stageSprite.setTexture(stageTexture);
		stageSprite.setTextureRect(sf::IntRect(stageTextureSize.x/2 - Game::SCREEN_X/2, 0, Game::SCREEN_X, Game::SCREEN_Y));
	}
	
	void Update() override {
		//draw stage
		Game::drawQ->add(stageSprite, DrawLayers::background);
	}
};

