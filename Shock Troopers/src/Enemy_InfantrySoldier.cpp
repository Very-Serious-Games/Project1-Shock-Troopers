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
	deathAnim.PushBack({});
	leftDeathAnim.PushBack({});
	rightDeathAnim.PushBack({});

	//Idle animations
	idleUpAnim.PushBack({ 267, 102, 20, 20 });
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
	gunDownAnim.PushBack({});
	gunLeftAnim.PushBack({});
	gunRightAnim.PushBack({});
	gunUpLeftAnim.PushBack({});
	gunUpRightAnim.PushBack({});
	gunDownLeftAnim.PushBack({});
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

	//falling soldiers
	fallRightAnim.PushBack({});
	fallLeftAnim.PushBack({});

	//Hiding half body sodier
	hidingIdleAnim.PushBack({});
	hidingDownAnim.PushBack({});
	hidingHalfLeftAnim.PushBack({});
	hidingHalfRightAnim.PushBack({});
	hidingLeftAnim.PushBack({});
	hidingRightAnim.PushBack({});

	//Hands in the head soldier
	headHandsAnim.PushBack({});





	// TODO cambiar tamaño collider
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
