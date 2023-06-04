#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePickUp.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include <iostream>
#include <stdio.h>
#include <SDL/include/SDL_timer.h>
#include "ModuleUI.h"
#include "Pickup.h"
#include "ModuleEnemies.h"

using namespace std;

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled) {

	//Setting up the player animations
	// Empty animation
	emptyAnimation.PushBack({ 0,0,0,0 });

	// Idle torso animations
	idleAnimUpTorso.PushBack({ 0,   676, 54, 52 });
	idleAnimUpTorso.PushBack({ 54,  676, 54, 52 });
	idleAnimUpTorso.PushBack({ 108, 676, 54, 52 });

	idleAnimDownTorso.PushBack({ 162, 676, 54, 52 });
	idleAnimDownTorso.PushBack({ 216, 676, 54, 52 });
	idleAnimDownTorso.PushBack({ 270, 676, 54, 52 });

	idleAnimLeftTorso.PushBack({ 486, 624, 54, 52 });
	idleAnimLeftTorso.PushBack({ 540, 624, 54, 52 });
	idleAnimLeftTorso.PushBack({ 594, 624, 54, 52 });

	idleAnimRightTorso.PushBack({ 648, 624, 54, 52 });
	idleAnimRightTorso.PushBack({ 702, 624, 54, 52 });
	idleAnimRightTorso.PushBack({ 756, 624, 54, 52 });

	idleAnimUpLeftTorso.PushBack({ 0,   624, 54, 52 });
	idleAnimUpLeftTorso.PushBack({ 54,  624, 54, 52 });
	idleAnimUpLeftTorso.PushBack({ 108, 624, 54, 52 });

	idleAnimUpRightTorso.PushBack({ 324, 624, 54, 52 });
	idleAnimUpRightTorso.PushBack({ 378, 624, 54, 52 });
	idleAnimUpRightTorso.PushBack({ 432, 624, 54, 52 });

	idleAnimDownLeftTorso.PushBack({ 756, 572, 54, 52 });
	idleAnimDownLeftTorso.PushBack({ 810, 572, 54, 52 });
	idleAnimDownLeftTorso.PushBack({ 864, 572, 54, 52 });

	idleAnimDownRightTorso.PushBack({ 162, 624, 54, 52 });
	idleAnimDownRightTorso.PushBack({ 216, 624, 54, 52 });
	idleAnimDownRightTorso.PushBack({ 270, 624, 54, 52 });

	// Idle legs animations
	idleAnimUpLegs.PushBack({ 864, 52, 54, 52 });
	idleAnimDownLegs.PushBack({ 648, 52, 54, 52 });
	idleAnimLeftLegs.PushBack({ 756, 52, 54, 52 });
	idleAnimRightLegs.PushBack({ 540, 52, 54, 52 });
	idleAnimDownLeftLegs.PushBack({ 702, 52, 54, 52 });
	idleAnimDownRightLegs.PushBack({ 594, 52, 54, 52 });
	idleAnimUpLeftLegs.PushBack({ 810, 52, 54, 52 });
	idleAnimUpRightLegs.PushBack({ 486, 52, 54, 52 });

	// Legs animations
	upAnimLegs.PushBack({ 378, 312, 54, 52 });
	upAnimLegs.PushBack({ 324, 312, 54, 52 });
	upAnimLegs.PushBack({ 270, 312, 54, 52 });
	upAnimLegs.PushBack({ 216, 312, 54, 52 });
	upAnimLegs.PushBack({ 162, 312, 54, 52 });
	upAnimLegs.PushBack({ 108, 312, 54, 52 });
	upAnimLegs.PushBack({ 54,  312, 54, 52 });
	upAnimLegs.PushBack({ 0,   312, 54, 52 });

	downAnimLegs.PushBack({ 378, 364, 54, 52 });
	downAnimLegs.PushBack({ 324, 364, 54, 52 });
	downAnimLegs.PushBack({ 270, 364, 54, 52 });
	downAnimLegs.PushBack({ 216, 364, 54, 52 });
	downAnimLegs.PushBack({ 162, 364, 54, 52 });
	downAnimLegs.PushBack({ 108, 364, 54, 52 });
	downAnimLegs.PushBack({ 54,  364, 54, 52 });
	downAnimLegs.PushBack({ 0,   364, 54, 52 });

	leftAnimLegs.PushBack({ 378, 416, 54, 52 });
	leftAnimLegs.PushBack({ 324, 416, 54, 52 });
	leftAnimLegs.PushBack({ 270, 416, 54, 52 });
	leftAnimLegs.PushBack({ 216, 416, 54, 52 });
	leftAnimLegs.PushBack({ 162, 416, 54, 52 });
	leftAnimLegs.PushBack({ 108, 416, 54, 52 });
	leftAnimLegs.PushBack({ 54,  416, 54, 52 });
	leftAnimLegs.PushBack({ 0,   416, 54, 52 });

	rightAnimLegs.PushBack({ 864, 0, 54, 52 });
	rightAnimLegs.PushBack({ 810, 0, 54, 52 });
	rightAnimLegs.PushBack({ 756, 0, 54, 52 });
	rightAnimLegs.PushBack({ 702, 0, 54, 52 });
	rightAnimLegs.PushBack({ 648, 0, 54, 52 });
	rightAnimLegs.PushBack({ 594, 0, 54, 52 });
	rightAnimLegs.PushBack({ 540, 0, 54, 52 });
	rightAnimLegs.PushBack({ 486, 0, 54, 52 });

	downLeftAnimLegs.PushBack({ 378, 260, 54, 52 });
	downLeftAnimLegs.PushBack({ 324, 260, 54, 52 });
	downLeftAnimLegs.PushBack({ 270, 260, 54, 52 });
	downLeftAnimLegs.PushBack({ 216, 260, 54, 52 });
	downLeftAnimLegs.PushBack({ 162, 260, 54, 52 });
	downLeftAnimLegs.PushBack({ 108, 260, 54, 52 });
	downLeftAnimLegs.PushBack({ 54,  260, 54, 52 });
	downLeftAnimLegs.PushBack({ 0,   260, 54, 52 });

	downRightAnimLegs.PushBack({ 864, 156, 54, 52 });
	downRightAnimLegs.PushBack({ 810, 156, 54, 52 });
	downRightAnimLegs.PushBack({ 756, 156, 54, 52 });
	downRightAnimLegs.PushBack({ 702, 156, 54, 52 });
	downRightAnimLegs.PushBack({ 648, 156, 54, 52 });
	downRightAnimLegs.PushBack({ 594, 156, 54, 52 });
	downRightAnimLegs.PushBack({ 540, 156, 54, 52 });
	downRightAnimLegs.PushBack({ 486, 156, 54, 52 });

	upLeftAnimLegs.PushBack({ 864, 208, 54, 52 });
	upLeftAnimLegs.PushBack({ 810, 208, 54, 52 });
	upLeftAnimLegs.PushBack({ 756, 208, 54, 52 });
	upLeftAnimLegs.PushBack({ 702, 208, 54, 52 });
	upLeftAnimLegs.PushBack({ 648, 208, 54, 52 });
	upLeftAnimLegs.PushBack({ 594, 208, 54, 52 });
	upLeftAnimLegs.PushBack({ 540, 208, 54, 52 });
	upLeftAnimLegs.PushBack({ 486, 208, 54, 52 });

	upRightAnimLegs.PushBack({ 864, 104, 54, 52 });
	upRightAnimLegs.PushBack({ 810, 104, 54, 52 });
	upRightAnimLegs.PushBack({ 756, 104, 54, 52 });
	upRightAnimLegs.PushBack({ 702, 104, 54, 52 });
	upRightAnimLegs.PushBack({ 648, 104, 54, 52 });
	upRightAnimLegs.PushBack({ 594, 104, 54, 52 });
	upRightAnimLegs.PushBack({ 540, 104, 54, 52 });
	upRightAnimLegs.PushBack({ 486, 104, 54, 52 });

	// Roll Animations
	rollAnimUp.PushBack({ 0,   0, 54, 52 });
	rollAnimUp.PushBack({ 54,  0, 54, 52 });
	rollAnimUp.PushBack({ 108, 0, 54, 52 });
	rollAnimUp.PushBack({ 162, 0, 54, 52 });
	rollAnimUp.PushBack({ 216, 0, 54, 52 });
	rollAnimUp.PushBack({ 270, 0, 54, 52 });
	rollAnimUp.PushBack({ 324, 0, 54, 52 });
	rollAnimUp.PushBack({ 378, 0, 54, 52 });
	rollAnimUp.PushBack({ 432, 0, 54, 52 });

	rollAnimDown.PushBack({ 0,   52, 54, 52 });
	rollAnimDown.PushBack({ 54,  52, 54, 52 });
	rollAnimDown.PushBack({ 108, 52, 54, 52 });
	rollAnimDown.PushBack({ 162, 52, 54, 52 });
	rollAnimDown.PushBack({ 216, 52, 54, 52 });
	rollAnimDown.PushBack({ 270, 52, 54, 52 });
	rollAnimDown.PushBack({ 324, 52, 54, 52 });
	rollAnimDown.PushBack({ 378, 52, 54, 52 });
	rollAnimDown.PushBack({ 432, 52, 54, 52 });

	rollAnimLeft.PushBack({ 486, 312, 54, 52 });
	rollAnimLeft.PushBack({ 540, 312, 54, 52 });
	rollAnimLeft.PushBack({ 594, 312, 54, 52 });
	rollAnimLeft.PushBack({ 648, 312, 54, 52 });
	rollAnimLeft.PushBack({ 702, 312, 54, 52 });
	rollAnimLeft.PushBack({ 756, 312, 54, 52 });
	rollAnimLeft.PushBack({ 810, 312, 54, 52 });
	rollAnimLeft.PushBack({ 864, 312, 54, 52 });

	rollAnimRight.PushBack({ 486, 364, 54, 52 });
	rollAnimRight.PushBack({ 540, 364, 54, 52 });
	rollAnimRight.PushBack({ 594, 364, 54, 52 });
	rollAnimRight.PushBack({ 648, 364, 54, 52 });
	rollAnimRight.PushBack({ 702, 364, 54, 52 });
	rollAnimRight.PushBack({ 756, 364, 54, 52 });
	rollAnimRight.PushBack({ 810, 364, 54, 52 });
	rollAnimRight.PushBack({ 864, 364, 54, 52 });

	rollAnimDownLeft.PushBack({ 0,   208, 54, 52 });
	rollAnimDownLeft.PushBack({ 54,  208, 54, 52 });
	rollAnimDownLeft.PushBack({ 108, 208, 54, 52 });
	rollAnimDownLeft.PushBack({ 162, 208, 54, 52 });
	rollAnimDownLeft.PushBack({ 216, 208, 54, 52 });
	rollAnimDownLeft.PushBack({ 270, 208, 54, 52 });
	rollAnimDownLeft.PushBack({ 324, 208, 54, 52 });
	rollAnimDownLeft.PushBack({ 378, 208, 54, 52 });
	rollAnimDownLeft.PushBack({ 432, 208, 54, 52 });

	rollAnimDownRight.PushBack({ 9 * 54, 7 * 52, 54, 52 });
	rollAnimDownRight.PushBack({ 10 * 54, 7 * 52, 54, 52 });
	rollAnimDownRight.PushBack({ 11 * 54, 7 * 52, 54, 52 });
	rollAnimDownRight.PushBack({ 12 * 54, 7 * 52, 54, 52 });
	rollAnimDownRight.PushBack({ 13 * 54, 7 * 52, 54, 52 });
	rollAnimDownRight.PushBack({ 14 * 54, 7 * 52, 54, 52 });
	rollAnimDownRight.PushBack({ 15 * 54, 7 * 52, 54, 52 });
	rollAnimDownRight.PushBack({ 16 * 54, 7 * 52, 54, 52 });

	rollAnimUpLeft.PushBack({ 0,   156, 54, 52 });
	rollAnimUpLeft.PushBack({ 54,  156, 54, 52 });
	rollAnimUpLeft.PushBack({ 108, 156, 54, 52 });
	rollAnimUpLeft.PushBack({ 162, 156, 54, 52 });
	rollAnimUpLeft.PushBack({ 216, 156, 54, 52 });
	rollAnimUpLeft.PushBack({ 270, 156, 54, 52 });
	rollAnimUpLeft.PushBack({ 324, 156, 54, 52 });
	rollAnimUpLeft.PushBack({ 378, 156, 54, 52 });
	rollAnimUpLeft.PushBack({ 432, 156, 54, 52 });

	rollAnimUpRight.PushBack({ 0,   104, 54, 52 });
	rollAnimUpRight.PushBack({ 54,  104, 54, 52 });
	rollAnimUpRight.PushBack({ 108, 104, 54, 52 });
	rollAnimUpRight.PushBack({ 162, 104, 54, 52 });
	rollAnimUpRight.PushBack({ 216, 104, 54, 52 });
	rollAnimUpRight.PushBack({ 270, 104, 54, 52 });
	rollAnimUpRight.PushBack({ 324, 104, 54, 52 });
	rollAnimUpRight.PushBack({ 378, 104, 54, 52 });
	rollAnimUpRight.PushBack({ 432, 104, 54, 52 });

	// Shoot Animations
	shootAnimUp.PushBack({ 648, 676, 54, 52 });
	shootAnimUp.PushBack({ 702, 676, 54, 52 });
	shootAnimUp.PushBack({ 756, 676, 54, 52 });

	shootAnimDown.PushBack({ 0  , 728, 54, 52 });
	shootAnimDown.PushBack({ 54 , 728, 54, 52 });
	shootAnimDown.PushBack({ 108, 728, 54, 52 });

	shootAnimLeft.PushBack({ 486, 676, 54, 52 });
	shootAnimLeft.PushBack({ 540, 676, 54, 52 });
	shootAnimLeft.PushBack({ 594, 676, 54, 52 });

	shootAnimRight.PushBack({ 324, 676, 54, 52 });
	shootAnimRight.PushBack({ 378, 676, 54, 52 });
	shootAnimRight.PushBack({ 432, 676, 54, 52 });

	shootAnimDownLeft.PushBack({ 156, 728, 54, 52 });
	shootAnimDownLeft.PushBack({ 210, 728, 54, 52 });
	shootAnimDownLeft.PushBack({ 264, 728, 54, 52 });

	shootAnimDownRight.PushBack({ 486, 728, 54, 52 });
	shootAnimDownRight.PushBack({ 540, 728, 54, 52 });
	shootAnimDownRight.PushBack({ 594, 728, 54, 52 });

	shootAnimUpLeft.PushBack({ 324, 728, 54, 52 });
	shootAnimUpLeft.PushBack({ 378, 728, 54, 52 });
	shootAnimUpLeft.PushBack({ 432, 728, 54, 52 });

	shootAnimUpRight.PushBack({ 648, 728, 54, 52 });
	shootAnimUpRight.PushBack({ 702, 728, 54, 52 });
	shootAnimUpRight.PushBack({ 756, 728, 54, 52 });

	// Grenade Animations
	grenadeAnimUp.PushBack({ 752, 520, 54, 52 });
	grenadeAnimUp.PushBack({ 702, 520, 54, 52 });
	grenadeAnimUp.PushBack({ 648, 520, 54, 52 });
	grenadeAnimUp.PushBack({ 594, 520, 54, 52 });
	grenadeAnimUp.PushBack({ 540, 520, 54, 52 });

	grenadeAnimDown.PushBack({ 270, 520, 54, 52 });
	grenadeAnimDown.PushBack({ 486, 520, 54, 52 });
	grenadeAnimDown.PushBack({ 432, 520, 54, 52 });
	grenadeAnimDown.PushBack({ 378, 520, 54, 52 });
	grenadeAnimDown.PushBack({ 324, 520, 54, 52 });

	grenadeAnimLeft.PushBack({ 216, 572, 54, 52 });
	grenadeAnimLeft.PushBack({ 162, 572, 54, 52 });
	grenadeAnimLeft.PushBack({ 108, 572, 54, 52 });
	grenadeAnimLeft.PushBack({ 54 , 572, 54, 52 });
	grenadeAnimLeft.PushBack({ 0  , 572, 54, 52 });

	grenadeAnimRight.PushBack({ 270, 572, 54, 52 });
	grenadeAnimRight.PushBack({ 324, 572, 54, 52 });
	grenadeAnimRight.PushBack({ 378, 572, 54, 52 });
	grenadeAnimRight.PushBack({ 432, 572, 54, 52 });
	grenadeAnimRight.PushBack({ 486, 572, 54, 52 });

	grenadeAnimDownLeft.PushBack({ 216, 468, 54, 52 });
	grenadeAnimDownLeft.PushBack({ 162, 468, 54, 52 });
	grenadeAnimDownLeft.PushBack({ 108, 468, 54, 52 });
	grenadeAnimDownLeft.PushBack({ 54 , 468, 54, 52 });
	grenadeAnimDownLeft.PushBack({ 0  , 468, 54, 52 });

	grenadeAnimDownRight.PushBack({ 756, 468, 54, 52 });
	grenadeAnimDownRight.PushBack({ 702, 468, 54, 52 });
	grenadeAnimDownRight.PushBack({ 648, 468, 54, 52 });
	grenadeAnimDownRight.PushBack({ 594, 468, 54, 52 });
	grenadeAnimDownRight.PushBack({ 540, 468, 54, 52 });

	grenadeAnimUpLeft.PushBack({ 486, 468, 54, 52 });
	grenadeAnimUpLeft.PushBack({ 432, 468, 54, 52 });
	grenadeAnimUpLeft.PushBack({ 378, 468, 54, 52 });
	grenadeAnimUpLeft.PushBack({ 324, 468, 54, 52 });
	grenadeAnimUpLeft.PushBack({ 270, 468, 54, 52 });

	grenadeAnimUpRight.PushBack({ 216, 520, 54, 52 });
	grenadeAnimUpRight.PushBack({ 162, 520, 54, 52 });
	grenadeAnimUpRight.PushBack({ 108, 520, 54, 52 });
	grenadeAnimUpRight.PushBack({ 54 , 520, 54, 52 });
	grenadeAnimUpRight.PushBack({ 0  , 520, 54, 52 });

	// Damage Animations
	damageAnim.PushBack({ 540, 572, 54, 52 });
	damageAnim.PushBack({ 594, 572, 54, 52 });
	damageAnim.PushBack({ 648, 572, 54, 52 });
	damageAnim.PushBack({ 702, 572, 54, 52 });

	// Death Animations
	deathAnim.PushBack({ 486, 416, 54, 52 });
	deathAnim.PushBack({ 540, 416, 54, 52 });
	deathAnim.PushBack({ 594, 416, 54, 52 });
	deathAnim.PushBack({ 648, 416, 54, 52 });
	deathAnim.PushBack({ 702, 416, 54, 52 });
	deathAnim.PushBack({ 756, 416, 54, 52 });
	deathAnim.PushBack({ 810, 416, 54, 52 });
	deathAnim.PushBack({ 864, 416, 54, 52 });

	// Win Animations
	winAnim.PushBack({ 0, 786, 54, 52 });
	winAnim.PushBack({ 54, 786, 54, 52 });
	winAnim.PushBack({ 108, 786, 54, 52 });
	winAnim.PushBack({ 162, 786, 54, 52 });
	winAnim.PushBack({ 216, 786, 54, 52 });
	winAnim.PushBack({ 270, 786, 54, 52 });
	winAnim.PushBack({ 324, 786, 54, 52 });
	winAnim.PushBack({ 378, 786, 54, 52 });
	winAnim.PushBack({ 432, 786, 54, 52 });
	winAnim.PushBack({ 486, 786, 54, 52 });
	winAnim.PushBack({ 540, 786, 54, 52 });
	winAnim.PushBack({ 594, 786, 54, 52 });
	winAnim.PushBack({ 648, 786, 54, 52 });
	winAnim.PushBack({ 702, 786, 54, 52 });
	winAnim.PushBack({ 756, 786, 54, 52 });
	winAnim.PushBack({ 810, 786, 54, 52 });
	winAnim.PushBack({ 864, 786, 54, 52 });

	winAnim.loop = false;

	idleAnimUpTorso.speed = animSpeed;
	idleAnimDownTorso.speed = animSpeed;
	idleAnimLeftTorso.speed = animSpeed;
	idleAnimRightTorso.speed = animSpeed;
	idleAnimDownLeftTorso.speed = animSpeed;
	idleAnimDownRightTorso.speed = animSpeed;
	idleAnimUpLeftTorso.speed = animSpeed;
	idleAnimUpRightTorso.speed = animSpeed;

	downAnimLegs.speed = animSpeed;
	leftAnimLegs.speed = animSpeed;
	rightAnimLegs.speed = animSpeed;
	downLeftAnimLegs.speed = animSpeed;
	downRightAnimLegs.speed = animSpeed;
	upLeftAnimLegs.speed = animSpeed;
	upRightAnimLegs.speed = animSpeed;
	upAnimLegs.speed = animSpeed;

	rollAnimUp.speed = animSpeed;
	rollAnimDown.speed = animSpeed;
	rollAnimLeft.speed = animSpeed;
	rollAnimRight.speed = animSpeed;
	rollAnimDownLeft.speed = animSpeed;
	rollAnimDownRight.speed = animSpeed;
	rollAnimUpLeft.speed = animSpeed;
	rollAnimUpRight.speed = animSpeed;

	rollAnimUp.loop = false;
	rollAnimDown.loop = false;
	rollAnimLeft.loop = false;
	rollAnimRight.loop = false;
	rollAnimDownLeft.loop = false;
	rollAnimDownRight.loop = false;
	rollAnimUpLeft.loop = false;
	rollAnimUpRight.loop = false;

	shootAnimUp.speed = animSpeed;
	shootAnimDown.speed = animSpeed;
	shootAnimLeft.speed = animSpeed;
	shootAnimRight.speed = animSpeed;
	shootAnimDownLeft.speed = animSpeed;
	shootAnimDownRight.speed = animSpeed;
	shootAnimUpLeft.speed = animSpeed;
	shootAnimUpRight.speed = animSpeed;

	deathAnim.speed = animSpeed;
	deathAnim.loop = false;

	damageAnim.speed = animSpeed;

	winAnim.speed = animSpeed;

}

