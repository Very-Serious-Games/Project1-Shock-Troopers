#ifndef __ENEMY_TANKBOSS_H__
#define __ENEMY_TANKBOSS_H__

#include "Enemy.h"
#include "Path.h"
#include "Module.h"

class Enemy_TankBoss : public Enemy {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_TankBoss(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void deathAnimation() override;

	void idleAnimation() override;

	void StateMachine() override;

	void Attack() override;

	void canon();

	void shot();

	void grenade();

private:
	// The path that will define the position in the world
	Path path;

	SDL_Texture* textureTankBoss = nullptr;

};

#endif // __ENEMY_TANKBOSS_H__