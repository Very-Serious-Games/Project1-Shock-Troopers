#include "Enemy_BarrelGroup.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

Enemy_BarrelGroup::Enemy_BarrelGroup(int x, int y) : Enemy(x, y) {

    spawnAnim.PushBack({ 0, 0, 90, 126 });

    idleAnim.PushBack({ 0, 0, 90, 126 });

    int disX = 0;
    for (int i = 0; i < 54; i++)
    {
        deathAnim.PushBack({ disX, 0, 90, 126 });
        disX += 90;
    }
    deathAnim.speed = 0.4f;
    deathAnim.loop = false;

    path.PushBack({ 0.0f, 0.0f }, 600, &deathAnim);

    // TODO cambiar tamaño collider//
    collider = App->collisions->AddCollider({ 0, 0, 70, 56 }, Collider::Type::OBJECT, (Module*)App->enemies);
    collider->SetPos(position.x + 7, position.y + 64);
    health = 5;
}

void Enemy_BarrelGroup::Update() {

    path.Update();
    position = spawnPos + path.GetRelativePosition();

    Enemy::Update();
}

void Enemy_BarrelGroup::deathAnimation() {
    currentAnim = &deathAnim;
}

void Enemy_BarrelGroup::spawnAnimation() {
    currentAnim = &spawnAnim;
}

void Enemy_BarrelGroup::idleAnimation() {
    currentAnim = &idleAnim;
}

void Enemy_BarrelGroup::StateMachine() {
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

void Enemy_BarrelGroup::OnCollision(Collider* collider) {
    if (collider->type == Collider::Type::PLAYER_SHOT) {
        health--;
        if (health == 0) {
            App->audio->PlayFx(App->enemies->tankDestroyed);
            SetToDelete();
        }
    }
}