ModulePlayer::~ModulePlayer() {

}

void ModulePlayer::updateHp() {
		
	if (!isInvulnerable) {
		// TODO revisar esta invulnerabilidad
		invulnerabilityTimer = 0.0f;
		
	}
	if (!hitIsInvulnerable) {
		hitIsInvulnerable = true;
		hitInvulnerabilityTimer = 0.0f;
	
	}
}

void ModulePlayer::godMode() {
	// Activate god mode
	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN) {
		isGodMode = !isGodMode;
	}

	// Damage player 
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) {
		hp -= 10;
	}

	// Heal player
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && hp < 100) {
		hp += 10;
	}

	// Kill player
	if (App->input->keys[SDL_SCANCODE_F5] == Key_State::KEY_DOWN) {
		isGodMode = false;
		hp = 0;
	}

	// Win game
	if (App->input->keys[SDL_SCANCODE_F6] == Key_State::KEY_DOWN) {
		App->enemies->winCondition = true;
	}

	// TP player to the flying battleship (for testing purposes)
	if (App->input->keys[SDL_SCANCODE_F7] == Key_State::KEY_DOWN) {
		App->player->position.x = 180;
		App->player->position.y = 1400;
		App->render->camera.x = 180;
		App->render->camera.y = 1400;
	}

	// TP player to the tank boss (for testing purposes)
	if (App->input->keys[SDL_SCANCODE_F8] == Key_State::KEY_DOWN) {
		App->player->position.x = 1430;
		App->player->position.y = 250;
		App->render->camera.x = 1430;
		App->render->camera.y = 250;
	}

	// Spawn score pick up
	if (App->input->keys[SDL_SCANCODE_F9] == Key_State::KEY_DOWN) {
		App->pickUps->SpawnPickUp({ PickUp_Type::DIAMOND,(int)position.x, (int)position.y - 50 , false });
	}

	// Spawn No Damage pick up
	if (App->input->keys[SDL_SCANCODE_F10] == Key_State::KEY_DOWN) {
		App->pickUps->SpawnPickUp({ PickUp_Type::INVENCIBILITY,(int)position.x, (int)position.y - 50 , false });
	}

	// Spawn heal pick up
	if (App->input->keys[SDL_SCANCODE_F11] == Key_State::KEY_DOWN) {
		App->pickUps->SpawnPickUp({ PickUp_Type::HP,(int)position.x, (int)position.y - 50 , false });
	}

}

