#ifndef __ENEMY_SANDBAG_H__
#define __ENEMY_SANDBAG_H__

#include "Enemy.h"
#include "Path.h"
#include "Module.h"

class Enemy_Sandbag : public Enemy {
public:

	Enemy_Sandbag(int x, int y);


	void Update() override;

	void deathAnimation() override;

	void idleAnimation() override;

	void spawnAnimation() override;

	void brokenAnimation();

	void idlebrokenAnimation();

	void StateMachine() override;

	void OnCollision(Collider* collider) override;

private:

	Path path;

	SDL_Texture* textureSandbag = nullptr;

};

#endif