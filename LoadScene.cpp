//LoadScene.cpp
#include "LoadScene.h"
#include "Entity.cpp"
#include "DrawQ.h"

int loadScene(SceneList::Scene scene){
	//TODO clear entity list/drawQ, put up loading screen
	
	Game::drawQ->clear();
	
	//load new scene
	switch (scene){
		case SceneList::MainMenu:{
			//instantiate main menu controller
			MainMenuController *mainMenu = new MainMenuController();
			Game::entityList->push_back(mainMenu);
		}
		break;
			
		case SceneList::CharSelect:
			
			break;
			
		case SceneList::FightScene:{
			//instantiate stage
			FightStage* stage = new FightStage(Game::stageID);
			Game::entityList->push_back(stage);
			
			//instantiate fighters
			Entity* leftFighter = new Fighter(0);
			Game::entityList->push_back(leftFighter);
			//instantiate controller?
			
		}
		break;
	}
	
	return 0;
}