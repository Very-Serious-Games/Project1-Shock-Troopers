#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
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

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Milky_Spritesheet.png");
	currentAnimationLegs = &idleAnimUpLegs;
	currentAnimationTorso = &idleAnimUpTorso;
	
	// TODO add torso animations
	// currentAnimationTorso = &idleAnimUpTorso;

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 220;
	position.y = 1870;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	int initialX = position.x;
	int initialY = position.y;

	if (roll) {
		position.x += direccion.x * 3;
		position.y += direccion.y * 3;
		if ((abs(diferencia.x - position.x) > 50) || (abs(diferencia.y - position.y) > 50)) {
			roll = false;
		}
	}
	else {

		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			position.x -= speed.x;
			if (currentAnimationLegs != &leftAnimLegs)
			{
				//leftAnimLegs.Reset();
				currentAnimationLegs = &idleAnimLeftLegs;
				currentAnimationTorso = &idleAnimLeftTorso;
			}
		}

		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{
			position.x += speed.x;
			if (currentAnimationLegs != &rightAnimLegs)
			{
				rightAnimLegs.Reset();
				currentAnimationLegs = &idleAnimRightLegs;
				currentAnimationTorso = &idleAnimRightTorso;
			}
		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
		{
			position.y += speed.y;
			if (currentAnimationLegs != &downAnimLegs)
			{
				downAnimLegs.Reset();
				currentAnimationLegs = &idleAnimDownLegs;
				currentAnimationTorso = &idleAnimDownTorso;
			}
		}

		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			position.y -= speed.y;
			if (currentAnimationLegs != &upAnimLegs)
			{
				upAnimLegs.Reset();
				currentAnimationLegs = &idleAnimUpLegs;		// TESTING ANIMATIONS
				currentAnimationTorso = &idleAnimUpTorso;
			}
		}

		if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
		{
			roll = true;
		}

		direccion.x = -(initialX - position.x);
		direccion.y = -(initialY - position.y);

		diferencia.x = position.x;
		diferencia.y = position.y;

		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
		{
			App->particles->laser.speed.x = direccion.x * 5;
			App->particles->laser.speed.y = direccion.y * 5;
			if (App->particles->laser.speed.x == 0 && App->particles->laser.speed.y == 0) {
				App->particles->laser.speed.x = 5;
				App->particles->laser.speed.y = 0;
			}
			Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			newParticle->collider->AddListener(this);
			App->audio->PlayFx(laserFx);
		}

		// If no up/down movement detected, set the current animation back to idle
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE) {
			// TODO revisar esto, si lo descomentas jodes las animaciones
			//currentAnimationLegs = &idleAnimUpLegs;
			//currentAnimationTorso = &idleAnimUpTorso;
		}
	}



	collider->SetPos(position.x, position.y);

	currentAnimationLegs->Update();
	currentAnimationTorso->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rectLegs = currentAnimationLegs->GetCurrentFrame();
		SDL_Rect rectTorso = currentAnimationTorso->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rectLegs);
		App->render->Blit(texture, position.x+3, position.y-18, &rectTorso);
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(58, 248, scoreFont, scoreText);

	App->fonts->BlitText(150, 248, scoreFont, "this is just a font test");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneMenu, 60);

		destroyed = true;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}
}