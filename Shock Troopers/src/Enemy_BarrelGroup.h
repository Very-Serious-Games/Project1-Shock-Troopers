#ifndef __ENEMY_BARRELGROUP_H__
#define __ENEMY_BARRELGROUP_H__

#include "Enemy.h"
#include "Path.h"
#include "Module.h"

class Enemy_BarrelGroup : public Enemy {
public:

	Enemy_BarrelGroup(int x, int y);


	void Update() override;

	void deathAnimation() override;

	void idleAnimation() override;

	void spawnAnimation() override;

	void StateMachine() override;

	void OnCollision(Collider* collider) override;

private:

	Path path;

	SDL_Texture* textureBarrelGroup = nullptr;

};

#endif