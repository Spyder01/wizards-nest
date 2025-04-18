#include <cstdlib>
#include<vector>
#include<iostream>

#include "physics/physics-engine.hpp"
#include "raylib.h"
#include "./game-state/world/world.hpp"
#include "./game-state/objects/objects.hpp"
#include "./game-loop/game-loop.hpp"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 750
#define GROUND_HEIGHT 0
#define FPS 90
#define FRAME_DELAY 0.1

int main () {
	
	SetTargetFPS(FPS);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Wizard's Nest");
	
	float currentFrameTime = 0;
	World world = World(WINDOW_HEIGHT, WINDOW_WIDTH, GROUND_HEIGHT, 0, 20);
	PhysicsEngine physics = PhysicsEngine(&world);

	GameInanimateObject tileObject = GameInanimateObject(LoadTexture("assets/background/tiles/tile.png"), 1.2, Vector2{0, WINDOW_HEIGHT}, Direction::RIGHT);
	const int tileCount = (WINDOW_WIDTH/tileObject.getWidth()) + 1;

	std::vector<GameInanimateObject> tileObjects = {};
	for (int i=-1; i<tileCount; i++) {
		GameInanimateObject obj = GameInanimateObject(&tileObject);
		obj.setPosition(Vector2{ i * tileObject.getWidth(), world.getGroundLevel() - tileObject.getHeight() });
		tileObjects.push_back(obj);
	}


	GameCharacterObject wizard = GameCharacterObject({
				AnimationFrames{
				 	{
						LoadTexture("./assets/characters/old-wizard/idle/1.png"),
						LoadTexture("./assets/characters/old-wizard/idle/2.png"),
						LoadTexture("./assets/characters/old-wizard/idle/3.png"),
						LoadTexture("./assets/characters/old-wizard/idle/4.png"),
						LoadTexture("./assets/characters/old-wizard/idle/5.png"),
						LoadTexture("./assets/characters/old-wizard/idle/6.png"),
						LoadTexture("./assets/characters/old-wizard/idle/7.png")
					},
					0.0f
				},
			AnimationFrames{
			{
				LoadTexture("./assets/characters/old-wizard/fall/1.png"),
				LoadTexture("./assets/characters/old-wizard/fall/2.png"),
			},
				0.0f
			}
			}, 1, Direction::RIGHT);

	wizard.setOnGround(false);
	wizard.setState(CHARACTER_STATE::FALL);

	GameLoop gameLoop = GameLoop(&world, tileObjects, &wizard, &physics);	

	while (!WindowShouldClose()) {
		float deltaTime = GetFrameTime();

		gameLoop.handleWizardState(deltaTime);

		currentFrameTime += deltaTime;
		if (currentFrameTime >= FRAME_DELAY) {
			wizard.animate();  
			currentFrameTime = 0;
		}

		BeginDrawing();
			ClearBackground(BLACK);
			for (GameInanimateObject tileObject : tileObjects) {
				  tileObject.draw();
			}
			wizard.draw();
		EndDrawing();
	}

	CloseWindow();
	tileObject.unload();
	return 0;
}
