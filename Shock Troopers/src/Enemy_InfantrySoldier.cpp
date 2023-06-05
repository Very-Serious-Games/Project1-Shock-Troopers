#include "Enemy_InfantrySoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePickup.h"
#include "ModuleEnemies.h"


Enemy_InfantrySoldier::Enemy_InfantrySoldier(int x, int y) : Enemy(x, y) {
	
	//falling soldiers spawn
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

	fallLeftAnim.PushBack({ 50, 103, 62, 67 });
	fallLeftAnim.PushBack({ 113, 103, 62, 67 });
	fallLeftAnim.PushBack({ 176, 103, 62, 67 });
	fallLeftAnim.PushBack({ 239, 103, 62, 67 });
	fallLeftAnim.PushBack({ 302, 103, 62, 67 });
	fallLeftAnim.PushBack({ 365, 103, 62, 67 });
	fallLeftAnim.PushBack({ 428, 103, 62, 67 });
	fallLeftAnim.PushBack({ 491, 103, 62, 67 });
	fallLeftAnim.PushBack({ 554, 103, 62, 67 });
	fallLeftAnim.PushBack({ 617, 103, 62, 67 });
	fallLeftAnim.PushBack({ 680, 103, 62, 67 });
	fallLeftAnim.PushBack({ 743, 103, 62, 67 });
	fallLeftAnim.PushBack({ 806, 103, 62, 67 });
	fallLeftAnim.PushBack({ 869, 103, 62, 67 });
	fallLeftAnim.PushBack({ 932, 103, 62, 67 });
	fallLeftAnim.PushBack({ 995, 103, 62, 67 });

	//Death Animation
	deathAnim.PushBack({436, 828, 42, 53}); 
	deathAnim.PushBack({478, 828, 42, 53});
	deathAnim.PushBack({520, 828, 42, 53});
	deathAnim.PushBack({562, 828, 42, 53});
	deathAnim.PushBack({604, 828, 42, 53});  
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
	rightDeathAnim.PushBack({960, 827, 54, 54});   
	rightDeathAnim.PushBack({1015, 827, 54, 54});
	rightDeathAnim.PushBack({1070, 827, 54, 54});

	//Gun
	//Gun movement
	gunUpAnim.PushBack({702, 228, 35, 50});  //35x50
	gunUpAnim.PushBack({738, 228, 35, 50});
	gunUpAnim.PushBack({774, 228, 35, 50});
	gunUpAnim.PushBack({810, 228, 35, 50});

	gunDownAnim.PushBack({50, 179, 29, 47});
	gunDownAnim.PushBack({80, 179, 29, 47});
	gunDownAnim.PushBack({110, 179, 29, 47});
	gunDownAnim.PushBack({140, 179, 29, 47});
	gunDownAnim.PushBack({170, 179, 29, 47});
	gunDownAnim.PushBack({200, 179, 29, 47});
	gunDownAnim.PushBack({230, 179, 29, 47});
	gunDownAnim.PushBack({260, 179, 29, 47});

	gunLeftAnim.PushBack({ 49, 230, 41, 47 });
	gunLeftAnim.PushBack({ 90, 230, 41, 47 });
	gunLeftAnim.PushBack({ 131, 230, 41, 48 });
	gunLeftAnim.PushBack({ 172, 230, 41, 47 });
	gunLeftAnim.PushBack({ 213, 230, 41, 47 });
	gunLeftAnim.PushBack({ 254, 230, 40, 47 });
	gunLeftAnim.PushBack({ 295, 230, 41, 48 });
	gunLeftAnim.PushBack({ 336, 230, 41, 47 });

	gunRightAnim.PushBack({657, 230, 41, 47});
	gunRightAnim.PushBack({ 616, 230, 41, 47 }); 
	gunRightAnim.PushBack({ 575, 230, 41, 47 });
	gunRightAnim.PushBack({ 534, 230, 41, 47 });
	gunRightAnim.PushBack({ 493, 230, 41, 47 });
	gunRightAnim.PushBack({ 452, 230, 41, 47 });
	gunRightAnim.PushBack({ 411, 230, 41, 47 });
	gunRightAnim.PushBack({ 370, 230, 41, 47 });

	gunUpLeftAnim.PushBack({295, 176, 34, 50}); 
	gunUpLeftAnim.PushBack({329, 176, 34, 50});
	gunUpLeftAnim.PushBack({363, 176, 34, 50});
	gunUpLeftAnim.PushBack({397, 176, 34, 50});

	gunUpRightAnim.PushBack({437, 176, 34, 50});
	gunUpRightAnim.PushBack({471, 176, 34, 50});
	gunUpRightAnim.PushBack({505, 176, 34, 50});
	gunUpRightAnim.PushBack({539, 176, 34, 50});

	gunDownLeftAnim.PushBack({ 1084, 177, 33, 50 }); 
	gunDownLeftAnim.PushBack({ 1051, 177, 33, 50 });
	gunDownLeftAnim.PushBack({ 1019, 177, 33, 50 });
	gunDownLeftAnim.PushBack({ 986, 177, 33, 50 });
	gunDownLeftAnim.PushBack({ 953, 177, 33, 51 });
	gunDownLeftAnim.PushBack({ 920, 177, 33, 51 });
	gunDownLeftAnim.PushBack({ 887, 177, 33, 50 });
	gunDownLeftAnim.PushBack({ 854, 177, 33, 50 });

	gunDownRightAnim.PushBack({ 576, 177, 33, 50 });
	gunDownRightAnim.PushBack({ 609, 177, 33, 50 });
	gunDownRightAnim.PushBack({ 642, 177, 33, 50 });
	gunDownRightAnim.PushBack({ 675, 177, 33, 50 });
	gunDownRightAnim.PushBack({ 708, 177, 33, 50 });
	gunDownRightAnim.PushBack({ 741, 177, 33, 50 });
	gunDownRightAnim.PushBack({ 774, 177, 33, 50 });
	gunDownRightAnim.PushBack({ 810, 177, 33, 50 });

	//Gun Idle
	gunIdleUpAnim.PushBack({1107, 295, 29, 46}); 
	gunIdleDownAnim.PushBack({ 1171, 296, 29, 45 }); 
	gunIdleLeftAnim.PushBack({1022, 231, 43, 47 }); 
	gunIdleRightAnim.PushBack({ 1066, 231, 43, 47 }); 
	gunIdleUpLeftAnim.PushBack({942, 232, 38, 46}); 
	gunIdleUpRightAnim.PushBack({981, 232, 38, 46}); 
	gunIdleDownLeftAnim.PushBack({915, 232, 26, 46}); 
	gunIdleDownRightAnim.PushBack({ 887, 231, 26, 46 });  

	//gun idle pointing
	gunPointUp.PushBack({1141, 232, 28, 46});
	gunPointDown.PushBack({857, 232, 28, 46});
	gunPointRight.PushBack({ 1066, 231, 43, 47 });
	gunPointLeft.PushBack({ 1022, 231, 43, 47 });
	gunPointUpLeft.PushBack({ 942, 232, 38, 46 });
	gunPointUpRight.PushBack({ 981, 232, 38, 46 });
	gunPointDownRight.PushBack({ 887, 231, 26, 46 });
	gunPointDownLeft.PushBack({ 915, 232, 26, 46 });
	//no need to speed these animations since they only have 1 frame
	
	//Gun hit
	gunHitRightAnim.PushBack({51, 289, 47, 50});
	gunHitRightAnim.PushBack({98, 289, 47, 50});
	gunHitRightAnim.PushBack({145, 289, 47, 50});
	gunHitRightAnim.PushBack({192, 289, 47, 50});
	gunHitRightAnim.PushBack({239, 289, 47, 50});
	gunHitRightAnim.PushBack({286, 289, 47, 50});
	gunHitRightAnim.PushBack({333, 289, 47, 50});
	gunHitRightAnim.PushBack({380, 289, 47, 50});

	gunHitLeftAnim.PushBack({448, 289, 47, 50});
	gunHitLeftAnim.PushBack({495, 289, 47, 50});
	gunHitLeftAnim.PushBack({542, 289, 47, 50});
	gunHitLeftAnim.PushBack({589, 289, 47, 50});
	gunHitLeftAnim.PushBack({636, 289, 47, 50});
	gunHitLeftAnim.PushBack({683, 289, 47, 50});
	gunHitLeftAnim.PushBack({730, 289, 47, 50});
	gunHitLeftAnim.PushBack({777, 289, 47, 50});

	gunHitUpAnim.PushBack({996, 410, 51, 55});
	gunHitUpAnim.PushBack({1047, 410, 51, 55});
	gunHitUpAnim.PushBack({1098, 410, 51, 55});
	gunHitUpAnim.PushBack({1149, 410, 51, 55});
	gunHitUpAnim.PushBack({1201, 410, 51, 55});
	gunHitUpAnim.PushBack({1252, 410, 51, 55});
	gunHitUpAnim.PushBack({1353, 410, 51, 55}); //check

	gunHitUpLeftAnim.PushBack({366, 906, 53, 50});
	gunHitUpLeftAnim.PushBack({420, 906, 53, 50});
	gunHitUpLeftAnim.PushBack({474, 906, 53, 50});
	gunHitUpLeftAnim.PushBack({528, 906, 53, 50});
	gunHitUpLeftAnim.PushBack({582, 906, 53, 50});

	gunHitUpRightAnim.PushBack({654, 907, 53, 50});
	gunHitUpRightAnim.PushBack({708, 907, 53, 50});
	gunHitUpRightAnim.PushBack({762, 907, 53, 50});
	gunHitUpRightAnim.PushBack({816, 907, 53, 50});
	gunHitUpRightAnim.PushBack({870, 907, 53, 50});

	gunHitDownAnim.PushBack({50, 902, 45, 55});
	gunHitDownAnim.PushBack({96, 902, 45, 55});
	gunHitDownAnim.PushBack({142, 902, 45, 55});
	gunHitDownAnim.PushBack({188, 902, 45, 55});
	gunHitDownAnim.PushBack({234, 902, 45, 55});
	gunHitDownAnim.PushBack({280, 902, 45, 55});

	gunHitDownLeftAnim.PushBack({ 448, 289, 47, 50 });
	gunHitDownLeftAnim.PushBack({ 495, 289, 47, 50 });
	gunHitDownLeftAnim.PushBack({ 542, 289, 47, 50 });
	gunHitDownLeftAnim.PushBack({ 589, 289, 47, 50 });
	gunHitDownLeftAnim.PushBack({ 636, 289, 47, 50 });
	gunHitDownLeftAnim.PushBack({ 683, 289, 47, 50 });
	gunHitDownLeftAnim.PushBack({ 730, 289, 47, 50 });
	gunHitDownLeftAnim.PushBack({ 777, 289, 47, 50 });

	gunHitDownRightAnim.PushBack({ 51, 289, 47, 50 });
	gunHitDownRightAnim.PushBack({ 98, 289, 47, 50 });
	gunHitDownRightAnim.PushBack({ 145, 289, 47, 50 });
	gunHitDownRightAnim.PushBack({ 192, 289, 47, 50 });
	gunHitDownRightAnim.PushBack({ 239, 289, 47, 50 });
	gunHitDownRightAnim.PushBack({ 286, 289, 47, 50 });
	gunHitDownRightAnim.PushBack({ 333, 289, 47, 50 });
	gunHitDownRightAnim.PushBack({ 380, 289, 47, 50 });

	collider = App->collisions->AddCollider({ 0, 0, 26, 50 }, Collider::Type::ENEMY, (Module*)App->enemies);
	
	path.PushBack({ 0.0f, 0.0f }, 500, &spawnAnim);
	
	// Spawn fall animation
	fallRightAnim.speed = 0.1f;
	fallLeftAnim.speed = 0.1f;

	//Death
	deathAnim.speed = 0.2f;
	leftDeathAnim.speed = 0.2f;
	rightDeathAnim.speed = 0.2f;

	//gun movement
	gunUpAnim.speed = 0.1f;
	gunUpLeftAnim.speed = 0.1f;
	gunUpRightAnim.speed = 0.1f;
	gunDownAnim.speed = 0.1f;
	gunDownLeftAnim.speed = 0.1f;
	gunDownRightAnim.speed = 0.1f;
	gunLeftAnim.speed = 0.1f;
	gunRightAnim.speed = 0.1f;

	//gun hit
	gunHitUpAnim.speed = 0.1f;
	gunHitUpRightAnim.speed = 0.1f;
	gunHitUpLeftAnim.speed = 0.1f;
	gunHitLeftAnim.speed = 0.1f;
	gunHitRightAnim.speed = 0.1f;
	gunHitDownAnim.speed = 0.1f;
	gunHitDownRightAnim.speed = 0.1f;
	gunHitDownLeftAnim.speed = 0.1f;

	this->health = 10;
}

