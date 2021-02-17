//LoadScene.cpp
#include "LoadScene.h"
#include "DrawQ.h"
#include "Entity.cpp"

int loadScene(Scene scene){
	//TODO clear entity list, put up loading screen
	
	Game::drawQ->clear();
	
	//load new scene
	switch (scene){
		case Scene::MainMenu:{
			//instantiate main menu controller
			MainMenuController *mainMenu = new MainMenuController();
			Game::entityList->push_back(mainMenu);
		}
		break;
			
		case Scene::CharSelect:
			//TODO
			break;
			
		case Scene::FightScene:{
			//instantiate stage
			FightStage* stage = new FightStage(Game::stageID);
			Game::entityList->push_back(stage);
			
			//instantiate fighters
			Entity* leftFighter = new Fighter(0, true);
			Entity* rightFighter = new Fighter(1, false);
			Game::entityList->push_back(leftFighter);
			Game::entityList->push_back(rightFighter);
			//instantiate controller?
			
		}
		break;
	}
	
	return 0;
}