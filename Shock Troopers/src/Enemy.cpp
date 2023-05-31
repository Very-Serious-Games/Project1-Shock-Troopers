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
    // TODO revisar añadir triggerArea a enemy
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

void Enemy::Update() {

	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

    StateMachine();
}

int Enemy::GetPlayerDirection() {
	// Get the player position
	fPoint playerPos = App->player->position;

	// Calculate the direction vector from enemy position to player position
	fPoint enemyPos = position;
	fPoint direction = playerPos - enemyPos;

	// Determine the player direction based on the direction vector
	int playerDirection = 0;

	if (direction.y < 0) {
		// Player is above the enemy
		if (fabsf(direction.x) <= fabsf(direction.y) * 0.5f) {

			playerDirection = 8; // Up

		}
		else if (direction.x < 0) {

			playerDirection = 2; // Up-Left

		}
		else {

			playerDirection = 1; // Up-Right

		}

	}
	else if (direction.y > 0) {

		// Player is below the enemy
		if (fabsf(direction.x) <= fabsf(direction.y) * 0.5f) {

			playerDirection = 7; // Down

		}
		else if (direction.x < 0) {

			playerDirection = 4; // Down-Left

		}
		else {

			playerDirection = 3; // Down-Right
		}

	}
	else {
		// Player is at the same height as the enemy
		if (direction.x < 0) {

			playerDirection = 6; // Left

		}
		else if (direction.x > 0) {

			playerDirection = 5; // Right

		}
		else {

			// Player is at the exact position as the enemy (unlikely scenario)
			playerDirection = 0; // No direction

		}

	}

	// Return the player direction
	return playerDirection;
}

int Enemy::GetPlayerDirectionBelow() {
    // Get the player position
    fPoint playerPos = App->player->position;

    // Calculate the direction vector from enemy position to player position
    fPoint enemyPos = position;
    fPoint direction = playerPos - enemyPos;

    // Determine the player direction based on the direction vector
    int playerDirection = 0;

    if (direction.y > 0) {
        // Player is below the enemy

        float angle = atan2f(direction.y, direction.x) * 180.0f / M_PI;

        if (angle > 120 && angle <= 135) {
            playerDirection = 6; // Down-Left-Diagonal 
        } else if (angle >= 30 && angle < 40) {
            playerDirection = 5; // Down-Right-Diagonal
        } else if (angle < 65 && angle >= 40) {
            playerDirection = 9; // Down-Right
        } else if (angle > 105 && angle <= 120) {
            playerDirection = 10; // Down-Left
        } else if (angle > 135 || angle < -135) {
            playerDirection = 4; // Left
        } else if (angle < 30 && angle > -30) {
            playerDirection = 3; // Right
        } else if (angle >= 65 && angle <= 105) {
            playerDirection = 7; // Below
        }
    }

    // Return the player direction
    return playerDirection;
}



void Enemy::StateMachine()
{
}

void Enemy::Attack()
{
}

void Enemy::move()
{
}

void Enemy::deathAnimation()
{
}

void Enemy::spawnAnimation()
{
}

void Enemy::idleAnimation()
{
}

void Enemy::idleAnimation(int direction)
{
}

void Enemy::idleAnimation(int direction, int directionBelow)
{
}

void Enemy::moveAnimation()
{
}

void Enemy::attackAnimation(int direction)
{
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));

	// TODO ajustar posicion a la q se renderizan las partes del boss

    

	if (botCurrentAnim != nullptr) {
		App->render->Blit(texture, position.x, position.y, &(botCurrentAnim->GetCurrentFrame()));
	}

	if (midCurrentAnim != nullptr) {
		App->render->Blit(texture, position.x, position.y, &(midCurrentAnim->GetCurrentFrame()));
	}

	switch (GetPlayerDirectionBelow()) {
	case 1: // Down -Right
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x, position.y, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	case 2: // Down-Left
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x, position.y, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	case 3: // Right
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x, position.y, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	case 4: // Left
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x, position.y, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	case 5: // Down-Right-Diagonal
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x, position.y, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	case 6: // Down-Left-Diagonal
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x, position.y, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	case 7: // Below
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x, position.y, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	default:
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x, position.y, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	}
	

}

void Enemy::OnCollision(Collider* collider)
{   
    this->health = health - 10; // TODO : change this to the damage of the bullet
   
    if (health <= 0) {
        App->particles->AddParticle(App->particles->explosion, position.x, position.y,0);
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
    

    // TODO print debug mode detection zone
    /*
    SDL_Rect rect = { position.x, position.y, detectionDistance, detectionDistance };
    App->collisions->AddCollider(rect, Collider::Type::DETECTION_ZONE);
    */

    if (distance <= detectionDistance) {
        return true;
    }

    return false;
}

bool Enemy::PlayerIsAttackRange() {

    int detectionDistance = 150; // TODO : change this to the detection distance of the enemy (maybe a variable in the enemy class)
    int distance = sqrt(pow(App->player->position.x - position.x, 2) + pow(App->player->position.y - position.y, 2)); // pythagoras

    if (distance <= detectionDistance) {
        return true;
    }

    return false;
}

bool Enemy::PlayerIsMele() {

    int detectionDistance = 50; // TODO : change this to the detection distance of the enemy (maybe a variable in the enemy class)
    int distance = sqrt(pow(App->player->position.x - position.x, 2) + pow(App->player->position.y - position.y, 2)); // pythagoras


    // TODO print debug mode detection zone
    /*
    SDL_Rect rect = { position.x, position.y, detectionDistance, detectionDistance };
    App->collisions->AddCollider(rect, Collider::Type::DETECTION_ZONE);
    */

    if (distance <= detectionDistance) {
        return true;
    }

    return false;
}