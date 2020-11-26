#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "Sprite.h"
#include "Label.h"

class Player final : public Sprite
{
public:
	Player();
	~Player();
	bool collision = false;

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void dontMove();
	float checkDistance(GameObject* pGameObject);

	bool isColliding(GameObject*);
	float getDistance(GameObject*);

private:
	const float SPEED = 150.0f;
};

#endif /* defined (__PLAYER__) */