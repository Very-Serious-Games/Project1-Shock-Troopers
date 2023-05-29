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

	//Gun
	//Gun movement
	gunUpAnim.PushBack({702, 227, 35, 50});  //35x50
	gunUpAnim.PushBack({738, 227, 35, 50});
	gunUpAnim.PushBack({774, 227, 35, 50});
	gunUpAnim.PushBack({810, 227, 35, 50});

	gunDownAnim.PushBack({50, 179, 29, 47});
	gunDownAnim.PushBack({80, 179, 29, 47});
	gunDownAnim.PushBack({110, 179, 29, 47});
	gunDownAnim.PushBack({140, 179, 29, 47});
	gunDownAnim.PushBack({170, 179, 29, 47});
	gunDownAnim.PushBack({200, 179, 29, 47});
	gunDownAnim.PushBack({230, 179, 29, 47});
	gunDownAnim.PushBack({260, 179, 29, 47});

	gunLeftAnim.PushBack({50, 230, 41, 47});
	gunLeftAnim.PushBack({91, 230, 41, 47});
	gunLeftAnim.PushBack({132, 230, 41, 47});
	gunLeftAnim.PushBack({173, 230, 41, 47});
	gunLeftAnim.PushBack({214, 230, 41, 47});
	gunLeftAnim.PushBack({255, 230, 41, 47});
	gunLeftAnim.PushBack({296, 230, 41, 47});
	gunLeftAnim.PushBack({337, 230, 41, 47});

	gunRightAnim.PushBack({370, 230, 41, 47}); //puede ser que haya que cambiarlos
	gunRightAnim.PushBack({411, 230, 41, 47}); //410?
	gunRightAnim.PushBack({452, 230, 41, 47});
	gunRightAnim.PushBack({493, 230, 41, 47});
	gunRightAnim.PushBack({534, 230, 41, 47});
	gunRightAnim.PushBack({575, 230, 41, 47});
	gunRightAnim.PushBack({616, 230, 41, 47});
	gunRightAnim.PushBack({657, 230, 41, 47});

	gunUpLeftAnim.PushBack({295, 176, 34, 50}); // check
	gunUpLeftAnim.PushBack({329, 176, 34, 50});
	gunUpLeftAnim.PushBack({363, 176, 34, 50});
	gunUpLeftAnim.PushBack({397, 176, 34, 50});

	gunUpRightAnim.PushBack({437, 176, 34, 50});
	gunUpRightAnim.PushBack({471, 176, 34, 50});
	gunUpRightAnim.PushBack({505, 176, 34, 50});
	gunUpRightAnim.PushBack({539, 176, 34, 50});

	gunDownLeftAnim.PushBack({854, 176, 33, 50}); //check. 34? if not right fix spritesheet
	gunDownLeftAnim.PushBack({887, 176, 33, 50});
	gunDownLeftAnim.PushBack({920, 176, 33, 50});
	gunDownLeftAnim.PushBack({953, 176, 33, 50});
	gunDownLeftAnim.PushBack({986, 176, 33, 50});
	gunDownLeftAnim.PushBack({1019, 176, 33, 50});
	gunDownLeftAnim.PushBack({1052, 176, 33, 50});
	gunDownLeftAnim.PushBack({1085, 176, 33, 50});

	gunDownRightAnim.PushBack({ 576, 176, 33, 50 });
	gunDownRightAnim.PushBack({ 609, 176, 33, 50 });
	gunDownRightAnim.PushBack({ 642, 176, 33, 50 });
	gunDownRightAnim.PushBack({ 675, 176, 33, 50 });
	gunDownRightAnim.PushBack({ 708, 176, 33, 50 });
	gunDownRightAnim.PushBack({ 741, 176, 33, 50 });
	gunDownRightAnim.PushBack({ 774, 176, 33, 50 });
	gunDownRightAnim.PushBack({ 810, 176, 33, 50 });

	//Gun Idle
	gunIdleUpAnim.PushBack({1108, 232, 29, 46}); //close legs
	gunIdle2UpAnim.PushBack({ 850, 232, 28, 46}); //spread legs
	gunIdleDownAnim.PushBack({ 1172, 233, 29, 45 }); //close legs
	gunIdle2DownAnim.PushBack({ 910, 232, 26, 46 }); //spread legs
	gunIdlePointDownAnim.PushBack({ 879, 232, 28, 46}); //pointing gun idle down
	gunIdleLeftAnim.PushBack({1019, 231, 43, 47 });
	gunIdleRightAnim.PushBack({ 1063, 231, 43, 47 });
	gunIdleUpLeftAnim.PushBack({939, 232, 38, 46});
	gunIdleUpRightAnim.PushBack({978, 232, 38, 46});
	gunIdleDownLeftAnim.PushBack({}); //none atm
	gunIdleDownRightAnim.PushBack({}); //none atm
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

	//Knife movement
	knifeUpAnim.PushBack({51, 352, 35, 50});
	knifeUpAnim.PushBack({87, 352, 35, 50});
	knifeUpAnim.PushBack({123, 352, 35, 50});
	knifeUpAnim.PushBack({159, 352, 35, 50});

	knifeDownAnim.PushBack({202, 355, 38, 47});
	knifeDownAnim.PushBack({241, 355, 38, 47});

	knifeLeftAnim.PushBack({625, 354, 48, 49}); //check
	knifeLeftAnim.PushBack({577, 354, 48, 49});
	knifeLeftAnim.PushBack({529, 354, 48, 49});
	knifeLeftAnim.PushBack({481, 354, 48, 49});

	knifeRightAnim.PushBack({284, 354, 48, 49}); //check
	knifeRightAnim.PushBack({332, 354, 48, 49});
	knifeRightAnim.PushBack({380, 354, 48, 49}); //379?
	knifeRightAnim.PushBack({428, 354, 48, 49});

	knifeUpLeftAnim.PushBack({858, 352, 43, 50}); //check
	knifeUpLeftAnim.PushBack({901, 352, 43, 50});
	knifeUpLeftAnim.PushBack({941, 352, 43, 50});
	knifeUpLeftAnim.PushBack({985, 352, 43, 50});

	knifeUpRightAnim.PushBack({678, 352, 43, 50});
	knifeUpRightAnim.PushBack({722, 352, 43, 50});
	knifeUpRightAnim.PushBack({766, 352, 43, 50});
	knifeUpRightAnim.PushBack({810, 352, 43, 50});

	knifeDownLeftAnim.PushBack({51, 418, 39, 47});
	knifeDownLeftAnim.PushBack({91, 418, 39, 47});
	knifeDownLeftAnim.PushBack({131, 418, 39, 47});
	knifeDownLeftAnim.PushBack({171, 418, 39, 47});

	knifeDownRightAnim.PushBack({219, 418, 39, 47});
	knifeDownRightAnim.PushBack({259, 418, 39, 47});
	knifeDownRightAnim.PushBack({299, 418, 39, 47});
	knifeDownRightAnim.PushBack({339, 418, 39, 47});

	//knife Idle
	//no need to speed these animations bc they only have one frame
	knifeIdleUpAnim.PushBack({51, 491, 35, 50});
	knifeIdleDownAnim.PushBack({254, 494, 38, 47});
	knifeIdleLeftAnim.PushBack({90, 488, 34, 53});
	knifeIdleRightAnim.PushBack({130, 488, 34, 53});
	knifeIdleUpLeftAnim.PushBack({}); // none atm
	knifeIdleUpRightAnim.PushBack({});  //none atm
	knifeIdleDownLeftAnim.PushBack({167, 499, 41, 42});
	knifeIdleDownRightAnim.PushBack({209, 499, 41, 42});

	//knife hit
	knifeHitRightAnim.PushBack({});
	knifeHitRightAnim.PushBack({});
	knifeHitRightAnim.PushBack({});
	knifeHitRightAnim.PushBack({});
	knifeHitRightAnim.PushBack({});
	knifeHitRightAnim.PushBack({});

	knifeHitLeftAnim.PushBack({385, 412, 50, 53}); //check
	knifeHitLeftAnim.PushBack({431, 412, 50, 53});
	knifeHitLeftAnim.PushBack({482, 412, 50, 53});
	knifeHitLeftAnim.PushBack({532, 412, 50, 53});
	knifeHitLeftAnim.PushBack({582, 412, 50, 53});
	knifeHitLeftAnim.PushBack({632, 412, 50, 53});

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
	hidingIdleRightAnim.PushBack({381, 519, 25, 22});
	hidingIdleLeftAnim.PushBack({355, 519, 25, 22});
	hidingDownAnim.PushBack({477, 514, 25, 27});
	hidingHalfLeftAnim.PushBack({444, 513, 26, 28});
	hidingHalfRightAnim.PushBack({543, 514, 23, 27});
	hidingLeftAnim.PushBack({411, 516, 32, 25});
	hidingRightAnim.PushBack({510, 516, 26, 25});

	//Hands in the head soldier
	headHandsLeftAnim.PushBack({294, 494, 27, 47});
	headHandsRightAnim.PushBack({321, 494, 25, 47});

	//General soldier with binoculars
	generalAnim.PushBack({595, 478, 41, 63});
	generalAnim.PushBack({637, 478, 41, 63});
	generalAnim.PushBack({679, 478, 41, 63});
	generalAnim.PushBack({721, 478, 41, 63});
	generalAnim.PushBack({763, 478, 41, 63});
	generalAnim.PushBack({805, 478, 41, 63});
	generalAnim.PushBack({847, 478, 41, 63});
	generalAnim.PushBack({889, 478, 41, 63});
	generalAnim.PushBack({931, 478, 41, 63});
	generalAnim.PushBack({973, 478, 41, 63});
	generalAnim.PushBack({1015, 478, 41, 63});
	generalAnim.PushBack({1057, 478, 41, 63});
	generalAnim.PushBack({1099, 478, 41, 63});

	//Flying soldiers
	flyingSoldiersLeftAnim.PushBack({156, 551, 52, 53});
	flyingSoldiersDownLeftAnim.PushBack({ 209, 554, 46, 50 });
	flyingSoldiersRightAnim.PushBack({103, 551, 52, 53});
	flyingSoldiersDownRightAnim.PushBack({ 51, 554, 46, 50 });

	//Bazooka soldiers
	bazookaDownAnim.PushBack({584, 551, 28, 53});
	bazookaDownLeftAnim.PushBack({526, 551, 28, 53}); //looking at left side
	bazookaDownHalfLeftAnim.PushBack({555, 551, 28, 53});
	bazookaDownRightAnim.PushBack({641, 551, 28, 53}); //looking at right side
	bazookaDownHalfRightAnim.PushBack({613, 551, 28, 53});
	bazookaRightAnim.PushBack({474, 553, 41, 51});
	bazookaLeftAnim.PushBack({265, 553, 41, 51});
	bazookaUpLeftAnim.PushBack({349, 548, 29, 56});
	bazookaUpRightAnim.PushBack({391, 548, 29, 56});
	bazookaHalfRightAnim.PushBack({433, 551, 35, 53});
	bazookaHalfLeftAnim.PushBack({307, 551, 35, 53});

	//Throwing grenade soldiers
	grenadeSoldierLeftAnim.PushBack({410, 615, 46, 52});
	grenadeSoldierLeftAnim.PushBack({457, 615, 46, 52});
	grenadeSoldierLeftAnim.PushBack({504, 615, 46, 52});
	grenadeSoldierLeftAnim.PushBack({551, 615, 46, 52});
	grenadeSoldierLeftAnim.PushBack({598, 615, 46, 52});

	grenadeSoldierDownLeftAnim.PushBack({50, 615, 42, 52});
	grenadeSoldierDownLeftAnim.PushBack({92, 615, 42, 52});
	grenadeSoldierDownLeftAnim.PushBack({135, 615, 42, 52});
	grenadeSoldierDownLeftAnim.PushBack({176, 615, 42, 52});

	grenadeSoldierUpLeftAnim.PushBack({918, 557, 45, 47});
	grenadeSoldierUpLeftAnim.PushBack({964, 557, 45, 47});
	grenadeSoldierUpLeftAnim.PushBack({1010, 557, 45, 47});
	grenadeSoldierUpLeftAnim.PushBack({1056, 557, 45, 47});
	grenadeSoldierUpLeftAnim.PushBack({1102, 557, 45, 47});

	grenadeSoldierRightAnim.PushBack({656, 615, 46, 52});
	grenadeSoldierRightAnim.PushBack({703, 615, 46, 52});
	grenadeSoldierRightAnim.PushBack({750, 615, 46, 52});
	grenadeSoldierRightAnim.PushBack({797, 615, 46, 52});
	grenadeSoldierRightAnim.PushBack({844, 615, 46, 52});

	grenadeSoldierDownRightAnim.PushBack({232, 615, 42, 52});
	grenadeSoldierDownRightAnim.PushBack({275, 615, 42, 52});
	grenadeSoldierDownRightAnim.PushBack({318, 615, 42, 52});
	grenadeSoldierDownRightAnim.PushBack({360, 615, 42, 52});

	grenadeSoldierUpRightAnim.PushBack({909, 620, 45, 47});
	grenadeSoldierUpRightAnim.PushBack({954, 620, 45, 47});
	grenadeSoldierUpRightAnim.PushBack({999, 620, 45, 47});
	grenadeSoldierUpRightAnim.PushBack({1047, 620, 45, 47});
	grenadeSoldierUpRightAnim.PushBack({1093, 620, 45, 47});

	//Final boss soldier
	headBossSoldierAnim.PushBack({53, 740, 21, 15});

	grenadeBossSoldierAnim.PushBack({81, 713, 38, 42});
	grenadeBossSoldierAnim.PushBack({120, 713, 38, 42});
	grenadeBossSoldierAnim.PushBack({159, 713, 38, 42});
	grenadeBossSoldierAnim.PushBack({198, 713, 38, 42});
	grenadeBossSoldierAnim.PushBack({237, 713, 38, 42});
	grenadeBossSoldierAnim.PushBack({276, 713, 38, 42});

	grenadeBossSoldierRightAnim.PushBack({604, 717, 50, 38});
	grenadeBossSoldierRightAnim.PushBack({655, 717, 50, 38});
	grenadeBossSoldierRightAnim.PushBack({706, 717, 50, 38});
	grenadeBossSoldierRightAnim.PushBack({757, 717, 50, 38});
	grenadeBossSoldierRightAnim.PushBack({808, 717, 50, 38});

	grenadeBossSoldierLeftAnim.PushBack({ 346, 717, 50, 38 });
	grenadeBossSoldierLeftAnim.PushBack({ 397, 717, 50, 38 });
	grenadeBossSoldierLeftAnim.PushBack({ 448, 717, 50, 38 });
	grenadeBossSoldierLeftAnim.PushBack({ 498, 717, 50, 38 });
	grenadeBossSoldierLeftAnim.PushBack({ 549, 717, 50, 38 });

	bossSoldierIdleAnim.PushBack({868, 704, 28, 51});

	upBossSoldierAnim.PushBack({907, 702, 30, 53});
	upBossSoldierAnim.PushBack({938, 702, 30, 53});
	upBossSoldierAnim.PushBack({969, 702, 30, 53});
	upBossSoldierAnim.PushBack({1000, 702, 30, 53});
	upBossSoldierAnim.PushBack({1031, 702, 30, 53});
	upBossSoldierAnim.PushBack({1062, 702, 30, 53});
	upBossSoldierAnim.PushBack({1093, 702, 30, 53});
	upBossSoldierAnim.PushBack({1124, 702, 30, 53});
	upBossSoldierAnim.PushBack({1155, 702, 30, 53});

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
		if (fabsf(direction.x) <= fabsf(direction.y) * 0.5f) {

			playerDirection = 8; // Up

		} else if (direction.x < 0) {

			playerDirection = 2; // Up-Left

		} else {

			playerDirection = 1; // Up-Right

		}

	} else if (direction.y > 0) {

		// Player is below the enemy
		if (fabsf(direction.x) <= fabsf(direction.y) * 0.5f) {

			playerDirection = 7; // Down

		} else if (direction.x < 0) {

			playerDirection = 4; // Down-Left

		} else {

			playerDirection = 3; // Down-Right
		}

	} else {
		// Player is at the same height as the enemy
		if (direction.x < 0) {

			playerDirection = 6; // Left

		} else if (direction.x > 0) {

			playerDirection = 5; // Right

		} else {

			// Player is at the exact position as the enemy (unlikely scenario)
			playerDirection = 0; // No direction

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

			if (PlayerIsAttackRange()) {
				state = Enemy_State::ATTACK;
			}

			if (PlayerIsNear()) {
				state = Enemy_State::MOVE;
			}

			LOG("IDLE STATE");

			break;

		case Enemy_State::ATTACK:

			attackAnimation();

			Attack();

			if (!PlayerIsAttackRange()) {
				state = Enemy_State::IDLE;
			}

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

			if (PlayerIsAttackRange()) {
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
	/*
	int attackType = rand() % 10; // generate a random number between 0 and 9
	if (attackType < 6) { // 60% chance to do a normal attack
		
		Shoot();

		LOG("Enemy: Infantry Soldier normal attack");

	} else if (attackType < 4) { // 30% chance to do a mele attack

		Knife();

		LOG("Enemy: Infantry Soldier mele attack");

	} else { // 10% chance to not attack

		LOG("Enemy: Infantry Soldier no attack");

		// do nothing
	}
	*/

	if (PlayerIsMele()) {
		LOG("Enemy: mele");
		delayKnife--;
		if (delayKnife == 0) {
			Knife();
			delayKnife = 500;
		}
		
		
	} else {
		LOG("Enemy: shot");
		Shoot();
	}
	
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
		// TODO modify shot to be an enemy shot
		Particle* shot = App->particles->AddParticle(App->particles->playerShot, position.x, position.y, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
		shot->collider->AddListener(NULL);
		App->audio->PlayFx(/*sound effect*/NULL);
		delayShoot = 700;
	}


	// TODO add normal attack with bullets shooting towards player position

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
	if (knifeUpAnim.HasFinished()) {
		App->collisions->RemoveCollider(knife);
	}

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