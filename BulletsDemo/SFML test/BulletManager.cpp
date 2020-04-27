#include "BulletManager.h"
#include "Bullet.h"
#include <chrono>
#include <iostream>
#include <algorithm>

BulletManager::BulletManager()
{
	bulletsVertices.setPrimitiveType(Points);
}

BulletManager::~BulletManager()
{
}

void BulletManager::Fire(sf::Vector2f pos, sf::Vector2f dir, float speed, float time, float life_time)
{
	if (time > 0)
	{
		std::thread([pos, dir, speed, time, life_time, this] 
		{
			std::this_thread::sleep_for(std::chrono::seconds((long long)time));
			AddBullet(pos, dir, speed, life_time);

		}).detach();
	}
	else
	{
		AddBullet(pos, dir, speed, life_time);
	}
}

void BulletManager::AddBullet(sf::Vector2f pos, sf::Vector2f dir, float speed, float time)
{
	auto It = std::find_if_not(bullets.begin(), bullets.end(), [](auto value) { return value->GetIsActive(); });
	if (It != bullets.end())
	{
		(*It)->Initialize(pos, dir, speed, time);
	}
	else
	{
		std::unique_lock<std::mutex> lock(bulletmx);
		bullets.push_back(std::shared_ptr<Bullet>(new Bullet(pos, dir, speed, time)));
		lock.unlock();

		AddVertex(pos);
	}
}

void BulletManager::Update(float time)
{
	for (size_t i = 0; i < GetBullets().size(); i++)
	{
		auto bullet = GetBullets()[i];

		auto& vertex = GetVertices()[i];

		if (bullet && bullet->GetIsActive())
		{
			bullet->elapsedTime += time;
			if (bullet->elapsedTime < bullet->lifeTime)
			{
				bullet->Move(time);
				vertex.position = bullet->GetPosition();
				vertex.color = sf::Color::Red;
				
				continue;
			}
			else
			{
				bullet->SetIsActive(false);
			}
		}
		
		vertex.color = sf::Color::Transparent;
	}
}

const VectorBullets& BulletManager::GetBullets()
{
	std::lock_guard<std::mutex> lock(bulletmx);
	return bullets;
}

BulletManager& BulletManager::GetInstance()
{
	static BulletManager instance;
	return instance;
}

sf::VertexArray& BulletManager::GetVertices()
{
	std::lock_guard<std::mutex> lock(verticesmx);
	return bulletsVertices;
}

void BulletManager::AddVertex(const sf::Vector2f& position)
{
	std::lock_guard<std::mutex> lock(verticesmx);
	sf::Vertex newVertex(position);
	newVertex.color = sf::Color::Red;
	bulletsVertices.append(newVertex);
}
