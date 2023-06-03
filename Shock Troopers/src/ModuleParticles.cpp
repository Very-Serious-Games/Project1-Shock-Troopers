#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
    for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
        particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start() {

    LOG("Loading particles");
    texture = App->textures->Load("Assets/sprites/particles/particles.png");
    if (texture == nullptr) {
        LOG("Error loading particles texture");
    }

    // Animations particle
    // Explosion
    explosion.anim.PushBack(                {});

    explosion.anim.loop = false;
    explosion.anim.speed = 0.3;
    explosion.lifetime = 180;

    // Shots
    // Flying battleship shot
    flyingbattleshipShot.anim.PushBack(     { 0, 0, 4, 4 });
    flyingbattleshipShot.anim.PushBack(     { 5, 0, 4, 4 });

    flyingbattleshipShot.anim.loop = true;
    flyingbattleshipShot.anim.speed = 0.3;
    flyingbattleshipShot.lifetime = 180;

    // Player shot
    playerShotUp.anim.PushBack(             { 1,    325,    6,  13  });
    playerShotUp.anim.PushBack(             { 9,    325,    6,  13  });
    playerShotDown.anim.PushBack(           { 1,    339,    6,  13  });
    playerShotDown.anim.PushBack(           { 9,    339,    6,  13  });
    playerShotLeft.anim.PushBack(           { 1,    362,    13, 6   });
    playerShotLeft.anim.PushBack(           { 15,   362,    13, 6   });
    playerShotRight.anim.PushBack(          { 1,    354,    13, 6   });
    playerShotRight.anim.PushBack(          { 15,   354,    13, 6   });
    playerShotUpRight.anim.PushBack(        { 1,    370,    12, 12  });
    playerShotUpRight.anim.PushBack(        { 15,   370,    12, 12  });
    playerShotUpLeft.anim.PushBack(         { 1,    384,    12, 12  });
    playerShotUpLeft.anim.PushBack(         { 15,   384,    12, 12  });
    playerShotDownRight.anim.PushBack(      { 1,    398,    12, 12  });
    playerShotDownRight.anim.PushBack(      { 15,   398,    12, 12  });
    playerShotDownLeft.anim.PushBack(       { 1,    413,    12, 12, });
    playerShotDownLeft.anim.PushBack(       { 15,   413,    12, 12, });

    playerShotUp.anim.loop = true;
    playerShotUp.anim.speed = 0.3;
    playerShotUp.lifetime = 180;

    playerShotDown.anim.loop = true;
    playerShotDown.anim.speed = 0.3;
    playerShotDown.lifetime = 180;

    playerShotLeft.anim.loop = true;
    playerShotLeft.anim.speed = 0.3;
    playerShotLeft.lifetime = 180;

    playerShotRight.anim.loop = true;
    playerShotRight.anim.speed = 0.3;
    playerShotRight.lifetime = 180;

    playerShotUpRight.anim.loop = true;
    playerShotUpRight.anim.speed = 0.3;
    playerShotUpRight.lifetime = 180;

    playerShotUpLeft.anim.loop = true;
    playerShotUpLeft.anim.speed = 0.3;
    playerShotUpLeft.lifetime = 180;

    playerShotDownRight.anim.loop = true;
    playerShotDownRight.anim.speed = 0.3;
    playerShotDownRight.lifetime = 180;

    playerShotDownLeft.anim.loop = true;
    playerShotDownLeft.anim.speed = 0.3;
    playerShotDownLeft.lifetime = 180;

    // Enemy shot
    enemyShot.anim.PushBack(                { 0, 4, 6, 6 });
    enemyShot.anim.PushBack(                { 8, 4, 6, 6 });
    enemyShot.anim.PushBack(                { 16, 4, 6, 6 });
    enemyShot.anim.PushBack(                { 24, 4, 6, 6 });

    enemyShot.anim.loop = true;
    enemyShot.anim.speed = 0.3;
    enemyShot.lifetime = 180;

    // Tank shots
    tankMissileUp.anim.PushBack(            { 53*0, 206, 53, 53 });
    tankMissileUp.anim.PushBack(            { 53*1, 206, 53, 53 });
    tankMissileUp.anim.PushBack(            { 53*2, 206, 53, 53 });
    tankMissileUp.anim.PushBack(            { 53*3, 206, 53, 53 });
    tankMissileUp.anim.PushBack(            { 53*4, 206, 53, 53 });
    tankMissileDown.anim.PushBack(          { 53*5, 206, 53, 53 });
    tankMissileDown.anim.PushBack(          { 53*6, 206, 53, 53 });
    tankMissileDown.anim.PushBack(          { 53*7, 206, 53, 53 });
    tankMissileDown.anim.PushBack(          { 53*8, 206, 53, 53 });
    tankMissileDown.anim.PushBack(          { 53*9, 206, 53, 53 });
    tankMissileLeft.anim.PushBack(          { 53*10, 206, 53, 53 });
    tankMissileLeft.anim.PushBack(          { 53*11, 206, 53, 53 });
    tankMissileLeft.anim.PushBack(          { 53*12, 206, 53, 53 });
    tankMissileLeft.anim.PushBack(          { 53*13, 206, 53, 53 });
    tankMissileLeft.anim.PushBack(          { 53*14, 206, 53, 53 });
    tankMissileRight.anim.PushBack(         { 53*15, 206, 53, 53 });
    tankMissileRight.anim.PushBack(         { 53*16, 206, 53, 53 });
    tankMissileRight.anim.PushBack(         { 53*17, 206, 53, 53 });
    tankMissileRight.anim.PushBack(         { 53*18, 206, 53, 53 });
    tankMissileRight.anim.PushBack(         { 53*19, 206, 53, 53 });
    tankMissileUpRight.anim.PushBack(       { 53*20, 206, 53, 53 });
    tankMissileUpRight.anim.PushBack(       { 53*21, 206, 53, 53 });
    tankMissileUpRight.anim.PushBack(       { 53*22, 206, 53, 53 });
    tankMissileUpRight.anim.PushBack(       { 53*23, 206, 53, 53 });
    tankMissileUpRight.anim.PushBack(       { 53*24, 206, 53, 53 });
    tankMissileUpLeft.anim.PushBack(        { 53*25, 206, 53, 53 });
    tankMissileUpLeft.anim.PushBack(        { 53*26, 206, 53, 53 });
    tankMissileUpLeft.anim.PushBack(        { 53*27, 206, 53, 53 });
    tankMissileUpLeft.anim.PushBack(        { 53*28, 206, 53, 53 });
    tankMissileUpLeft.anim.PushBack(        { 53*29, 206, 53, 53 });
    tankMissileDownRight.anim.PushBack(     { 53*30, 206, 53, 53 });
    tankMissileDownRight.anim.PushBack(     { 53*31, 206, 53, 53 });
    tankMissileDownRight.anim.PushBack(     { 53*32, 206, 53, 53 });
    tankMissileDownRight.anim.PushBack(     { 53*33, 206, 53, 53 });
    tankMissileDownRight.anim.PushBack(     { 53*34, 206, 53, 53 });
    tankMissileDownLeft.anim.PushBack(      { 53*35, 206, 53, 53 });
    tankMissileDownLeft.anim.PushBack(      { 53*36, 206, 53, 53 });
    tankMissileDownLeft.anim.PushBack(      { 53*37, 206, 53, 53 });
    tankMissileDownLeft.anim.PushBack(      { 53*38, 206, 53, 53 });
    tankMissileDownLeft.anim.PushBack(      { 53*39, 206, 53, 53 });

    tankMissileUp.anim.loop = true;
    tankMissileUp.anim.speed = 0.3;
    tankMissileUp.lifetime = 180;

    tankMissileDown.anim.loop = true;
    tankMissileDown.anim.speed = 0.3;
    tankMissileDown.lifetime = 180;

    tankMissileLeft.anim.loop = true;
    tankMissileLeft.anim.speed = 0.3;
    tankMissileLeft.lifetime = 180;

    tankMissileRight.anim.loop = true;
    tankMissileRight.anim.speed = 0.3;
    tankMissileRight.lifetime = 180;

    tankMissileUpRight.anim.loop = true;
    tankMissileUpRight.anim.speed = 0.3;
    tankMissileUpRight.lifetime = 180;

    tankMissileUpLeft.anim.loop = true;
    tankMissileUpLeft.anim.speed = 0.3;
    tankMissileUpLeft.lifetime = 180;

    tankMissileDownRight.anim.loop = true;
    tankMissileDownRight.anim.speed = 0.3;
    tankMissileDownRight.lifetime = 180;

    tankMissileDownLeft.anim.loop = true;
    tankMissileDownLeft.anim.speed = 0.3;
    tankMissileDownLeft.lifetime = 180;

    // Tank shots
    tankShotUp.anim.PushBack(               { 48*6, 110, 48, 48 });
    tankShotUp.anim.PushBack(               { 48*6, 158, 48, 48 });
    tankShotDown.anim.PushBack(             { 48*7, 110, 48, 48 });
    tankShotDown.anim.PushBack(             { 48*7, 158, 48, 48 }); 
    tankShotLeft.anim.PushBack(             { 48*1, 110, 48, 48 });
    tankShotLeft.anim.PushBack(             { 48*1, 158, 48, 48 });
    tankShotRight.anim.PushBack(            { 48*0, 110, 48, 48 });
    tankShotRight.anim.PushBack(            { 48*0, 158, 48, 48 });
    tankShotUpRight.anim.PushBack(          { 48*4, 110, 48, 48 });
    tankShotUpRight.anim.PushBack(          { 48*4, 158, 48, 48 });
    tankShotUpLeft.anim.PushBack(           { 48*3, 110, 48, 48 });
    tankShotUpLeft.anim.PushBack(           { 48*2, 158, 48, 48 });
    tankShotDownRight.anim.PushBack(        { 48*2, 110, 48, 48 });
    tankShotDownRight.anim.PushBack(        { 48*3, 158, 48, 48 });
    tankShotDownLeft.anim.PushBack(         { 48*5, 110, 48, 48 });
    tankShotDownLeft.anim.PushBack(         { 48*5, 158, 48, 48 });

    tankShotUp.anim.loop = true;
    tankShotUp.anim.speed = 0.3;
    tankShotUp.lifetime = 180;

    tankShotDown.anim.loop = true;
    tankShotDown.anim.speed = 0.3;
    tankShotDown.lifetime = 180;

    tankShotLeft.anim.loop = true;
    tankShotLeft.anim.speed = 0.3;
    tankShotLeft.lifetime = 180;

    tankShotRight.anim.loop = true;
    tankShotRight.anim.speed = 0.3;
    tankShotRight.lifetime = 180;

    tankShotUpRight.anim.loop = true;
    tankShotUpRight.anim.speed = 0.3;
    tankShotUpRight.lifetime = 180;

    tankShotUpLeft.anim.loop = true;
    tankShotUpLeft.anim.speed = 0.3;
    tankShotUpLeft.lifetime = 180;

    tankShotDownRight.anim.loop = true;
    tankShotDownRight.anim.speed = 0.3;
    tankShotDownRight.lifetime = 180;

    tankShotDownLeft.anim.loop = true;
    tankShotDownLeft.anim.speed = 0.3;
    tankShotDownLeft.lifetime = 180;

    // Grenades
    playerGrenade.anim.PushBack(            {});

    playerGrenade.anim.loop = true;
    playerGrenade.anim.speed = 0.3;
    playerGrenade.lifetime = 180;

    // Muzzles
    // Muzzle Player
    playerMuzzleUp.anim.PushBack(           { 23*21, 26, 23, 23 });
    playerMuzzleUp.anim.PushBack(           { 23*22, 26, 23, 23 });
    playerMuzzleUp.anim.PushBack(           { 23*23, 26, 23, 23 });
    playerMuzzleDown.anim.PushBack(         { 23*18, 26, 23, 23 });
    playerMuzzleDown.anim.PushBack(         { 23*19, 26, 23, 23 });
    playerMuzzleDown.anim.PushBack(         { 23*20, 26, 23, 23 });
    playerMuzzleLeft.anim.PushBack(         { 23*15, 26, 23, 23 });
    playerMuzzleLeft.anim.PushBack(         { 23*16, 26, 23, 23 });
    playerMuzzleLeft.anim.PushBack(         { 23*17, 26, 23, 23 });
    playerMuzzleRight.anim.PushBack(        { 23*12, 26, 23, 23 });
    playerMuzzleRight.anim.PushBack(        { 23*13, 26, 23, 23 });
    playerMuzzleRight.anim.PushBack(        { 23*14, 26, 23, 23 });
    playerMuzzleUpRight.anim.PushBack(      { 23*6,  26, 23, 23 });
    playerMuzzleUpRight.anim.PushBack(      { 23*7,  26, 23, 23 });
    playerMuzzleUpRight.anim.PushBack(      { 23*8,  26, 23, 23 });
    playerMuzzleUpLeft.anim.PushBack(       { 23*9,  26, 23, 23 });
    playerMuzzleUpLeft.anim.PushBack(       { 23*10, 26, 23, 23 });
    playerMuzzleUpLeft.anim.PushBack(       { 23*11, 26, 23, 23 });
    playerMuzzleDownRight.anim.PushBack(    { 23*0,  26, 23, 23 });
    playerMuzzleDownRight.anim.PushBack(    { 23*1,  26, 23, 23 });
    playerMuzzleDownRight.anim.PushBack(    { 23*2,  26, 23, 23 });
    playerMuzzleDownLeft.anim.PushBack(     { 23*3,  26, 23, 23 });
    playerMuzzleDownLeft.anim.PushBack(     { 23*4,  26, 23, 23 });
    playerMuzzleDownLeft.anim.PushBack(     { 23*5,  26, 23, 23 });

    playerMuzzleUp.anim.loop = false;
    playerMuzzleUp.anim.speed = 0.3;

    playerMuzzleDown.anim.loop = false;
    playerMuzzleDown.anim.speed = 0.3;

    playerMuzzleLeft.anim.loop = false;
    playerMuzzleLeft.anim.speed = 0.3;

    playerMuzzleRight.anim.loop = false;
    playerMuzzleRight.anim.speed = 0.3;

    playerMuzzleUpRight.anim.loop = false;
    playerMuzzleUpRight.anim.speed = 0.3;

    playerMuzzleUpLeft.anim.loop = false;
    playerMuzzleUpLeft.anim.speed = 0.3;

    playerMuzzleDownRight.anim.loop = false;
    playerMuzzleDownRight.anim.speed = 0.3;

    playerMuzzleDownLeft.anim.loop = false;
    playerMuzzleDownLeft.anim.speed = 0.3;

    // Muzzle Enemy
    enemyMuzzleUp.anim.PushBack(            { 15*14, 11, 15, 15 });
    enemyMuzzleUp.anim.PushBack(            { 15*15, 11, 15, 15 });
    enemyMuzzleDown.anim.PushBack(          { 15*12, 11, 15, 15 });
    enemyMuzzleDown.anim.PushBack(          { 15*13, 11, 15, 15 });
    enemyMuzzleLeft.anim.PushBack(          { 15*10, 11, 15, 15 });
    enemyMuzzleLeft.anim.PushBack(          { 15*11, 11, 15, 15 });
    enemyMuzzleRight.anim.PushBack(         { 15*8,  11, 15, 15 });
    enemyMuzzleRight.anim.PushBack(         { 15*9,  11, 15, 15 });
    enemyMuzzleUpRight.anim.PushBack(       { 15*4,  11, 15, 15 });
    enemyMuzzleUpRight.anim.PushBack(       { 15*5,  11, 15, 15 });
    enemyMuzzleUpLeft.anim.PushBack(        { 15*6,  11, 15, 15 });
    enemyMuzzleUpLeft.anim.PushBack(        { 15*7,  11, 15, 15 });
    enemyMuzzleDownRight.anim.PushBack(     { 15*0,  11, 15, 15 });
    enemyMuzzleDownRight.anim.PushBack(     { 15*1,  11, 15, 15 });
    enemyMuzzleDownLeft.anim.PushBack(      { 15*2,  11, 15, 15 });
    enemyMuzzleDownLeft.anim.PushBack(      { 15*3,  11, 15, 15 });

    enemyMuzzleUp.anim.loop = false;
    enemyMuzzleUp.anim.speed = 0.3;

    enemyMuzzleDown.anim.loop = false;
    enemyMuzzleDown.anim.speed = 0.3;

    enemyMuzzleLeft.anim.loop = false;
    enemyMuzzleLeft.anim.speed = 0.3;

    enemyMuzzleRight.anim.loop = false;
    enemyMuzzleRight.anim.speed = 0.3;

    enemyMuzzleUpRight.anim.loop = false;
    enemyMuzzleUpRight.anim.speed = 0.3;

    enemyMuzzleUpLeft.anim.loop = false;
    enemyMuzzleUpLeft.anim.speed = 0.3;

    enemyMuzzleDownRight.anim.loop = false;
    enemyMuzzleDownRight.anim.speed = 0.3;

    enemyMuzzleDownLeft.anim.loop = false;
    enemyMuzzleDownLeft.anim.speed = 0.3;

    // Muzzle Flying Battleship
    flyingBattleshipMuzzle.anim.PushBack(   { 26*0, 49, 26, 29 });
    flyingBattleshipMuzzle.anim.PushBack(   { 26*1, 49, 26, 29 });
    flyingBattleshipMuzzle.anim.PushBack(   { 26*2, 49, 26, 29 });

    flyingBattleshipMuzzle.anim.loop = false;
    flyingBattleshipMuzzle.anim.speed = 0.3;

    // Landmine Explosion
    for (int i = 0; i < 29; i++)
    {
        landmineExplosion.anim.PushBack({ (66 * i)-i, 260, 66, 65 });
        }
    landmineExplosion.anim.loop = false;
    landmineExplosion.anim.speed = 0.3;

    return true;
}

