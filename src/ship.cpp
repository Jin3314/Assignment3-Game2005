#include "ship.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"

Ship::Ship() : m_maxSpeed(10.0f)
{
	TextureManager::Instance()->load("../Assets/textures/brick.png","brick");

	auto size = TextureManager::Instance()->getTextureSize("brick");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SHIP);
	
}


Ship::~Ship()
= default;

void Ship::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	TextureManager::Instance()->draw("brick", x, y, 0, 255, true);
}


void Ship::update()
{
	move();
	m_checkBounds();
}

void Ship::clean()
{
}

void Ship::turnRight()
{
	getRigidBody()->velocity = glm::vec2(SPEED, 0.0f);
}

void Ship::turnLeft()
{
	getRigidBody()->velocity = glm::vec2(-SPEED, 0.0f);
}

void Ship::moveForward()
{
	getRigidBody()->velocity = glm::vec2(0.0f, -SPEED);
}

void Ship::moveBack()
{
	getRigidBody()->velocity = glm::vec2(0.0f, SPEED);
}

void Ship::dontMove() {
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
}

void Ship::move()
{
	const float deltaTime = 1.0f / 60.f;

	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;
}

glm::vec2 Ship::getTargetPosition() const
{
	return m_targetPosition;
}

glm::vec2 Ship::getCurrentDirection() const
{
	return m_currentDirection;
}

float Ship::getMaxSpeed() const
{
	return m_maxSpeed;
}

void Ship::setTargetPosition(glm::vec2 newPosition)
{
	m_targetPosition = newPosition;

}

void Ship::setCurrentDirection(glm::vec2 newDirection)
{
	m_currentDirection = newDirection;
}

void Ship::setMaxSpeed(float newSpeed)
{
	m_maxSpeed = newSpeed;
}



void Ship::m_checkBounds()
{

	if (getTransform()->position.x > Config::SCREEN_WIDTH)
	{
		getTransform()->position = glm::vec2(0.0f, getTransform()->position.y);
	}

	if (getTransform()->position.x < 0)
	{
		getTransform()->position = glm::vec2(800.0f, getTransform()->position.y);
	}

	if (getTransform()->position.y > Config::SCREEN_HEIGHT)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 0.0f);
	}

	if (getTransform()->position.y < 0)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 600.0f);
	}

}

void Ship::m_reset()
{
	getRigidBody()->isColliding = false;
	const int halfWidth = getWidth() * 0.5f;
	const auto xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	const auto yComponent = -getHeight();
	getTransform()->position = glm::vec2(xComponent, yComponent);
}

void Ship::m_changeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);

	glm::vec2 size = TextureManager::Instance()->getTextureSize("ship");
}

