#include "Enemy_Barrel.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Barrel::Enemy_Barrel(int x, int y) : Enemy(x, y) {

    spawnAnim.PushBack({ 0, 0, 63, 124 });

    idleAnim.PushBack({ 0, 0, 63, 124 });

    int disX = 0;
    int con = 5;
    for (int i = 0; i < 24; i++)
    {
        deathAnim.PushBack({ disX, 0, 63, 124 });
        disX += 63;
    }
    disX = 1071;
    for (int i = 0; i < 6; i++)
    {
        deathAnim.PushBack({ disX, 0, 63, 124 });
        disX += 63;
        if (con != 0 and i == 6)
        {
            disX = 1071;
            con--;
            i = 0;
        }
    }
    deathAnim.speed = 0.2f;
    deathAnim.loop = false;

    path.PushBack({ 0.0f, 0.0f }, 600, &deathAnim);

    // TODO cambiar tamaño collider//
    collider = App->collisions->AddCollider({ 0, 0, 19, 32 }, Collider::Type::OBJECT, (Module*)App->enemies);
    collider->SetPos(position.x+21, position.y+85);
    health = 1;
}

void Enemy_Barrel::Update() {

    path.Update();
    position = spawnPos + path.GetRelativePosition();

    Enemy::Update();
}

void Enemy_Barrel::deathAnimation() {
    currentAnim = &deathAnim;
}

void Enemy_Barrel::spawnAnimation() {
    currentAnim = &spawnAnim;
}

void Enemy_Barrel::idleAnimation() {
    currentAnim = &idleAnim;
}

void Enemy_Barrel::StateMachine() {
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
        if (this->health == 0)
        {
            state = Enemy_State::HIT;
        }
        break;
    case Enemy_State::DEATH:
        deathAnimation();

        if (deathAnim.HasFinished()) {
            pendingToDelete = true;
            LOG("pendingToDelete Barrel");
        }
        break;
    default:
        // Handle default state logic
        LOG("ERROR STATE");
        break;
    }
}

void Enemy_Barrel::OnCollision(Collider* collider) {
    if (collider->type == Collider::Type::PLAYER_SHOT) {
        health--;
        if (health == 0) {
            App->audio->PlayFx(destroyedFx);
            SetToDelete();
        }
    }
}