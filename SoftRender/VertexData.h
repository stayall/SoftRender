#pragma once

#include <DirectXMath.h>

struct VertexData
{
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 normal;
};

using Vertex = VertexData;

struct FragmentData
{
	DirectX::XMINT2 viewPosition;
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 normal;
	DirectX::XMFLOAT3 color;
	DirectX::XMFLOAT2 uv;
};

using Fragment = FragmentData;
