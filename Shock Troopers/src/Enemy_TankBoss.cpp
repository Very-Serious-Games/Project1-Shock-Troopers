#include "Enemy_TankBoss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Particle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

Enemy_TankBoss::Enemy_TankBoss(int x, int y) : Enemy(x, y) {

    // animations
    emptyAnimation.PushBack({ 0,0,0,0 });

    topAnimDown.PushBack(                   {52*7,31,52,31});
    topAnimUp.PushBack(                     {52*6,31,52,31});
    topAnimLeft.PushBack(                   {52*1,31,52,31});
    topAnimRight.PushBack(                  {52*0,31,52,31});
    topAnimDownLeft.PushBack(               {52*5,31,52,31});
    topAnimDownRight.PushBack(              {52*4,31,52,31});
    topAnimUpLeft.PushBack(                 {52*3,31,52,31});
    topAnimUpRight.PushBack(                {52*2,31,52,31});
                                             
    hitTopAnimDown.PushBack(                {52*7,0,52,31});
    hitTopAnimUp.PushBack(                  {52*6,0,52,31});
    hitTopAnimLeft.PushBack(                {52*1,0,52,31});
    hitTopAnimRight.PushBack(               {52*0,0,52,31});
    hitTopAnimDownLeft.PushBack(            {52*7,0,52,31});
    hitTopAnimDownRight.PushBack(           {52*4,0,52,31});
    hitTopAnimUpLeft.PushBack(              {52*3,0,52,31});
    hitTopAnimUpRight.PushBack(             {52*2,0,52,31});
                                     
    midAnimDown.PushBack(                   {114*0,62,114,74});
    midAnimLeft.PushBack(                   {114*6,62,114,74});
    midAnimRight.PushBack(                  {114*5,62,114,74});
    midAnimDownLeft.PushBack(               {114*2,62,114,74});
    midAnimDownRight.PushBack(              {114*1,62,114,74});
    midAnimDownLeftDiagonal.PushBack(       {114*4,62,114,74});
    midAnimDownRightDiagonal.PushBack(      {114*3,62,114,74});
                                     
    hitMidAnimDown.PushBack(                {114*6,136,114,74});
    hitMidAnimLeft.PushBack(                {114*5,136,114,74});
    hitMidAnimRight.PushBack(               {114*4,136,114,74});
    hitMidAnimDownLeft.PushBack(            {114*1,136,114,74});
    hitMidAnimDownRight.PushBack(           {114*0,136,114,74});
    hitMidAnimDownLeftDiagonal.PushBack(    {114*3,136,114,74});
    hitMidAnimDownRightDiagonal.PushBack(   {114*2,136,114,74});

    botAnimMoving.PushBack(                 {0,210,109,163});
    botAnimMoving.PushBack(                 {109,210,109,163});
    botAnimMoving.PushBack(                 {218,210,109,163});
    botAnimMoving.PushBack(                 {327,210,109,163});
    
    hitBotAnimMoving.PushBack(              {0,374,109,163});

    deathAnim.PushBack(                     {109,374,109,163});

    soldierGrenadeRightAnim.PushBack(       {109, 535, 50, 38});
    soldierGrenadeRightAnim.PushBack(       {159, 535, 50, 38});
    soldierGrenadeRightAnim.PushBack(       {209, 535, 50, 38});
    soldierGrenadeRightAnim.PushBack(       {9, 535, 50, 38});
    soldierGrenadeRightAnim.PushBack(       {59, 535, 50, 38});

    soldierGrenadeFrontAnim.PushBack(       {0, 612, 38, 50});
    soldierGrenadeFrontAnim.PushBack(       {38, 612, 38, 50});
    soldierGrenadeFrontAnim.PushBack(       {155, 612, 38, 50});
    soldierGrenadeFrontAnim.PushBack(       {117, 612, 38, 50});
    soldierGrenadeFrontAnim.PushBack(       {79, 612, 38, 50});

    soldierGrenadeLeftAnim.PushBack(        {200, 574, 50, 38});
    soldierGrenadeLeftAnim.PushBack(        {150, 574, 50, 38});
    soldierGrenadeLeftAnim.PushBack(        {100, 574, 50, 38});
    soldierGrenadeLeftAnim.PushBack(        {50, 574, 50, 38});
    soldierGrenadeLeftAnim.PushBack(        {0, 574, 50, 38});

    soldierHideAnim.PushBack(               {28, 697, 21, 15});
    //no need to set speed since it only has 1 frame

    soldierPointAnim.PushBack({0, 661, 27, 51}); //28?
    //no need to set speed since it only has 1 frame

    soldierUpAnim.PushBack({0, 713, 30, 53});  
    soldierUpAnim.PushBack({31, 713, 30, 53});
    soldierUpAnim.PushBack({62, 713, 30, 53});
    soldierUpAnim.PushBack({93, 713, 30, 53});
    soldierUpAnim.PushBack({124, 713, 30, 53});
    soldierUpAnim.PushBack({155, 713, 30, 55});
    soldierUpAnim.PushBack({186, 713, 30, 55});
    soldierUpAnim.PushBack({217, 713, 30, 55});
    soldierUpAnim.PushBack({248, 713, 30, 55});

    botAnimMoving.speed = 0.1f;
    soldierGrenadeFrontAnim.speed = 0.1f;
    soldierGrenadeLeftAnim.speed = 0.1f;
    soldierGrenadeRightAnim.speed = 0.1f;
    soldierUpAnim.speed = 0.1f;

    // TODO cambiar tamaño collider
    collider = App->collisions->AddCollider({ 0, 0, 109, 163 }, Collider::Type::ENEMY, (Module*)App->enemies);

    path.PushBack({0,0}, 200, &botAnimMoving);
    //path.PushBack({0,100}, 200, &botAnimMoving);
    //path.PushBack({0,0}, 200, &botAnimMoving);
    //path.PushBack({0,-100}, 200, &botAnimMoving);

    this->health = 2000;

}