void ModulePlayer::setIdleAnimations() {
	switch (lastDirection) {
		case 1: //UR
			currentAnimationTorso = &idleAnimUpRightTorso;
			currentAnimationLegs = &idleAnimUpRightLegs;
			break;
		case 2: //UL
			currentAnimationTorso = &idleAnimUpLeftTorso;
			currentAnimationLegs = &idleAnimUpLeftLegs;
			break;
		case 3: //DR
			currentAnimationTorso = &idleAnimDownRightTorso;
			currentAnimationLegs = &idleAnimDownRightLegs;
			break;
		case 4: //DL
			currentAnimationTorso = &idleAnimDownLeftTorso;
			currentAnimationLegs = &idleAnimDownLeftLegs;
			break;
		case 5: //R
			currentAnimationTorso = &idleAnimRightTorso;
			currentAnimationLegs = &idleAnimRightLegs;
			break;
		case 6: //L
			currentAnimationTorso = &idleAnimLeftTorso;
			currentAnimationLegs = &idleAnimLeftLegs;
			break;
		case 7: //D
			currentAnimationTorso = &idleAnimDownTorso;
			currentAnimationLegs = &idleAnimDownLegs;
			break;
		case 8: //U
			currentAnimationTorso = &idleAnimUpTorso;
			currentAnimationLegs = &idleAnimUpLegs;
			break;
		}
}

