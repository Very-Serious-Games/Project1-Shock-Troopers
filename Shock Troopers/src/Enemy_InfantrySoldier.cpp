#include "Enemy_InfantrySoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_InfantrySoldier::Enemy_InfantrySoldier(int x, int y) : Enemy(x, y) {

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
