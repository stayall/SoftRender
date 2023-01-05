#pragma once
#include <vector>

#include <DirectXMath.h>

#include "IndexTriangleList.h"
#include "VertexData.h"



class RasterizationStage
{

public:
	void TriangleSetUp(const std::vector<Vertex>& vertexes, const std::vector<unsigned short> &indices);
	void TriangleTraversel();
	void SetViewDirection(DirectX::FXMVECTOR v);
	const std::vector<Fragment>& GetFragments() const;
private:
	class Triangle
	{
	public:
		Triangle() = default;
		Triangle(Vertex p1, Vertex p2, Vertex p3);
		~Triangle() = default;
		DirectX::XMFLOAT3 InTriangle(float x, float y) const;
		bool BackFaceCulling(DirectX::FXMVECTOR& viewDirection) const;
	
	public:
		Vertex points[3];
	};

	void MakeFragment(const Triangle& t);

private:
	//acquiesce negtive z-aixs
	DirectX::XMFLOAT4 viewDirection = { 0.0f, 0.0f, -1.0f, 0.0f };
	std::vector<Triangle> primitives;
	std::vector<Fragment> fragments;
};