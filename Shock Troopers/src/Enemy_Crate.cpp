#include "Enemy_Crate.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Particle.h"

Enemy_Crate::Enemy_Crate(int x, int y) : Enemy(x, y) {



    spawnAnim.PushBack({ 96, 0, 124, 90 });
    spawnAnim.speed = 0.2f;

    idleAnim.PushBack({ 96, 0, 124, 90 });

    deathAnim.PushBack({ 135, 0, 177, 90 });
    deathAnim.PushBack({ 188, 0, 241, 90 });
    deathAnim.PushBack({ 255, 0, 317, 90 });
    deathAnim.PushBack({ 329, 0, 391, 90 });
    deathAnim.PushBack({ 403, 0, 465, 90 });
    deathAnim.PushBack({ 476, 0, 539, 90 });
    deathAnim.PushBack({ 550, 0, 613, 90 });
    deathAnim.PushBack({ 625, 0, 687, 90 });

    //path.PushBack({ 0.0f, 0.0f }, 500, &spawnAnim);
    //path.PushBack({ 1.0f, 0.0f }, 150, &idleAnim);
    //path.PushBack({ -1.0f, 0.0f }, 150, &idleAnim);
    path.PushBack({ 0.0f, 0.0f }, 100, &deathAnim);


    // TODO cambiar tamaño collider
    collider = App->collisions->AddCollider({ 0, 0, 124, 90 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Crate::Update() {

    path.Update();
    position = spawnPos + path.GetRelativePosition();
    //currentAnim = path.GetCurrentAnimation();
    currentAnim = &spawnAnim;

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