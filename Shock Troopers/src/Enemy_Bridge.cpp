#include "Enemy_Bridge.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Particle.h"

Enemy_Bridge::Enemy_Bridge(int x, int y) : Enemy(x, y) {

    spawnAnim.PushBack({ 0, 0, 121, 124 });
    spawnAnim.PushBack({ 128, 0, 121, 124 });
    spawnAnim.pingpong = false;
    spawnAnim.speed = 0.2f;

    idleAnim.PushBack({ 256, 0 , 121, 124 });

    deathAnim.PushBack({ 384, 0, 121, 124 });

    path.PushBack({ 1.0f, 0.0f }, 150, &idleAnim);
    path.PushBack({ -1.0f, 0.0f }, 150, &idleAnim);

    // TODO cambiar tamaño collider
    collider = App->collisions->AddCollider({ 0, 0, 121, 124 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Bridge::Update() {

    path.Update();
    position = spawnPos + path.GetRelativePosition();
    currentAnim = &spawnAnim;

    Enemy::Update();
}

void Enemy_Bridge::deathAnimation() {
    currentAnim = &deathAnim;
}

void Enemy_Bridge::spawnAnimation() {
    currentAnim = &spawnAnim;
}

void Enemy_Bridge::idleAnimation() {
    currentAnim = &idleAnim;
}

void Enemy_Bridge::StateMachine() {
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
        if (PlayerIsNear()) {
            state = Enemy_State::ATTACK;
            LOG("state changed to ATTACK");
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