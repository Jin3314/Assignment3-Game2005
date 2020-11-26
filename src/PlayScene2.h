#pragma once
#ifndef __PLAY_SCENE2__
#define __PLAY_SCENE2__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Enemy.h"
#include "BulletPool.h"
#include "Target.h"
#include "ship.h"

class PlayScene2 : public Scene
{
public:
	PlayScene2();
	~PlayScene2();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	void GUI_Function() const;
	std::string m_guiTitle;

	glm::vec2 m_mousePosition;
	Target* m_pBounce;
	Plane* m_pPlaneSprite;
	Player* m_pPlayer;
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructLabel1;
	Ship* m_pBrick;
	
};

#endif /* defined (__PLAY_SCENE2__) */