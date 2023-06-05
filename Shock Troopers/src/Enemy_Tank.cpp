#include "Enemy_Tank.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Particle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

Enemy_Tank::Enemy_Tank(int x, int y) : Enemy(x, y) {

    // animations
    moveAnim.PushBack(              { 86 * 1,69 * 3,86,69 });
    moveAnim.PushBack(              { 86 * 2,69 * 3,86,69 });
    moveAnim.PushBack(              { 86 * 3,69 * 3,86,69 });
    moveAnim.PushBack(              { 86 * 4,69 * 3,86,69 });

    hitMoveAnim.PushBack(           { 86 * 1,69 * 1,86,69 });
    hitMoveAnim.PushBack(           { 86 * 2,69 * 1,86,69 });
    hitMoveAnim.PushBack(           { 86 * 3,69 * 1,86,69 });
    hitMoveAnim.PushBack(           { 86 * 4,69 * 1,86,69 });

    idleAnimUp.PushBack(            { 86 * 3,69 * 2,86,69 });
    idleAnimDown.PushBack(          { 86 * 4,69 * 2,86,69 });
    idleAnimLeft.PushBack(          { 86 * 1,69 * 2,86,69 });
    idleAnimRight.PushBack(         { 86 * 6,69 * 2,86,69 });
    idleAnimDownLeft.PushBack(      { 86 * 0,69 * 2,86,69 });
    idleAnimDownRight.PushBack(     { 86 * 5,69 * 2,86,69 });
    idleAnimUpLeft.PushBack(        { 86 * 2,69 * 2,86,69 });
    idleAnimUpRight.PushBack(       { 86 * 7,69 * 2,86,69 });

    hitIdleAnimUp.PushBack(         { 86 * 3,69 * 0,86,69 });
    hitIdleAnimDown.PushBack(       { 86 * 4,69 * 0,86,69 });
    hitIdleAnimLeft.PushBack(       { 86 * 1,69 * 0,86,69 });
    hitIdleAnimRight.PushBack(      { 86 * 6,69 * 0,86,69 });
    hitIdleAnimDownLeft.PushBack(   { 86 * 0,69 * 0,86,69 });
    hitIdleAnimDownRight.PushBack(  { 86 * 5,69 * 0,86,69 });
    hitIdleAnimUpLeft.PushBack(     { 86 * 2,69 * 0,86,69 });
    hitIdleAnimUpRight.PushBack(    { 86 * 7,69 * 0,86,69 });

    deathAnim.PushBack(             { 86 * 0,69 * 3,86,69 });

    collider = App->collisions->AddCollider({ 0, 0, 86, 69 }, Collider::Type::ENEMY, (Module*)App->enemies);

    this->health = 150;

}

void Enemy_Tank::OnCollision(Collider* collider) {
    if (collider->type == Collider::Type::PLAYER_SHOT) {
        isHitted = true;
    }

    this->health = health - 10;

    if (health <= 0) {
        App->particles->AddParticle(App->particles->explosion, position.x, position.y, 0);
        App->audio->PlayFx(App->enemies->tankDestroyed);
        SetToDelete();
    }
}

void Enemy_Tank::Update() {

    StateMachine();

    path.Update();
    position = spawnPos + path.GetRelativePosition();
    //botAnimMoving.Update();

    // Call to the base class. It must be called at the end
    // It will update the collider depending on the position
    Enemy::Update();

}

void Enemy_Tank::deathAnimation() {
    currentAnim2 = &deathAnim;
}

void Enemy_Tank::idleAnimation(int direction) {
    currentAnim2 = &moveAnim;
    switch (direction) {
    case 1: //UR
        currentAnim = &idleAnimUpRight;
        break;
    case 2: //UL
        currentAnim = &idleAnimUpLeft;
        break;
    case 3: //DR
        currentAnim = &idleAnimDownRight;
        break;
    case 4: //DL
        currentAnim = &idleAnimDownLeft;
        break;
    case 5: //R
        currentAnim = &idleAnimRight;
        break;
    case 6: //L
        currentAnim = &idleAnimLeft;
        break;
    case 7: //D
        currentAnim = &idleAnimDown;
        break;
    case 8: //U
        currentAnim = &idleAnimUp;
        break;
    }
}

