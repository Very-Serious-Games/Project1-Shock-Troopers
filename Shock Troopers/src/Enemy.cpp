#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include <cmath>

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

void Enemy::Update() {

	if (currentAnim != nullptr)
		currentAnim->Update();

    if (collider != nullptr) {
        if (collider->type != Collider::Type::OBJECT)
        {
            collider->SetPos(position.x, position.y);
        }
    }

    StateMachine();
}

int Enemy::GetPlayerDirection() {
    // Get the player position
    fPoint playerPos = App->player->position;

    // Calculate the direction vector from enemy position to player position
    fPoint enemyPos = position;
    fPoint direction = playerPos - enemyPos;

    // Calculate the angle between the enemy and the player
    float angle = atan2(direction.y, direction.x);

    // Convert the angle to degrees
    float angleDegrees = angle * (180.0f / M_PI);

    // Determine the player direction based on the angle
    int playerDirection = 0;

    if (angleDegrees >= -22.5f && angleDegrees < 22.5f) {
        playerDirection = 5; // Right
    }
    else if (angleDegrees >= 22.5f && angleDegrees < 67.5f) {
        playerDirection = 3; // Down-Right
    }
    else if (angleDegrees >= 67.5f && angleDegrees < 112.5f) {
        playerDirection = 7; // Down
    }
    else if (angleDegrees >= 112.5f && angleDegrees < 157.5f) {
        playerDirection = 4; // Down-Left
    }
    else if (angleDegrees >= 157.5f || angleDegrees < -157.5f) {
        playerDirection = 6; // Left
    }
    else if (angleDegrees >= -157.5f && angleDegrees < -112.5f) {
        playerDirection = 2; // Up-Left
    }
    else if (angleDegrees >= -112.5f && angleDegrees < -67.5f) {
        playerDirection = 8; // Up
    }
    else if (angleDegrees >= -67.5f && angleDegrees < -22.5f) {
        playerDirection = 1; // Up-Right
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
            playerDirection = 4; // Down-Left-Diagonal 
        } else if (angle >= 30 && angle < 40) {
            playerDirection = 3; // Down-Right-Diagonal
        } else if (angle < 65 && angle >= 40) {
            playerDirection = 9; // Down-Right
        } else if (angle > 105 && angle <= 120) {
            playerDirection = 10; // Down-Left
        } else if (angle > 135 || angle < -135) {
            playerDirection = 6; // Left
        } else if (angle < 30 && angle > -30) {
            playerDirection = 5; // Right
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
	if (currentAnim2 != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim2->GetCurrentFrame()));

	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));

	if (botCurrentAnim != nullptr) {
		App->render->Blit(texture, position.x, position.y, &(botCurrentAnim->GetCurrentFrame()));
	}

	if (midCurrentAnim != nullptr) {
		App->render->Blit(texture, position.x+3, position.y+10, &(midCurrentAnim->GetCurrentFrame()));
	}

	switch (GetPlayerDirectionBelow()) {
	case 9: // Down-Right
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x+48, position.y+22, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	case 10: // Down-Left
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x+48, position.y+23, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	case 3: // Right
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x+32, position.y+16, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	case 4: // Left
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x+36, position.y+32, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	case 5: // Down-Right-Diagonal
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x+42, position.y+16, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	case 6: // Down-Left-Diagonal
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x+45, position.y+33, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	case 7: // Below
		if (topCurrentAnim != nullptr) {
			App->render->Blit(texture, position.x+48, position.y+22, &(topCurrentAnim->GetCurrentFrame()));
		}
		break;
	default:
		switch (GetPlayerDirection()) {
		case 1:
			if (topCurrentAnim != nullptr) {
				App->render->Blit(texture, position.x + 32, position.y + 16, &(topCurrentAnim->GetCurrentFrame()));
			}
			break;
		case 2:
			if (topCurrentAnim != nullptr) {
				App->render->Blit(texture, position.x + 36, position.y + 32, &(topCurrentAnim->GetCurrentFrame()));
			}
			break;
		}
		break;
	}

}

void Enemy::OnCollision(Collider* collider)
{   
    if (collider->type != Collider::Type::PLAYER and collider->type != Collider::Type::STOP_ENEMY) {

        this->health = health - 10;
   
        if (health <= 0) {
            App->particles->AddParticle(App->particles->explosion, position.x, position.y,0);
            SetToDelete();
        }

    }
    if (collider->type == Collider::Type::STOP_ENEMY) {
        canMove = false;
	}
}

void Enemy::SetToDelete()
{
    this->state = Enemy_State::DEATH;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Enemy::PlayerIsNear() {

    int detectionDistance = 200;
    int distance = sqrt(pow(App->player->position.x - position.x, 2) + pow(App->player->position.y - position.y, 2)); // pythagoras
    
    if (distance <= detectionDistance) {
        return true;
    }

    return false;
}

bool Enemy::PlayerIsAttackRange() {

    int detectionDistance = 150;
    int distance = sqrt(pow(App->player->position.x - position.x, 2) + pow(App->player->position.y - position.y, 2)); // pythagoras

    if (distance <= detectionDistance) {
        return true;
    }

    return false;
}

bool Enemy::PlayerIsMele() {

    int detectionDistance = 50;
    int distance = sqrt(pow(App->player->position.x - position.x, 2) + pow(App->player->position.y - position.y, 2)); // pythagoras

    if (distance <= detectionDistance) {
        return true;
    }

    return false;
}