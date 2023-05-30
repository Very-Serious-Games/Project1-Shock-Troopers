#include "Enemy_TankBoss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Particle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

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
                                     
    midAnimDown.PushBack(                   {114*7,62,114,74});
    midAnimLeft.PushBack(                   {114*6,62,114,74});
    midAnimRight.PushBack(                  {114*5,62,114,74});
    midAnimDownLeft.PushBack(               {114*1,62,114,74});
    midAnimDownRight.PushBack(              {114*2,62,114,74});
    midAnimDownLeftDiagonal.PushBack(       {114*4,62,114,74});
    midAnimDownRightDiagonal.PushBack(      {114*3,62,114,74});
                                     
    hitMidAnimDown.PushBack(                {114*7,136,114,74});
    hitMidAnimLeft.PushBack(                {114*6,136,114,74});
    hitMidAnimRight.PushBack(               {114*5,136,114,74});
    hitMidAnimDownLeft.PushBack(            {114*1,136,114,74});
    hitMidAnimDownRight.PushBack(           {114*2,136,114,74});
    hitMidAnimDownLeftDiagonal.PushBack(    {114*4,136,114,74});
    hitMidAnimDownRightDiagonal.PushBack(   {114*3,136,114,74});

    botAnimMoving.PushBack(                 {0,210,109,163});
    botAnimMoving.PushBack(                 {109,210,109,163});
    botAnimMoving.PushBack(                 {218,210,109,163});
    botAnimMoving.PushBack(                 {327,210,109,163});
    
    hitBotAnimMoving.PushBack(              {0,374,109,163});

    deathAnim.PushBack(                     {109,374,109,163});

    botAnimMoving.speed = 0.1f;

    // TODO cambiar tama�o collider
    collider = App->collisions->AddCollider({ 0, 0, 109, 163 }, Collider::Type::ENEMY, (Module*)App->enemies);

    path.PushBack({0,0}, 200, &botAnimMoving);
    //path.PushBack({0,100}, 200, &botAnimMoving);
    //path.PushBack({0,0}, 200, &botAnimMoving);
    //path.PushBack({0,-100}, 200, &botAnimMoving);

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

void Enemy_TankBoss::Attack() {

    canon();
    shot();
    grenade();

}

void Enemy_TankBoss::deathAnimation() {
    topCurrentAnim = &emptyAnimation;
    midCurrentAnim = &emptyAnimation;
    botCurrentAnim = &deathAnim;
}

void Enemy_TankBoss::idleAnimation(int direction, int directionBelow) {
    botCurrentAnim = &botAnimMoving;
    switch (direction) {
    case 1: //UR - Down-Right (60�)
        topCurrentAnim = &topAnimUpRight;
        midCurrentAnim = &midAnimDownRight;
        break;
    case 2: //UL - Down-Left (120�)
        topCurrentAnim = &topAnimUpLeft;
        midCurrentAnim = &midAnimDownLeft;
        break;
    case 3: //DR - Right (180�)
        topCurrentAnim = &topAnimDownRight;
        midCurrentAnim = &midAnimRight;
        break;
    case 4: //DL - Left (0�)
        topCurrentAnim = &topAnimDownLeft;
        midCurrentAnim = &midAnimLeft;
        break;
    case 5: //R - Down-Right-Diagonal (135�)
        topCurrentAnim = &topAnimRight;
        midCurrentAnim = &midAnimDownRightDiagonal;
        break;
    case 6: //L - Down-Left-Diagonal (45�)
        topCurrentAnim = &topAnimLeft;
        midCurrentAnim = &midAnimDownLeftDiagonal;
        break;
    case 7: //D - Below (90�)
        topCurrentAnim = &topAnimDown;
        midCurrentAnim = &midAnimDown;
        break;
    case 8: //U
        topCurrentAnim = &topAnimUp;
        break;
    }
}

void Enemy_TankBoss::hitAnimation(int direction, int directionBelow) {
    botCurrentAnim = &hitBotAnimMoving;
    switch (direction) {
    case 1: //UR - Down-Right (60�)
        topCurrentAnim = &hitTopAnimUpRight;
        midCurrentAnim = &hitMidAnimDownRight;
        break;
    case 2: //UL - Down-Left (120�)
        topCurrentAnim = &hitTopAnimUpLeft;
        midCurrentAnim = &hitMidAnimDownLeft;
        break;
    case 3: //DR - Right (180�)
        topCurrentAnim = &hitTopAnimDownRight;
        midCurrentAnim = &hitMidAnimRight;
        break;
    case 4: //DL - Left (0�)
        topCurrentAnim = &hitTopAnimDownLeft;
        midCurrentAnim = &hitMidAnimLeft;
        break;
    case 5: //R - Down-Right-Diagonal (135�)
        topCurrentAnim = &hitTopAnimRight;
        midCurrentAnim = &hitMidAnimDownRightDiagonal;
        break;
    case 6: //L - Down-Left-Diagonal (45�)
        topCurrentAnim = &hitTopAnimLeft;
        midCurrentAnim = &hitMidAnimDownLeftDiagonal;
        break;
    case 7: //D - Below (90�)
        topCurrentAnim = &hitTopAnimDown;
        midCurrentAnim = &hitMidAnimDown;
        break;
    case 8: //U
        topCurrentAnim = &hitTopAnimUp;
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
            //LOG("state changed to ATTACK");
        }

        if (isHitted) {
            state = Enemy_State::HIT;
        }

        break;
    case Enemy_State::ATTACK:
        idleAnimation(GetPlayerDirection(), GetPlayerDirectionBelow());
        //Attack();
        if (!PlayerIsNear()) {
            state = Enemy_State::IDLE;
            //LOG("state changed to IDLE");
        }

        if (isHitted) {
            state = Enemy_State::HIT;
        }

        if (this->health == 0) {
            state = Enemy_State::DEATH;
            //LOG("state changed to DEATH");
        }
        break;
    case Enemy_State::DEATH:
        deathAnimation();
        if (deathAnimDelay == 0) {
            pendingToDelete = true;
            //LOG("pendingToDelete enemy");
        }

        deathAnimDelay--;

        break;

    case Enemy_State::HIT:
        hitAnimation(GetPlayerDirection(), GetPlayerDirectionBelow());
        isHitted = false;
        state = Enemy_State::IDLE;
        break;
    default:
        // Handle default state logic
        //LOG("ERROR STATE");
        break;
    }
}