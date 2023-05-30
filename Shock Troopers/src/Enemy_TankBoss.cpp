#include "Enemy_TankBoss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Particle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

Enemy_TankBoss::Enemy_TankBoss(int x, int y) : Enemy(x, y) {

    // TODO cambiar tamaño collider
    collider = App->collisions->AddCollider({ 0, 0, 121, 124 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_TankBoss::Update() {

    path.Update();
    position = spawnPos + path.GetRelativePosition();
    //currentAnim = path.GetCurrentAnimation();
    currentAnim = &spawnAnim;

    // Call to the base class. It must be called at the end
    // It will update the collider depending on the position
    Enemy::Update();
}

void Enemy_TankBoss::canon() {
    // Get the player position
    fPoint playerPos = App->player->position;

    // Calculate the direction vector from enemy position to player position
    fPoint enemyPos = position;
    fPoint direction = playerPos - enemyPos;

    // Normalize the direction vector
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }

    delayCanon--;
    if (delayCanon == 0) {
        // TODO modify shot to be an enemy shot
        Particle* shot = App->particles->AddParticle(App->particles->playerShot, position.x, position.y, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
        shot->collider->AddListener(NULL);
        App->audio->PlayFx(/*sound effect*/NULL);
        delayCanon = 700;
    }
}

void Enemy_TankBoss::shot() {
    // Get the player position
    fPoint playerPos = App->player->position;

    // Calculate the direction vector from enemy position to player position
    fPoint enemyPos = position;
    fPoint direction = playerPos - enemyPos;

    // Normalize the direction vector
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }

    delayShoot--;
    if (delayShoot == 0) {
        // TODO modify shot to be an enemy shot
        Particle* shot = App->particles->AddParticle(App->particles->playerShot, position.x, position.y, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
        shot->collider->AddListener(NULL);
        App->audio->PlayFx(/*sound effect*/NULL);
        delayShoot = 700;
    }
}

void Enemy_TankBoss::grenade() {

}

void Enemy_TankBoss::deathAnimation() {
    currentAnim = &deathAnim;
}

void Enemy_TankBoss::idleAnimation() {
    currentAnim = &idleAnim;
}

void Enemy_TankBoss::Attack() {

    // TODO ataque
    canon();
    shot();
    grenade();

}

void Enemy_TankBoss::StateMachine() {
    switch (state) {
    case Enemy_State::IDLE:
        idleAnimation();
        if (PlayerIsNear()) {
            state = Enemy_State::ATTACK;
            LOG("state changed to ATTACK");
        }
        break;
    case Enemy_State::ATTACK:
        idleAnimation();
        Attack();
        if (!PlayerIsNear()) {
            state = Enemy_State::IDLE;
            LOG("state changed to IDLE");
        }
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