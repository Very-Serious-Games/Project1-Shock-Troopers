#include "Enemy_InfantrySoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"


Enemy_InfantrySoldier::Enemy_InfantrySoldier(int x, int y) : Enemy(x, y) {

	//Spawn animations
	spawnAnimLeft.PushBack({});
	spawnAnimRight.PushBack({});
	

	//Death Animation
	deathAnim.PushBack({436, 828, 42, 53 }); //41x53?
	deathAnim.PushBack({478, 828, 42, 53});
	deathAnim.PushBack({520, 828, 42, 53});
	deathAnim.PushBack({562, 828, 42, 53});
	deathAnim.PushBack({604, 828, 42, 53});  //604?
	deathAnim.PushBack({646, 828, 42, 53});
	deathAnim.PushBack({688, 828, 42, 53});
	leftDeathAnim.PushBack({51, 827, 54, 54});
	leftDeathAnim.PushBack({104, 827, 54, 54});
	leftDeathAnim.PushBack({158, 827, 54, 54});
	leftDeathAnim.PushBack({212, 827, 54, 54});
	leftDeathAnim.PushBack({266, 827, 54, 54});
	leftDeathAnim.PushBack({320, 827, 54, 54});
	leftDeathAnim.PushBack({374, 827, 54, 54});
	rightDeathAnim.PushBack({740, 827, 54, 54});
	rightDeathAnim.PushBack({795, 827, 54, 54});
	rightDeathAnim.PushBack({850, 827, 54, 54});
	rightDeathAnim.PushBack({905, 827, 54, 54});
	rightDeathAnim.PushBack({960, 827, 54, 54});   //54+1 o 54 entre x i x
	rightDeathAnim.PushBack({1015, 827, 54, 54});
	rightDeathAnim.PushBack({1070, 827, 54, 54});
	//Pink Death Animation
	pinkDeathAnim.PushBack({50, 765, 42, 53});  //41?
	pinkDeathAnim.PushBack({92, 765, 42, 53 });
	pinkDeathAnim.PushBack({134, 765, 42, 53});
	pinkDeathAnim.PushBack({176, 765, 42, 53});
	pinkDeathAnim.PushBack({218, 765, 42, 53});
	pinkDeathAnim.PushBack({260, 765, 42, 53});
	pinkDeathAnim.PushBack({302, 765, 42, 53});
	leftPinkDeathAnim.PushBack({});
	rightPinkDeathAnim.PushBack({});

	//Idle animations
	idleUpAnim.PushBack({});
	idleDownAnim.PushBack({});
	idleLeftAnim.PushBack({});
	idleRightAnim.PushBack({});
	idleUpLeftAnim.PushBack({});
	idleUpRightAnim.PushBack({});
	idleDownLeftAnim.PushBack({});
	idleDownRightAnim.PushBack({});
	//no need to speed bc this animation has only one frame

	//Movement
	upAnim.PushBack({});
	downAnim.PushBack({});
	leftAnim.PushBack({});
	rightAnim.PushBack({});
	upLeftAnim.PushBack({});
	upRightAnim.PushBack({});
	downLeftAnim.PushBack({});
	downRightAnim.PushBack({});

	//Gun
	//Gun movement
	gunUpAnim.PushBack({});
	gunUpAnim.PushBack({});
	gunUpAnim.PushBack({});
	gunUpAnim.PushBack({});
	gunDownAnim.PushBack({});
	gunDownAnim.PushBack({});
	gunDownAnim.PushBack({});
	gunDownAnim.PushBack({});
	gunDownAnim.PushBack({});
	gunDownAnim.PushBack({});
	gunDownAnim.PushBack({});
	gunDownAnim.PushBack({});
	gunLeftAnim.PushBack({});
	gunLeftAnim.PushBack({});
	gunLeftAnim.PushBack({});
	gunLeftAnim.PushBack({});
	gunLeftAnim.PushBack({});
	gunLeftAnim.PushBack({});
	gunLeftAnim.PushBack({});
	gunLeftAnim.PushBack({});
	gunRightAnim.PushBack({});
	gunRightAnim.PushBack({});
	gunRightAnim.PushBack({});
	gunRightAnim.PushBack({});
	gunRightAnim.PushBack({});
	gunRightAnim.PushBack({});
	gunRightAnim.PushBack({});
	gunRightAnim.PushBack({});
	gunUpLeftAnim.PushBack({});
	gunUpLeftAnim.PushBack({});
	gunUpLeftAnim.PushBack({});
	gunUpLeftAnim.PushBack({});
	gunUpRightAnim.PushBack({});
	gunUpRightAnim.PushBack({});
	gunUpRightAnim.PushBack({});
	gunUpRightAnim.PushBack({});
	gunDownLeftAnim.PushBack({});
	gunDownLeftAnim.PushBack({});
	gunDownLeftAnim.PushBack({});
	gunDownLeftAnim.PushBack({});
	gunDownLeftAnim.PushBack({});
	gunDownLeftAnim.PushBack({});
	gunDownLeftAnim.PushBack({});
	gunDownLeftAnim.PushBack({});
	gunDownRightAnim.PushBack({});
	gunDownRightAnim.PushBack({});
	gunDownRightAnim.PushBack({});
	gunDownRightAnim.PushBack({});
	gunDownRightAnim.PushBack({});
	gunDownRightAnim.PushBack({});
	gunDownRightAnim.PushBack({});
	gunDownRightAnim.PushBack({});
	//Gun Idle
	gunIdleUpAnim.PushBack({});
	gunIdleDownAnim.PushBack({});
	gunIdleLeftAnim.PushBack({});
	gunIdleRightAnim.PushBack({});
	gunIdleUpLeftAnim.PushBack({});
	gunIdleUpRightAnim.PushBack({});
	gunIdleDownLeftAnim.PushBack({});
	gunIdleDownRightAnim.PushBack({});
	//no need to speed these animations since they only have 1 frame
	
	//Gun hit
	gunHitRightAnim.PushBack({});
	gunHitRightAnim.PushBack({});
	gunHitRightAnim.PushBack({});
	gunHitRightAnim.PushBack({});
	gunHitRightAnim.PushBack({});
	gunHitRightAnim.PushBack({});
	gunHitRightAnim.PushBack({});
	gunHitRightAnim.PushBack({});
	gunHitLeftAnim.PushBack({});
	gunHitLeftAnim.PushBack({});
	gunHitLeftAnim.PushBack({});
	gunHitLeftAnim.PushBack({});
	gunHitLeftAnim.PushBack({});
	gunHitLeftAnim.PushBack({});
	gunHitLeftAnim.PushBack({});
	gunHitLeftAnim.PushBack({});

	//Knife movement
	knifeUpAnim.PushBack({});
	knifeUpAnim.PushBack({});
	knifeUpAnim.PushBack({});
	knifeUpAnim.PushBack({});
	knifeDownAnim.PushBack({});
	knifeDownAnim.PushBack({});
	knifeLeftAnim.PushBack({});
	knifeLeftAnim.PushBack({});
	knifeLeftAnim.PushBack({});
	knifeLeftAnim.PushBack({});
	knifeRightAnim.PushBack({});
	knifeRightAnim.PushBack({});
	knifeRightAnim.PushBack({});
	knifeRightAnim.PushBack({});
	knifeUpLeftAnim.PushBack({});
	knifeUpLeftAnim.PushBack({});
	knifeUpLeftAnim.PushBack({});
	knifeUpLeftAnim.PushBack({});
	knifeUpRightAnim.PushBack({});
	knifeUpRightAnim.PushBack({});
	knifeUpRightAnim.PushBack({});
	knifeUpRightAnim.PushBack({});
	knifeDownLeftAnim.PushBack({});
	knifeDownLeftAnim.PushBack({});
	knifeDownLeftAnim.PushBack({});
	knifeDownLeftAnim.PushBack({});
	knifeDownRightAnim.PushBack({});
	knifeDownRightAnim.PushBack({});
	knifeDownRightAnim.PushBack({});
	knifeDownRightAnim.PushBack({});
	//knife Idle
	//no need to speed these animations bc they only have one frame
	knifeIdleUpAnim.PushBack({});
	knifeIdleDownAnim.PushBack({});
	knifeIdleLeftAnim.PushBack({});
	knifeIdleRightAnim.PushBack({});
	knifeIdleUpLeftAnim.PushBack({});
	knifeIdleUpRightAnim.PushBack({});
	knifeIdleDownLeftAnim.PushBack({});
	knifeIdleDownRightAnim.PushBack({});
	//knife hit
	knifeHitRightAnim.PushBack({});
	knifeHitRightAnim.PushBack({});
	knifeHitRightAnim.PushBack({});
	knifeHitRightAnim.PushBack({});
	knifeHitRightAnim.PushBack({});
	knifeHitRightAnim.PushBack({});
	knifeHitLeftAnim.PushBack({});
	knifeHitLeftAnim.PushBack({});
	knifeHitLeftAnim.PushBack({});
	knifeHitLeftAnim.PushBack({});
	knifeHitLeftAnim.PushBack({});
	knifeHitLeftAnim.PushBack({});

	//falling soldiers
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });
	fallLeftAnim.PushBack({ 50, 829, 62, 67 });

	//Hiding half body sodier
	hidingIdleRightAnim.PushBack({});
	hidingIdleLeftAnim.PushBack({});
	hidingDownAnim.PushBack({});
	hidingHalfLeftAnim.PushBack({});
	hidingHalfRightAnim.PushBack({});
	hidingLeftAnim.PushBack({});
	hidingRightAnim.PushBack({});

	//Hands in the head soldier
	headHandsLeftAnim.PushBack({});
	headHandsRightAnim.PushBack({});

	//General soldier with binoculars
	generalAnim.PushBack({});
	generalAnim.PushBack({});
	generalAnim.PushBack({});
	generalAnim.PushBack({});
	generalAnim.PushBack({});
	generalAnim.PushBack({});
	generalAnim.PushBack({});
	generalAnim.PushBack({});
	generalAnim.PushBack({});
	generalAnim.PushBack({});
	generalAnim.PushBack({});
	generalAnim.PushBack({});
	generalAnim.PushBack({});

	//Flying soldiers
	flyingSoldiersLeftAnim.PushBack({});
	flyingSoldiersDownLeftAnim.PushBack({});
	flyingSoldiersRightAnim.PushBack({});
	flyingSoldiersDownRightAnim.PushBack({});

	//Bazooka soldiers
	bazookaDownAnim.PushBack({});
	bazookaRightAnim.PushBack({});
	bazookaLeftAnim.PushBack({});
	bazookaUpLeftAnim.PushBack({});
	bazookaUpRightAnim.PushBack({});
	bazookaHalfRightAnim.PushBack({});
	bazookaHalfLeftAnim.PushBack({});

	//Throwing grenade soldiers
	grenadeSoldierLeftAnim.PushBack({});
	grenadeSoldierLeftAnim.PushBack({});
	grenadeSoldierLeftAnim.PushBack({});
	grenadeSoldierLeftAnim.PushBack({});
	grenadeSoldierLeftAnim.PushBack({});
	grenadeSoldierDownLeftAnim.PushBack({});
	grenadeSoldierDownLeftAnim.PushBack({});
	grenadeSoldierDownLeftAnim.PushBack({});
	grenadeSoldierDownLeftAnim.PushBack({});
	grenadeSoldierDownLeftAnim.PushBack({});
	grenadeSoldierUpLeftAnim.PushBack({});
	grenadeSoldierUpLeftAnim.PushBack({});
	grenadeSoldierUpLeftAnim.PushBack({});
	grenadeSoldierUpLeftAnim.PushBack({});
	grenadeSoldierUpLeftAnim.PushBack({});
	grenadeSoldierRightAnim.PushBack({});
	grenadeSoldierRightAnim.PushBack({});
	grenadeSoldierRightAnim.PushBack({});
	grenadeSoldierRightAnim.PushBack({});
	grenadeSoldierRightAnim.PushBack({});
	grenadeSoldierDownRightAnim.PushBack({});
	grenadeSoldierDownRightAnim.PushBack({});
	grenadeSoldierDownRightAnim.PushBack({});
	grenadeSoldierDownRightAnim.PushBack({});
	grenadeSoldierUpRightAnim.PushBack({});
	grenadeSoldierUpRightAnim.PushBack({});
	grenadeSoldierUpRightAnim.PushBack({});
	grenadeSoldierUpRightAnim.PushBack({});
	grenadeSoldierUpRightAnim.PushBack({});

	//Final boss soldier
	headBossSoldierAnim.PushBack({});
	grenadeBossSoldierAnim.PushBack({});
	grenadeBossSoldierAnim.PushBack({});
	grenadeBossSoldierAnim.PushBack({});
	grenadeBossSoldierAnim.PushBack({});
	grenadeBossSoldierAnim.PushBack({});
	grenadeBossSoldierAnim.PushBack({});
	grenadeBossSoldierRightAnim.PushBack({});
	grenadeBossSoldierRightAnim.PushBack({});
	grenadeBossSoldierRightAnim.PushBack({});
	grenadeBossSoldierRightAnim.PushBack({});
	grenadeBossSoldierRightAnim.PushBack({});
	grenadeBossSoldierLeftAnim.PushBack({});
	grenadeBossSoldierLeftAnim.PushBack({});
	grenadeBossSoldierLeftAnim.PushBack({});
	grenadeBossSoldierLeftAnim.PushBack({});
	grenadeBossSoldierLeftAnim.PushBack({});
	bossSoldierIdleAnim.PushBack({});
	upBossSoldierAnim.PushBack({});
	upBossSoldierAnim.PushBack({});
	upBossSoldierAnim.PushBack({});
	upBossSoldierAnim.PushBack({});
	upBossSoldierAnim.PushBack({});
	upBossSoldierAnim.PushBack({});
	upBossSoldierAnim.PushBack({});
	upBossSoldierAnim.PushBack({});
	upBossSoldierAnim.PushBack({});  


	// TODO cambiar tamaño collider
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);

	// TODO add animations

}

