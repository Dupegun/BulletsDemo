#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include "SFML/Graphics.hpp"

class Bullet;

typedef std::vector<std::shared_ptr<Bullet>> VectorBullets;

class BulletManager
{
	BulletManager();

public:

	~BulletManager();

	void Fire(sf::Vector2f pos, sf::Vector2f dir, float speed, float time, float life_time);

	void Update(float time);

	const VectorBullets& GetBullets();
	
	static BulletManager& GetInstance();

	sf::VertexArray& GetVertices();

private:
	
	void AddBullet(sf::Vector2f pos, sf::Vector2f dir, float speed, float time);

	void AddVertex(const sf::Vector2f& position);
	void RemoveVertex(size_t index);

	VectorBullets bullets;
	sf::VertexArray bulletsVertices;
	std::mutex bulletmx;
	std::mutex verticesmx;

	friend class Bullet;
};