void Enemy_InfantrySoldier::Update() {

	StateMachine();

	path.Update();
	position = spawnPos + relativePosition;
	//currentAnim = &upBossSoldierAnim;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

bool Enemy_InfantrySoldier::PlayerIsNear() {

	int detectionDistance = 150; // TODO : change this to the detection distance of the enemy (maybe a variable in the enemy class)
	int distance = sqrt(pow(App->player->position.x - position.x, 2) + pow(App->player->position.y - position.y, 2)); // pythagoras


	// TODO print debug mode detection zone
	/*
	SDL_Rect rect = { position.x, position.y, detectionDistance, detectionDistance };
	App->collisions->AddCollider(rect, Collider::Type::DETECTION_ZONE);
	*/

	if (distance <= detectionDistance) {
		return true;
	}

	return false;
}

bool Enemy_InfantrySoldier::PlayerIsAttackRange() {

	int detectionDistance = 100; // TODO : change this to the detection distance of the enemy (maybe a variable in the enemy class)
	int distance = sqrt(pow(App->player->position.x - position.x, 2) + pow(App->player->position.y - position.y, 2)); // pythagoras

	if (distance <= detectionDistance) {
		return true;
	}

	return false;
}

void Enemy_InfantrySoldier::deathAnimation() {
	currentAnim = &deathAnim;
}

void Enemy_InfantrySoldier::idleAnimation(int direction) {
	switch (direction) {
		case 1: //UR
			currentAnim = &gunIdleUpRightAnim;
			break;
		case 2: //UL
			currentAnim = &gunIdleUpLeftAnim;
			break;
		case 3: //DR
			currentAnim = &gunIdleDownRightAnim;
			break;
		case 4: //DL
			currentAnim = &gunIdleDownLeftAnim;
			break;
		case 5: //R
			currentAnim = &gunIdleRightAnim;
			break;
		case 6: //L
			currentAnim = &gunIdleLeftAnim;
			break;
		case 7: //D
			currentAnim = &gunIdleDownAnim;
			break;
		case 8: //U
			currentAnim = &gunIdleUpAnim;
			break;
		}

}

void Enemy_InfantrySoldier::spawnAnimation(int direction) {

	switch (direction) {
	case 1: //L
		currentAnim = &fallLeftAnim;
		break;
	case 2: //R
		currentAnim = &fallRightAnim;
		break;
	}
	
}

void Enemy_InfantrySoldier::moveAnimation(int direction) {
	switch (direction) {
		case 1: //UR
			currentAnim = &gunUpRightAnim;
			break;
		case 2: //UL
			currentAnim = &gunUpLeftAnim;
			break;
		case 3: //DR
			currentAnim = &gunDownRightAnim;
			break;
		case 4: //DL
			currentAnim = &gunDownLeftAnim;
			break;
		case 5: //R
			currentAnim = &gunRightAnim;
			break;
		case 6: //L
			currentAnim = &gunLeftAnim;
			break;
		case 7: //D
			currentAnim = &gunDownAnim;
			break;
		case 8: //U
			currentAnim = &gunUpAnim;
			break;
	}
}

void Enemy_InfantrySoldier::attackAnimation(int direction) {
	switch (direction) {
	case 1: //UR
		currentAnim = &gunPointUpRight;
		break;
	case 2: //UL
		currentAnim = &gunPointUpLeft;
		break;
	case 3: //DR
		currentAnim = &gunPointDownRight;
		break;
	case 4: //DL
		currentAnim = &gunPointDownLeft;
		break;
	case 5: //R
		currentAnim = &gunPointRight;
		break;
	case 6: //L
		currentAnim = &gunPointLeft;
		break;
	case 7: //D
		currentAnim = &gunPointDown;
		break;
	case 8: //U
		currentAnim = &gunPointUp;
		break;
	}
}

void Enemy_InfantrySoldier::attackMeleAnimation(int direction) {
	switch (direction) {
	case 1: //UR
		currentAnim = &gunHitUpAnim;
		break;
	case 2: //UL
		currentAnim = &gunHitUpLeftAnim;
		break;
	case 3: //DR
		currentAnim = &gunHitDownRightAnim;
		break;
	case 4: //DL
		currentAnim = &gunHitDownLeftAnim;
		break;
	case 5: //R
		currentAnim = &gunHitRightAnim;
		break;
	case 6: //L
		currentAnim = &gunHitLeftAnim;
		break;
	case 7: //D
		currentAnim = &gunHitDownAnim;
		break;
	case 8: //U
		currentAnim = &gunHitUpAnim;
		break;
	}
}

void Enemy_InfantrySoldier::StateMachine() {
	switch (state) {
		case Enemy_State::SPAWN:

			spawnAnimation(GetPlayerDirection());
			if (true) {
				state = Enemy_State::IDLE;
			}

			break;

		case Enemy_State::IDLE:

			idleAnimation(GetPlayerDirection());

			if (PlayerIsAttackRange()) {
				state = Enemy_State::ATTACK;
			}

			if (PlayerIsNear()) {
				state = Enemy_State::MOVE;
			}

			break;

		case Enemy_State::ATTACK:

			attackAnimation(GetPlayerDirection());

			Attack();

			if (!PlayerIsAttackRange()) {
				state = Enemy_State::IDLE;
			}

			break;

		case Enemy_State::DEATH:

			deathAnimation();

			// rand number between 0 and 1
			if (!playOnce) {
				if ((rand() % 2) == 0) {
					App->audio->PlayFx(App->enemies->soldierDamaged1);
				} else {
					App->audio->PlayFx(App->enemies->soldierDamaged2);
				}
				playOnce = true;
			}
			

			if (deathAnimDelay == 0) {
				App->pickUps->SpawnPickUp({ PickUp_Type::DIAMOND, (int)position.x, (int)position.y });
				pendingToDelete = true;
				
				LOG("pendingToDelete enemy");
			}

			deathAnimDelay--;

			break;

		case Enemy_State::MOVE:

			moveAnimation(GetPlayerDirection());

			move();

			if (PlayerIsAttackRange()) {
				state = Enemy_State::ATTACK;
			}

			if (!PlayerIsNear()) {
				state = Enemy_State::IDLE;
			}

			break;

	}

}

void Enemy_InfantrySoldier::Attack() {
	/*
	if (PlayerIsMele()) {
		delayKnife--;
		if (delayKnife == 0) {
			Knife();
			delayKnife = 500;
		}
	} else {
		Shoot();
	}
	*/
	Shoot();
	
}

void Enemy_InfantrySoldier::Shoot() {
	// Get the player position
	fPoint playerPos = App->player->position;

	// Calculate the direction vector from enemy position to player position
	fPoint enemyPos = position;
	fPoint direction = playerPos - enemyPos;

	// Normalize the direction vector
	float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) {
		direction.x /= length;
		direction.y /= length;
	}

	delayShoot--;
	if (delayShoot == 0) {
		Particle* newParticle = nullptr;
		Particle* newParticleMuzzle = nullptr;
		switch (GetPlayerDirection()) {
		case 1: // Up-Right
			newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x + 30, position.y - 2, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleUpRight, position.x + 30, position.y - 2, 0, Collider::Type::MUZZLE);
			break;
		case 2: // Up-Left
			newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x - 3, position.y - 3, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleUpLeft, position.x - 3, position.y - 3, 0, Collider::Type::MUZZLE);
			break;
		case 3: // Down-Right
			newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x + 10, position.y + 25, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleDownRight, position.x + 10, position.y + 25, 0, Collider::Type::MUZZLE);
			break;
		case 4: // Down-Left
			newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x + 5, position.y + 25, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleDownLeft, position.x + 0, position.y + 25, 0, Collider::Type::MUZZLE);
			break;
		case 5: // Right
			newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x + 35, position.y + 8, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleRight, position.x + 35, position.y + 8, 0, Collider::Type::MUZZLE);
			break;
		case 6: // Left
			newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x - 10, position.y + 15, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleLeft, position.x - 10, position.y + 10, 0, Collider::Type::MUZZLE);
			break;
		case 7: // Down
			newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x + 10, position.y + 30, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleDown, position.x + 5, position.y + 30, 0, Collider::Type::MUZZLE);
			break;
		case 8: // Up
			newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x + 0, position.y - 10, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleUp, position.x + 0, position.y - 10, 0, Collider::Type::MUZZLE);
			break;
		}

		newParticle->collider->AddListener(NULL);
		newParticleMuzzle->collider->AddListener(NULL);
		App->audio->PlayFx(App->enemies->soldierShot);

		delayShoot = 700;
	}

}

