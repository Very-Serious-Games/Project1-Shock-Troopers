#include "Enemy_InfantrySoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_InfantrySoldier::Enemy_InfantrySoldier(int x, int y) : Enemy(x, y) {

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
