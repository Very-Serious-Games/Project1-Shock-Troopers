#include "Enemy_InfantrySoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"


Enemy_InfantrySoldier::Enemy_InfantrySoldier(int x, int y) : Enemy(x, y) {

	//Spawn animations
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimLeft.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});
	spawnAnimRight.PushBack({});

	//Death Animation
	deathAnim.PushBack({51, });
	deathAnim.PushBack({51, });
	deathAnim.PushBack({51, });
	deathAnim.PushBack({51, });
	deathAnim.PushBack({51, });
	deathAnim.PushBack({51, });
	deathAnim.PushBack({51, });
	leftDeathAnim.PushBack({});
	leftDeathAnim.PushBack({});
	leftDeathAnim.PushBack({});
	leftDeathAnim.PushBack({});
	leftDeathAnim.PushBack({});
	leftDeathAnim.PushBack({});
	leftDeathAnim.PushBack({});
	rightDeathAnim.PushBack({});
	rightDeathAnim.PushBack({});
	rightDeathAnim.PushBack({});
	rightDeathAnim.PushBack({});
	rightDeathAnim.PushBack({});
	rightDeathAnim.PushBack({});
	rightDeathAnim.PushBack({});
	//Pink Death Animation
	pinkDeathAnim.PushBack({50, });
	pinkDeathAnim.PushBack({50, });
	pinkDeathAnim.PushBack({50, });
	pinkDeathAnim.PushBack({50, });
	pinkDeathAnim.PushBack({50, });
	pinkDeathAnim.PushBack({50, });
	pinkDeathAnim.PushBack({50, });
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
	//Gun hit
	gunHitRightAnim.PushBack({});
	gunHitLeftAnim.PushBack({});

	//Knife movement
	knifeUpAnim.PushBack({});
	knifeDownAnim.PushBack({});
	knifeLeftAnim.PushBack({});
	knifeRightAnim.PushBack({});
	knifeUpLeftAnim.PushBack({});
	knifeUpRightAnim.PushBack({});
	knifeDownLeftAnim.PushBack({});
	knifeDownRightAnim.PushBack({});
	//knife Idle
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
	knifeHitLeftAnim.PushBack({});

	//falling soldiers
	fallRightAnim.PushBack({ 50, 899, 62, 67 });
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
	headHandsAnim.PushBack({});

	//General soldier with binoculars
	generalAnim.PushBack({});

	//Flying soldiers
	flyingSoldiersLeftAnim.PushBack({});
	flyingSoldiersRightAnim.PushBack({});

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
	grenadeSoldierRightAnim.PushBack({});

	//Final boss soldier
	headBossSoldierAnim.PushBack({});
	grenadeBossSoldierAnim.PushBack({});
	bossSoldierIdleAnim.PushBack({});
	upBossSoldierAnim.PushBack({});


	// TODO cambiar tama�o collider
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);

	// TODO add animations

}

void Enemy_InfantrySoldier::Update() {

	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
