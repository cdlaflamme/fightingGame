//DrawQ.cpp
//used to keep track of all Drawables, and their sorting order

#ifndef DRAWQ_H
#define DRAWQ_H

#include <SFML/Graphics.hpp>


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
	
	
	public:
	void clear();
	void add(sf::Drawable&, DrawLayers::Layer);
	void add(sf::Drawable&, DrawLayers::Layer, int);
	void remove(sf::Drawable&); //walks through the entire Q until the object is found :(
	void remove(sf::Drawable&, DrawLayers::Layer); //walks through only the specified layer (makes things a little faster)
	void drawToWindow(sf::RenderWindow&);
	
	~DrawQ(){
		clear();
	}
};

#endif