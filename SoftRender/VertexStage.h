#pragma once
#include <vector>
#include <DirectXMath.h>

#include "VertexData.h"


class VertexStage
{
public:
	VertexStage(std::vector<Vertex> s) : vertexData(std::move(s)) { matrix = DirectX::XMMatrixIdentity(); };
	void Transform(DirectX::FXMMATRIX m);
	std::vector<Vertex>& GetVertexData();
private:
	DirectX::XMMATRIX matrix;
	std::vector<Vertex> vertexData;
};


