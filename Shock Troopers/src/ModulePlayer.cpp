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

	rollAnimDownRight.PushBack({ 486, 416, 54, 52 });
	rollAnimDownRight.PushBack({ 540, 416, 54, 52 });
	rollAnimDownRight.PushBack({ 594, 416, 54, 52 });
	rollAnimDownRight.PushBack({ 648, 416, 54, 52 });
	rollAnimDownRight.PushBack({ 702, 416, 54, 52 });
	rollAnimDownRight.PushBack({ 756, 416, 54, 52 });
	rollAnimDownRight.PushBack({ 810, 416, 54, 52 });
	rollAnimDownRight.PushBack({ 864, 416, 54, 52 });

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

	shootAnimUp.speed = animSpeed;
	shootAnimDown.speed = animSpeed;
	shootAnimLeft.speed = animSpeed;
	shootAnimRight.speed = animSpeed;
	shootAnimDownLeft.speed = animSpeed;
	shootAnimDownRight.speed = animSpeed;
	shootAnimUpLeft.speed = animSpeed;
	shootAnimUpRight.speed = animSpeed;

	deathAnim.speed = animSpeed;

	damageAnim.speed = animSpeed;
}

ModulePlayer::~ModulePlayer() {

}

void ModulePlayer::updateHp() {

	//Carga sprite en base a la vida del jugador
	switch (hp) {
	case 100:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_100.png");
		break;
	case 90:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_90.png");
		break;
	case 80:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_80.png");
		break;
	case 70:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_70.png");
		break;
	case 60:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_60.png");
		break;
	case 50:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_50.png");
		break;
	case 40:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_40.png");
		break;
	case 30:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_30.png");
		break;
	case 20:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_20.png");
		break;
	case 10:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_10.png");
		break;
	case 0:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_00.png");
		destroyed = true;
		//TODO  poner esto donde toque
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneMenu, 60);
		break;
	default:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_00.png");
		break;
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
		default:
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
		currentAnimationLegs = &upRightAnimLegs;
		break;
	case 2: //UL
		currentAnimationTorso = &shootAnimUpLeft;
		currentAnimationLegs = &upLeftAnimLegs;
		break;
	case 3: //DR
		currentAnimationTorso = &shootAnimDownRight;
		currentAnimationLegs = &downRightAnimLegs;
		break;
	case 4: //DL
		currentAnimationTorso = &shootAnimDownLeft;
		currentAnimationLegs = &downLeftAnimLegs;
		break;
	case 5: //R
		currentAnimationTorso = &shootAnimRight;
		currentAnimationLegs = &rightAnimLegs;
		break;
	case 6: //L
		currentAnimationTorso = &shootAnimLeft;
		currentAnimationLegs = &leftAnimLegs;
		break;
	case 7: //D
		currentAnimationTorso = &shootAnimDown;
		currentAnimationLegs = &downAnimLegs;
		break;
	case 8: //U
		currentAnimationTorso = &shootAnimUp;
		currentAnimationLegs = &upAnimLegs;
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
	// TODO
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

bool ModulePlayer::isMoving() {

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT or
		App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT or
		App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT or
		App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) {

		return true;

	}
	else {

		return false;

	}
}

bool ModulePlayer::isShooting() {

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT) {

		return true;

	}
	else {

		return false;

	}
}

bool ModulePlayer::isGrenade() {

	if (App->input->keys[SDL_SCANCODE_Z] == Key_State::KEY_REPEAT) {

		return true;

	}
	else {

		return false;

	}
}

bool ModulePlayer::isRoll()
{
	if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_REPEAT) {

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
}

void ModulePlayer::roll() {

	if (isRolling) {

		//If the player is rolling, the speed is increased
		speed = 3;

		//then the player moves
		move();

		//and when the player has moved 50 pixels, the roll ends
		if ((abs(diferencia.x - position.x) > 50) || (abs(diferencia.y - position.y) > 50) || ((abs(diferencia.x - position.x) == 0) && (abs(diferencia.y - position.y) == 0))) {
			isRolling = false;
		}

	} else {	

		if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) {
			hp -= 10;

		}

		if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && hp < 100) {
			hp += 10;

		}

		if (App->input->keys[SDL_SCANCODE_F5] == Key_State::KEY_DOWN) {
			godMode = false;
			hp = 0;
		}

		if (App->input->keys[SDL_SCANCODE_B] == Key_State::KEY_DOWN) {
			App->pickUps->SpawnPickUp({ PickUp_Type::HP,position.x - 90, position.y , true });
		}

	}
}

void ModulePlayer::getLastDirection() {
	//Map controls
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) {
		currentDirection = 1;
	}
	else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) {
		currentDirection = 2;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) {
		currentDirection = 3;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) {
		currentDirection = 4;
	}
	else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) {
		currentDirection = 5;
	}
	else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) {
		currentDirection = 6;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) {
		currentDirection = 7;
	}
	else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT) {
		currentDirection = 8;
	}
	else {
		currentDirection = 0;
	}

	//We save the current direction if there is a new one
	if (currentDirection != 0) {
		lastDirection = currentDirection;
	}
}	

