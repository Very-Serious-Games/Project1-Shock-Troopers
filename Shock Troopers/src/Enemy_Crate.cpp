#include "Enemy_Crate.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Particle.h"
#include "ModulePickUp.h"

Enemy_Crate::Enemy_Crate(int x, int y) : Enemy(x, y) {

    spawnAnim.PushBack({ 0, 0, 64, 54 });

    idleAnim.PushBack({ 0, 0, 64, 54 });

    deathAnim.PushBack({ 64, 0, 64, 54 });
    deathAnim.PushBack({ 128, 0, 64, 54 });
    deathAnim.PushBack({ 192, 0, 64, 54 });
    deathAnim.PushBack({ 256, 0, 64, 54 });
    deathAnim.PushBack({ 320, 0, 64, 54 });
    deathAnim.PushBack({ 384, 0, 64, 54 });
    deathAnim.PushBack({ 448, 0, 64, 54 });
    deathAnim.PushBack({ 512, 0, 64, 54 });

    deathAnim.speed = 0.1f;

    //path.PushBack({ 0.0f, 0.0f }, 500, &spawnAnim);
    //path.PushBack({ 0.0f, 0.0f }, 150, &idleAnim);
    path.PushBack({ 0.0f, 0.0f }, 80, &deathAnim);

    // TODO cambiar tamaño collider
    collider = App->collisions->AddCollider({ 0, 0, 47, 49 }, Collider::Type::OBJECT, (Module*)App->enemies);
    
    health = 1;
}

void Enemy_Crate::Update() {

    path.Update();
    position = spawnPos + path.GetRelativePosition();
    //currentAnim = &spawnAnim;

    // Call to the base class. It must be called at the end
    // It will update the collider depending on the position
    Enemy::Update();
}

void Enemy_Crate::deathAnimation() {
    currentAnim = &deathAnim;
}

void Enemy_Crate::spawnAnimation() {
    currentAnim = &spawnAnim;
}

void Enemy_Crate::idleAnimation() {
    currentAnim = &idleAnim;
}

void Enemy_Crate::StateMachine() {
    switch (state) {
    case Enemy_State::SPAWN:
        spawnAnimation();
        // Handle spawn state logic
        if (/* some condition for idle */true) {
            state = Enemy_State::IDLE;
            LOG("state changed to IDLE");
        }
        break;
    case Enemy_State::IDLE:
        idleAnimation();
        if (this->health == 0) {
            state = Enemy_State::DEATH;
            LOG("state changed to DEATH");
        }
        break;
    case Enemy_State::DEATH:
        deathAnimation();
        App->pickUps->SpawnPickUp({ PickUp_Type::HP, (int)position.x, (int)position.y });
        //SpawnPickUp({ PickUp_Type::HP, 220, 1800 });

        if (deathAnimDelay == 0) {
            pendingToDelete = true;
            LOG("pendingToDelete enemy");
        }
        deathAnimDelay--;

        break;

    default:
        // Handle default state logic
        LOG("ERROR STATE");
        break;
    }
}

void Enemy_Crate::OnCollision(Collider* collider) {
    if (collider->type == Collider::Type::PLAYER_SHOT) {
		health--;
        if (health == 0) {
            App->audio->PlayFx(destroyedFx);
            SetToDelete();
		}
	}
}