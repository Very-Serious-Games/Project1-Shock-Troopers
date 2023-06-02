#ifndef __ENEMY_TANK_H__
#define __ENEMY_TANK_H__

#include "Enemy.h"
#include "Path.h"
#include "Module.h"

class Enemy_Tank : public Enemy {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Tank(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void deathAnimation() override;

	void idleAnimation(int direction) override;

	void hitAnimation(int direction);

	void StateMachine() override;

	void Attack() override;

private:
	// The path that will define the position in the world
	Path path;

	bool isHitted = false;

	Animation moveAnim;

	Animation hitMoveAnim;

	Animation idleAnimUp;
	Animation idleAnimDown;
	Animation idleAnimLeft;
	Animation idleAnimRight;
	Animation idleAnimDownLeft;
	Animation idleAnimDownRight;
	Animation idleAnimUpLeft;
	Animation idleAnimUpRight;

	Animation hitIdleAnimUp;
	Animation hitIdleAnimDown;
	Animation hitIdleAnimLeft;
	Animation hitIdleAnimRight;
	Animation hitIdleAnimDownLeft;
	Animation hitIdleAnimDownRight;
	Animation hitIdleAnimUpLeft;
	Animation hitIdleAnimUpRight;

	Animation deathAnim;

};

#endif // __ENEMY_TANK_H__