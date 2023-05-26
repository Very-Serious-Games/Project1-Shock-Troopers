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

	//Death Animations
	Animation deathAnim;
	Animation leftDeathAnim;
	Animation rightDeathAnim;
	//Pink Death Animations
	Animation pinkDeathAnim;
	Animation leftPinkDeathAnim;
	Animation rightPinkDeathAnim;

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

	Animation gunHitRightAnim;
	Animation gunHitLeftAnim;

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

	Animation knifeHitRightAnim;
	Animation knifeHitLeftAnim; 

	//falling soldiers
	Animation fallRightAnim;
	Animation fallLeftAnim;

	//Hiding half body soldier
	Animation hidingIdleRightAnim;
	Animation hidingIdleLeftAnim;
	Animation hidingDownAnim;
	Animation hidingHalfLeftAnim;
	Animation hidingHalfRightAnim;
	Animation hidingLeftAnim;
	Animation hidingRightAnim;

	//Hands in the head soldier
	Animation headHandsLeftAnim;
	Animation headHandsRightAnim;
	
	//General soldier binoculars behind barrels
	Animation generalAnim;

	//Flying soldiers
	Animation flyingSoldiersRightAnim;
	Animation flyingSoldiersDownRightAnim;
	Animation flyingSoldiersLeftAnim;
	Animation flyingSoldiersDownLeftAnim;

	//Bazooka soldiers
	Animation bazookaDownAnim;
	Animation bazookaRightAnim;
	Animation bazookaLeftAnim;
	Animation bazookaUpRightAnim;
	Animation bazookaUpLeftAnim;
	Animation bazookaHalfLeftAnim;
	Animation bazookaHalfRightAnim;

	//Throwing throwing grenade soldier
	Animation grenadeSoldierRightAnim;
	Animation grenadeSoldierDownRightAnim;
	Animation grenadeSoldierLeftAnim;
	Animation grenadeSoldierDownLeftAnim;
	Animation grenadeSoldierUpLeftAnim;
	Animation grenadeSoldierUpRightAnim;

	//Final boss soldier
	Animation headBossSoldierAnim;
	Animation grenadeBossSoldierAnim;
	Animation grenadeBossSoldierRightAnim;
	Animation grenadeBossSoldierLeftAnim;
	Animation bossSoldierIdleAnim;
	Animation upBossSoldierAnim;


};

#endif // __ENEMY_INFANTRYSOLDIER_H__