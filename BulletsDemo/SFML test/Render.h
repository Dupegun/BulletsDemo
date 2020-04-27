#pragma once
#include "SFML/Graphics.hpp"

namespace Render
{
	using namespace sf;
	using namespace std;

	extern bool bIsLinesDestroyable;
	extern VertexArray lines;

	extern void GetWallsFromFile();

	extern void RenderLoop();

	extern float GetCrossProduct2D(const Vector2f& a, const Vector2f& b);
	
	extern float GetDotProduct2D(const Vector2f& a, const Vector2f& b);

	extern float GetVectorMagnitude(const Vector2f& a);

	extern bool GetIsPointOnLineSegment(const Vector2f& LineStart, const Vector2f& LineEnd, const Vector2f& Point);

	// 0 --> collinear 
	// 1 --> Clockwise 
	// 2 --> Counterclockwise 
	extern int GetVectorsOrientation(const Vector2f& A, const Vector2f& B, const Vector2f& C);

	extern bool GetIsLinesIntersecting(const Vector2f& AStart, const Vector2f& AEnd, const Vector2f& BStart, const Vector2f& BEnd);
}