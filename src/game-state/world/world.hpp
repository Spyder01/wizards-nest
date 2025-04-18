#ifndef WORLD_H
#define WORLD_H

class World {
	private:
		int height, width, groundDelta, tileCount;
		const float gravity;
	
	public:
		World(int height, int width, int groundDelta, int tileCount, float gravity) : height(height), width(width), groundDelta(groundDelta), tileCount(tileCount), gravity(gravity) {}
		int getTileCount() {
			return tileCount;  
		}

		int getGroundLevel() {
			  return (height - groundDelta);
		}

		const float getGravity() const {
			 return gravity; 
		}
};

#endif