void Enemy_TankBoss::Update() {

    StateMachine();

    path.Update();
    position = spawnPos + path.GetRelativePosition();
    botAnimMoving.Update();

    // Call to the base class. It must be called at the end
    // It will update the collider depending on the position
    Enemy::Update();

}

void Enemy_TankBoss::OnCollision(Collider* collider) {
    if (collider->type == Collider::Type::PLAYER_SHOT) {
        isHitted = true;
    }

    this->health = health - 10; // TODO : change this to the damage of the bullet

    if (health <= 0) {
        App->particles->AddParticle(App->particles->explosion, position.x, position.y, 0);
        App->audio->PlayFx(destroyedFx);
        SetToDelete();
    }
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
        Particle* newParticle = nullptr;
        Particle* newParticleMuzzle = nullptr;

        switch (GetPlayerDirectionBelow()) {
        case 9: // Down-Right
            newParticle = App->particles->AddParticle(App->particles->tankShotDownRight, position.x + 65, position.y - 10, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleDownRight, position.x + 65, position.y - 10, 0, Collider::Type::MUZZLE);
            newParticle->collider->AddListener(NULL);
            newParticleMuzzle->collider->AddListener(NULL);
            break;
        case 10: // Down-Left
            newParticle = App->particles->AddParticle(App->particles->tankShotDownLeft, position.x - 10, position.y - 10, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleDownLeft, position.x - 10, position.y - 10, 0, Collider::Type::MUZZLE);
            newParticle->collider->AddListener(NULL);
            newParticleMuzzle->collider->AddListener(NULL);
            break;
        case 5: // Down-Right-Diagonal
            newParticle = App->particles->AddParticle(App->particles->tankShotDownRight, position.x + 63, position.y + 28, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleDownRight, position.x + 63, position.y + 28, 0, Collider::Type::MUZZLE);
            newParticle->collider->AddListener(NULL);
            newParticleMuzzle->collider->AddListener(NULL);
            break;
        case 6: // Down-Left-Diagonal
            newParticle = App->particles->AddParticle(App->particles->tankShotDownLeft, position.x - 10, position.y + 35, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleDownLeft, position.x - 10, position.y + 35, 0, Collider::Type::MUZZLE);
            newParticle->collider->AddListener(NULL);
            newParticleMuzzle->collider->AddListener(NULL);
            break;
        case 3: // Right
            newParticle = App->particles->AddParticle(App->particles->tankShotRight, position.x + 70, position.y + 10, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleRight, position.x + 70, position.y + 10, 0, Collider::Type::MUZZLE);
            newParticle->collider->AddListener(NULL);
            newParticleMuzzle->collider->AddListener(NULL);
            break;
        case 4: // Left
            newParticle = App->particles->AddParticle(App->particles->tankShotLeft, position.x - 20, position.y + 10, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleLeft, position.x - 20, position.y + 10, 0, Collider::Type::MUZZLE);
            newParticle->collider->AddListener(NULL);
            newParticleMuzzle->collider->AddListener(NULL);
            break;
        case 7: // Down
            newParticle = App->particles->AddParticle(App->particles->tankShotDown, position.x + 24, position.y + 50, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->miniTankMuzzleDown, position.x + 24, position.y + 50, 0, Collider::Type::MUZZLE);
            newParticle->collider->AddListener(NULL);
            newParticleMuzzle->collider->AddListener(NULL);
            break;
        default:
            LOG("Pleyer above boss");
			break;
        }
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

        Particle* newParticle = nullptr;
        Particle* newParticleMuzzle = nullptr;

        switch (GetPlayerDirection()) {
        case 1: // Up-Right
            newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x + 30, position.y - 2, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleUpRight, position.x + 30, position.y - 2, 0, Collider::Type::MUZZLE);
            break;
        case 2: // Up-Left
            newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x - 3, position.y - 3, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleUpLeft, position.x - 3, position.y - 3, 0, Collider::Type::MUZZLE);
            break;
        case 3: // Down-Right
            newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x + 10, position.y + 25, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleDownRight, position.x + 10, position.y + 25, 0, Collider::Type::MUZZLE);
            break;
        case 4: // Down-Left
            newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x + 5, position.y + 25, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleDownLeft, position.x + 0, position.y + 25, 0, Collider::Type::MUZZLE);
            break;
        case 5: // Right
            newParticle = App->particles->AddParticle(App->particles->enemyShot, (collider->rect.w / 2), position.y + (collider->rect.h / 2), GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleRight, position.x + 35, position.y + 8, 0, Collider::Type::MUZZLE);
            break;
        case 6: // Left
            newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x - 10, position.y + 15, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleLeft, position.x - 10, position.y + 10, 0, Collider::Type::MUZZLE);
            break;
        case 7: // Down
            newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x + 10, position.y + 30, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleDown, position.x + 5, position.y + 30, 0, Collider::Type::MUZZLE);
            break;
        case 8: // Up
            newParticle = App->particles->AddParticle(App->particles->enemyShot, position.x + 0, position.y - 10, GetPlayerDirection(), Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->enemyMuzzleUp, position.x + 0, position.y - 10, 0, Collider::Type::MUZZLE);
            break;
        }

        newParticle->collider->AddListener(NULL);
        newParticleMuzzle->collider->AddListener(NULL);

        App->audio->PlayFx(NULL);

        delayShoot = 100;
    }
}

