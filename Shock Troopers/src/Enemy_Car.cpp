#include "Enemy_Car.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Car::Enemy_Car(int x, int y) : Enemy(x, y) {

    spawnAnim.PushBack({ 0, 0, 120, 112 });

    idleAnim.PushBack({ 0, 0, 120, 112 });

    int disX = 0;
    for (int i = 0; i < 62; i++)
    {
        deathAnim.PushBack({ disX, 0, 120, 112 });
        disX += 120;
    }
    deathAnim.speed = 0.3f;
    deathAnim.loop = false;

    path.PushBack({ 0.0f, 0.0f }, 600, &deathAnim);

    // TODO cambiar tamaño collider//
    collider = App->collisions->AddCollider({ 0, 0, 106, 101 }, Collider::Type::OBJECT, (Module*)App->enemies);

    health = 7;
}

void Enemy_Car::Update() {

    path.Update();
    position = spawnPos + path.GetRelativePosition();

    Enemy::Update();
}

void Enemy_Car::deathAnimation() {
    currentAnim = &deathAnim;
}

void Enemy_Car::spawnAnimation() {
    currentAnim = &spawnAnim;
}

void Enemy_Car::idleAnimation() {
    currentAnim = &idleAnim;
}

void Enemy_Car::StateMachine() {
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
            LOG("pendingToDelete Car");
        }
        break;
    default:
        // Handle default state logic
        LOG("ERROR STATE");
        break;
    }
}

void Enemy_Car::OnCollision(Collider* collider) {
    if (collider->type == Collider::Type::PLAYER_SHOT) {
        health--;
        if (health == 0) {
            App->audio->PlayFx(destroyedFx);
            SetToDelete();
        }
    }
}