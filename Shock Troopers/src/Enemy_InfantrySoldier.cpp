#include "Enemy_InfantrySoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"


Enemy_InfantrySoldier::Enemy_InfantrySoldier(int x, int y) : Enemy(x, y) {

	//Spawn animations
	spawnAnimLeft.PushBack({});
	spawnAnimRight.PushBack({});
	
	//Death Animation
	deathAnim.PushBack({436, 828, 42, 53}); //41x53?
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
	fallRightAnim.PushBack({ 50, 33, 62, 67 });
	fallRightAnim.PushBack({ 113, 33, 62, 67 });
	fallRightAnim.PushBack({ 176, 33, 62, 67 });
	fallRightAnim.PushBack({ 239, 33, 62, 67 });
	fallRightAnim.PushBack({ 302, 33, 62, 67 });
	fallRightAnim.PushBack({ 365, 33, 62, 67 });
	fallRightAnim.PushBack({ 428, 33, 62, 67 });
	fallRightAnim.PushBack({ 491, 33, 62, 67 });
	fallRightAnim.PushBack({ 554, 33, 62, 67 });
	fallRightAnim.PushBack({ 617, 33, 62, 67 });
	fallRightAnim.PushBack({ 680, 33, 62, 67 });
	fallRightAnim.PushBack({ 743, 33, 62, 67 });
	fallRightAnim.PushBack({ 806, 33, 62, 67 });
	fallRightAnim.PushBack({ 869, 33, 62, 67 });
	fallRightAnim.PushBack({ 932, 33, 62, 67 });
	fallRightAnim.PushBack({ 995, 33, 62, 67 });

	fallRightAnim.PushBack({ 50, 103, 62, 67 });
	fallRightAnim.PushBack({ 113, 103, 62, 67 });
	fallRightAnim.PushBack({ 176, 103, 62, 67 });
	fallRightAnim.PushBack({ 239, 103, 62, 67 });
	fallRightAnim.PushBack({ 302, 103, 62, 67 });
	fallRightAnim.PushBack({ 365, 103, 62, 67 });
	fallRightAnim.PushBack({ 428, 103, 62, 67 });
	fallRightAnim.PushBack({ 491, 103, 62, 67 });
	fallRightAnim.PushBack({ 554, 103, 62, 67 });
	fallRightAnim.PushBack({ 617, 103, 62, 67 });
	fallRightAnim.PushBack({ 680, 103, 62, 67 });
	fallRightAnim.PushBack({ 743, 103, 62, 67 });
	fallRightAnim.PushBack({ 806, 103, 62, 67 });
	fallRightAnim.PushBack({ 869, 103, 62, 67 });
	fallRightAnim.PushBack({ 932, 103, 62, 67 });
	fallRightAnim.PushBack({ 995, 103, 62, 67 });

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

	path.PushBack({ 0.0f, 0.0f }, 1000, &fallLeftAnim);
	path.PushBack({ 0.0f, 0.0f }, 1000, &fallRightAnim);

	// AAA
	fallRightAnim.speed = 0.1f;
	fallLeftAnim.speed = 0.1f;

}