Update_Status ModuleParticles::PreUpdate()
{
    // Remove all particles scheduled for deletion
    for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
    {
        if (particles[i] != nullptr && particles[i]->pendingToDelete)
        {
            delete particles[i];
            particles[i] = nullptr;
        }
    }

    return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
    LOG("Unloading particles");

    // Delete all remaining active particles on application exit
    for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
    {
        if (particles[i] != nullptr)
        {
            delete particles[i];
            particles[i] = nullptr;
        }
    }

    return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
    for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
    {
        // Always destroy particles that collide
        if (particles[i] != nullptr && particles[i]->collider == c1)
        {
            particles[i]->pendingToDelete = true;
            particles[i]->collider->pendingToDelete = true;
            break;
        }
    }
}

Update_Status ModuleParticles::Update()
{
    for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
    {
        Particle* particle = particles[i];

        if (particle == nullptr)    continue;

        // Call particle Update. If it has reached its lifetime, destroy it
        if (particle->Update() == false)
        {
            particles[i]->SetToDelete();
        }
    }

    return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
    //Iterating all particle array and drawing any active particles
    for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
    {
        Particle* particle = particles[i];

        if (particle != nullptr && particle->isAlive)
        {
            App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
        }
    }

    return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, int playerDirection, Collider::Type colliderType, uint delay)
{
    Particle* newParticle = nullptr;

    for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
    {
        // Finding an empty slot for a new particle
        if (particles[i] == nullptr)
        {
            newParticle = new Particle(particle);
            newParticle->frameCount = -(int)delay;            // We start the frameCount as the negative delay
            newParticle->position.x = x;                        // so when frameCount reaches 0 the particle will be activated
            newParticle->position.y = y;
            newParticle->playerDirection = playerDirection;    // Assign the player direction

            // Modify particle speed based on player direction
            switch (playerDirection)
            {
            case 1: // Up-Right
                newParticle->speed.x = 5;   // Set appropriate values for x and y based on the direction
                newParticle->speed.y = -5;
                break;
            case 2: // Up-Left
                newParticle->speed.x = -5;
                newParticle->speed.y = -5;
                break;
            case 3: // Down-Right
                newParticle->speed.x = 5;
                newParticle->speed.y = 5;
                break;
            case 4: // Down-Left
                newParticle->speed.x = -5;
                newParticle->speed.y = 5;
                break;
            case 5: // Right
                newParticle->speed.x = 5;
                newParticle->speed.y = 0;
                break;
            case 6: // Left
                newParticle->speed.x = -5;
                newParticle->speed.y = 0;
                break;
            case 7: // Down
                newParticle->speed.x = 0;
                newParticle->speed.y = 5;
                break;
            case 8: // Up
                newParticle->speed.x = 0;
                newParticle->speed.y = -5;
                break;
            default: // Invalid direction
                newParticle->speed.SetToZero();
                break;
            }

            // Adding the particle's collider
            if (colliderType != Collider::Type::NONE)
                newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

            particles[i] = newParticle;
            break;
        }
    }

    return newParticle;
}
