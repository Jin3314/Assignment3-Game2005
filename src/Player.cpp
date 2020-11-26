#include "Player.h"
#include "TextureManager.h"
using namespace std;
Player::Player()
{
	TextureManager::Instance()->load("../Assets/textures/spaceship.png", "plane");

	auto size = TextureManager::Instance()->getTextureSize("plane");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("plane", x, y, 0, 255, true);
}

void Player::update()
{
	const float deltaTime = 1.0f / 60.f;

	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;
}

void Player::clean()
{

}

void Player::moveLeft() {
	getRigidBody()->velocity = glm::vec2(-SPEED, 0.0f);
}

void Player::moveRight() {
	getRigidBody()->velocity = glm::vec2(SPEED, 0.0f);
}

void Player::moveUp() {
	getRigidBody()->velocity = glm::vec2(0.0f, -SPEED);
}

void Player::moveDown() {
	getRigidBody()->velocity = glm::vec2(0.0f, SPEED);
}

void Player::dontMove() {
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
}

float Player::checkDistance(GameObject * pGameObject) {


	float Distance;

	float First = pGameObject->getTransform()->position.x - getTransform()->position.x;
	float Second = pGameObject->getTransform()->position.y - getTransform()->position.y;

	Distance = sqrt(First * First + Second * Second);

	if (Distance <= First + Second)
	{
		return Distance;
		collision = false;

	}
	else cout << "collision!" << endl;
	collision = true;
}


bool Player::isColliding(GameObject* pOther) {
	// Works for square sprites only
	float myRadius = getWidth() * 0.5f;
	float otherRadius = pOther->getWidth() * 0.5f;

	return (getDistance(pOther) <= myRadius + otherRadius);
}

float Player::getDistance(GameObject* pOther) {
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}