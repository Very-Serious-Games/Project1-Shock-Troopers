#ifndef __ENEMY_BRIDGE_H__
#define __ENEMY_BRIDGE_H__

#include "Enemy.h"
#include "Path.h"
#include "Module.h"

class Enemy_Bridge : public Enemy {
public:

	Enemy_Bridge(int x, int y);


	void Update() override;

	void deathAnimation() override;

	void idleAnimation() override;

	void spawnAnimation() override;

	void StateMachine() override;

protected:

	Path path;

	SDL_Texture* textureBridge = nullptr;

};

#endif // __ENEMY_BRIDGE_H__