#include "Enemy_FlyingBattleship.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_FlyingBattleship::Enemy_FlyingBattleship(int x, int y) : Enemy(x, y) {

	spawnAnim.PushBack({0, 0, 121, 124});
	spawnAnim.PushBack({128, 0, 121, 124});
	spawnAnim.pingpong = true;
	spawnAnim.speed = 0.2f;

	idleAnim.PushBack({256, 0 , 121, 124});

	deathAnim.PushBack({384, 0, 121, 124});

	path.PushBack({ 0.0f, 0.0f }, 500, &spawnAnim);
	
	path.PushBack({ 0.0f, 0.0f }, 100, &idleAnim);
	path.PushBack({ 0.0f, 0.0f }, 100, &deathAnim);
	

	// TODO cambiar tamaño collider
	collider = App->collisions->AddCollider({ 0, 0, 121, 124 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_FlyingBattleship::Update() {

	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}