void ModulePlayer::setMovingAnimations() {
	switch (lastDirection) {
	case 1: //UR
		currentAnimationTorso = &idleAnimUpRightTorso;
		currentAnimationLegs = &upRightAnimLegs;
		break;
	case 2: //UL
		currentAnimationTorso = &idleAnimUpLeftTorso;
		currentAnimationLegs = &upLeftAnimLegs;
		break;
	case 3: //DR
		currentAnimationTorso = &idleAnimDownRightTorso;
		currentAnimationLegs = &downRightAnimLegs;
		break;
	case 4: //DL
		currentAnimationTorso = &idleAnimDownLeftTorso;
		currentAnimationLegs = &downLeftAnimLegs;
		break;
	case 5: //R
		currentAnimationTorso = &idleAnimRightTorso;
		currentAnimationLegs = &rightAnimLegs;
		break;
	case 6: //L
		currentAnimationTorso = &idleAnimLeftTorso;
		currentAnimationLegs = &leftAnimLegs;
		break;
	case 7: //D
		currentAnimationTorso = &idleAnimDownTorso;
		currentAnimationLegs = &downAnimLegs;
		break;
	case 8: //U
		currentAnimationTorso = &idleAnimUpTorso;
		currentAnimationLegs = &upAnimLegs;
		break;
	}
}

