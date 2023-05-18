#ifndef __ENEMY_FLYINGBATTLESHIP_H__
#define __ENEMY_FLYINGBATTLESHIP_H__

#include "Enemy.h"
#include "Path.h"
#include "Module.h"

class Enemy_FlyingBattleship : public Enemy {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_FlyingBattleship(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void deathAnimation() override;

	void idleAnimation() override;

	void spawnAnimation() override;

	void StateMachine() override;

	void Attack() override;

private:
	// The path that will define the position in the world
	Path path;

	SDL_Texture* texture = nullptr;

};

#endif // __ENEMY_FLYINGBATTLESHIP_H__