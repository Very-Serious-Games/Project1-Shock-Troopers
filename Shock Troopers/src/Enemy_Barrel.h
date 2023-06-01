#ifndef __ENEMY_BARREL_H__
#define __ENEMY_BARREL_H__

#include "Enemy.h"
#include "Path.h"
#include "Module.h"

class Enemy_Barrel : public Enemy {
public:

	Enemy_Barrel(int x, int y);


	void Update() override;

	void deathAnimation() override;

	void idleAnimation() override;

	void spawnAnimation() override;

	void StateMachine() override;

	void OnCollision(Collider* collider) override;

private:

	Path path;

	SDL_Texture* textureBarrel = nullptr;

};

#endif