void Enemy_Tank::hitAnimation(int direction) {
    currentAnim2 = &hitMoveAnim;
    switch (direction) {
    case 1: //UR
        currentAnim = &hitIdleAnimUpRight;
        break;
    case 2: //UL
        currentAnim = &hitIdleAnimUpLeft;
        break;
    case 3: //DR
        currentAnim = &hitIdleAnimDownRight;
        break;
    case 4: //DL
        currentAnim = &hitIdleAnimDownLeft;
        break;
    case 5: //R
        currentAnim = &hitIdleAnimRight;
        break;
    case 6: //L
        currentAnim = &hitIdleAnimLeft;
        break;
    case 7: //D
        currentAnim = &hitIdleAnimDown;
        break;
    case 8: //U
        currentAnim = &hitIdleAnimUp;
        break;
    }
}

void Enemy_Tank::StateMachine() {
    switch (state) {
    case Enemy_State::SPAWN:

        state = Enemy_State::IDLE;
        LOG("state changed to IDLE");
        break;
    case Enemy_State::IDLE:
        idleAnimation(GetPlayerDirection());
        if (PlayerIsNear()) {
            state = Enemy_State::ATTACK;
            LOG("state changed to ATTACK");
        }
        if (isHitted) {
            state = Enemy_State::HIT;
        }
        break;
    case Enemy_State::ATTACK:
        idleAnimation(GetPlayerDirection());
        Attack();
        if (!PlayerIsNear()) {
            state = Enemy_State::IDLE;
            LOG("state changed to IDLE");
        }
        if (this->health == 0) {
            state = Enemy_State::DEATH;
            LOG("state changed to DEATH");
        }
        if (isHitted) {
            state = Enemy_State::HIT;
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

    case Enemy_State::HIT:
        hitAnimation(GetPlayerDirection());
        isHitted = false;
        state = Enemy_State::IDLE;
        break;
        break;
    }
}

void Enemy_Tank::Attack() {
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

        Particle* newParticle = nullptr;
        Particle* newParticleMuzzle = nullptr;
		switch (GetPlayerDirection()) {
		case 1: // Up-Right
			newParticle = App->particles->AddParticle(App->particles->miniTankShotUpRight, position.x + 65, position.y - 10, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleUpRight, position.x + 65, position.y - 10, 0, Collider::Type::MUZZLE);
			break;
		case 2: // Up-Left
			newParticle = App->particles->AddParticle(App->particles->miniTankShotUpLeft, position.x - 10, position.y - 10, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleUpLeft, position.x - 10, position.y - 10, 0, Collider::Type::MUZZLE);
			break;
		case 3: // Down-Right
			newParticle = App->particles->AddParticle(App->particles->miniTankShotDownRight, position.x + 63, position.y + 28, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleRight, position.x + 63, position.y + 28, 0, Collider::Type::MUZZLE);
			break;
		case 4: // Down-Left
			newParticle = App->particles->AddParticle(App->particles->miniTankShotDownLeft, position.x - 10, position.y + 35, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleDownLeft, position.x - 10, position.y + 35, 0, Collider::Type::MUZZLE);
			break;
		case 5: // Right
			newParticle = App->particles->AddParticle(App->particles->miniTankShotRight, position.x + 70, position.y + 10, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleRight, position.x + 70, position.y + 10, 0, Collider::Type::MUZZLE);
			break;
		case 6: // Left
			newParticle = App->particles->AddParticle(App->particles->miniTankShotLeft, position.x - 20, position.y + 10, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleLeft, position.x - 20, position.y + 10, 0, Collider::Type::MUZZLE);
			break;
		case 7: // Down
			newParticle = App->particles->AddParticle(App->particles->miniTankShotDown, position.x + 24, position.y + 50, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleDown, position.x + 24, position.y + 50, 0, Collider::Type::MUZZLE);
			break;
		case 8: // Up
			newParticle = App->particles->AddParticle(App->particles->miniTankShotUp, position.x + 22, position.y - 20, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleUp, position.x + 22, position.y - 20, 0, Collider::Type::MUZZLE);
			break;
		}

        newParticleMuzzle->collider->AddListener(NULL);
        newParticle->collider->AddListener(NULL);

        App->audio->PlayFx(App->enemies->tankShot);
        delayShoot = 700;
    }
}