void ModulePlayer::setShootingAnimations() {
	switch (lastDirection) {
	case 1: //UR
		currentAnimationTorso = &shootAnimUpRight;
		currentAnimationLegs = &idleAnimUpLegs;
		break;
	case 2: //UL
		currentAnimationTorso = &shootAnimUpLeft;
		currentAnimationLegs = &idleAnimUpLeftLegs;
		break;
	case 3: //DR
		currentAnimationTorso = &shootAnimDownRight;
		currentAnimationLegs = &idleAnimDownRightLegs;
		break;
	case 4: //DL
		currentAnimationTorso = &shootAnimDownLeft;
		currentAnimationLegs = &idleAnimDownLeftLegs;
		break;
	case 5: //R
		currentAnimationTorso = &shootAnimRight;
		currentAnimationLegs = &idleAnimRightLegs;
		break;
	case 6: //L
		currentAnimationTorso = &shootAnimLeft;
		currentAnimationLegs = &idleAnimLeftLegs;
		break;
	case 7: //D
		 currentAnimationTorso = &shootAnimDown;
		currentAnimationLegs = &idleAnimDownLegs;
		break;
	case 8: //U
		currentAnimationTorso = &shootAnimUp;
		currentAnimationLegs = &idleAnimUpLegs;
		break;
	}
}

void ModulePlayer::setGrenadeAnimations() {
	// revisar
	switch (lastDirection) {
	case 1: //UR
		currentAnimationTorso = &grenadeAnimUpRight;
		currentAnimationLegs = &upRightAnimLegs;
		break;
	case 2: //UL
		currentAnimationTorso = &grenadeAnimUpLeft;
		currentAnimationLegs = &upLeftAnimLegs;
		break;
	case 3: //DR
		currentAnimationTorso = &grenadeAnimDownRight;
		currentAnimationLegs = &downRightAnimLegs;
		break;
	case 4: //DL
		currentAnimationTorso = &grenadeAnimDownLeft;
		currentAnimationLegs = &downLeftAnimLegs;
		break;
	case 5: //R
		currentAnimationTorso = &grenadeAnimRight;
		currentAnimationLegs = &rightAnimLegs;
		break;
	case 6: //L
		currentAnimationTorso = &grenadeAnimLeft;
		currentAnimationLegs = &leftAnimLegs;
		break;
	case 7: //D
		currentAnimationTorso = &grenadeAnimDown;
		currentAnimationLegs = &downAnimLegs;
		break;
	case 8: //U
		currentAnimationTorso = &grenadeAnimUp;
		currentAnimationLegs = &upAnimLegs;
		break;
	}
}

void ModulePlayer::setRollAnimations() {
	currentAnimationTorso = &emptyAnimation;
	switch (lastDirection) {
	case 1: //UR
		currentAnimationLegs = &rollAnimUpRight;
		break;
	case 2: //UL
		currentAnimationLegs = &rollAnimUpLeft;
		break;
	case 3: //DR
		currentAnimationLegs = &rollAnimDownRight;
		break;
	case 4: //DL
		currentAnimationLegs = &rollAnimDownLeft;
		break;
	case 5: //R
		currentAnimationLegs = &rollAnimRight;
		break;
	case 6: //L
		currentAnimationLegs = &rollAnimLeft;
		break;
	case 7: //D
		currentAnimationLegs = &rollAnimDown;
		break;
	case 8: //U
		currentAnimationLegs = &rollAnimUp;
		break;
	}
}

void ModulePlayer::setWinAnimations() {
	currentAnimationTorso = &emptyAnimation;
	currentAnimationLegs = &winAnim;
}

void ModulePlayer::setSpawnAnimations() {
	currentAnimationLegs = &idleAnimUpLegs;
	currentAnimationTorso = &idleAnimUpTorso;
}

void ModulePlayer::setDeathAnimations() {
	currentAnimationTorso = &emptyAnimation;
	currentAnimationLegs = &deathAnim;
}

void ModulePlayer::setDamageAnimations() {
	currentAnimationTorso = &emptyAnimation;
	currentAnimationLegs = &damageAnim;
}

void ModulePlayer::setShootingMovingAnimations() {
	switch (shootDirection) {
	case 1: //UR
		currentAnimationTorso = &shootAnimUpRight;
		break;
	case 2: //UL
		currentAnimationTorso = &shootAnimUpLeft;
		break;
	case 3: //DR
		currentAnimationTorso = &shootAnimDownRight;
		break;
	case 4: //DL
		currentAnimationTorso = &shootAnimDownLeft;
		break;
	case 5: //R
		currentAnimationTorso = &shootAnimRight;
		break;
	case 6: //L
		currentAnimationTorso = &shootAnimLeft;
		break;
	case 7: //D
		currentAnimationTorso = &shootAnimDown;
		break;
	case 8: //U
		currentAnimationTorso = &shootAnimUp;
		break;
	}

	switch (lastDirection) {
	case 1: //UR
		currentAnimationLegs = &upRightAnimLegs;
		break;
	case 2: //UL
		currentAnimationLegs = &upLeftAnimLegs;
		break;
	case 3: //DR
		currentAnimationLegs = &downRightAnimLegs;
		break;
	case 4: //DL
		currentAnimationLegs = &downLeftAnimLegs;
		break;
	case 5: //R
		currentAnimationLegs = &rightAnimLegs;
		break;
	case 6: //L
		currentAnimationLegs = &leftAnimLegs;
		break;
	case 7: //D
		currentAnimationLegs = &downAnimLegs;
		break;
	case 8: //U
		currentAnimationLegs = &upAnimLegs;
		break;
	}
}

bool ModulePlayer::isShootingMoving() {
	GamePad& pad = App->input->pads[0];

	if ((App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT or
		App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT or
		App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT or
		App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) 
		and
		(App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT)
		and !lockControls) {
		return true;

	}
	else if ((pad.l_y < 0 or pad.l_x < 0 or pad.l_y > 0 or pad.l_x > 0) and
		(pad.x == true) and !lockControls) {
		return true;

	}
	else {

		return false;

	}
}

bool ModulePlayer::isMoving() {
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT or
		App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT or
		App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT or
		App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT or
		pad.l_y < 0 or pad.l_x < 0 or pad.l_y > 0 or pad.l_x > 0 and

		!lockControls) {

		return true;

	}
	else {

		return false;

	}
}

bool ModulePlayer::isShooting() {
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT or pad.x == true and !lockControls) {
		return true;

	}
	else {

		return false;

	}

}

bool ModulePlayer::isGrenade() {
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_Z] == Key_State::KEY_REPEAT or pad.y == true and !lockControls) {

		return true;

	}
	else {

		return false;

	}
}

bool ModulePlayer::isRoll() {
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN or pad.b == true or isRolling) {
		isRolling = true;
		
		return true;

	}
	else {

		return false;

	}
}

void ModulePlayer::move() {
	switch (currentDirection) {
		case 1: //UR
			if (!lockR) {
				position.x += speed;
			}
			if (!lockU) {
				position.y -= speed;
			}
			break;
		case 2: //UL
			if (!lockU) {
				position.y -= speed;
			}
			if (!lockL) {
				position.x -= speed;
			}
			break;
		case 3: //DR
			if (!lockR) position.x += speed;
			if (!lockD) position.y += speed;
			break;
		case 4: //DL
			if (!lockL) {
				position.x -= speed;
			}
			if (!lockD) {
				position.y += speed;
			}
			break;
		case 5: //R
			if (!lockR) {
				position.x += speed;
			}
			break;
		case 6: //L
			if (!lockL) {
				position.x -= speed;
			}
			break;
		case 7: //D
			if (!lockD) {
				position.y += speed;
			}
			break;
		case 8: //U
			if (!lockU) {
				position.y -= speed;
			}
			break;
		default:
			break;
		}

	//We save the current direction if there is a new one
	if (currentDirection != 0) {
		lastDirection = currentDirection;
	}
	if (!isShootingMoving()) {
		shootDirection = currentDirection;
	}
}

