#include "Enemy_Sandbag.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Sandbag::Enemy_Sandbag(int x, int y) : Enemy(x, y) {

    spawnAnim.PushBack({ 0, 0, 118, 189 });

    idleAnim.PushBack({ 0, 0, 118, 189 });

    int disX = 0;
    int disY = 0;
    for (int i = 0; i < 36; ++i)
    {
        if (i == 20)
        {
            disY += 191;
            disX = 0;
        }
        brokenAnim.PushBack({ disX, disY, 118, 189 });
        disX += 120;
    }
    brokenAnim.speed = 0.2f;
    brokenAnim.loop = false;

    idlebrokenAnim.PushBack({ 0, 382, 118, 189 });

    disX = 0;
    disY = 382;
    for (int j = 0; j < 60; ++j)
    {
        if (j == 20 and j == 40)
        {
            disY += 191;
            disX = 0;
        }
        deathAnim.PushBack({ disX, disY, 118, 189 });
        disX += 120;
    }
    deathAnim.speed = 0.7f;
    deathAnim.loop = false;

    path.PushBack({ 0.0f, 0.0f }, 300, &brokenAnim);

    path.PushBack({ 0.0f, 0.0f }, 600, &deathAnim);

    // TODO cambiar tamaño collider
    collider = App->collisions->AddCollider({ 10, 74, 97, 42 }, Collider::Type::OBJECT, (Module*)App->enemies);
    health = 20;
}

void Enemy_Sandbag::Update() {

    path.Update();
    position = spawnPos + path.GetRelativePosition();
    currentAnim = path.GetCurrentAnimation();
    //currentAnim = &spawnAnim;

    // Call to the base class. It must be called at the end
    // It will update the collider depending on the position
    Enemy::Update();
}

void Enemy_Sandbag::deathAnimation() {
    currentAnim = &deathAnim;
}

void Enemy_Sandbag::spawnAnimation() {
    currentAnim = &spawnAnim;
}

void Enemy_Sandbag::brokenAnimation() {
    currentAnim = &brokenAnim;
}

void Enemy_Sandbag::idlebrokenAnimation() {
    currentAnim = &idlebrokenAnim;
}

void Enemy_Sandbag::idleAnimation() {
    currentAnim = &idleAnim;
}

void Enemy_Sandbag::StateMachine() {
    switch (state) {
    case Enemy_State::SPAWN:
        spawnAnimation();
        // Handle spawn state logic
        if (/* some condition for idle */true) {
            state = Enemy_State::IDLE;
        }
        break;
    case Enemy_State::IDLE:
        LOG("Sandbag state changed to IDLE");
        idleAnimation();
        if (this->health <= 10)
        {
            brokenAnimation();
            if (brokenAnim.HasFinished()) {
                state = Enemy_State::HIT;
            }
        }
        break;
    case Enemy_State::HIT:
        LOG("Sandbag state changed to HIT");
        idlebrokenAnimation();
        if (this->health == 0) {
            state = Enemy_State::DEATH;
        }
        break;
    case Enemy_State::DEATH:
        LOG("Sandbag state changed to DEATH");
        deathAnimation();

        if (deathAnim.HasFinished()) {
            pendingToDelete = true;
            LOG("pendingToDelete Sandbag");
        }
        break;
    default:
        // Handle default state logic
        LOG("ERROR STATE");
        break;
    }
}

void Enemy_Sandbag::OnCollision(Collider* collider) {
    if (collider->type == Collider::Type::PLAYER_SHOT) {
        health -= 10;
        if (health == 0) {
            App->audio->PlayFx(destroyedFx);
            SetToDelete();
        }
    }
}