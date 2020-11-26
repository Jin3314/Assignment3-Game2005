#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"
#include "Renderer.h"
#include "SoundManager.h"
using namespace std;
PlayScene::PlayScene()
{
	PlayScene::start();

}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("Background", 400, 300, 0, 255, true);

	drawDisplayList();
	

}

void PlayScene::update()
{
	updateDisplayList();

	if (SDL_GetTicks() - bulletSpawnTimerStart >= bulletSpawnTimerDuration) {
		SpawnBullet();
	}

	std::vector<Bullet*>& activeBullets = m_pPool->all;
	for (std::vector<Bullet*>::iterator myiter = activeBullets.begin(); myiter != activeBullets.end(); ++myiter)
	{
		Bullet* bullet = *myiter;

		if (m_pPlayer->isColliding(bullet)) 
		{
			
				SoundManager::Instance().allocateChannels(16);
				SoundManager::Instance().load("../Assets/audio/explosion.wav", "Explosion", SOUND_SFX);
				SoundManager::Instance().playSound("Explosion", 0, -1);
				SoundManager::Instance().setSoundVolume(10);

			
		}

		if (bullet->active && bullet->getTransform()->position.y >= 650)
		{
			m_pPool->Despawn(bullet);
			break;
		}
	}

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->moveLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->moveRight();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		m_pPlayer->moveUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		m_pPlayer->moveDown();
	}
	else m_pPlayer->dontMove();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	
	TextureManager::Instance()->load("../Assets/textures/space.png", "Background");
	// Player Sprite

	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(100.0f, 50.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Enemy Sprite
	m_pPool = new BulletPool(10);
	for (std::vector<Bullet*>::iterator myiter = m_pPool->all.begin(); myiter != m_pPool->all.end(); ++myiter)
	{
		Bullet* bullet = *myiter;
		addChild(bullet);

	}
	bulletSpawnTimerStart = SDL_GetTicks();
	// Label
}

void PlayScene::SpawnBullet()
{
	Bullet* bullet = m_pPool->Spawn();
	if (bullet)
	{
	
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, 0);
	}

	bulletSpawnTimerStart = SDL_GetTicks();
}