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

	void brokenAnimation();

	void idlebrokenAnimation();

	void StateMachine() override;

	void OnCollision(Collider* collider) override;

private:

	Path path;

	SDL_Texture* textureBridge = nullptr;

};

#endif // __ENEMY_BRIDGE_H__