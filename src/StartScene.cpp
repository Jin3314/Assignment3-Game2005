#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("START SCENE", "Consolas", 80, blue, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press first button for Scene1", "Consolas", 40, blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel2 = new Label("Press second button for Scene2", "Consolas", 40, blue, glm::vec2(400.0f, 170.0f));
	m_pInstructionsLabel2->setParent(this);
	addChild(m_pInstructionsLabel2);

	const SDL_Color skyblue = { 0, 255, 255, 0 };
	m_pinfoLabel1 = new Label("Yeongjin Lim 101256371", "Consolas", 30, skyblue, glm::vec2(400.0f, 230.0f));
	m_pinfoLabel1->setParent(this);
	addChild(m_pinfoLabel1);

	m_pinfoLabel2 = new Label("Uzay Sahiner 101264923", "Consolas", 30, skyblue, glm::vec2(400.0f, 260.0f));
	m_pinfoLabel2->setParent(this);
	addChild(m_pinfoLabel2); 

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	m_pStartButton2 = new Button();
	m_pStartButton2->getTransform()->position = glm::vec2(400.0f, 480.0f);

	m_pStartButton2->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton2->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE2);
	});

	m_pStartButton2->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton2->setAlpha(128);
	});

	m_pStartButton2->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton2->setAlpha(255);
	});
	addChild(m_pStartButton2);
	
}

