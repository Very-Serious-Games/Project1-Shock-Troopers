#ifndef __ENEMY_INFANTRYSOLDIER_H__
#define __ENEMY_INFANTRYSOLDIER_H__

#include "Enemy.h"
#include "Path.h"
		
#pragma once
class Enemy_InfantrySoldier : public Enemy {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_InfantrySoldier(int x, int y, bool isFalling);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void deathAnimation() override;

	void idleAnimation(int direction);

	int spawnAnimation(int direction);

	void moveAnimation(int direction);

	void attackAnimation(int direction) override;

	bool PlayerIsNear() override;

	bool PlayerIsAttackRange() override;

	void attackMeleAnimation(int direction);

	void StateMachine() override;

	void Attack() override;

	void Shoot();

	void Knife();

	void move() override;

private:

	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation spawnAnimRight;
	Animation spawnAnimLeft;

	//Death Animations
	Animation leftDeathAnim;
	Animation rightDeathAnim;
	Animation deathAnim;
	
	//Gun
	//movement
	Animation gunUpAnim;
	Animation gunDownAnim;
	Animation gunLeftAnim;
	Animation gunRightAnim;
	Animation gunUpLeftAnim;
	Animation gunUpRightAnim;
	Animation gunDownLeftAnim;
	Animation gunDownRightAnim;

	//idle
	Animation gunIdleUpAnim;
	Animation gunIdle2UpAnim;
	Animation gunIdleDownAnim;
	Animation gunIdle2DownAnim;
	Animation gunIdlePointDownAnim;
	Animation gunIdleLeftAnim;
	Animation gunIdleRightAnim;
	Animation gunIdleUpLeftAnim;
	Animation gunIdleUpRightAnim;
	Animation gunIdleDownLeftAnim;
	Animation gunIdleDownRightAnim;

	//idle pointing
	Animation gunPointUp;
	Animation gunPointDown;
	Animation gunPointLeft;
	Animation gunPointRight;
	Animation gunPointUpRight;
	Animation gunPointUpLeft;
	Animation gunPointDownLeft;
	Animation gunPointDownRight;

	//gun hit
	Animation gunHitRightAnim;
	Animation gunHitLeftAnim;
	Animation gunHitUpAnim;
	Animation gunHitUpLeftAnim;
	Animation gunHitUpRightAnim;
	Animation gunHitDownAnim;
	Animation gunHitDownRightAnim;
	Animation gunHitDownLeftAnim;

	//falling soldiers
	Animation fallRightAnim;
	Animation fallLeftAnim;

	bool playOnce = false;
	int direction;
};

#endif // __ENEMY_INFANTRYSOLDIER_H__