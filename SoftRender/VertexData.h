#pragma once

#include <DirectXMath.h>

struct VertexData
{
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 normal;
};

using Vertex = VertexData;

using Color = DirectX::XMFLOAT4;
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

	operator Vertex() const;
};

using Data = InputData;