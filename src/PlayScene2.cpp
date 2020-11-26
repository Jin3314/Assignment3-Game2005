#include "PlayScene2.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"
#include "Renderer.h"
#include "SoundManager.h"
#include "imgui.h"
#include "imgui_sdl.h"
using namespace std;

PlayScene2::PlayScene2()
{
	PlayScene2::start();

}

PlayScene2::~PlayScene2()
= default;

void PlayScene2::draw()
{
	TextureManager::Instance()->draw("Background", 400, 300, 0, 255, true);

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

}

void PlayScene2::update()
{
	updateDisplayList();


}

void PlayScene2::clean()
{
	removeAllChildren();
}

void PlayScene2::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		
		m_pBrick->turnLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		
		m_pBrick->turnRight();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		m_pBrick->moveForward();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		m_pBrick->moveBack();
	}
	else m_pBrick->dontMove();
	



	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene2::start()
{

	TextureManager::Instance()->load("../Assets/textures/background.png", "Background");
	// Player Sprite

	m_guiTitle = "Play Scene";

	m_pBrick = new Ship();
	addChild(m_pBrick);

	m_pBounce = new Target();
	addChild(m_pBounce);

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
	// Label
	m_pInstructLabel1 = new Label("Press the backtick (`) button to turn on IMGUI", "Consolas");
	m_pInstructLabel1->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	addChild(m_pInstructLabel1);
}

void PlayScene2::GUI_Function() const
{
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Bounce Ball", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	if (ImGui::Button("Reset")) {
		m_pBounce->Reset();
	}

	ImGui::Separator();

	//ImGui::Checkbox("Gravity", m_isGravityEnabled);

	static float velocity[2] = { 0,0 };
	if (ImGui::SliderFloat2("Fall Speed", velocity, 0, 500)) {
		m_pBounce->getRigidBody()->acceleration = glm::vec2(velocity[0], velocity[1]);
	}

	ImGui::End();
	ImGui::EndFrame();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
