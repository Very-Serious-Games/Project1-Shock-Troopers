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
	deathAnim.PushBack({51, 849, 54, 54 });
	deathAnim.PushBack({});
	deathAnim.PushBack({});
	deathAnim.PushBack({});
	deathAnim.PushBack({});
	deathAnim.PushBack({});
	deathAnim.PushBack({});
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
