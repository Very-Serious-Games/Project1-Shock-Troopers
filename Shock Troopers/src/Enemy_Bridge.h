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

private:

	Path path;

	SDL_Texture* texture = nullptr;

};

#endif // __ENEMY_BRIDGE_H__