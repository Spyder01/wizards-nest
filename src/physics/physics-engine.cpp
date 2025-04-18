#include "physics-engine.hpp"
#include <raylib.h>
#include <vector>

bool PhysicsEngine::isColliding(GameInanimateObject* object, GameCharacterObject* character) {
		Vector2 objPos = object->getPosition();
		Vector2 charPos = character->getPosition();

		float objW = object->getWidth();
		float objH = object->getHeight();

		const AnimationFrames& anim = character->getCurrentAnimation();
		if (anim.frames.empty()) return false;

		float charW = anim.frames[0].width * character->getScale();
		float charH = anim.frames[0].height * character->getScale();

		return (charPos.x < objPos.x + objW &&
						charPos.x + charW > objPos.x &&
						charPos.y < objPos.y + objH &&
						charPos.y + charH > objPos.y);
}

bool PhysicsEngine::isColliding(const std::vector<GameInanimateObject>& objects, GameCharacterObject* character) {
		Rectangle characterDst = character->getDestinationRect();

	  for (GameInanimateObject obj:objects) {
			if (isColliding(&obj, character)) {
				return true;  
			}
		}

		return false;
}

PhysicsEngine* PhysicsEngine::freeFall(GameCharacterObject *character, float deltaTime) {
		if (character->isOnGround()) {
			return this;  
		}

		float gravity = world->getGravity();

		Vector2 position = character->getPosition();
		Vector2 velocity = character->getVelocity();
		
	 	velocity.y += gravity * deltaTime;
		position.y += velocity.y * deltaTime;

		character->setPosition(position);
		character->setVelocity(velocity);

	  return this;
}
