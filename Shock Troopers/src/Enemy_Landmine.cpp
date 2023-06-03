#include "Enemy_Landmine.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Particle.h"

Enemy_Landmine::Enemy_Landmine(int x, int y) : Enemy(x, y) {

    int disX = 0;
    for (int i = 0; i < 4; i++)
    {
        idleAnim.PushBack({ disX, 0, 28, 16 });
        disX+= 28;
    }

    idleAnim.speed = 0.1f;
    
    path.PushBack({ 0.0f, 0.0f }, 150, &idleAnim);

    // TODO cambiar tama�o collider
    collider = App->collisions->AddCollider({ 0, 0, 28, 16 }, Collider::Type::LANDMINE, (Module*)App->enemies);

    health = 1;
}

void Enemy_Landmine::Update() {

    path.Update();
    position = spawnPos + path.GetRelativePosition();
    //currentAnim = &spawnAnim;

    // Call to the base class. It must be called at the end
    // It will update the collider depending on the position
    Enemy::Update();
}

void Enemy_Landmine::deathAnimation() {
    currentAnim = &deathAnim;
}

void Enemy_Landmine::spawnAnimation() {
    currentAnim = &spawnAnim;
}

void Enemy_Landmine::idleAnimation() {
    currentAnim = &idleAnim;
}

void Enemy_Landmine::StateMachine() {
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
        if (this->health == 0) {
            state = Enemy_State::DEATH;
        }
        break;
    case Enemy_State::DEATH:
        deathAnimation();

        if (deathAnimDelay == 0) {
            Particle* newParticle = nullptr;
            newParticle = App->particles->AddParticle(App->particles->landmineExplosion, this->position.x-14, this->position.y-24, Collider::Type::NONE);
            pendingToDelete = true;
        }
        deathAnimDelay--;

        break;

    default:
        // Handle default state logic
        break;
    }
}

void Enemy_Landmine::OnCollision(Collider* collider) {
    if (collider->type == Collider::Type::PLAYER) {
        health--;
        if (health == 0) {
            App->audio->PlayFx(destroyedFx);
            SetToDelete();
        }
    }
}