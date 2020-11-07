//DrawQ.cpp
//used to keep track of all Drawables, and their sorting order

#ifndef DRAWQ_H
#define DRAWQ_H

#include "Game.h"

namespace DrawLayers{
	const int NUM_LAYERS = 5;
	enum Layer {
		background, backstage, stage, foreground, HUD
	};
}

class DrawQ{
	private:
	struct entry {
		DrawLayers::Layer layer;
		int order;
		sf::Drawable* drawable = NULL;
		entry* next = NULL;
	};
	entry* layerHeads[DrawLayers::NUM_LAYERS] = {NULL};
	
	void clearQ();
	
	public:
	void add(sf::Drawable&, DrawLayers::Layer);
	void add(sf::Drawable&, DrawLayers::Layer, int);
	void drawToWindow(sf::RenderWindow&);
	
	~DrawQ(){
		clearQ();
	}
};



#endif