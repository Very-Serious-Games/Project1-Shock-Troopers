#include "ModulePlayer.h"
#include <iostream>
using namespace std;
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

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	//Setting up the player animations
	idleAnimUpLegs.PushBack({ 282, 52, 47, 52 }); 
	idleAnimDownLegs.PushBack({ 94, 52, 47, 52 }); 
	idleAnimLeftLegs.PushBack({ 0, 52, 47, 52 });
	idleAnimRightLegs.PushBack({ 188, 52, 47, 52 });
	idleAnimDownLeftLegs.PushBack({ 47, 52, 47, 52 });
	idleAnimDownRightLegs.PushBack({ 141, 52, 47, 52 });
	idleAnimUpLeftLegs.PushBack({ 329, 52, 47, 52 }); 
	idleAnimUpRightLegs.PushBack({ 235, 52, 47, 52 });

	idleAnimUpTorso.PushBack({ 423, 520, 47, 52 });
	idleAnimUpTorso.PushBack({ 470, 520, 47, 52 });
	idleAnimUpTorso.PushBack({ 517, 520, 47, 52 });

	idleAnimDownTorso.PushBack({ 282, 520, 47, 52 });
	idleAnimDownTorso.PushBack({ 329, 520, 47, 52 });
	idleAnimDownTorso.PushBack({ 376, 520, 47, 52 });
	idleAnimLeftTorso.PushBack({ 282, 416, 47, 52 });						
	idleAnimLeftTorso.PushBack({ 329, 416, 47, 52 });
	idleAnimLeftTorso.PushBack({ 376, 416, 47, 52 });

	idleAnimRightTorso.PushBack({ 282, 364, 47, 52 });
	idleAnimRightTorso.PushBack({ 329, 364, 47, 52 });
	idleAnimRightTorso.PushBack({ 376, 364, 47, 52 });

	upAnimLegs.PushBack({ 0, 312, 47, 52 });
	upAnimLegs.PushBack({ 47, 312, 47, 52 });
	upAnimLegs.PushBack({ 94, 312, 47, 52 });
	upAnimLegs.PushBack({ 141, 312, 47, 52 });
	upAnimLegs.PushBack({ 188, 312, 47, 52 });
	upAnimLegs.PushBack({ 235, 312, 47, 52 });
	upAnimLegs.PushBack({ 282, 312, 47, 52 });
	upAnimLegs.PushBack({ 329, 312, 47, 52 });

	downAnimLegs.PushBack({ 376, 0, 47, 52 });
	downAnimLegs.PushBack({ 423, 0, 47, 52 });
	downAnimLegs.PushBack({ 470, 0, 47, 52 });
	downAnimLegs.PushBack({ 517, 0, 47, 52 });
	downAnimLegs.PushBack({ 564, 0, 47, 52 });
	downAnimLegs.PushBack({ 611, 0, 47, 52 });
	downAnimLegs.PushBack({ 658, 0, 47, 52 });
	downAnimLegs.PushBack({ 705, 0, 47, 52 });

	leftAnimLegs.PushBack({ 376, 52, 47, 52 });
	leftAnimLegs.PushBack({ 423, 52, 47, 52 });
	leftAnimLegs.PushBack({ 470, 52, 47, 52 });
	leftAnimLegs.PushBack({ 517, 52, 47, 52 });
	leftAnimLegs.PushBack({ 564, 52, 47, 52 });
	leftAnimLegs.PushBack({ 611, 52, 47, 52 });
	leftAnimLegs.PushBack({ 658, 52, 47, 52 });
	leftAnimLegs.PushBack({ 705, 52, 47, 52 });

	rightAnimLegs.PushBack({ 0, 0, 47, 52 });
	rightAnimLegs.PushBack({ 47, 0, 47, 52 });
	rightAnimLegs.PushBack({ 94, 0, 47, 52 });
	rightAnimLegs.PushBack({ 141, 0, 47, 52 });
	rightAnimLegs.PushBack({ 188, 0, 47, 52 });
	rightAnimLegs.PushBack({ 235, 0, 47, 52 });
	rightAnimLegs.PushBack({ 282, 0, 47, 52 });
	rightAnimLegs.PushBack({ 329, 0, 47, 52 });

	downLeftAnimLegs.PushBack({});
	downRightAnimLegs.PushBack({});
	upLeftAnimLegs.PushBack({});
	upRightAnimLegs.PushBack({});

	rollAnimUp.PushBack({});
	rollAnimDown.PushBack({});
	rollAnimLeft.PushBack({});
	rollAnimRight.PushBack({});
	rollAnimDownLeft.PushBack({});
	rollAnimDownRight.PushBack({});
	rollAnimUpLeft.PushBack({});
	rollAnimUpRight.PushBack({});

	shootAnimUp.PushBack({});
	shootAnimDown.PushBack({});
	shootAnimLeft.PushBack({});
	shootAnimRight.PushBack({});
	shootAnimDownLeft.PushBack({});
	shootAnimDownRight.PushBack({});
	shootAnimUpLeft.PushBack({});
	shootAnimUpRight.PushBack({});

	idleAnimUpLeftTorso.PushBack({});
	idleAnimUpLeftTorso.PushBack({});
	idleAnimUpLeftTorso.PushBack({});
	idleAnimUpRightTorso.PushBack({});
	idleAnimUpRightTorso.PushBack({});
	idleAnimUpRightTorso.PushBack({});

	idleAnimDownLeftTorso.PushBack({});
	idleAnimDownLeftTorso.PushBack({});
	idleAnimDownLeftTorso.PushBack({});
	idleAnimDownRightTorso.PushBack({});
	idleAnimDownRightTorso.PushBack({});
	idleAnimDownRightTorso.PushBack({});


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

	// death animation
	deathAnim.PushBack({});
	deathAnim.speed = animSpeed;
}

