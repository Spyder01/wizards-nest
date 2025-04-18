#ifndef TEXTURE_CONTAINER_H
#define TEXTURE_CONTAINER_H

#include "raylib.h"

class TextureContainer {
	private:
		Texture2D tile;
	
	public:
		TextureContainer(Texture2D tile) : tile(tile) {}
		Texture2D getTile() {
			return tile;  
		}
};

#endif

