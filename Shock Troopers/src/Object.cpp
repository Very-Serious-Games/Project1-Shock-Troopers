#include "Object.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Object::Object(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Object::~Object()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Object::GetCollider() const
{
	return collider;
}

void Object::Update()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Object::Draw()
{
	App->render->Blit(texture, position.x, position.y, NULL);
}

void Object::OnCollision(Collider* collider)
{
	SetToDelete();
}

void Object::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}