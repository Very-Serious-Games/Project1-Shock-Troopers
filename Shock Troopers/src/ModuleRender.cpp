#include "ModuleRender.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"

#include "SDL/include/SDL_render.h"

ModuleRender::ModuleRender(bool startEnabled) : Module(startEnabled)
{

}

ModuleRender::~ModuleRender()
{

}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;	
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);



	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
Update_Status ModuleRender::PreUpdate()
{
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//Clear rendering target
	SDL_RenderClear(renderer);

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleRender::Update()
{
	int nextCameraY = App->player->position.y - 100;
	int nextCameraX = App->player->position.x - 120;

	if (App->player->IsEnabled()) {

		if (nextCameraY <= camera.y) {
			camera.y = App->player->position.y - 100;
		}
	
		if (camera.y <= 975 && camera.x < 1100) {
			if (nextCameraX > camera.x && leaveZone) {
				camera.y = 975;
				if (nextCameraX > camera.x && !blockRight) {
					camera.x = nextCameraX;
				}
				else if (nextCameraX < camera.x && !blockLeft) {
					camera.x = nextCameraX;
				}
			}
			else if (!isInZone2) {
				if (nextCameraX > camera.x && !blockRight) {
					camera.x = nextCameraX;
				}
				else if (nextCameraX < camera.x && !blockLeft) {
					camera.x = nextCameraX;
				}
			}
		}
		else if (!isInZone2) {
			if (nextCameraX > camera.x && !blockRight) {
				camera.x = nextCameraX;
			}
			else if (nextCameraX < camera.x && !blockLeft) {
				camera.x = nextCameraX;
			}
		}

		if (isInZone) {
			camera.y = nextCameraY;
			if (nextCameraX > camera.x && !blockRight) {
				camera.x = nextCameraX;
			}
			else if (nextCameraX < camera.x && !blockLeft) {
				camera.x = nextCameraX;
			}
			if (camera.x < minX) {
				camera.x = minX;
			}
			else if (camera.x + camera.w > maxX) {
				camera.x = maxX - camera.w;
			}
			if (camera.y < minY) {
				camera.y = minY;
			}
			else if (camera.y + camera.h > maxY) {
				camera.y = maxY - camera.h;
			}
		}
	} 

	if (camera.x < 0) camera.x = 0;

	if (camera.x + camera.w > 1748) camera.x = 1748 - camera.w;

	if (camera.y < 0) camera.y = 0;

	if (camera.y + camera.h > 2999) camera.y = 2999 - camera.h;


	if (App->input->keys[SDL_SCANCODE_M] == KEY_DOWN) leaveZone = !leaveZone;

	blockLeft = false;
	blockRight = false;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleRender::PostUpdate()
{
	//Update the screen
	SDL_RenderPresent(renderer);

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy the rendering context
	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	return true;
}

void ModuleRender::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == stopCameraCollider && c2->type == Collider::Type::STOP_CAM_ZONE) {

		if (c1->rect.y < c2->rect.y + c2->rect.h && !isInZone) {
			camera.y--;
		}

		if (camera.y + camera.h <= c2->rect.y + c2->rect.h || camera.y == c2->rect.y) {
			isInZone = true;
		}

		minX = c2->rect.x;
		minY = c2->rect.y;
		maxX = c2->rect.x + c2->rect.w;
		maxY = c2->rect.y + c2->rect.h;

		if (leaveZone) {
			camera.y = 975;
			c2->pendingToDelete = true;
			leaveZone = false;
			isInZone = !isInZone;
		}
	}

	if (c1 == stopCameraCollider && c2->type == Collider::Type::STOP_CAM_ZONE_3) {

		if (c1->rect.y < c2->rect.y + c2->rect.h && !isInZone) {
			camera.y--;
		}

		if (camera.y + camera.h <= c2->rect.y + c2->rect.h || camera.y == c2->rect.y) {
			isInZone3 = true;
		}

		minX = c2->rect.x;
		minY = c2->rect.y;
		maxX = c2->rect.x + c2->rect.w;
		maxY = c2->rect.y + c2->rect.h;

		if (leaveZone) {
			c2->pendingToDelete = true;
			isInZone = !isInZone;
		}
	}

	if (c1 == stopCameraCollider && c2->type == Collider::Type::STOP_CAM_ZONE_2) {
		isInZone2 = true;
		if (c1->rect.x + c1->rect.w > c2->rect.x && !isInZone) {
			camera.x++;
		}

		if (camera.x >= c2->rect.x || camera.x == c2->rect.x) {
			isInZone = true;
		}

		minX = c2->rect.x;
		minY = c2->rect.y;
		maxX = c2->rect.x + c2->rect.w;
		maxY = c2->rect.y + c2->rect.h;

		if (leaveZone) {
			c2->pendingToDelete = true;
			leaveZone = false;
			isInZone2 = !isInZone2;
			isInZone = !isInZone;
		}

	}	
	if (c1 == cameraRightCollider && c2->type == Collider::Type::CAMERA_LIMIT) {
		blockRight = true;
	}
	if (c1 == cameraLeftCollider && c2->type == Collider::Type::CAMERA_LIMIT) {
		blockLeft = true;
	}
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, bool useCamera)
{
	bool ret = true;

	SDL_Rect dstRect{ x * SCREEN_SIZE, y * SCREEN_SIZE, 0, 0 };

	if (useCamera)
	{
		dstRect = {
		(int)((-camera.x * speed) + x) * SCREEN_SIZE,
		(int)((-camera.y * speed) + y) * SCREEN_SIZE,
		(0,0)};
	}

	if (section != nullptr)
	{
		dstRect.w = section->w;
		dstRect.h = section->h;
	}
	else
	{
		//Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);
	}

	dstRect.w *= SCREEN_SIZE;
	dstRect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &dstRect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed, bool useCamera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect dstRect { rect.x * SCREEN_SIZE, rect.y * SCREEN_SIZE, rect.w * SCREEN_SIZE, rect.h * SCREEN_SIZE };

	if (useCamera) {
		dstRect.x -= ((camera.x * speed) * SCREEN_SIZE);
		dstRect.y -= ((camera.y * speed) * SCREEN_SIZE);
	}

	if (SDL_RenderFillRect(renderer, &dstRect) != 0) {
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}