void Enemy_InfantrySoldier::Update() {

	StateMachine();

	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_InfantrySoldier::deathAnimation() {
	//currentAnim = &deathAnim;
}

void Enemy_InfantrySoldier::idleAnimation() {
	//currentAnim = &idleAnim;
}

void Enemy_InfantrySoldier::spawnAnimation() {
	//currentAnim = &spawnAnim;
}

void Enemy_InfantrySoldier::moveAnimation() {
	//currentAnim = &moveAnim;
}

void Enemy_InfantrySoldier::attackAnimation() {
	//currentAnim = &attackAnim;
}

void Enemy_InfantrySoldier::StateMachine() {
	switch (state) {
		case Enemy_State::SPAWN:

			spawnAnimation();

			break;

		case Enemy_State::IDLE:

			idleAnimation();

			break;

		case Enemy_State::ATTACK:

			attackAnimation();

			Attack();

			break;

		case Enemy_State::DEATH:

			deathAnimation();

			if (deathAnimDelay == 0) {
				pendingToDelete = true;
				LOG("pendingToDelete enemy");
			}

			deathAnimDelay--;

			break;

		case Enemy_State::MOVE:

			moveAnimation();

			move();

			break;

	}

}

// 3 diferent states for attack with diferent percentages of chance to happen
// 1. normal attack
// 2. mele attack
// 3. no attack
void Enemy_InfantrySoldier::Attack() {
	// get random number between with 10%, 30, 60% chance to happen
	int attackType = rand() % 10; // generate a random number between 0 and 9
	if (attackType < 6) { // 60% chance to do a melee attack
		LOG("Enemy: Infantry Soldier normal attack");
		// TODO add normal attack
	} else if (attackType < 4) { // 30% chance to do a normal attack
		LOG("Enemy: Infantry Soldier mele attack");
		// TODO add melee attack
	} else { // 10% chance to not attack
		LOG("Enemy: Infantry Soldier no attack");
		// do nothing
	}
	
}

void Enemy_InfantrySoldier::move() {

}
