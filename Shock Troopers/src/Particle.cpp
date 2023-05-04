#include "Particle.h"

#include "Collider.h"

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed),
frameCount(p.frameCount), lifetime(p.lifetime)
{

}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Particle::Update()
{
	bool ret = true;
	frameCount++;

	// The particle is set to 'alive' when the delay has been reached
	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		anim.Update();

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
				ret = false;
		}
		// Otherwise the particle is destroyed when the animation is finished
		else if (anim.HasFinished())
			ret = false;

		// Update the position in the screen
		if (granada) {
			position.x += speed.x * 2;
			int test = parabole(inicio, speed.x);
			//TODO añadir direccion
			position.y += test;
		}
		else {
			position.x += speed.x;
			position.y += speed.y;
		}


 		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}

	return ret;
}

int Particle::parabole(int x, int direction_x) {
	const float a = 1.0f / 32.0f;
	const int b = 3;
	const int c = 1;
	int y = -a * (x - c) * (x - c) + b;
	if (direction_x == 1) {
		y = -y;
	}
	inicio++;
	return y;
}

void Particle::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

void Particle::setDirection(int direction) {
	switch (direction)
	{
	case 1: //UR
		speed.x = 5;
		speed.y = -5;
		break;
	case 2: //UL
		speed.x = -5;
		speed.y = -5;
		break;
	case 3: //DR
		speed.x = 5;
		speed.y = 5;
		break;
	case 4: //DL
		speed.x = -5;
		speed.y = 5;
		break;
	case 5: //R
		speed.x = 5;
		speed.y = 0;
		break;
	case 6: //L
		speed.x = -5;
		speed.y = 0;
		break;
	case 7: //D
		speed.x = 0;
		speed.y = 5;
		break;
	case 8: //U
		speed.x = 0;
		speed.y = -5;
		break;
	default:

		break;
	}
}