ModulePlayer::~ModulePlayer()
{

}

void ModulePlayer::updateHp() {
	//Carga sprite en base a la vida del jugador
	switch (hp) {
	case 100:
		textureHp = App->textures->Load("Assets/Sprites/HpBar_100.png");
		break;
	case 90:
		textureHp = App->textures->Load("Assets/Sprites/HpBar_90.png");
		break;
	case 80:
		textureHp = App->textures->Load("Assets/Sprites/HpBar_80.png");
		break;
	case 70:
		textureHp = App->textures->Load("Assets/Sprites/HpBar_70.png");
		break;
	case 60:
		textureHp = App->textures->Load("Assets/Sprites/HpBar_60.png");
		break;
	case 50:
		textureHp = App->textures->Load("Assets/Sprites/HpBar_50.png");
		break;
	case 40:
		textureHp = App->textures->Load("Assets/Sprites/HpBar_40.png");
		break;
	case 30:
		textureHp = App->textures->Load("Assets/Sprites/HpBar_30.png");
		break;
	case 20:
		textureHp = App->textures->Load("Assets/Sprites/HpBar_20.png");
		break;
	case 10:
		textureHp = App->textures->Load("Assets/Sprites/HpBar_10.png");
		break;
	case 0:
		textureHp = App->textures->Load("Assets/Sprites/HpBar_00.png");
		destroyed = true;
		//TODO  poner esto donde toque
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneMenu, 60);
		break;
	default:
		textureHp = App->textures->Load("Assets/Sprites/HpBar_00.png");
		break;
	}
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	// Animation
	texture = App->textures->Load("Assets/Sprites/Milky/milkySpritesheet.png");
	currentAnimationLegs = &idleAnimUpLegs;
	currentAnimationTorso = &idleAnimUpTorso;

	// Starting sprite
	textureP1 = App->textures->Load("Assets/Sprites/Player1_Milky.png");
	textureWeapon = App->textures->Load("Assets/Sprites/Weapon_Normal.png");

	// Spund effects
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