void ModulePlayer::roll() {

	if (cantRoll) {
		return;
	}
	isRolling = true;

	lockControls = true;

	//If the player is rolling, the speed is increased
	speed = 1.5;

	//then the player moves
	currentDirection = lastDirection;
	move();

	//and when the player has moved 100 pixels, the roll ends
	if ((abs(diferencia.x - position.x) > 100) || (abs(diferencia.y - position.y) > 100) || ((abs(diferencia.x - position.x) == 0) && (abs(diferencia.y - position.y) == 0))) {
		isRolling = false;
	}
}

void ModulePlayer::shoot() {
	if (!isShootingMoving()) {
		shootDirection = lastDirection;
	}

	delay--;
	if (delay == 0) {
		Particle* newParticle = nullptr;
		Particle* newParticleMuzzle = nullptr;
		switch (lastDirection) {
		case 1: // Up-Right
			newParticle = App->particles->AddParticle(App->particles->playerShotUpRight, position.x + 33, position.y + 6, lastDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleUpRight, position.x + 33, position.y - 4, 0, Collider::Type::MUZZLE);
			break;
		case 2: // Up-Left
			newParticle = App->particles->AddParticle(App->particles->playerShotUpLeft, position.x + 13, position.y + 0, lastDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleUpLeft, position.x + 3, position.y - 10, 0, Collider::Type::MUZZLE);
			break;
		case 3: // Down-Right
			newParticle = App->particles->AddParticle(App->particles->playerShotDownRight, position.x + 35, position.y + 35, lastDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleDownRight, position.x + 28, position.y + 25, 0, Collider::Type::MUZZLE);
			break;
		case 4: // Down-Left
			newParticle = App->particles->AddParticle(App->particles->playerShotDownLeft, position.x - 2, position.y + 30, lastDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleDownLeft, position.x - 2, position.y + 20, 0, Collider::Type::MUZZLE);
			break;
		case 5: // Right
			newParticle = App->particles->AddParticle(App->particles->playerShotRight, position.x + 43, position.y + 18, lastDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleRight, position.x + 43, position.y + 10, 0, Collider::Type::MUZZLE);
			break;
		case 6: // Left
			newParticle = App->particles->AddParticle(App->particles->playerShotLeft, position.x - 15, position.y + 16, lastDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleLeft, position.x - 15, position.y + 8, 0, Collider::Type::MUZZLE);
			break;
		case 7: // Down
			newParticle = App->particles->AddParticle(App->particles->playerShotDown, position.x + 20, position.y + 54, lastDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleDown, position.x + 12, position.y + 34, 0, Collider::Type::MUZZLE);
			break;
		case 8: // Up
			newParticle = App->particles->AddParticle(App->particles->playerShotUp, position.x + 30, position.y - 6, lastDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleUp, position.x + 21, position.y - 16, 0, Collider::Type::MUZZLE);
			break;
		}
		newParticle->collider->AddListener(this);
		newParticleMuzzle->collider->AddListener(this);
		App->audio->PlayFx(playerShot);

		delay = 10;
	}
}

void ModulePlayer::grenade() {
	/*
	App->particles->playerShot.setDirection(lastDirection);
	//TODO a�adir direccion
	Particle* newParticle = App->particles->AddParticle(App->particles->playerShot, position.x, position.y, lastDirection, Collider::Type::PLAYER_SHOT);
 	newParticle->collider->AddListener(this);
	newParticle->granada = true
	App->audio->PlayFx(laserFx);
	*/
}

void ModulePlayer::shootMoving() {
	delay--;
	if (delay == 0) {
		Particle* newParticle = nullptr;
		Particle* newParticleMuzzle = nullptr;
		switch (shootDirection) {
		case 1: // Up-Right
			newParticle = App->particles->AddParticle(App->particles->playerShotUpRight, position.x + 41, position.y - 2, shootDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleUpRight, position.x + 41, position.y - 12, 0, Collider::Type::MUZZLE);
			newParticle->collider->AddListener(this);
			newParticleMuzzle->collider->AddListener(this);
			break;
		case 2: // Up-Left
			newParticle = App->particles->AddParticle(App->particles->playerShotUpLeft, position.x + 5, position.y - 8, shootDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleUpLeft, position.x - 5, position.y - 18, 0, Collider::Type::MUZZLE);
			newParticle->collider->AddListener(this);
			newParticleMuzzle->collider->AddListener(this);
			break;
		case 3: // Down-Right
			newParticle = App->particles->AddParticle(App->particles->playerShotDownRight, position.x + 43, position.y + 43, shootDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleDownRight, position.x + 36, position.y + 33, 0, Collider::Type::MUZZLE);
			newParticle->collider->AddListener(this);
			newParticleMuzzle->collider->AddListener(this);
			break;
		case 4: // Down-Left
			newParticle = App->particles->AddParticle(App->particles->playerShotDownLeft, position.x - 9, position.y + 39, shootDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleDownLeft, position.x - 9, position.y + 29, 0, Collider::Type::MUZZLE);
			newParticle->collider->AddListener(this);
			newParticleMuzzle->collider->AddListener(this);
			break;
		case 5: // Right
			newParticle = App->particles->AddParticle(App->particles->playerShotRight, position.x + 51, position.y + 18, shootDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleRight, position.x + 51, position.y + 10, 0, Collider::Type::MUZZLE);
			newParticle->collider->AddListener(this);
			newParticleMuzzle->collider->AddListener(this);
			break;
		case 6: // Left
			newParticle = App->particles->AddParticle(App->particles->playerShotLeft, position.x - 23, position.y + 16, shootDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleLeft, position.x - 23, position.y + 8, 0, Collider::Type::MUZZLE);
			newParticle->collider->AddListener(this);
			newParticleMuzzle->collider->AddListener(this);
			break;
		case 7: // Down
			newParticle = App->particles->AddParticle(App->particles->playerShotDown, position.x + 20, position.y + 60, shootDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleDown, position.x + 12, position.y + 40, 0, Collider::Type::MUZZLE);
			newParticle->collider->AddListener(this);
			newParticleMuzzle->collider->AddListener(this);
			break;
		case 8: // Up
			newParticle = App->particles->AddParticle(App->particles->playerShotUp, position.x + 30, position.y - 13, shootDirection, Collider::Type::PLAYER_SHOT);
			newParticleMuzzle = App->particles->AddParticle(App->particles->playerMuzzleUp, position.x + 21, position.y - 23, 0, Collider::Type::MUZZLE);
			newParticle->collider->AddListener(this);
			newParticleMuzzle->collider->AddListener(this);
			break;
		}
		App->audio->PlayFx(playerShot);

		delay = 10;
	}
}

