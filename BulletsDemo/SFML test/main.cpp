
#include <iostream>
#include <thread>
#include <chrono>

#include "Bullet.h"
#include "BulletManager.h"
#include "Render.h"

using namespace std;

void InputLoop()
{
	BulletManager& bulletManager = BulletManager::GetInstance();
	bool bWasPressed = false;
	while (true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			bWasPressed = true;
		}
		else if(bWasPressed)
		{
			//this_thread::sleep_for(chrono::milliseconds(1000));
			bWasPressed = false;
			//srand(time(NULL));
			sf::Vector2f position(float(rand() % 490 + 10), float(rand() % 490 + 10));
			sf::Vector2f direction(float(rand() % 10 - 5), float(rand() % 10 - 5));
			direction /= sqrt(direction.x*direction.x + direction.y*direction.y);
			bulletManager.Fire(position, direction, 100.f, 0.f, 10.f);
		}
	}		
}

int main()
{
	thread renderThread(Render::RenderLoop);
	renderThread.detach();

	this_thread::sleep_for(chrono::milliseconds(250));

	thread inputThread(InputLoop);
	inputThread.detach();

	BulletManager& bulletManager = BulletManager::GetInstance();
	
	auto start = chrono::high_resolution_clock::now();

	while (!Render::bIsWindowClosed.load())
	{
		chrono::duration<float> duration = chrono::high_resolution_clock::now() - start;
		start = chrono::high_resolution_clock::now();
		float deltaTime = duration.count();
		if (deltaTime < 0.01f)
		{
			this_thread::sleep_for(chrono::milliseconds(10));
			deltaTime = 0.01f;
		}

		bulletManager.Update(deltaTime);
	}

	return 0;
}