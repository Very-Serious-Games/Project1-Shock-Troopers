#include "Enemy_FlyingBattleship.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Particle.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"

Enemy_FlyingBattleship::Enemy_FlyingBattleship(int x, int y) : Enemy(x, y) {
	


	spawnAnim.PushBack({0, 0, 121, 124});
	spawnAnim.PushBack({128, 0, 121, 124});
	spawnAnim.pingpong = true;
	spawnAnim.speed = 0.2f;

	idleAnim.PushBack({256, 0 , 121, 124});

	deathAnim.PushBack({384, 0, 121, 124});

	//path.PushBack({ 0.0f, 0.0f }, 500, &spawnAnim);
	path.PushBack({ 1.0f, 0.0f }, 150, &idleAnim);
	path.PushBack({ -1.0f, 0.0f }, 150, &idleAnim);
	//path.PushBack({ 0.0f, 0.0f }, 100, &deathAnim);
	

	// TODO cambiar tamaño collider
	collider = App->collisions->AddCollider({ 0, 0, 121, 124 }, Collider::Type::ENEMY, (Module*)App->enemies);

    this->health = 300;
}

void Enemy_FlyingBattleship::Update() {

	path.Update();
	position = spawnPos + path.GetRelativePosition();
	//currentAnim = path.GetCurrentAnimation();
	currentAnim = &spawnAnim;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_FlyingBattleship::Attack() {
                                    // get random number between with 10%, 30, 60% chance to happen
    int attackType = rand() % 100 + 1;

    //LOG("Random attack type: %d", attackType);

    if (attackType <= 10) {           // 10% chance to do a not attack
        delay--;
        if (delay == 0) {
            LOG("No attack");
            // do nothing   
            delay = 15;
        }
        
    } else if (attackType <= 30) {    // 30% chance to do a rocket attack
        delay--;
        if (delay == 0) {
            LOG("Rocket attack");
            Particle* newParticle = App->particles->AddParticle(App->particles->tankMissileDown, position.x + 27, position.y + 70, 7, Collider::Type::ENEMY_SHOT);
            Particle* newParticle2 = App->particles->AddParticle(App->particles->tankMissileDown, position.x + 87, position.y + 70, 7, Collider::Type::ENEMY_SHOT);
            newParticle->collider->AddListener(NULL);
            newParticle2->collider->AddListener(NULL);
            App->audio->PlayFx(App->enemies->flyingBattleshipMissile);
            
            delay = 15;
        }

    } else {                       // 60% chance to do a normal attack
        delay--;
        if (delay == 0) {
            LOG("Normal attack");
            
            Particle* newParticle = nullptr;
            Particle* newParticleMuzzle = nullptr;

            newParticle = App->particles->AddParticle(App->particles->flyingbattleshipShot, position.x + 27, position.y + 70, 7, Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->flyingBattleshipMuzzle, position.x + 27, position.y + 70, 0, Collider::Type::MUZZLE);
            
            newParticle = App->particles->AddParticle(App->particles->flyingbattleshipShot, position.x + 87, position.y + 70, 7, Collider::Type::ENEMY_SHOT);
            newParticleMuzzle = App->particles->AddParticle(App->particles->flyingBattleshipMuzzle, position.x + 87, position.y + 70, 0, Collider::Type::MUZZLE);

            newParticle->collider->AddListener(NULL);
            newParticleMuzzle->collider->AddListener(NULL);
            App->audio->PlayFx(App->enemies->flyingBattleshipShot);
            
            delay = 15;
        }
    }
        
}

void Enemy_FlyingBattleship::deathAnimation() {
    currentAnim = &deathAnim;
}

void Enemy_FlyingBattleship::spawnAnimation() {
    currentAnim = &spawnAnim;
}

void Enemy_FlyingBattleship::idleAnimation() {
    currentAnim = &idleAnim;
}

void Enemy_FlyingBattleship::StateMachine() {
    switch (state) {
    case Enemy_State::SPAWN:
        spawnAnimation();
        // Handle spawn state logic
        if (/* some condition for idle */true) {
            state = Enemy_State::IDLE;
            LOG("state changed to IDLE");
        }
        break;
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

        if (!playOnce) {
            App->audio->PlayFx(App->enemies->tankDestroyed);
            playOnce = true;
        }
        

        if (deathAnimDelay == 0) {
            App->enemies->miniBossKilled = true;
            pendingToDelete = true;
            App->render->leaveZone = true;
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