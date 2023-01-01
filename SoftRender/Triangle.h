#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include "Graphics.h"

class Triangle
{

public:
	Triangle(DirectX::XMFLOAT3 p1, DirectX::XMFLOAT3 p2, DirectX::XMFLOAT3 p3);
	void DrawCall(Graphics &ghs);
	DirectX::XMFLOAT3 InTriangle(float x, float y);
private:
	DirectX::XMFLOAT3 points[3];
};

