#ifndef __ENEMY_INFANTRYSOLDIER_H__
#define __ENEMY_INFANTRYSOLDIER_H__

#include "Enemy.h"
#include "Path.h"

#pragma once
class Enemy_InfantrySoldier : public Enemy {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_InfantrySoldier(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void deathAnimation() override;

	void idleAnimation() override;

	void spawnAnimation() override;

	void moveAnimation() override;

	void attackAnimation() override;

	void StateMachine() override;

	void Attack() override;

	void move() override;

private:
	

	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation spawnAnimRight;
	Animation spawnAnimLeft;

	Animation upAnim;
	Animation downAnim;
	Animation leftAnim;
	Animation rightAnim;
	Animation upLeftAnim;
	Animation upRightAnim;
	Animation downLeftAnim;
	Animation downRightAnim;

	Animation deathAnim;

	Animation idleUpAnim;
	Animation idleDownAnim;
	Animation idleLeftAnim;
	Animation idleRightAnim;
	Animation idleUpLeftAnim;
	Animation idleUpRightAnim;
	Animation idleDownLeftAnim;
	Animation idleDownRightAnim;

};

#endif // __ENEMY_INFANTRYSOLDIER_H__