void ModulePlayer::stateMachine() {
	getLastDirection();

	switch (currentState) {

	case PlayerState::Idle:

		setIdleAnimations();

		if (isMoving()) {
			currentState = PlayerState::Moving;
		}

		if (false/*player got hitted*/) {
			currentState = PlayerState::Damage;
		}

		if (isShooting()) {
			currentState = PlayerState::Shooting;
		}

		if (hp == 0) {
			currentState = PlayerState::Death;
		}

		if (false/*win condition*/) {
			currentState = PlayerState::Win;
		}

		if (isRoll()) {
			currentState = PlayerState::Roll;
		}

		if (isGrenade()) {
			currentState = PlayerState::Grenade;
		}

		LOG("idle state");

		break;

	case PlayerState::Moving:

		setMovingAnimations();

		move();

		if (false/*player got hitted*/) {
			currentState = PlayerState::Damage;
		}

		if (isShooting()) {
			currentState = PlayerState::Shooting;
		}

		if (hp == 0) {
			currentState = PlayerState::Death;
		}

		if (isRoll()) {
			currentState = PlayerState::Roll;
		}

		if (isGrenade()) {
			currentState = PlayerState::Grenade;
		}

		if (!isMoving()) {
			currentState = PlayerState::Idle;
		}

		LOG("moving state");

		break;

	case PlayerState::Shooting:

		setShootingAnimations();

		// Shoot logic
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT) {
			delay--;
			if (delay == 0) {
				//App->particles->laser.setDirection(lastDirection);
				Particle* newParticle = App->particles->AddParticle(App->particles->playerShot, position.x + 5, position.y + 20, lastDirection, Collider::Type::PLAYER_SHOT);
				newParticle->collider->AddListener(this);
				App->audio->PlayFx(laserFx);

				delay = 10;
			}
		}

		if (isMoving()) {
			currentState = PlayerState::Moving;
		}

		if (false/*player got hitted*/) {
			currentState = PlayerState::Damage;
		}

		if (hp == 0) {
			currentState = PlayerState::Death;
		}

		if (isRoll()) {
			currentState = PlayerState::Roll;
		}

		if (isGrenade()) {
			currentState = PlayerState::Grenade;
		}

		if (!isShooting()) {
			currentState = PlayerState::Idle;
		}

		LOG("shooting state");

		break;

	case PlayerState::Grenade:

		setGrenadeAnimations();

		// Grenade logic
		if (App->input->keys[SDL_SCANCODE_Z] == Key_State::KEY_DOWN) {
			App->particles->playerShot.setDirection(lastDirection);
			//TODO añadir direccion
			Particle* newParticle = App->particles->AddParticle(App->particles->playerShot, position.x, position.y, lastDirection, Collider::Type::PLAYER_SHOT);
			newParticle->collider->AddListener(this);
			newParticle->granada = true;
			App->audio->PlayFx(laserFx);
		}

		// probar si es posible mandar granada a idle directamente y usar los estados de idle para ahorrar comprobaciones
		// sino hay que comprobar todos los estados comentados abajo

		/*
		if (isMoving()) {
			PlayerState::Moving;
		}

		if (false/*player got hitted/) {
			PlayerState::Damage;
		}

		if (hp == 0) {
			PlayerState::Death;
		}

		if (isRoll()) {
			PlayerState::Roll;
		}

		if (isShooting()) {
			PlayerState::Shooting;
		}
		*/

		currentState = PlayerState::Idle;

		LOG("grenade state");

		break;

	case PlayerState::Roll:

		setRollAnimations();

		roll();

		// Roll logic
		if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN) {
			isRolling = true;
			diferencia.x = position.x;
			diferencia.y = position.y;
		}

		if (isMoving()) {
			currentState = PlayerState::Moving;
		}

		if (!isRoll()) {
			currentState = PlayerState::Idle;
		}

		LOG("roll state");

		break;

	case PlayerState::Win:

		setWinAnimations();

		// Win logic
		// TODO

		LOG("win state");

		break;

	case PlayerState::Spawn:

		setSpawnAnimations();

		// Spawn logic
		// TODO

		// enter idle state
		currentState = PlayerState::Idle;

		LOG("spawn state");

		break;

	case PlayerState::Death:

		setDeathAnimations();

		// Death logic
		// TODO

		LOG("death state");

		break;

	case PlayerState::Damage:

		setDamageAnimations();

		// Damage logic
		updateHp();

		if (hp == 0) {
			currentState = PlayerState::Death;
		}

		
		currentState = PlayerState::Idle;
		

		LOG("damage state");

		break;
	}
}

