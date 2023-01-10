#pragma once
#include <vector>

#include <DirectXMath.h>

#include "IndexTriangleList.h"
#include "VertexData.h"



class RasterizationStage
{

public:
	void TriangleSetUp(const std::vector<Vertex>& vertexes, const std::vector<unsigned short> &indices);
	void TriangleTraversel(const std::vector<Vertex>& vertexes);
	void SetViewDirection(DirectX::FXMVECTOR v);
	const std::vector<Fragment>& GetFragments() const;
private:
	class Triangle
	{
	public:
		Triangle() = default;
		Triangle(const Vertex& p1, const Vertex& p2, const Vertex& p3, const unsigned short in1, const unsigned short in2, const unsigned short in3);
		~Triangle() = default;
		DirectX::XMFLOAT3 InTriangle(float x, float y) const;
		bool BackFaceCulling(DirectX::FXMVECTOR& viewDirection) const;
	
	public:
		Vertex points[3];
		unsigned short index[3];
	};

	void MakeFragment(const Triangle& t, const std::vector<Vertex>& vertexes);
	DirectX::XMFLOAT4 PerspectiveCorrectInterpolate(const DirectX::XMFLOAT3& bc, const std::vector<float>& vertexes);
private:
	//acquiesce negtive z-aixs
	DirectX::XMFLOAT4 viewDirection = { 0.0f, 0.0f, -1.0f, 0.0f };
	std::vector<Triangle> primitives;
	std::vector<Fragment> fragments;
};