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

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// the loop parameter is set to true by default

	// idle animations
	// legs 
	idleAnimUpLegs.PushBack({101, 152, 30, 25});
	idleAnimDownLegs.PushBack({5, 151, 28, 25});
	idleAnimLeftLegs.PushBack({158, 149, 12, 28});
	idleAnimRightLegs.PushBack({62, 149, 12, 28});
	idleAnimDownLeftLegs.PushBack({174, 149, 22, 28});
	idleAnimDownRightLegs.PushBack({36, 149, 22, 28});
	idleAnimUpLeftLegs.PushBack({134, 150, 21, 27});
	idleAnimUpRightLegs.PushBack({77, 150, 21, 27});
	// no need to set speed since this animation only has one frame

	// torso 
	idleAnimUpTorso.PushBack({5, 5, 22, 23});
	idleAnimUpTorso.PushBack({28, 5, 22, 23});
	idleAnimUpTorso.PushBack({51, 5, 22, 23});
	idleAnimDownTorso.PushBack({5, 473, 23, 30});
	idleAnimDownTorso.PushBack({29, 473, 23, 30});
	idleAnimDownTorso.PushBack({53, 473, 23, 30});
	idleAnimLeftTorso.PushBack({5, 513, 18, 32});						// TODO check if this animation shows as intended
	idleAnimLeftTorso.PushBack({24, 513, 18, 32});
	idleAnimLeftTorso.PushBack({43, 513, 18, 32});
	idleAnimRightTorso.PushBack({5, 188, 20, 28});
	idleAnimRightTorso.PushBack({26, 188, 20, 28});
	idleAnimRightTorso.PushBack({47, 188, 20, 28});
	idleAnimDownLeftTorso.PushBack({5, 556, 17, 32});
	idleAnimDownLeftTorso.PushBack({23, 556, 17, 32});
	idleAnimDownLeftTorso.PushBack({41, 556, 17, 32});
	idleAnimDownRightTorso.PushBack({5, 75, 27, 30});
	idleAnimDownRightTorso.PushBack({33, 75, 27, 30});
	idleAnimDownRightTorso.PushBack({61, 75, 27, 30});
	idleAnimUpLeftTorso.PushBack({5, 111, 21, 27});
	idleAnimUpLeftTorso.PushBack({27, 111, 21, 27});
	idleAnimUpLeftTorso.PushBack({49, 111, 21, 27});
	idleAnimUpRightTorso.PushBack({5 ,39, 15, 25});
	idleAnimUpRightTorso.PushBack({21 ,39, 15, 25});
	idleAnimUpRightTorso.PushBack({37 ,39, 15, 25});

	idleAnimUpTorso.speed = animSpeed;
	idleAnimDownTorso.speed = animSpeed;
	idleAnimLeftTorso.speed = animSpeed;
	idleAnimRightTorso.speed = animSpeed;
	idleAnimDownLeftTorso.speed = animSpeed;
	idleAnimDownRightTorso.speed = animSpeed;
	idleAnimUpLeftTorso.speed = animSpeed;
	idleAnimUpRightTorso.speed = animSpeed;

	// running animations
	// legs
	upAnimLegs.PushBack({5, 268, 22, 30});
	upAnimLegs.PushBack({28, 268, 22, 30});
	upAnimLegs.PushBack({51, 268, 22, 30});
	upAnimLegs.PushBack({74, 268, 22, 30});
	upAnimLegs.PushBack({97, 268, 22, 30});
	upAnimLegs.PushBack({120, 268, 22, 30});
	upAnimLegs.PushBack({143, 268, 22, 30});
	upAnimLegs.PushBack({166, 268, 22, 30});
	downAnimLegs.PushBack({5, 227, 22, 30});
	downAnimLegs.PushBack({28, 227, 22, 30});
	downAnimLegs.PushBack({51, 227, 22, 30});
	downAnimLegs.PushBack({74, 227, 22, 30});
	downAnimLegs.PushBack({97, 227, 22, 30});
	downAnimLegs.PushBack({120, 227, 22, 30});
	downAnimLegs.PushBack({143, 227, 22, 30});
	downAnimLegs.PushBack({166, 227, 22, 30});
	leftAnimLegs.PushBack({});
	rightAnimLegs.PushBack({});
	downLeftAnimLegs.PushBack({});
	downRightAnimLegs.PushBack({});
	upLeftAnimLegs.PushBack({});
	upRightAnimLegs.PushBack({});

	upAnimLegs.speed = animSpeed;
	downAnimLegs.speed = animSpeed;
	leftAnimLegs.speed = animSpeed;
	rightAnimLegs.speed = animSpeed;
	downLeftAnimLegs.speed = animSpeed;
	downRightAnimLegs.speed = animSpeed;
	upLeftAnimLegs.speed = animSpeed;
	upRightAnimLegs.speed = animSpeed;

	// roll animations
	rollAnimUp.PushBack({});
	rollAnimDown.PushBack({});
	rollAnimLeft.PushBack({});
	rollAnimRight.PushBack({});
	rollAnimDownLeft.PushBack({});
	rollAnimDownRight.PushBack({});
	rollAnimUpLeft.PushBack({});
	rollAnimUpRight.PushBack({});

	rollAnimUp.speed = animSpeed;
	rollAnimDown.speed = animSpeed;
	rollAnimLeft.speed = animSpeed;
	rollAnimRight.speed = animSpeed;
	rollAnimDownLeft.speed = animSpeed;
	rollAnimDownRight.speed = animSpeed;
	rollAnimUpLeft.speed = animSpeed;
	rollAnimUpRight.speed = animSpeed;

	// shooting animations
	shootAnimUp.PushBack({});
	shootAnimDown.PushBack({});
	shootAnimLeft.PushBack({});
	shootAnimRight.PushBack({});
	shootAnimDownLeft.PushBack({});
	shootAnimDownRight.PushBack({});
	shootAnimUpLeft.PushBack({});
	shootAnimUpRight.PushBack({});

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

	texture = App->textures->Load("Assets/Sprites/Milky_Spritesheet.png");
	currentAnimationLegs = &idleAnimUpLegs;
	currentAnimationTorso = &idleAnimUpTorso;

	textureP1 = App->textures->Load("Assets/Sprites/Player1_Milky.png");
	textureWeapon = App->textures->Load("Assets/Sprites/Weapon_Normal.png");

	laserFx = App->audio->LoadFx("Assets/fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/fx/ExplosionGranada.wav");

	position.x = 220;
	position.y = 1870;
	hp = 100;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);


	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	updateHp();
	if (roll) {
		speed = 3;
		move();
		if ((abs(diferencia.x - position.x) > 50) || (abs(diferencia.y - position.y) > 50) || ((abs(diferencia.x - position.x) == 0) && (abs(diferencia.y - position.y) == 0))) {
			roll = false;
		}
	}else {
		speed = 1;

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
		}if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) {
			hp += 10;
		}if (App->input->keys[SDL_SCANCODE_F5] == Key_State::KEY_DOWN) {
			hp = 0;
		}
		if (App->input->keys[SDL_SCANCODE_B] == Key_State::KEY_DOWN) {
			position.x = 58;
			position.y = 248;
			App->pickUps->SpawnPickUp({ PickUp_Type::HP,position.x-90, position.y });
		}
		move();
		setAnimations();


		diferencia.x = position.x;
		diferencia.y = position.y;

		if (App->input->keys[SDL_SCANCODE_Z] == Key_State::KEY_DOWN) {
			App->particles->laser.setDirection(lastDirection);
			//TODO añadir direccion
			Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x, position.y, lastDirection, Collider::Type::PLAYER_SHOT);
			newParticle->collider->AddListener(this);
			newParticle->granada = true;
			App->audio->PlayFx(laserFx);
		}

		if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
		{
			roll = true;
		}
		
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT)
		{
			delay--;
			if (delay == 0) {
				//App->particles->laser.setDirection(lastDirection);
 				Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x, position.y, lastDirection, Collider::Type::PLAYER_SHOT);
				newParticle->collider->AddListener(this);
  				App->audio->PlayFx(laserFx);

				delay = 10;
			}
		}
	}
	if (currentDirection != 0) {
		lastDirection = currentDirection;
	}

	collider->SetPos(position.x, position.y);

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
	if (godMode)
	{
		hp = 100;
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
		int x, y;
	if (!destroyed)
	{
		SDL_Rect rectLegs = currentAnimationLegs->GetCurrentFrame();
		SDL_Rect rectTorso = currentAnimationTorso->GetCurrentFrame();
		//TODO arreglar lumbago
		App->render->Blit(texture, position.x, position.y, &rectLegs);
		App->render->Blit(texture, position.x+3, position.y-18, &rectTorso);
		
		x = (position.x >= 302) ? 203 : (position.x <= 134) ? 34 : position.x - 100;
		y = (position.y >= 1786) ? 1740 : (position.y <= 100) ? 55 : position.y - 45;
		App->render->Blit(textureHp,x - 10, y, NULL);
		App->render->Blit(textureP1, x - 20, y - 50, NULL);
		App->render->Blit(textureWeapon, x + 10, y + 150, NULL);
	}

	sprintf_s(scoreText, 10, "%7d", score);

	App->fonts->BlitText(30, 5, scoreFont, scoreText);

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false && c2->type == Collider::Type::ENEMY && roll == false)
	{
		//TODO AÑADIR ANIMACION SA EXO PUPA
		if(hp < 0)
		hp -= 10;
	}
	if (c1 == collider && destroyed == false && c2->type == Collider::Type::ENEMY_SHOT && roll == false)
	{
		//TODO AÑADIR ANIMACION SA EXO PUPA
		if (hp < 0)
		hp -= 10;
	}

	if (c1 == collider && destroyed == false && c2->type == Collider::Type::WALL) {

		if (c1->rect.y < c2->rect.y) {
			speed = 0;
			position.y -= 1;
		}
		else if (c1->rect.y + c1->rect.h > c2->rect.y + c2->rect.h) {
			speed = 0;
			position.y += 1;
		}else if (c1->rect.x < c2->rect.x) {
			speed = 0;
			position.x -= 1;
		}
		else if (c1->rect.x + c1->rect.w > c2->rect.x + c2->rect.w ) {
			speed = 0;
			position.x += 1;
		}

	}
	if (c1 == collider && destroyed == false && c2->type == Collider::Type::HEAL) {
		//TODO añadir animacion c muere jugador
		if (hp > 100)
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

float* ModulePlayer::normalize(float normV[]) {
	float norm = 0.0f;
	norm += position.x * position.x;
	norm += position.y * position.y;
	norm = std::sqrt(norm);
	normV[0] = position.x / norm;
	normV[1] = position.y / norm;

	return normV;
}

void ModulePlayer::move() {

	switch (currentDirection)
	{
		case 1: //UR
			position.x += speed;
			position.y -= speed;
			//position.x *= normalize()[0];
			//position.y *= normalize()[1];
		break;
		case 2: //UL
			position.x -= speed;
			position.y -= speed;
			//position.x *= normalize()[0];
			//position.y *= normalize()[1];
		break;
		case 3: //DR
			position.x += speed;
			position.y += speed;
			//position.x *= normalize()[0];
			//position.y *= normalize()[1];
		break;
		case 4: //DL
			position.x -= speed;
			position.y += speed;
			//position.x *= normalize()[0];
			//position.y *= normalize()[1];
		break;
		case 5: //R
			position.x += speed;
		break;
		case 6: //L
			position.x -= speed;
		break;
		case 7: //D
			position.y += speed;
		break;
		case 8: //U
			position.y -= speed;
		break;
	default:
		break;
	}
}