#include "Collider.h"

Collider::Collider(SDL_Rect rectangle, Type type, Module* listener): rect(rectangle), type(type), listener(listener)
{

}

void Collider::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	// TODO 1:	Return true if there is an overlap
	//			between argument "r" and property "rect"

	return (rect.x < r.x + r.w &&
			rect.x + rect.w > r.x &&
			rect.y < r.y + r.h &&
			rect.h + rect.y > r.y);
}