void ModulePlayer::getLastDirection() {
	
	GamePad& pad = App->input->pads[0];

//Map controls
	if(!lockControls){

		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT || pad.l_y < 0 && pad.l_x > 0) {
			currentDirection = 1;
		} else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || pad.l_y < 0 && pad.l_x < 0) {
			currentDirection = 2;
		} else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT || pad.l_y > 0 && pad.l_x > 0) {
			currentDirection = 3;
		} else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || pad.l_y > 0 && pad.l_x < 0) {
			currentDirection = 4;
		} else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT || pad.l_x > 0) {
			currentDirection = 5;
		} else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || pad.l_x < 0) {
			currentDirection = 6;
		} else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT || pad.l_y > 0) {
			currentDirection = 7;
		} else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT || pad.l_y < 0) {
			currentDirection = 8;
		} else {
			currentDirection = 0;
		}
	}

	//We save the current direction if there is a new one
	if (currentDirection != 0) {
		lastDirection = currentDirection;
	}
}

void ModulePlayer::saveLastPosition() {
	diferencia.x = position.x;
	diferencia.y = position.y;
}

void ModulePlayer::stateMachine() {
	getLastDirection();

	switch (currentState) {

	case PlayerState::Idle:

		setIdleAnimations();

		if (isShootingMoving()) {
			currentState = PlayerState::ShootingMoving;
		}

		if (isMoving()) {
			currentState = PlayerState::Moving;
		}

		if (isHitted) {
			currentState = PlayerState::Damage;
		}

		if (isShooting()) {
			currentState = PlayerState::Shooting;
		}

		if (hp == 0 or App->ui->timerCounter == 0) {
			currentState = PlayerState::Death;
		}

		if (App->enemies->winCondition) {
			currentState = PlayerState::Win;
		}

		if (isRoll()) {
			currentState = PlayerState::Roll;
		}

		if (isGrenade()) {
			currentState = PlayerState::Grenade;
		}

		saveLastPosition();
		invulnerability();
		break;

	case PlayerState::ShootingMoving:

		setShootingMovingAnimations();

		move();

		saveLastPosition();

		shootMoving();
		
		if (isHitted) {
			currentState = PlayerState::Damage;
		}

		if (!isShootingMoving()) {
			currentState = PlayerState::Idle;
		}

		if (isRoll()) {
			currentState = PlayerState::Roll;
		}

		if (App->enemies->winCondition) {
			currentState = PlayerState::Win;
		}

		invulnerability();
		break;

	case PlayerState::Moving:

		setMovingAnimations();

		move();

		saveLastPosition();

		if (isHitted) {
			currentState = PlayerState::Damage;
		}

		if (isShootingMoving()) {
			currentState = PlayerState::ShootingMoving;
		}

		if (isRoll()) {
			currentState = PlayerState::Roll;
		}

		if (!isMoving()) {
			currentState = PlayerState::Idle;
		}

		if (App->enemies->winCondition) {
			currentState = PlayerState::Win;
		}

		invulnerability();
		break;

	case PlayerState::Shooting:
		
		setShootingAnimations();

		shoot();

		if (isHitted) {
			currentState = PlayerState::Damage;
		}

		if (isShootingMoving()) {
			currentState = PlayerState::ShootingMoving;
		}

		if (isRoll()) {
			currentState = PlayerState::Roll;
		}

		if (!isShooting()) {
			currentState = PlayerState::Idle;
		}

		if (App->enemies->winCondition) {
			currentState = PlayerState::Win;
		}

		invulnerability();
		break;

	case PlayerState::Grenade:

		setGrenadeAnimations();

		// Grenade logic
		grenade();

		if (isHitted) {
			currentState = PlayerState::Damage;
		}

		if (isRoll()) {
			currentState = PlayerState::Roll;
		}

		if (!isGrenade()) {
			currentState = PlayerState::Idle;
		}

		invulnerability();
		break;

	case PlayerState::Roll:

		setRollAnimations();

		roll();

		if (!isRoll()) {
			currentAnimationLegs->Reset();
			lockControls = false;
			isRolling = false;
			currentState = PlayerState::Idle;
		}

		break;

	case PlayerState::Win:

		setWinAnimations();

		if (playStageClearOnce < 1) {
			playStageClearOnce++;
			App->audio->PlayMusic("Assets/Audio/Music/05_Shock_Troopers_stage_clear.ogg", 0.1f);
		}

		if (winAnim.HasFinished() and App->ui->endStage.HasFinished()) {
			App->render->leaveZone = true;
			App->render->isInZone = false;
			App->render->isInZone2 = false;
			App->render->isInZone3 = false;
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneMenu, 60);

		}

		break;

	case PlayerState::Spawn:

		setSpawnAnimations();

		// reset camera position
		App->render->camera.x = 66;
		App->render->camera.y = 2800;

		// enter idle state
		currentState = PlayerState::Idle;

		break;

	case PlayerState::Death:

		setDeathAnimations();

		if (deathAnim.HasFinished()) {
			App->render->leaveZone = true;
			App->render->isInZone = false;
			App->render->isInZone2 = false;
			App->render->isInZone3 = false;
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneMenu, 200);
		}

		break;

	case PlayerState::Damage:

		setDamageAnimations();

		// Damage logic
		updateHp();

		if (hitIsInvulnerable) {
			// Check if the invulnerability period has ended
			if (hitInvulnerabilityTimer >= hitInvulnerabilityDuration) {
				// Make the player vulnerable again
				hitIsInvulnerable = false;
				isHitted = false;
			}

			// Update the invulnerability timer
			hitInvulnerabilityTimer += 1;
		}

		if (hp == 0 || App->ui->timerCounter == 0) {
			currentState = PlayerState::Death;
		}
		
		if (!isHitted) {
			currentState = PlayerState::Idle;
		}

		break;
	}
}

void ModulePlayer::invulnerability() {

	if (isInvulnerable && !hitIsInvulnerable) {
		// Check if the invulnerability period has ended
		if (invulnerabilityTimer >= invulnerabilityDuration) {
			// Make the player vulnerable again
			isInvulnerable = false;
			isHitted = false;
		}

		// Update the invulnerability timer
		invulnerabilityTimer += 1;
	}
}