Update_Status ModulePlayer::Update()
{
	updateHp();

	cout << App->render->camera.x;
	cout << App->render->camera.y;

	if (roll) {

		//If the player is rolling, the speed is increased
		speed = 3;

		//then the player moves
		move();

		//and when the player has moved 50 pixels, the roll ends
		if ((abs(diferencia.x - position.x) > 50) || (abs(diferencia.y - position.y) > 50) || ((abs(diferencia.x - position.x) == 0) && (abs(diferencia.y - position.y) == 0))) {
			roll = false;
		}
	}else {

		//Map controls
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) {
			currentDirection = 1;
		}else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) {
			currentDirection = 2;
		}else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) {
			currentDirection = 3;
		}else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) {
			currentDirection = 4;
		}else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT){
			currentDirection = 5;
		}else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT){
			currentDirection = 6;
		}else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT){
			currentDirection = 7;
		}else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT){
			currentDirection = 8;
		}else {
			currentDirection = 0;
		}



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
			App->pickUps->SpawnPickUp({ PickUp_Type::HP,position.x-90, position.y });
		}
		//Player movement
		move();
		//Player animation update
		setAnimations();

		//Granade
		if (App->input->keys[SDL_SCANCODE_Z] == Key_State::KEY_DOWN) {
			App->particles->playerShot.setDirection(lastDirection);
			//TODO añadir direccion
			Particle* newParticle = App->particles->AddParticle(App->particles->playerShot, position.x, position.y, lastDirection, Collider::Type::PLAYER_SHOT);
			newParticle->collider->AddListener(this);
			newParticle->granada = true;
			App->audio->PlayFx(laserFx);
		}
		//Roll
		if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
		{
			roll = true;
			diferencia.x = position.x;
			diferencia.y = position.y;
		}

		//Player shooting
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT)
		{
			delay--;
			if (delay == 0) {
				//App->particles->laser.setDirection(lastDirection);
 				Particle* newParticle = App->particles->AddParticle(App->particles->playerShot, position.x+5, position.y+20, lastDirection, Collider::Type::PLAYER_SHOT);
				newParticle->collider->AddListener(this);
  				App->audio->PlayFx(laserFx);

				delay = 10;
			}
		}
	}

	//We save the current direction if there is a new one
	if (currentDirection != 0) {
		lastDirection = currentDirection;
	}

	//Collider update
	collider->SetPos(position.x + 12, position.y + 10);
	colliderU->SetPos(position.x + 12, position.y + 8);
	colliderR->SetPos(position.x + 34, position.y + 10);
	colliderD->SetPos(position.x + 12, position.y + 53);
	colliderL->SetPos(position.x + 10, position.y + 10);

	//We update the current animation
	currentAnimationLegs->Update();
	currentAnimationTorso->Update();

	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN)
	{
		godMode = !godMode;
	}
	if (App->input->keys[SDL_SCANCODE_F6] == Key_State::KEY_DOWN)
	{
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

Update_Status ModulePlayer::PostUpdate()
{
		int x, y;
	if (!destroyed)
	{
		//Obtenemos el rectangulo actual de la animacion
		SDL_Rect rectLegs = currentAnimationLegs->GetCurrentFrame();
		SDL_Rect rectTorso = currentAnimationTorso->GetCurrentFrame();
		//TODO arreglar lumbago
		//Mostramos por pantalla el frame de la animacion
		App->render->Blit(texture, position.x+1, position.y+3, &rectLegs);
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

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false && c2->type == Collider::Type::ENEMY && roll == false && !godMode)
	{
		//TODO AÑADIR ANIMACION SA EXO PUPA
		if(hp < 0)
		hp -= 10;
	}
	if (c1 == collider && destroyed == false && c2->type == Collider::Type::ENEMY_SHOT && roll == false && !godMode)
	{
		//TODO AÑADIR ANIMACION SA EXO PUPA
		if (hp < 0)
		hp -= 10;
	}


	if (c1 == colliderR && destroyed == false && c2->type == Collider::Type::WALL && !godMode) {
		lockR = true;
		roll = false;
	}
	if (c1 == colliderU && destroyed == false && c2->type == Collider::Type::WALL && !godMode) {
		lockU = true;
		roll = false;
	}
	if (c1 == colliderD && destroyed == false && c2->type == Collider::Type::WALL && !godMode) {
		lockD = true;
		roll = false;
	}
	if (c1 == colliderL && destroyed == false && c2->type == Collider::Type::WALL && !godMode) {
		lockL = true;
		roll = false;
	}


	if (c1 == collider && destroyed == false && c2->type == Collider::Type::HEAL) {
		hp += 10;
	}
	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}
}

void ModulePlayer::setIdleAnimations() {
	switch (lastDirection)
	{
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

void ModulePlayer::setAnimations()
{
	switch (currentDirection)
	{
	case 1: //UR
		currentAnimationLegs = &upRightAnimLegs;
		currentAnimationTorso = &idleAnimUpRightTorso;
		break;
	case 2: //UL
		currentAnimationLegs = &upLeftAnimLegs;
		currentAnimationTorso = &idleAnimUpLeftTorso;
		break;
	case 3: //DR
		currentAnimationLegs = &downRightAnimLegs;
		currentAnimationTorso = &idleAnimDownRightTorso;
		break;
	case 4: //DL
		currentAnimationLegs = &downLeftAnimLegs;
		currentAnimationTorso = &idleAnimDownLeftTorso;
		break;
	case 5: //R
		currentAnimationLegs = &rightAnimLegs;
		currentAnimationTorso = &idleAnimRightTorso;
		break;
	case 6: //L
		currentAnimationLegs = &leftAnimLegs;
		currentAnimationTorso = &idleAnimLeftTorso;
		break;
	case 7: //D
		currentAnimationLegs = &downAnimLegs;
		currentAnimationTorso = &idleAnimDownTorso;
		break;
	case 8: //U
		currentAnimationLegs = &upAnimLegs;
		currentAnimationTorso = &idleAnimUpTorso;
		break;
	default:
		setIdleAnimations();
		break;
	}
}

void ModulePlayer::move() {


	switch (currentDirection)
	{
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
			if(!lockR) position.x += speed;
			if(!lockD) position.y += speed;
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
}