#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	Vector2f m_Position;
	
	Sprite m_Sprite;
	Texture m_Texture;

	Vector2f m_Resolution;
	IntRect m_Arena;
	int m_TileSize;

	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	int m_Health;
	int m_MaxHealth;

	Time m_LastHit;

	float m_Speed;

public:
	Player();

	void Spawn(IntRect arena, Vector2f resolution, int tileSize);

	void ResetPlayerStats();

	bool Hit(Time timeHit);

	Time GetLastHitTime();

	FloatRect GetPosition();

	Vector2f GetCentre();

	float GetRotation();

	Sprite GetSprite();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void StopLeft();
	void StopRight();
	void StopUp();
	void StopDown();

	void Update(float elapsedTime, Vector2i mousePosition);

	void UpgradeSpeed();

	void UpgradeHealth();

	void IncreasedHealthLevel(int amount);

	int GetHealth();
};

#endif PLAYER_H