bool ModulePlayer::Start() {
	// start and reset some variables
	lastDirection = 8;
	hp = 100;
	deathAnim.Reset();
	isInvulnerable = false;
	hitIsInvulnerable = false;
	currentState = PlayerState::Spawn;
	App->render->camera.x = 66;
	App->render->camera.y = 2800;
	playStageClearOnce = 0;



	// Set the animations to spawn
	setSpawnAnimations();

	LOG("Loading player textures");

	bool ret = true;

	// Load milky textures
	texture = App->textures->Load("Assets/Sprites/characters/milky_spritesheet.png");
	if (texture == nullptr)
	{
		LOG("Failed to load milky_spritesheet.png texture");
		ret = false;
	}

	// Load UI textures
	textureP1 = App->textures->Load("Assets/Sprites/ui/Player1_Milky.png");
	if (textureP1 == nullptr)
	{
		LOG("Failed to load Player1_Milky.png texture");
		ret = false;
	}

	textureWeapon = App->textures->Load("Assets/Sprites/ui/Weapon_Normal.png");
	if (textureWeapon == nullptr)
	{
		LOG("Failed to load Weapon_Normal.png texture");
		ret = false;
	}

	// Load sound effects
	playerShot = App->audio->LoadFx("Assets/fx/disparoMilky.wav");
	if (playerShot == -1)
	{
		LOG("Failed to load disparoMilky.wav sound effect");
		ret = false;
	}

	//Setting up player position
	position.x = 186;
	position.y = 2900;

	//Setting up player wall coliders
	colliderL = App->collisions->AddCollider({ (int)position.x + 5, (int)position.y + 2, 2, 43 }, Collider::Type::LASER, this);
	colliderU = App->collisions->AddCollider({ (int)position.x + 5, (int)position.y + 8, 22, 2 }, Collider::Type::LASER, this);
	colliderD = App->collisions->AddCollider({ (int)position.x + 5, (int)position.y + 51, 22, 2 }, Collider::Type::LASER, this);
	colliderR = App->collisions->AddCollider({ (int)position.x + 32, (int)position.y + 2, 2,43 }, Collider::Type::LASER, this);

	//Setting up player hitbox
	collider = App->collisions->AddCollider({ (int)position.x + 5,(int)position.y + 10, 22, 43 }, Collider::Type::PLAYER, this);

	App->render->cameraDownCollider = App->collisions->AddCollider({ SCREEN_WIDTH, SCREEN_HEIGHT + 10, SCREEN_WIDTH, 5 }, Collider::Type::WALL);
	App->render->cameraLeftCollider = App->collisions->AddCollider({ SCREEN_WIDTH, SCREEN_HEIGHT + 10, 5, SCREEN_HEIGHT }, Collider::Type::WALL);
	App->render->cameraRightCollider = App->collisions->AddCollider({ SCREEN_WIDTH, SCREEN_HEIGHT, 5, SCREEN_HEIGHT }, Collider::Type::WALL);
	App->render->cameraUpCollider = App->collisions->AddCollider({ SCREEN_WIDTH, SCREEN_HEIGHT + 10, SCREEN_WIDTH, 5 }, Collider::Type::WALL);
	App->render->stopCameraCollider = App->collisions->AddCollider({ 0, 0, 2, 2 }, Collider::Type::STOP_CAM_TRIGGER, App->render);
	App->render->stopCameraCollider->AddListener(App->render);

	return ret;
}

Update_Status ModulePlayer::Update() {

	// Update the state machine
	stateMachine();

	godMode();

	//Collider update
	collider->SetPos(position.x + 12, position.y + 10);
	colliderR->SetPos(position.x + 34, position.y + 10);
	colliderD->SetPos(position.x + 12, position.y + 53);
	colliderL->SetPos(position.x + 10 , position.y + 10);
	colliderU->SetPos(position.x + 12, position.y +8);

	//We update the current animation
	currentAnimationLegs->Update();
	currentAnimationTorso->Update();

	App->render->cameraDownCollider->SetPos(App->render->camera.x, App->render->camera.y + SCREEN_HEIGHT);
	App->render->cameraLeftCollider->SetPos(App->render->camera.x, App->render->camera.y);
	App->render->cameraRightCollider->SetPos(App->render->camera.x + SCREEN_WIDTH, App->render->camera.y);
	App->render->cameraUpCollider->SetPos(App->render->camera.x, App->render->camera.y);
	App->render->stopCameraCollider->SetPos(App->render->camera.x + SCREEN_WIDTH / 2, App->render->camera.y + SCREEN_HEIGHT / 2);

	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	if (App->input->keys[SDL_SCANCODE_G] == Key_State::KEY_REPEAT)
	{
		App->pickUps->SpawnPickUp({PickUp_Type::INVENCIBILITY, (int)position.x + 10, (int)position.y + 10 });
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


	//Reset variables
	lockR = false;
	lockU = false;
	lockD = false;
	lockL = false;
	cantRoll = false;
	speed = 1;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate() {

	if (!destroyed) {

		//Obtenemos el rectangulo actual de la animacion
		SDL_Rect rectLegs = currentAnimationLegs->GetCurrentFrame();
		SDL_Rect rectTorso = currentAnimationTorso->GetCurrentFrame();

		//Mostramos por pantalla el frame de la animacion
		App->render->Blit(texture, position.x, position.y, &rectLegs);
		App->render->Blit(texture, position.x, position.y, &rectTorso);

	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {

	if (!hitIsInvulnerable && !isInvulnerable) {
		// Ignore collision while invulnerable
		if (c1 == collider && destroyed == false && c2->type == Collider::Type::ENEMY_SHOT && isRolling == false && !isGodMode) {

			if (hp > 0) {
				hp -= 10;
			}

			isHitted = true;

		}

	}

	if (c1 == colliderR && destroyed == false && (c2->type == Collider::Type::WALL || c2->type == Collider::Type::PLAYER_WALL || c2->type == Collider::Type::OBJECT) && !isGodMode) {
		lockR = true;
		if (isRolling) {
			position.x -= 2;
		}
		isRolling = false;
		cantRoll = true;
	}

	if (c1 == colliderU && destroyed == false && (c2->type == Collider::Type::WALL || c2->type == Collider::Type::PLAYER_WALL || c2->type == Collider::Type::OBJECT) && !isGodMode) {
		lockU = true;
		if (isRolling) {
			position.y += 2;
		}
		isRolling = false;
		cantRoll = true;
	}

	if (c1 == colliderD && destroyed == false && (c2->type == Collider::Type::WALL || c2->type == Collider::Type::PLAYER_WALL || c2->type == Collider::Type::OBJECT) && !isGodMode) {
		lockD = true;
		if (isRolling) {
			position.y -= 2;
		}
		isRolling = false;
		cantRoll = true;
	}

	if (c1 == colliderL && destroyed == false && (c2->type == Collider::Type::WALL || c2->type == Collider::Type::PLAYER_WALL || c2->type == Collider::Type::OBJECT) && !isGodMode) {
		lockL = true;
		if (isRolling) {
			position.x += 2;
		}
		isRolling = false;
		cantRoll = true;
	}
	

	if (c1 == collider && destroyed == false && c2->type == Collider::Type::PICKUP_HP) {
		if (hp < 100)
		hp += 10;
	}
	if (c1 == collider && destroyed == false && c2->type == Collider::Type::PICKUP_DIAMOND) {
		App->ui->updateScore(3000);
	}
	if (c1 == collider && destroyed == false && c2->type == Collider::Type::PICKUP_NODAMAGE) {
			isInvulnerable = true;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY) {
		App->ui->updateScore(300);
	}

	if (!isRolling) {
		if (c1 == collider && destroyed == false && c2->type == Collider::Type::LANDMINE && !isGodMode) {

			if (hp < 0) {
				hp -= 20;
			}

			isHitted = true;

		}
	}

}