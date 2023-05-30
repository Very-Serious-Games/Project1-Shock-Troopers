#include "Enemy_TankBoss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Particle.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

Enemy_TankBoss::Enemy_TankBoss(int x, int y) : Enemy(x, y) {

    // animations
    topAnimDown.PushBack(           {0,0,42,27});
    topAnimUp.PushBack(             {0,0,42,27});
    topAnimLeft.PushBack(           {0,0,42,27});
    topAnimRight.PushBack(          {0,0,42,27});
    topAnimDownLeft.PushBack(       {0,0,42,27});
    topAnimDownRight.PushBack(      {0,0,42,27});
    topAnimUpLeft.PushBack(         {0,0,42,27});
    topAnimUpRight.PushBack(        {0,0,42,27});
                                     
    hitTopAnimDown.PushBack(        {0,0,42,27});
    hitTopAnimUp.PushBack(          {0,0,42,27});
    hitTopAnimLeft.PushBack(        {0,0,42,27});
    hitTopAnimRight.PushBack(       {0,0,42,27});
    hitTopAnimDownLeft.PushBack(    {0,0,42,27});
    hitTopAnimDownRight.PushBack(   {0,0,42,27});
    hitTopAnimUpLeft.PushBack(      {0,0,42,27});
    hitTopAnimUpRight.PushBack(     {0,0,42,27});
                                     
    midAnimDown.PushBack(           {0,0,42,27});
    midAnimUp.PushBack(             {0,0,42,27});
    midAnimLeft.PushBack(           {0,0,42,27});
    midAnimRight.PushBack(          {0,0,42,27});
    midAnimDownLeft.PushBack(       {0,0,42,27});
    midAnimDownRight.PushBack(      {0,0,42,27});
    midAnimUpLeft.PushBack(         {0,0,42,27});
    midAnimUpRight.PushBack(        {0,0,42,27});
                                     
    hitMidAnimDown.PushBack(        {0,0,42,27});
    hitMidAnimUp.PushBack(          {0,0,42,27});
    hitMidAnimLeft.PushBack(        {0,0,42,27});
    hitMidAnimRight.PushBack(       {0,0,42,27});
    hitMidAnimDownLeft.PushBack(    {0,0,42,27});
    hitMidAnimDownRight.PushBack(   {0,0,42,27});
    hitMidAnimUpLeft.PushBack(      {0,0,42,27});
    hitMidAnimUpRight.PushBack(     {0,0,42,27});
                                     
    botAnimMoving.PushBack(         {0,0,42,27});
                                     
    hitBotAnimMoving.PushBack(      {0,0,42,27});
    deathAnim.PushBack(             {0,0,42,27});

    // TODO cambiar tamaño collider
    collider = App->collisions->AddCollider({ 0, 0, 200, 500 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_TankBoss::Update() {

    path.Update();
    position = spawnPos + path.GetRelativePosition();
    
    topCurrentAnim = &topAnimDown;
    midCurrentAnim = &midAnimDown;
    botCurrentAnim = &botAnimMoving;

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

    case Enemy_State::HIT:
        // hitanim
        break;
    default:
        // Handle default state logic
        LOG("ERROR STATE");
        break;
    }
}