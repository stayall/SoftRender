#pragma once

#include <DirectXMath.h>

using Color = DirectX::XMFLOAT4;

struct VertexData
{
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 normal;
	Color color;
};

using Vertex = VertexData;

struct FragmentData
{
	DirectX::XMINT2 viewPosition;
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 normal;
	Color color;
	DirectX::XMFLOAT2 uv;
};

using Fragment = FragmentData;

struct InputData
{
	DirectX::XMFLOAT3 position;
	Color color;
	operator Vertex() const;
};

using Data = InputData;