#include "game-loop.hpp"
#include <raylib.h>

GameLoop* GameLoop::handleWizardState(float deltaTime) {
	  switch(wizard->getCharacterState()) {
			case FALL:  
				
				if (!physics->isColliding(tileObjects, wizard)) {
					physics->freeFall(wizard, deltaTime);
					break;
				}

				wizard->setOnGround(true);	  
				Vector2 velocity = wizard->getVelocity();
				velocity.y = 0;
				wizard->setVelocity(velocity);
				wizard->setState(CHARACTER_STATE::IDLE);

				break;
		}

		return this;
}

