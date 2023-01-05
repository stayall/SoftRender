#include "VertexStage.h"

void VertexStage::Transform(DirectX::FXMMATRIX m)
{
	matrix = m;
	for (auto& v : vertexData)
	{
		DirectX::XMStoreFloat4(&v.position, DirectX::XMVector4Transform(DirectX::XMLoadFloat4(&v.position), m));
		v.position = DirectX::XMFLOAT4{ v.position.x / v.position.w, v.position.y / v.position.w, v.position.z / v.position.w, 1.0f };
	}
}


std::vector<Vertex>& VertexStage::GetVertexData()
{
	return vertexData;
}
