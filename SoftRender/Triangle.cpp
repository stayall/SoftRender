#include "Triangle.h"
#include <algorithm>
#include "Graphics.h"

inline Triangle::Triangle(Vertex p1, Vertex p2, Vertex p3)
{
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;
}

inline void Triangle::DrawCall(Graphics& ghs)
{

	size_t min_x = min(min(points[0].position.x, points[1].position.x), points[2].position.x);
	size_t max_x = max(max(points[0].position.x, points[1].position.x), points[2].position.x);
	size_t min_y = min(min(points[0].position.y, points[1].position.y), points[2].position.y);
	size_t max_y = max(max(points[0].position.y, points[1].position.y), points[2].position.y);
	for (size_t i = min_x; i < max_x; i++)
	{
		constexpr float a = std::numeric_limits<float>::epsilon();
		for (size_t j = min_y; j < max_y; j++)
		{
			const auto res = InTriangle(i + 0.5f, j + 0.5f);
			if (std::numeric_limits<float>::epsilon() <= res.x && res.y - 1.0f <= std::numeric_limits<float>::epsilon() && 0.0f < res.y && res.y <= 1.0f && 0.0f < res.z && res.z <= 1.0f)
			{
				ghs.SetPixel(i, j, 0, 0, 0);
			}
		}
	}

}

DirectX::XMFLOAT3 Triangle::InTriangle(float x, float y)
{
	DirectX::XMFLOAT3 P0P1, P0P2, PP0;
	DirectX::XMStoreFloat3(&P0P1, DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[1].position.x, points[1].position.y, 0.0f, 0.0f), DirectX::XMVectorSet(points[0].position.x, points[0].position.y, 0.0f, 0.0f)));
	DirectX::XMStoreFloat3(&P0P2, DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[2].position.x, points[2].position.y, 0.0f, 0.0f), DirectX::XMVectorSet(points[0].position.x, points[0].position.y, 0.0f, 0.0f)));
	DirectX::XMStoreFloat3(&PP0, DirectX::XMVectorSet(points[0].position.x - x, points[0].position.y - y, 0.0f, 0.0f));

	DirectX::XMFLOAT3 cross;
	DirectX::XMStoreFloat3(&cross, DirectX::XMVector3Cross(DirectX::XMVectorSet(P0P1.x, P0P2.x, PP0.x, 0.0f), DirectX::XMVectorSet(P0P1.y, P0P2.y, PP0.y, 0.0f)));
	float a, b, c;
	b = cross.x / cross.z;
	c = cross.y / cross.z;

	return { 1 - c - b, b, c };

}


bool Triangle::BackFaceCulling()
{

	const auto P0P1 = DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[1].position.x, points[1].position.y, 0.0f, 0.0f), DirectX::XMVectorSet(points[0].position.x, points[0].position.y, 0.0f, 0.0f));
	const auto P1P2 = DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[2].position.x, points[2].position.y, 0.0f, 0.0f), DirectX::XMVectorSet(points[1].position.x, points[1].position.y, 0.0f, 0.0f));
	//DirectX::XMStoreFloat3(&P2P0, DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[0].x, points[0].y, 0.0f, 0.0f), DirectX::XMVectorSet(points[2].x, points[2].y, 0.0f, 0.0f)));

	const auto cross = DirectX::XMVector3Cross(P0P1, P1P2);
	//getView
	float dot;
	DirectX::XMStoreFloat(&dot, DirectX::XMVector3Dot(DirectX::XMVECTOR{ 0.0f, 0.0f, -1.0f }, cross));

	return dot > 0 ? false : true;


}





