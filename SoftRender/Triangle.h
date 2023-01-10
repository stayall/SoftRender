#pragma once

#include <Windows.h>
#include <DirectXMath.h>
#include "VertexData.h"

//TODO:Big question

class Graphics;

class Triangle
{

public:
	Triangle() = default;
	Triangle(Vertex p1, Vertex p2, Vertex p3);
	~Triangle() = default;
	void DrawCall(Graphics &ghs);
	DirectX::XMFLOAT3 InTriangle(float x, float y);
	bool BackFaceCulling();
private:
	Vertex points[3];
};