void Enemy_TankBoss::grenade() {

}

void Enemy_TankBoss::missileRain() {
    int numMissiles = rand() % 8 + 3; // Generate a random number between 3 and 10

    delayMissileRain--;
    if (delayMissileRain == 0) {
        for (int i = 0; i < numMissiles; ++i) {
            
            Particle* missile = App->particles->AddParticle(App->particles->tankMissileUp, position.x + (rand() % SCREEN_WIDTH), position.y + 10 + (rand() % (SCREEN_WIDTH/2)), 7, Collider::Type::ENEMY_SHOT);
            missile->collider->AddListener(NULL);
            missile->speed.y = 1;
            App->audio->PlayFx(/*sound effect*/NULL);
        }
        delayMissileRain = 700;
    }
}

void Enemy_TankBoss::missileLaunch() {
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

    delayMissile--;
    if (delayMissile == 0) {
        // TODO modify shot to be an missile
        /*
        Particle* shot = App->particles->AddParticle(App->particles->playerShot, position.x + (collider->rect.w / 2), position.y + (collider->rect.h / 2), GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
        shot->collider->AddListener(NULL);
        */
        Particle* newParticle = nullptr;

        switch (GetPlayerDirectionBelow()) {
        case 9: // Down-Right
            newParticle = App->particles->AddParticle(App->particles->tankMissileRight, position.x + 65, position.y - 10, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticle->collider->AddListener(NULL);
            break;
        case 10: // Down-Left
            newParticle = App->particles->AddParticle(App->particles->tankMissileLeft, position.x - 10, position.y - 10, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticle->collider->AddListener(NULL);
            break;
        case 5: // Down-Right-Diagonal 
            newParticle = App->particles->AddParticle(App->particles->tankMissileRight, position.x + 63, position.y + 28, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticle->collider->AddListener(NULL);
            break;
        case 6: // Down-Left-Diagonal 
            newParticle = App->particles->AddParticle(App->particles->tankMissileLeft, position.x - 10, position.y + 35, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticle->collider->AddListener(NULL);
            break;
        case 3: // Right 
            newParticle = App->particles->AddParticle(App->particles->tankMissileDownRight, position.x + 70, position.y + 10, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticle->collider->AddListener(NULL);
            break;
        case 4: // Left 
            newParticle = App->particles->AddParticle(App->particles->tankMissileDownLeft, position.x - 20, position.y + 10, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticle->collider->AddListener(NULL);
            break;
        case 7: // Down
            newParticle = App->particles->AddParticle(App->particles->tankMissileDown, position.x + 24, position.y + 50, GetPlayerDirectionBelow(), Collider::Type::ENEMY_SHOT);
            newParticle->collider->AddListener(NULL);
            break;
        default:
            LOG("Pleyer above boss");
            break;
        }
        App->audio->PlayFx(/*sound effect*/NULL);
        delayMissile = 700;
    }
}

void Enemy_TankBoss::Attack() {
    canon();
    shot();
    //grenade();
    missileRain();
    missileLaunch();
}

void Enemy_TankBoss::deathAnimation() {
    topCurrentAnim = &emptyAnimation;
    midCurrentAnim = &emptyAnimation;
    botCurrentAnim = &deathAnim;
}

void Enemy_TankBoss::idleAnimation(int direction, int directionBelow) {
    botCurrentAnim = &botAnimMoving;
    switch (direction) {
    case 1: //UR
        topCurrentAnim = &topAnimUpRight;
        break;
    case 2: //UL
        topCurrentAnim = &topAnimUpLeft;
        break;
    case 3: //DR
        topCurrentAnim = &topAnimDownRight;
        break;
    case 4: //DL
        topCurrentAnim = &topAnimDownLeft;
        break;
    case 5: //R
        topCurrentAnim = &topAnimRight;
        break;
    case 6: //L
        topCurrentAnim = &topAnimLeft;
        break;
    case 7: //D
        topCurrentAnim = &topAnimDown;
        break;
    case 8: //U
        topCurrentAnim = &topAnimUp;
        break;
    }

    switch (directionBelow) {
    case 9: // Down-Right
        midCurrentAnim = &midAnimDownRight;
        break;
    case 10: // Down-Left
        midCurrentAnim = &midAnimDownLeft;
        break;
    case 5: // Right
        midCurrentAnim = &midAnimRight;
        break;
    case 6: // Left
        midCurrentAnim = &midAnimLeft;
        break;
    case 3: // Down-Right-Diagonal
        midCurrentAnim = &midAnimDownRightDiagonal;
        break;
    case 4: // Down-Left-Diagonal
        midCurrentAnim = &midAnimDownLeftDiagonal;
        break;
    case 7: // Below
        midCurrentAnim = &midAnimDown;
        break;
    }
}

void Enemy_TankBoss::hitAnimation(int direction, int directionBelow) {
    botCurrentAnim = &hitBotAnimMoving;
    switch (direction) {
    case 1: // UR
        topCurrentAnim = &hitTopAnimUpRight;
        break;
    case 2: // UL
        topCurrentAnim = &hitTopAnimUpLeft;
        break;
    case 3: // DR
        topCurrentAnim = &hitTopAnimDownRight;
        break;
    case 4: // DL
        topCurrentAnim = &hitTopAnimDownLeft;
        break;
    case 5: // R
        topCurrentAnim = &hitTopAnimRight;
        break;
    case 6: // L
        topCurrentAnim = &hitTopAnimLeft;
        break;
    case 7: // D
        topCurrentAnim = &hitTopAnimDown;
        break;
    case 8: // U
        topCurrentAnim = &hitTopAnimUp;
        break;
    };

    switch (directionBelow) {
    case 9: // Down-Right
        midCurrentAnim = &hitMidAnimDownRight;
        break;
    case 10: // Down-Left
        midCurrentAnim = &hitMidAnimDownLeft;
        break;
    case 5: // Right
        midCurrentAnim = &hitMidAnimRight;
        break;
    case 6: // Left
        midCurrentAnim = &hitMidAnimLeft;
        break;
    case 3: // Down-Right-Diagonal
        midCurrentAnim = &hitMidAnimDownRightDiagonal;
        break;
    case 4: // Down-Left-Diagonal
        midCurrentAnim = &hitMidAnimDownLeftDiagonal;
        break;
    case 7: // Below
        midCurrentAnim = &hitMidAnimDown;
        break;
    };
}

void Enemy_TankBoss::StateMachine() {
    switch (state) {
    case Enemy_State::SPAWN:
        state = Enemy_State::IDLE;
        break;
    case Enemy_State::IDLE:
        idleAnimation(GetPlayerDirection(), GetPlayerDirectionBelow());
        if (PlayerIsNear()) {
            state = Enemy_State::ATTACK;
        }

        if (isHitted) {
            state = Enemy_State::HIT;
        }

        break;
    case Enemy_State::ATTACK:
        idleAnimation(GetPlayerDirection(), GetPlayerDirectionBelow());

        Attack();

        if (!PlayerIsNear()) {
            state = Enemy_State::IDLE;
        }

        if (isHitted) {
            state = Enemy_State::HIT;
        }

        if (this->health == 0) {
            state = Enemy_State::DEATH;
        }
        break;
    case Enemy_State::DEATH:
        deathAnimation();
        if (deathAnimDelay == 0) {
            App->enemies->winCondition = true;
            App->render->leaveZone = true;
            pendingToDelete = true;
            LOG("pendingToDelete enemy");
        }

        deathAnimDelay--;

        break;

    case Enemy_State::HIT:
        hitAnimation(GetPlayerDirection(), GetPlayerDirectionBelow());
        isHitted = false;
        state = Enemy_State::IDLE;
        break;
    }
}