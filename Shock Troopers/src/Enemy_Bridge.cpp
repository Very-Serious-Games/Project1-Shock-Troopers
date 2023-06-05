#include "Enemy_Bridge.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

Enemy_Bridge::Enemy_Bridge(int x, int y) : Enemy(x, y) {

    spawnAnim.PushBack({ 0, 0, 224, 220 });

    idleAnim.PushBack({ 0, 0, 224, 220 });

    int disX = 0;
    int disY = 0;
    for (int i = 0; i < 37; ++i)
    {
        if (i == 20)
        {
            disY += 222;
            disX = 0;
        }
        brokenAnim.PushBack({ disX, disY, 224, 220 });
        disX += 304;
    }
    brokenAnim.speed = 0.7f;
    brokenAnim.loop = false;

    idlebrokenAnim.PushBack({ 0, 444, 224, 220 });

    disY = 444;
    disX = 0;
    for (int j = 0; j < 106; ++j)
    {
        if (j == 20 or j == 40 or j == 60 or j == 80)
        {
            disY += 222;
            disX = 0;
        }
        deathAnim.PushBack({ disX, disY, 224, 220 });
        disX += 304;
    }
    deathAnim.speed = 0.7f;
    deathAnim.loop = false;

    path.PushBack({ 0.0f, 0.0f }, 150, &brokenAnim);

    path.PushBack({ 0.0f, 0.0f }, 600, &deathAnim);

    collider = App->collisions->AddCollider({ 0, 0, 224, 86 }, Collider::Type::BRIDGE, (Module*)App->enemies);
    health = 2;
}

void Enemy_Bridge::Update() {

    path.Update();
    position = spawnPos + path.GetRelativePosition();
    //currentAnim = &spawnAnim;

    // Call to the base class. It must be called at the end
    // It will update the collider depending on the position
    Enemy::Update();
}

void Enemy_Bridge::deathAnimation() {
    currentAnim = &deathAnim;
}

void Enemy_Bridge::spawnAnimation() {
    currentAnim = &spawnAnim;
}

void Enemy_Bridge::brokenAnimation() {
    currentAnim = &brokenAnim;
}

void Enemy_Bridge::idlebrokenAnimation() {
    currentAnim = &idlebrokenAnim;
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
        }
        break;
    case Enemy_State::IDLE:
        idleAnimation();
        if (this->health == 1)
        {
            state = Enemy_State::HIT;
        }
        break;
    case Enemy_State::HIT:
        brokenAnimation();
        if (brokenAnim.HasFinished()) {
            idlebrokenAnimation();
            if (this->health == 0) {
                state = Enemy_State::DEATH;
            }
        }
        break;
    case Enemy_State::DEATH:
        deathAnimation();

        if (deathAnim.HasFinished()) {
            pendingToDelete = true;
        }
        break;
    default:
        // Handle default state logic
        break;
    }
}

void Enemy_Bridge::OnCollision(Collider* collider) {
    if (collider->type == Collider::Type::PLAYER_SHOT) {
        health--;
        App->audio->PlayFx(App->enemies->bridgeDamaged);
        if (health == 0) {
            App->audio->PlayFx(App->enemies->bridgeDestroyed);
            SetToDelete();
        }
    }
}