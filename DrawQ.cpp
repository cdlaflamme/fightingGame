//DrawQ.cpp
#include "DrawQ.h"

void DrawQ::clearQ(){
	for (int l=0; l<DrawLayers::NUM_LAYERS; l++){
		//for each layer, delete each entry
		entry* currentEntry = layerHeads[l];
		entry* nextEntry = NULL;
		while(currentEntry != NULL){			
			nextEntry = currentEntry->next;
			delete currentEntry;
			currentEntry = nextEntry;
		}		
	}
}

void DrawQ::add(sf::Drawable &drawable, DrawLayers::Layer layer, int order=0){
	entry* newEntry;	//the eventual destination of the drawable to add
	entry* currentEntry; //iterator
	entry* prevEntry = NULL; //temp holder
	
	//if this is the first entry added, make it head of layer
	if (layerHeads[layer] == NULL || layerHeads[layer]->drawable == NULL){
		newEntry = new entry;
		layerHeads[layer] = newEntry;
	}
	
	//if the head exists and is occupied, and we should become the new head, based on sorting order
	else if (layerHeads[layer]->order > order){
		newEntry = new entry;
		newEntry->next = layerHeads[layer];
		layerHeads[layer] = newEntry;
	}
	//if the head was occupied and we are higher priority
	else {
		prevEntry = layerHeads[layer];
		currentEntry = prevEntry->next;
		//loop until we find an entry that is either null or vacant
		while(true){
			//we've found a vacant entry, use it
			if (currentEntry != NULL && currentEntry->drawable == NULL){
				currentEntry = currentEntry;
				break;
			}
			//we've found the end of the list, or need to add an entry between two existing ones
			else if (currentEntry == NULL || currentEntry->order > order){
				newEntry = new entry;
				prevEntry->next = newEntry;
				break;
			}
			prevEntry = currentEntry;
			currentEntry = currentEntry->next;
		}
		newEntry->next = currentEntry;
		prevEntry->next = newEntry;
	}
	
	//now that we've decided where this entry will go, set its values
	newEntry->layer = layer;
	newEntry->order = order;
	newEntry->drawable = &drawable;
}

//draws everything in the Q, and VACATES the Q, clearing the Q without deleting entries (to save time spent on memory allocation)
void DrawQ::drawToWindow(sf::RenderWindow& window){
	for (int l=0; l<DrawLayers::NUM_LAYERS; l++){
		//for each layer, starting with the back and heading forward
		entry* currentEntry = layerHeads[l];
		while(currentEntry != NULL && currentEntry->drawable != NULL){
			window.draw(*(currentEntry->drawable));
			currentEntry->drawable = NULL;
			currentEntry = currentEntry->next;
		}		
	}
}