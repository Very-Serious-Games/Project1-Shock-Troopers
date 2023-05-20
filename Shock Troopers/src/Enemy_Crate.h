#ifndef __ENEMY_CRATE_H__
#define __ENEMY_CRATE_H__

#include "Enemy.h"
#include "Path.h"
#include "Module.h"

class Enemy_Crate : public Enemy {
public:

	Enemy_Crate(int x, int y);


	void Update() override;

	void deathAnimation() override;

	void idleAnimation() override;

	void spawnAnimation() override;

	void StateMachine() override;

private:

	Path path;

	SDL_Texture* textureCrate = nullptr;

};

#endif