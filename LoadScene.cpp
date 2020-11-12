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
			FightStage* stage = new FightStage(Game::stageID);
			Game::entityList->push_back(stage);
		}
		break;
	}
	
	return 0;
}