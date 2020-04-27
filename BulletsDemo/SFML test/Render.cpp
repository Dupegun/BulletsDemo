
#include "Render.h"
#include <thread>
#include <chrono>
#include <fstream>
#include "BulletManager.h"
#include "Bullet.h"
#include <cmath>

namespace Render
{
	bool bIsLinesDestroyable = true;
	VertexArray lines;
	RenderWindow window;

	void GetWallsFromFile()
	{
		std::ifstream infile("../../WallsConfig.txt");
		if (infile.is_open())
		{
			lines.setPrimitiveType(sf::Lines);
			auto flags = infile.flags();
			infile.unsetf(std::ios_base::skipws);
			unsigned line_count = std::count(
				std::istream_iterator<char>(infile),
				std::istream_iterator<char>(),
				'\n');
			infile.setf(flags);
			line_count++;
			lines.resize(line_count * 2);
			infile.close();
			infile.open("../../WallsConfig.txt");
			int CurrentIndex = 0;
			float x1, y1, x2, y2;
			while (infile >> x1 >> y1 >> x2 >> y2)
			{
				lines.append(sf::Vertex(sf::Vector2f(x1, y1)));
				lines.append(sf::Vertex(sf::Vector2f(x2, y2)));
				CurrentIndex++;
			}
		}
	}

	extern void RenderLoop()
	{
		GetWallsFromFile();

		window.create(sf::VideoMode(600, 600), "Bullets demo");
		window.setFramerateLimit(120);
		window.clear();
		window.display();
		
		BulletManager& bulletManager = BulletManager::GetInstance();
		
		auto start = chrono::high_resolution_clock::now();

		while (window.isOpen())
		{
			chrono::duration<float> duration = chrono::high_resolution_clock::now() - start;
			start = chrono::high_resolution_clock::now();
			float deltaTime = duration.count();
			if (deltaTime < 0.01f)
			{
				this_thread::sleep_for(chrono::milliseconds(10));
				deltaTime = 0.01f;
			}

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();

		 
			window.draw(bulletManager.GetVertices());
			window.draw(lines);
			window.display();
			this_thread::sleep_for(chrono::milliseconds(1));
		}

	}

	extern float GetCrossProduct2D(const Vector2f& a, const Vector2f& b)
	{
		return a.x*b.y - b.x*a.y;
	}

	extern float GetDotProduct2D(const Vector2f& a, const Vector2f& b)
	{
		return a.x*b.x + a.y*b.y;
	}

	extern float GetVectorMagnitude(const Vector2f& a)
	{
		return sqrt(a.x*a.x + a.y*a.y);
	}

	extern bool GetIsPointOnLineSegment(const Vector2f& LineStart, const Vector2f& LineEnd, const Vector2f& Point)
	{
		if (Point.x <= std::max(LineStart.x, LineEnd.x) && Point.x >= std::min(LineStart.x, LineEnd.x) &&
			Point.y <= std::max(LineStart.y, LineEnd.y) && Point.y >= std::min(LineStart.y, LineEnd.y))
			return true;

		return false;
	}

	extern int GetVectorsOrientation(const Vector2f& A, const Vector2f& B, const Vector2f& C)
	{
		int val = int((B.y - A.y) * (C.x - B.x) - (B.x - A.x) * (C.y - B.y));

		if (val == 0) return 0;  // collinear 

		return (val > 0) ? 1 : 2; // clock or counterclock wise 
	}

	extern bool GetIsLinesIntersecting(const Vector2f& AStart, const Vector2f& AEnd, const Vector2f& BStart, const Vector2f& BEnd)
	{
		// Find the four orientations needed for general and 
		// special cases 
		int o1 = GetVectorsOrientation(AStart, AEnd, BStart);
		int o2 = GetVectorsOrientation(AStart, AEnd, BEnd);
		int o3 = GetVectorsOrientation(BStart, BEnd, AStart);
		int o4 = GetVectorsOrientation(BStart, BEnd, AEnd);

		// General case 
		if (o1 != o2 && o3 != o4)
			return true;

		// Special Cases 
		// AStart, AEnd and BStart are collinear and BStart lies on segment AStart AEnd
		if (o1 == 0 && GetIsPointOnLineSegment(AStart, BStart, AEnd)) 
			return true;

		// AStart, AEnd and BEnd are collinear and BEnd lies on segment AStart AEnd
		if (o2 == 0 && GetIsPointOnLineSegment(AStart, BEnd, AEnd)) 
			return true;

		// BStart, BEnd and AStart are collinear and AStart lies on segment BStart BEnd 
		if (o3 == 0 && GetIsPointOnLineSegment(BStart, AStart, BEnd))
			return true;

		// BStart, BEnd and AEnd are collinear and AEnd lies on segment BStart BEnd 
		if (o4 == 0 && GetIsPointOnLineSegment(BStart, AEnd, BEnd)) 
			return true;

		return false; // Doesn't fall in any of the above cases 
	}

}
