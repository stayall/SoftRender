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
	indices.insert(indices.end(), n.begin(), v.end());
}

template<class T>
inline void IndexTriangleList<T>::Transform(DirectX::FXMMATRIX m)
{
	for (auto& v : vertexes)
	{
		v = DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&v.position), m);
	}
}
