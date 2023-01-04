#pragma once
#include <vector>
#include <cassert>

#include <DirectXMath.h>

template<class T>
class IndexTriangleList
{
	friend class Graphics;
private:
	IndexTriangleList() = default;
	~IndexTriangleList() = default;

	void AddVertexes(const std::vector<T>& v);
	void AddIndex(const std::vector<unsigned short>& n);
	void Transform(DirectX::FXMMATRIX m);
	void HomogeneousTransform(DirectX::FXMMATRIX m);

private:
	std::vector<T> vertexes;
	std::vector<unsigned short> indices;
};



template<class T>
inline void IndexTriangleList<T>::AddVertexes(const std::vector<T>& v)
{
	assert(v.size() >= 3);
	vertexes.insert(vertexes.end(), v.begin(), v.end());
}

template<class T>
inline void IndexTriangleList<T>::AddIndex(const std::vector<unsigned short>& n)
{
	assert(n.size() % 3 == 0);
	indices.insert(indices.end(), n.begin(), n.end());
}

template<class T>
inline void IndexTriangleList<T>::Transform(DirectX::FXMMATRIX m)
{
	for (auto& v : vertexes)
	{
		DirectX::XMStoreFloat3(&v.position, DirectX::XMVector4Transform(DirectX::XMLoadFloat3(&v.position), m));
	}
}

template<class T>
inline void IndexTriangleList<T>::HomogeneousTransform(DirectX::FXMMATRIX m)
{
	std::vector<DirectX::XMFLOAT4> position;
	for (auto& v : vertexes)
	{
		DirectX::XMFLOAT4 pos;
		pos = { v.position.x, v.position.y, v.position.z, 1.0f };
		DirectX::XMStoreFloat4(&pos, DirectX::XMVector4Transform(DirectX::XMLoadFloat4(&pos), m));
		v.position = DirectX::XMFLOAT3{ pos.x / pos.w, pos.y / pos.w, pos.z / pos.w};
		position.emplace_back(std::move(pos));
		
	}
}