bool ModulePlayer::Start() {

	// Setup current state to spawn
	currentState = PlayerState::Spawn;
	setSpawnAnimations(); // TODO revisar esto, debería entrar al estado de spawn y cargar las animaciones de spawn

	LOG("Loading player textures");

	bool ret = true;

	// Load milky textures
	texture = App->textures->Load("Assets/Sprites/characters/milky_spritesheet.png");

	// Load UI textures
	textureP1 = App->textures->Load("Assets/Sprites/ui/Player1_Milky.png");
	textureWeapon = App->textures->Load("Assets/Sprites/ui/Weapon_Normal.png");

	// Load sound effects
	laserFx = App->audio->LoadFx("Assets/fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/fx/ExplosionGranada.wav");

	//Setting up player position
	position.x = 220;
	position.y = 1820;
	
	//Setting up player wall coliders
	colliderL = App->collisions->AddCollider({ position.x + 5, position.y + 2, 2, 43 }, Collider::Type::LASER, this);
	colliderU = App->collisions->AddCollider({ position.x + 5, position.y + 8, 22, 2 }, Collider::Type::LASER, this);
	colliderD = App->collisions->AddCollider({ position.x + 5, position.y + 51, 22, 2 }, Collider::Type::LASER, this);
	colliderR = App->collisions->AddCollider({ position.x + 32, position.y + 2, 2,43 }, Collider::Type::LASER, this);

	//Setting up player hitbox
	collider = App->collisions->AddCollider({ position.x + 5,position.y + 10, 22, 43 }, Collider::Type::PLAYER, this);


	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}

Update_Status ModulePlayer::Update() {

	// Update the state machine
	stateMachine();

	cout << App->render->camera.x;
	cout << App->render->camera.y;

	//Collider update
	collider->SetPos(position.x + 12, position.y + 10);
	colliderU->SetPos(position.x + 12, position.y + 8);
	colliderR->SetPos(position.x + 34, position.y + 10);
	colliderD->SetPos(position.x + 12, position.y + 53);
	colliderL->SetPos(position.x + 10, position.y + 10);

	//We update the current animation
	currentAnimationLegs->Update();
	currentAnimationTorso->Update();

	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN) {
		godMode = !godMode;
	}
	if (App->input->keys[SDL_SCANCODE_F6] == Key_State::KEY_DOWN) {
		App->player->position.x = 232;
		App->player->position.y = 190;
	}

	//Reset variables
	lockR = false;
	lockU = false;
	lockD = false;
	lockL = false;
	speed = 1;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate() {

	int x, y;

	if (!destroyed) {

		//Obtenemos el rectangulo actual de la animacion
		SDL_Rect rectLegs = currentAnimationLegs->GetCurrentFrame();
		SDL_Rect rectTorso = currentAnimationTorso->GetCurrentFrame();

		//Mostramos por pantalla el frame de la animacion
		App->render->Blit(texture, position.x, position.y, &rectLegs);
		App->render->Blit(texture, position.x, position.y, &rectTorso);
		
		//Obtenemos position de las diferentes partes de la UI en base al jugador y la camara
		x = (position.x >= 302) ? 203 : (position.x <= 134) ? 34 : position.x - 100;
		y = (position.y >= 1786) ? 1740 : (position.y <= 100) ? 55 : position.y - 45;

		//Mostramos por pantalla la UI
		App->render->Blit(textureHp,x - 10, y, NULL);
		App->render->Blit(textureP1, x - 20, y - 50, NULL);
		App->render->Blit(textureWeapon, x + 10, y + 150, NULL);
	}

	//Mostramos por pantalla el score
	sprintf_s(scoreText, 10, "%7d", score);
	App->fonts->BlitText(30, 5, scoreFont, scoreText);

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {

	if (c1 == collider && destroyed == false && c2->type == Collider::Type::ENEMY && isRolling == false && !godMode)
	{
		//TODO AÑADIR ANIMACION SA EXO PUPA
		if(hp < 0)
		hp -= 10;
	}
	if (c1 == collider && destroyed == false && c2->type == Collider::Type::ENEMY_SHOT && isRolling == false && !godMode)
	{
		//TODO AÑADIR ANIMACION SA EXO PUPA
		if (hp < 0)
		hp -= 10;
	}


	if (c1 == colliderR && destroyed == false && c2->type == Collider::Type::WALL && !godMode) {
		lockR = true;
		isRolling = false;
	}
	if (c1 == colliderU && destroyed == false && c2->type == Collider::Type::WALL && !godMode) {
		lockU = true;
		isRolling = false;
	}
	if (c1 == colliderD && destroyed == false && c2->type == Collider::Type::WALL && !godMode) {
		lockD = true;
		isRolling = false;
	}
	if (c1 == colliderL && destroyed == false && c2->type == Collider::Type::WALL && !godMode) {
		lockL = true;
		isRolling = false;
	}


	if (c1 == collider && destroyed == false && c2->type == Collider::Type::HEAL) {
		hp += 10;
	}
	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}
}