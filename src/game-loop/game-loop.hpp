#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include<vector>
#include "../physics/physics-engine.hpp"
#include "../game-state/world/world.hpp"
#include "../game-state/objects/objects.hpp"

class GameLoop {
	private:
		const std::vector<GameInanimateObject>& tileObjects;
		GameCharacterObject* wizard;
		const World *world;
		PhysicsEngine* physics;

	public:
		GameLoop(const World* world, const std::vector<GameInanimateObject>& tileObjects, GameCharacterObject* wizard, PhysicsEngine* physics) : tileObjects(tileObjects), wizard(wizard), world(world), physics(physics) {}

		GameLoop* handleWizardState(float deltaTime);
		GameLoop* render();
};

#endif
