#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "../game-state/world/world.hpp"
#include "../game-state/objects/objects.hpp"
#include <vector>

class PhysicsEngine {
	private:
		World *world;

	public:
		PhysicsEngine(World* world) : world(world) {}

		bool isColliding(GameInanimateObject* object, GameCharacterObject* character);
		bool isColliding(const std::vector<GameInanimateObject>& objects, GameCharacterObject* character);
		PhysicsEngine* freeFall(GameCharacterObject *character, float deltaTime);
};

#endif
