#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{}

SceneLevel1::~SceneLevel1()
{}

bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	// Load textures and fx
	bgTexture = App->textures->Load("Assets/Sprites/background_mountain.png");
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	// Add colliders
	App->collisions->AddCollider({ 0, 1909, 493, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 0, 1, 1909 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 493-11, 0, 1, 1909 }, Collider::Type::WALL);

	// Add enemies
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 100, 100);
	App->enemies->AddEnemy(Enemy_Type::FLYING_BATTLESHIP, 200, 100);

	App->render->camera.x = 515/2;
	App->render->camera.y = 5058;

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	int newCamX = App->player->position.x * 3 - 400;
	int newCamY = App->player->position.y * 3 - 300;

	if (newCamX < 515 && newCamX > 0) {
		App->render->camera.x = newCamX;
	}
	if (newCamY < 5058 && newCamY > -342) {
		App->render->camera.y = newCamY;
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel1::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->sceneLevel_1->Disable();

	// TODO remove all memory leaks

	return true;
}