void Enemy_InfantrySoldier::Update() {

	StateMachine();

	path.Update();
	position = spawnPos + relativePosition;
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

int Enemy_InfantrySoldier::GetPlayerDirection() {
	// Get the player position
	fPoint playerPos = App->player->position;

	// Calculate the direction vector from enemy position to player position
	fPoint enemyPos = position;
	fPoint direction = playerPos - enemyPos;

	// Determine the player direction based on the direction vector
	int playerDirection = 0;

	if (direction.y < 0) {
		// Player is above the enemy
		if (direction.x < 0) {
			// Player is above and to the left of the enemy
			playerDirection = 2; // Up-Left
		}
		else if (direction.x > 0) {
			// Player is above and to the right of the enemy
			playerDirection = 1; // Up-Right
		}
		else {
			// Player is directly above the enemy
			playerDirection = 8; // Up
		}
	}
	else if (direction.y > 0) {
		// Player is below the enemy
		if (direction.x < 0) {
			// Player is below and to the left of the enemy
			playerDirection = 4; // Down-Left
		}
		else if (direction.x > 0) {
			// Player is below and to the right of the enemy
			playerDirection = 3; // Down-Right
		}
		else {
			// Player is directly below the enemy
			playerDirection = 7; // Down
		}
	}
	else {
		// Player is at the same height as the enemy
		if (direction.x < 0) {
			// Player is to the left of the enemy
			playerDirection = 6; // Left
		}
		else if (direction.x > 0) {
			// Player is to the right of the enemy
			playerDirection = 5; // Right
		}
	}

	// Return the player direction
	return playerDirection;

}

void Enemy_InfantrySoldier::deathAnimation() {
	currentAnim = &deathAnim;
}

void Enemy_InfantrySoldier::idleAnimation(int direction) {
	switch (direction) {
		case 1: //UR
			currentAnim = &idleUpRightAnim;
			break;
		case 2: //UL
			currentAnim = &idleUpLeftAnim;
			break;
		case 3: //DR
			currentAnim = &idleDownRightAnim;
			break;
		case 4: //DL
			currentAnim = &idleDownLeftAnim;
			break;
		case 5: //R
			currentAnim = &idleRightAnim;
			break;
		case 6: //L
			currentAnim = &idleLeftAnim;
			break;
		case 7: //D
			currentAnim = &idleDownAnim;
			break;
		case 8: //U
			currentAnim = &idleUpAnim;
			break;
		}

}

void Enemy_InfantrySoldier::spawnAnimation(int direction) {
	switch (direction) {
	case 1: //L
		currentAnim = &spawnAnimLeft;
		break;
	case 2: //R
		currentAnim = &spawnAnimRight;
		break;
	}
}

void Enemy_InfantrySoldier::moveAnimation(int direction) {
	switch (direction) {
		case 1: //UR
			currentAnim = &upRightAnim;
			break;
		case 2: //UL
			currentAnim = &upLeftAnim;
			break;
		case 3: //DR
			currentAnim = &downRightAnim;
			break;
		case 4: //DL
			currentAnim = &downLeftAnim;
			break;
		case 5: //R
			currentAnim = &rightAnim;
			break;
		case 6: //L
			currentAnim = &leftAnim;
			break;
		case 7: //D
			currentAnim = &downAnim;
			break;
		case 8: //U
			currentAnim = &upAnim;
			break;
	}
}

void Enemy_InfantrySoldier::attackAnimation() {
	currentAnim = &attackAnim;
}

void Enemy_InfantrySoldier::StateMachine() {
	switch (state) {
		case Enemy_State::SPAWN:

			spawnAnimation(GetPlayerDirection());

			if (true /*condition to idle*/) {
				state = Enemy_State::IDLE;
			}

			LOG("SPAWN STATE");

			break;

		case Enemy_State::IDLE:

			idleAnimation(GetPlayerDirection());

			if (PlayerIsNear()) {
				state = Enemy_State::MOVE;
			}

			LOG("IDLE STATE");

			break;

		case Enemy_State::ATTACK:

			attackAnimation();

			Attack();

			LOG("ATTACK STATE");

			break;

		case Enemy_State::DEATH:

			deathAnimation();

			if (deathAnimDelay == 0) {
				pendingToDelete = true;
				LOG("pendingToDelete enemy");
			}

			deathAnimDelay--;

			LOG("DEATH STATE");

			break;

		case Enemy_State::MOVE:

			moveAnimation(GetPlayerDirection());

			move();

			if (PlayerIsMele()) {
				state = Enemy_State::ATTACK;
			}

			if (!PlayerIsNear()) {
				state = Enemy_State::IDLE;
			}

			LOG("MOVE STATE");

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

		Knife();

		LOG("Enemy: Infantry Soldier normal attack");

	} else if (attackType < 4) { // 30% chance to do a normal attack

		Shoot();

		LOG("Enemy: Infantry Soldier mele attack");

	} else { // 10% chance to not attack

		LOG("Enemy: Infantry Soldier no attack");

		// do nothing
	}
	
}

void Enemy_InfantrySoldier::Shoot() {
	// TODO add normal attack with bullets shooting towards player position
}

void Enemy_InfantrySoldier::Knife() {
	// TODO add melee attack with knife towards player position at mele range
}

void Enemy_InfantrySoldier::move() {
	/*
	
	probablemente esto no funcione, pero es una idea de como hacerlo
	
	*/

	// TODO add movement traking player position and moving towards him

	//iPoint direction = playerPos - enemyPos;
	fPoint direction;

	direction.x = App->player->position.x - relativePosition.x;
	direction.y = App->player->position.y - relativePosition.y;

	// Normalize the direction vector
	float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) {
		direction.x /= length;
		direction.y /= length;
	}

	// Update the enemy's position based on the direction and movement speed
	float speed = 0.5f; // Adjust the movement speed as needed
	relativePosition.x += (float)direction.x * speed;
	relativePosition.y += (float)direction.y * speed;

	
	LOG("Player position: %f, %f", App->player->position.x, App->player->position.y);
	LOG("Enemy position: %d, %d", relativePosition.x, relativePosition.y);
	LOG("Enemy direction: %f, %f", direction.x, direction.y);
	LOG("Enemy speed: %f", speed);
	LOG("Enemy lenght: %f", length);
	LOG("Enemy result: %f, %f", (float)direction.x * speed, (float)direction.y * speed);
	
	
}
