#include "Bullet.h"
#include "Render.h"
#include "BulletManager.h"
#include <iostream>

Bullet::Bullet(Vector2f pos, Vector2f dir, float initialSpeed, float inLifeTime)
{
	Initialize(pos, dir, initialSpeed, inLifeTime);
}

Bullet::~Bullet()
{

} 

void Bullet::Initialize(Vector2f pos, Vector2f dir, float initialSpeed, float inLifeTime)
{
	elapsedTime = 0.f;
	position = pos;
	direction = dir;
	speed = initialSpeed;
	lifeTime = inLifeTime;

	SetIsActive(true);
}

void Bullet::Move(float DeltaTime)
{
	Vector2f newPosition = position + direction * speed * DeltaTime;

	bool bWasHit = false;

	for (size_t i = 0; i < Render::lines.getVertexCount(); i += 2)
	{
		Vector2f& A = Render::lines[i].position;
		Vector2f& B = Render::lines[i+1].position;

		if(A==B) continue;

		bool intersectingRes = Render::GetIsLinesIntersecting(A, B, position, newPosition);
		if (intersectingRes)
		{
			bWasHit = true;
			Vector2f LineNormal(A.y - B.y, B.x - A.x);
			LineNormal /= Render::GetVectorMagnitude(LineNormal);
			direction = direction - LineNormal * 2.f * Render::GetDotProduct2D(direction, LineNormal);
			float collisionFixMult = 1;
			newPosition = position + direction * speed * DeltaTime * collisionFixMult;

			if (Render::bIsLinesDestroyable)
			{
				Render::lines[i].color = sf::Color::Transparent;
				Render::lines[i] = Render::lines[i + 1];
			}

			break;
		}

		///Calculating dot collision with line segment
		/*float CrossProd2D = Render::GetCrossProduct2D(A-B, A-newPosition);
		if (abs(CrossProd2D) < 800)
		{
			float ADotProd = Render::GetDotProduct2D(newPosition - A, B - A);
			if (ADotProd > 0)
			{
				float BDotProd = Render::GetDotProduct2D(B-A, B-A);
				if (ADotProd < BDotProd)
				{
					bWasHit = true;
					Vector2f LineNormal(A.y - B.y, B.x - A.x);
					LineNormal /= Render::GetVectorMagnitude(LineNormal);
					direction = direction - LineNormal * 2.f * Render::GetDotProduct2D(direction, LineNormal);
					newPosition = position + direction * speed * DeltaTime;
					break;
				}
			}
		}*/
	}


	position = newPosition;
}

const sf::Vector2f& Bullet::GetPosition() const
{
	return position;
}

bool Bullet::GetIsActive()
{
	std::lock_guard<std::mutex> lock(activemx);
	return bIsActive;
}

void Bullet::SetIsActive(bool newValue)
{
	std::lock_guard<std::mutex> lock(activemx);
	bIsActive = newValue;
}
