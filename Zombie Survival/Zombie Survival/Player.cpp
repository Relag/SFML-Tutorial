#include "Player.h"

Player::Player() {
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	m_Texture.loadFromFile("graphics/player.png");
	m_Sprite.setTexture(m_Texture);

	m_Sprite.setOrigin(25, 25);
}

void Player::Spawn(IntRect arena, Vector2f resolution, int tileSize) {
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 2;

	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	m_TileSize = tileSize;

	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Player::ResetPlayerStats() {
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

Time Player::GetLastHitTime() {
	return m_LastHit;
}

bool Player::Hit(Time timeHit) {
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200) {
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else {
		return false;
	}
}

FloatRect Player::GetPosition(){
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::GetCentre() {
	return m_Position;
}

float Player::GetRotation() {
	return m_Sprite.getRotation();
}

Sprite Player::GetSprite() {
	return m_Sprite;
}

int Player::GetHealth() {
	return m_Health;
}

void Player::MoveLeft() {
	m_LeftPressed = true;
}

void Player::MoveRight() {
	m_RightPressed = true;
}

void Player::MoveUp() {
	m_UpPressed = true;
}

void Player::MoveDown() {
	m_DownPressed = true;
}

void Player::StopLeft() {
	m_LeftPressed = false;
}

void Player::StopRight() {
	m_RightPressed = false;
}

void Player::StopUp() {
	m_UpPressed = false;
}

void Player::StopDown() {
	m_DownPressed = false;
}

void Player::Update(float elapsedTime, Vector2i mousePosition) {
	if (m_UpPressed) {
		m_Position.y -= m_Speed * elapsedTime;
	}
	if (m_DownPressed) {
		m_Position.y += m_Speed * elapsedTime;
	}
	if (m_RightPressed) {
		m_Position.x += m_Speed * elapsedTime;
	}
	if (m_LeftPressed) {
		m_Position.x -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);

	if (m_Position.x > m_Arena.width - m_TileSize) {
		m_Position.x = m_Arena.width - m_TileSize;
	}
	if (m_Position.x < m_Arena.left + m_TileSize) {
		m_Position.x = m_Arena.left + m_TileSize;
	}
	if (m_Position.y > m_Arena.height - m_TileSize) {
		m_Position.y = m_Arena.height - m_TileSize;
	}
	if (m_Position.y < m_Arena.top + m_TileSize) {
		m_Position.y = m_Arena.top + m_TileSize;
	}

	//Calculate the angle the player is facing
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2,
		mousePosition.x - m_Resolution.x / 2) * 180) / 3.141;

	m_Sprite.setRotation(angle);
}

void Player::UpgradeSpeed() {
	m_Speed += (START_SPEED * .2);
}

void Player::UpgradeHealth() {
	m_MaxHealth += (START_HEALTH * .2);
}

void Player::IncreasedHealthLevel(int amount) {
	m_Health += amount;

	if (m_Health > m_MaxHealth) {
		m_Health = m_MaxHealth;
	}
}