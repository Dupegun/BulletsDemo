#pragma once
#include "SFML/Graphics.hpp"
#include <mutex>

using namespace sf;

class Bullet
{
public:
	Bullet()
	{}
	Bullet(Vector2f pos, Vector2f dir, float initialSpeed, float inLifeTime);
	
	virtual ~Bullet();

	void Initialize(Vector2f pos, Vector2f dir, float initialSpeed, float inLifeTime);

	void Move(float DeltaTime);

	const Vector2f& GetPosition() const;

	bool GetIsActive();
	void SetIsActive(bool newValue);

	float elapsedTime;
	float lifeTime;
private:
	Vector2f	direction;
	Vector2f	position;
	float		speed;

	bool		bIsActive;

	std::mutex activemx;
};

