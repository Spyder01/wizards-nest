#ifndef GAME_STATE_OBJECT_H
#define GAME_STATE_OBJECT_H

#include <raylib.h>
#include <cstdint>
#include <vector>
#include <array>

enum Direction : int8_t {
	  LEFT = -1,
		RIGHT = 1,
};

typedef struct {
    std::vector<Texture2D> frames;
    float frameDuration;
} AnimationFrames;

class GameInanimateObject {
private:
    float scale;
    int height, width;
    Vector2 position, origin;
    Direction direction;
    Rectangle src, dst;
    Texture2D texture;

public:
    GameInanimateObject(Texture2D texture, float scale, Vector2 position, Direction direction)
        : texture(texture), scale(scale), position(position), direction(direction) {
        height = texture.height;
        width = texture.width;

        src = {0.0f, 0.0f, (float)width * direction, (float)height};
        dst = {position.x, position.y, width * scale, height * scale};
        origin = {dst.width / 2, dst.height / 2};
    }

		GameInanimateObject(GameInanimateObject* object) {
			texture = object->texture;  
			scale = object->scale;
			position = object->position;
			direction = object->direction;
			height = object->height;
			width = object->width;
			src = object->src;
			dst = object->dst;
			origin = object->origin;
		}

    inline Vector2 getPosition() const { return position; }
    inline float getWidth() const { return width * scale; }
    inline float getHeight() const { return height * scale; }

    inline GameInanimateObject* setPosition(Vector2 position) {
        this->position = position;
        dst.x = position.x;
        dst.y = position.y;
        return this;
    }
		 
		inline Rectangle getDestinationRect() const {
			return dst;  
		}

    inline GameInanimateObject* draw() {
        DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
        return this;
    }

		inline void unload() {
        UnloadTexture(texture);
		}

    ~GameInanimateObject() {}
};

enum CHARACTER_STATE : uint8_t {
    IDLE,
		FALL,
    RUN,
    ATTACK,
    COUNT,
};

class GameCharacterObject {
private:
    CHARACTER_STATE state;
		std::array<AnimationFrames, static_cast<size_t>(CHARACTER_STATE::COUNT)> characterAnimations;
		float scale;
		Direction direction;
		Vector2 position, velocity, origin, acleration;
		bool onGround;
    Rectangle src, dst;
		unsigned int currentFrame;

public:
		GameCharacterObject(std::array<AnimationFrames, static_cast<size_t>(CHARACTER_STATE::COUNT)> characterAnimations, float scale, Direction direction) : scale(scale), direction(direction), characterAnimations(characterAnimations) {
				onGround = false;
				velocity = Vector2{0,0};
				position = Vector2{100,100};
				currentFrame = 0;
				state = CHARACTER_STATE::IDLE;
			
				Texture2D texture = getCurrentAnimation().frames[currentFrame];

				int width = texture.width;
				int height = texture.height;

        src = {0.0f, 0.0f, (float)width * direction, (float)height};
        dst = {position.x, position.y, width * scale, height * scale};
        origin = {dst.width / 2, dst.height / 2};
		}

		inline Vector2 getPosition() {
			return position;	
		}

		inline Vector2 getVelocity() {
			return velocity;  
		}

		inline float getScale() const {
			return scale;  
		}

		inline bool isOnGround() {
			return onGround;	
		}

		inline GameCharacterObject* setOnGround(bool onGround) {
			this->onGround = onGround;
			return this;
		}

		inline GameCharacterObject* setPosition(Vector2 position) {
			this->position = position;  
			return this;
		}

		inline GameCharacterObject* setVelocity(Vector2 velocity) {
			this->velocity = velocity;  
			return this;
		}

    inline GameCharacterObject* setAnimation(CHARACTER_STATE s, AnimationFrames frames) {
        characterAnimations[static_cast<size_t>(s)] = frames;
				return this;
    }

    inline const AnimationFrames& getCurrentAnimation() const {
        return characterAnimations[static_cast<size_t>(state)];
    }

    inline GameCharacterObject* setState(CHARACTER_STATE s) {
        state = s;
				currentFrame = 0;
				return this;
    }

		inline GameCharacterObject* animate() {
			currentFrame = (currentFrame + 1)%getCurrentAnimation().frames.size();	  
			return this;
		}

		inline GameCharacterObject* draw() {
			Texture2D texture = getCurrentAnimation().frames[currentFrame];

			int width = texture.width;
			int height = texture.height;

			src.height = height;
			src.width = width*direction;
			
			dst.x = position.x;
			dst.y = position.y;
			dst.height = height*scale;
			dst.width = width*scale;

			origin.x = dst.width/2;
			origin.y = dst.height/2;

			DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);

			return this;
		}

		inline Rectangle getDestinationRect() const {
			return dst;  
		}

		inline CHARACTER_STATE getCharacterState() const {
			return state;  
		}

		~GameCharacterObject() {
			for (AnimationFrames frames:characterAnimations) {
				for (Texture2D texture:frames.frames) {
					 UnloadTexture(texture); 
				}
			}
		}
};

#endif

