#include "Target.h"
#include "TextureManager.h"


Target::Target()
{
	TextureManager::Instance()->load("../Assets/textures/Ball.png", "circle");

	const auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(300.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0, 50);
	getRigidBody()->isColliding = false;

	setType(TARGET);
}

Target::~Target()
= default;

void Target::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Target::update()
{
	m_move();
	m_checkBounds();
}

void Target::clean()
{
}

void Target::m_move()
{
	float deltaTime = 1.0f / 60.0f;
	glm::vec2 gravity = glm::vec2(0, 9.8f);

	getRigidBody()->velocity += (getRigidBody()->acceleration + gravity) * deltaTime;

	getTransform()->position += getRigidBody()->velocity * deltaTime;
}

void Target::m_move2()
{
	
}

void Target::Reset()
{
	getTransform()->position = glm::vec2(300.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);

}

void Target::m_checkBounds()
{

}

void Target::m_reset()
{
}


