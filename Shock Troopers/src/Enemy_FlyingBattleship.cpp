#include "Enemy_FlyingBattleship.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Particle.h"

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

void Enemy::Attack() {
        delay--;
        if (delay == 0) {
            // TODO add explosion when shooting
            Particle* shot1 = App->particles->AddParticle(App->particles->flyingbattleshipShop, position.x + 27, position.y + 70, 7, Collider::Type::ENEMY_SHOT);
            shot1->collider->AddListener(NULL);
            Particle* shot2 = App->particles->AddParticle(App->particles->flyingbattleshipShop, position.x + 87, position.y + 70, 7, Collider::Type::ENEMY_SHOT);
            shot2->collider->AddListener(NULL);
            App->audio->PlayFx(/*sound effect*/NULL);
            delay = 15;
        }
}

void Enemy::SpecialAttack() {

}

void Enemy::StateMachine() {
    switch (state) {
    case Enemy_State::SPAWN:
        // Handle spawn state logic
        if (/* some condition for idle */true) {
            state = Enemy_State::IDLE;
            LOG("state changed to IDLE");
        }
        break;
    case Enemy_State::IDLE:
        if (PlayerIsNear()) {
            state = Enemy_State::ATTACK;
            LOG("state changed to ATTACK");
        }
        break;
    case Enemy_State::ATTACK:
        
        Attack();

        if (!PlayerIsNear()) {
            state = Enemy_State::IDLE;
            LOG("state changed to IDLE");
        }
        if (this->health == 0) {
            state = Enemy_State::DEATH;
            LOG("state changed to DEATH");
        }
        break;
    case Enemy_State::DEATH:
        pendingToDelete = true;
        LOG("pendingToDelete enemy");
        break;
    default:
        // Handle default state logic
        LOG("ERROR STATE");
        break;
    }
}