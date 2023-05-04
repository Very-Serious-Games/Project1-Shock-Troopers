#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
    //triggerArea = App->collisions->AddCollider({ position.x, position.y, 1, 1 }, Collider::Type::TRIGGERAREA);
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

    switch (state) {
        case Enemy_State::SPAWN:
            // Handle spawn state logic
            if (/* some condition for idle */true) {
                state = Enemy_State::IDLE;
                LOG("state changed to IDLE");
            }
            break;
        case Enemy_State::IDLE:
            if (PlayerIsNear()) {
                state = Enemy_State::ATTACK;
                LOG("state changed to ATTACK");
            }
            break;
        case Enemy_State::ATTACK:
            if (this->health == 0) {
                LOG("state changed to ATTACK");
                state = Enemy_State::DEATH;
            }
            break;
        case Enemy_State::DEATH:
            LOG("state changed to DEATH");
            pendingToDelete = true;
            break;
        default:
            // Handle default state logic
            LOG("ERROR STATE");
            break;
    }
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
    this->health = health - 10; // TODO : change this to the damage of the bullet
    if (health <= 0) {
        App->particles->AddParticle(App->particles->explosion, position.x, position.y);
        App->audio->PlayFx(destroyedFx);
        SetToDelete();
    }
}

void Enemy::SetToDelete()
{
    this->state = Enemy_State::DEATH;
	if (collider != nullptr)
		collider->pendingToDelete = true; // TODO : colliders doesn't have an state machine
}

bool Enemy::PlayerIsNear() {

    int detectionDistance = 200; // TODO : change this to the detection distance of the enemy (maybe a variable in the enemy class)
    int distance = sqrt(pow(App->player->position.x - position.x, 2) + pow(App->player->position.y - position.y, 2)); // pythagoras

    if (distance <= detectionDistance) {
        return true;
    }

    return false;
}