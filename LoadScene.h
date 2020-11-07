//LoadScene.cpp

#ifndef LOADSCENE_H
#define LOADSCENE_H

#include "Game.h"

namespace SceneList{
	//while technically, everything could take place in one scene,
	//it's helpful to split load times between scenes,
	//and to clear out memory when a scene is over.
	enum Scene {
		MainMenu, CharSelect, FightScene
	};
}

int loadScene(SceneList::Scene scene);

#endif