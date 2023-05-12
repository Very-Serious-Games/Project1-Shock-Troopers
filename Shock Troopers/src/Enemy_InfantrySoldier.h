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

private:
	

	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation spawnAnimRight;
	Animation spawnAnimLeft;

	Animation deathAnim;

	Animation upAnim;
	Animation downAnim;
	Animation leftAnim;
	Animation rightAnim;
	Animation upLeftAnim;
	Animation upRightAnim;
	Animation downLeftAnim;
	Animation downRightAnim;

	Animation idleUpAnim;
	Animation idleDownAnim;
	Animation idleLeftAnim;
	Animation idleRightAnim;
	Animation idleUpLeftAnim;
	Animation idleUpRightAnim;
	Animation idleDownLeftAnim;
	Animation idleDownRightAnim;

	//Gun
	Animation gunUpAnim;
	Animation gunDownAnim;
	Animation gunLeftAnim;
	Animation gunRightAnim;
	Animation gunUpLeftAnim;
	Animation gunUpRightAnim;
	Animation gunDownLeftAnim;
	Animation gunDownRightAnim;

	Animation gunIdleUpAnim;
	Animation gunIdleDownAnim;
	Animation gunIdleLeftAnim;
	Animation gunIdleRightAnim;
	Animation gunIdleUpLeftAnim;
	Animation gunIdleUpRightAnim;
	Animation gunIdleDownLeftAnim;
	Animation gunIdleDownRightAnim;

	//knife
	Animation knifeUpAnim;
	Animation knifeDownAnim;
	Animation knifeLeftAnim;
	Animation knifeRightAnim;
	Animation knifeUpLeftAnim;
	Animation knifeUpRightAnim;
	Animation knifeDownLeftAnim;
	Animation knifeDownRightAnim;

	Animation knifeIdleUpAnim;
	Animation knifeIdleDownAnim;
	Animation knifeIdleLeftAnim;
	Animation knifeIdleRightAnim;
	Animation knifeIdleUpLeftAnim;
	Animation knifeIdleUpRightAnim;
	Animation knifeIdleDownLeftAnim;
	Animation knifeIdleDownRightAnim;
	

};

#endif // __ENEMY_INFANTRYSOLDIER_H__