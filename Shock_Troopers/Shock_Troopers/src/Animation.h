#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];

private:
	float currentFrame = 0.0f;
	int totalFrames = 0;
	int loopCount = 0;

public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[totalFrames++] = rect;
	}

	void Reset()
	{
		currentFrame = 0;
	}
	
	bool HasFinished()
	{
		return !loop && loopCount > 0;
	}

	void Update()
	{
		currentFrame += speed;
		if (currentFrame >= totalFrames)
		{
			currentFrame = (loop) ? 0.0f : totalFrames - 1;
			++loopCount;
		}
	}

	SDL_Rect& GetCurrentFrame()
	{
		return frames[(int)currentFrame];
	}
};

#endif