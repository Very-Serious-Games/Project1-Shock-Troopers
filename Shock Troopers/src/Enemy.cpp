#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
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
            // Handle idle state logic
            if (/* some condition for attacking */true) {
                state = Enemy_State::ATTACK;
                LOG("state changed to ATTACK");
            }
            break;
        case Enemy_State::ATTACK:
            // Handle attack state logic
            if (this->health == 0) {
                LOG("state changed to ATTACK");
                state = Enemy_State::DEATH;
            }
            break;
        case Enemy_State::DEATH:
            // Handle death state logic
            LOG("state changed to DEATH");
            //if (/* some condition for despawning */true) {
            pendingToDelete = true;
            //}
            break;
        default:
            // Handle default state logic
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