void Enemy_InfantrySoldier::Knife() {
	// Create a direction vector
	fPoint direction;

	// Calculate the direction between the enemy and the player
	direction.x = App->player->position.x - position.x;
	direction.y = App->player->position.y - position.y;

	// Normalize the direction vector
	float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) {
		direction.x /= length;
		direction.y /= length;
	}

	int knifeWidth = 20;
	int knifeHeight = 50;

	// Calculate the position of the knife collider based on the player's position
	int knifePosX = static_cast<int>(position.x);
	int knifePosY = static_cast<int>(position.y);

	// Adjust the position of the knife collider based on the player's direction
	if (direction.x < 0) {
		// Player is to the right of the enemy
		knifePosX += collider->rect.w;
	} else {
		// Player is to the left of the enemy
		knifePosX -= knifeWidth;
	}

	if (direction.y < 0) {
		// Player is above the enemy
		knifePosY -= knifeHeight;
	} else {
		// Player is below the enemy
		knifePosY += collider->rect.h;
	}

	// Add the knife collider
	Collider* knife = App->collisions->AddCollider(
		{
			knifePosX,
			knifePosY,
			knifeWidth,
			knifeHeight
		},
		Collider::Type::KNIFE, // TODO: KNIFE
		NULL);

	// TODO logica para borrar el collider dependiendo de la animacion
	/*
	if (knifeUpAnim.HasFinished()) {
		App->collisions->RemoveCollider(knife);
	}
	*/

}

void Enemy_InfantrySoldier::move() {

	// Create a direction vector
	fPoint direction;

	// Calculate the direction between the enemy and the player
	direction.x = App->player->position.x - position.x;
	direction.y = App->player->position.y - position.y;

	// Normalize the direction vector
	float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) {
		direction.x /= length;
		direction.y /= length;
	}

	// Update the enemy's position based on the direction and movement speed
	float speed = 0.1f; // Adjust the movement speed as needed
	relativePosition.x += (float)direction.x * speed;
	relativePosition.y += (float)direction.y * speed;
	
}