#include "Enemy_Sandbag.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

Enemy_Sandbag::Enemy_Sandbag(int x, int y) : Enemy(x, y) {

    spawnAnim.PushBack({ 0, 0, 109, 178 });

    idleAnim.PushBack({ 0, 0, 109, 178 });

    int disX = 0;
    for (int i = 0; i < 35; ++i)
    {
        brokenAnim.PushBack({ disX, 0, 109, 178 });
        disX += 109;
    }
    brokenAnim.speed = 0.5f;
    brokenAnim.loop = false;

    path.PushBack({ 0.0f, 0.0f }, 360, &brokenAnim);

    idlebrokenAnim.PushBack({ disX, 0, 109, 178 });

    for (int j = 0; j < 48; ++j)
    {
        deathAnim.PushBack({ disX, 0, 109, 178 });
        disX += 109;
    }
    deathAnim.speed = 0.5f;
    deathAnim.loop = false;

    path.PushBack({ 0.0f, 0.0f }, 480, &deathAnim);

    // TODO cambiar tama�o collider
    collider = App->collisions->AddCollider({ 0, 0, 94, 42 }, Collider::Type::OBJECT, (Module*)App->enemies);
    collider->SetPos(position.x + 4, position.y + 66);
    health = 10;
}

void Enemy_Sandbag::Update() {

    path.Update();
    position = spawnPos + path.GetRelativePosition();
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
        idleAnimation();
        if (this->health <= 5)
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

void Enemy_Sandbag::OnCollision(Collider* collider) {
    if (collider->type == Collider::Type::PLAYER_SHOT) {
        health --;
        App->audio->PlayFx(App->enemies->bridgeDamaged);
        if (health == 0) {
            App->audio->PlayFx(App->enemies->bridgeDestroyed);
            SetToDelete();
        }
    }
}