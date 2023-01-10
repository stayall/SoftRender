#include <algorithm>

#include "RasterizationStage.h"

RasterizationStage::Triangle::Triangle(const Vertex& p1, const Vertex& p2, const Vertex& p3, const unsigned short in1, const unsigned short in2, const unsigned short in3)
{
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;

	index[0] = in1;
	index[1] = in2;
	index[2] = in3;
}

DirectX::XMFLOAT3 RasterizationStage::Triangle::InTriangle(float x, float y) const
{
	DirectX::XMFLOAT3 P0P1, P0P2, PP0;
	DirectX::XMStoreFloat3(&P0P1, DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[1].position.x, points[1].position.y, 0.0f, 0.0f), DirectX::XMVectorSet(points[0].position.x, points[0].position.y, 0.0f, 0.0f)));
	DirectX::XMStoreFloat3(&P0P2, DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[2].position.x, points[2].position.y, 0.0f, 0.0f), DirectX::XMVectorSet(points[0].position.x, points[0].position.y, 0.0f, 0.0f)));
	DirectX::XMStoreFloat3(&PP0, DirectX::XMVectorSet(points[0].position.x - x, points[0].position.y - y, 0.0f, 0.0f));

	DirectX::XMFLOAT3 cross;
	DirectX::XMStoreFloat3(&cross, DirectX::XMVector3Cross(DirectX::XMVectorSet(P0P1.x, P0P2.x, PP0.x, 0.0f), DirectX::XMVectorSet(P0P1.y, P0P2.y, PP0.y, 0.0f)));
	float b, c;
	b = cross.x / cross.z;
	c = cross.y / cross.z;

	return { 1 - c - b, b, c };
}

bool RasterizationStage::Triangle::BackFaceCulling(DirectX::FXMVECTOR& viewDirection) const
{
	const auto P0P1 = DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[1].position.x, points[1].position.y, 0.0f, 0.0f), DirectX::XMVectorSet(points[0].position.x, points[0].position.y, 0.0f, 0.0f));
	const auto P1P2 = DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[2].position.x, points[2].position.y, 0.0f, 0.0f), DirectX::XMVectorSet(points[1].position.x, points[1].position.y, 0.0f, 0.0f));
	//DirectX::XMStoreFloat3(&P2P0, DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[0].x, points[0].y, 0.0f, 0.0f), DirectX::XMVectorSet(points[2].x, points[2].y, 0.0f, 0.0f)));

	const auto cross = DirectX::XMVector3Cross(P0P1, P1P2);

	float dot;
	DirectX::XMStoreFloat(&dot, DirectX::XMVector3Dot(viewDirection, cross));

	return dot < 0 ? false : true;
}





void RasterizationStage::TriangleSetUp(const std::vector<Vertex>& vertexes, const std::vector<unsigned short>& indices)
{
	size_t indicesNumber = indices.size() / 3;
	const auto lookDirction = DirectX::XMLoadFloat4(&viewDirection);
	for (size_t i = 0; i < indicesNumber; i++)
	{
		Triangle t{
			vertexes[indices[i]],
			vertexes[indices[i + 1]],
			vertexes[indices[i + 2]],
			indices[i], indices[i + 1], indices[i + 2] };

		if (t.BackFaceCulling(lookDirction))
		{
			continue;
		}

		primitives.push_back(std::move(t));
	}

}

void RasterizationStage::TriangleTraversel(const std::vector<Vertex>& vertexes)
{
	for (const auto& t : primitives)
	{
		MakeFragment(t, vertexes);
	}
}

void RasterizationStage::SetViewDirection(DirectX::FXMVECTOR v)
{
	DirectX::XMStoreFloat4(&viewDirection, v);
}

const std::vector<Fragment>& RasterizationStage::GetFragments() const
{
	return fragments;
}

void RasterizationStage::MakeFragment(const Triangle& t, const std::vector<Vertex>& vertexes)
{
	int min_x = std::min(std::min(t.points[0].position.x, t.points[1].position.x), t.points[2].position.x);
	int max_x = std::max(std::max(t.points[0].position.x, t.points[1].position.x), t.points[2].position.x);
	int min_y = std::min(std::min(t.points[0].position.y, t.points[1].position.y), t.points[2].position.y);
	int max_y = std::max(std::max(t.points[0].position.y, t.points[1].position.y), t.points[2].position.y);

	std::vector<float> v;
	for (size_t i = 0; i < 3; i++)
	{
		v.push_back(vertexes[t.index[i]].position.z);
	}

	for (int i = min_x; i < max_x; i++)
	{
		constexpr float a = std::numeric_limits<float>::epsilon();
		for (int j = min_y; j < max_y; j++)
		{
			const auto res = t.InTriangle(i + 0.5f, j + 0.5f);
			if (std::numeric_limits<float>::epsilon() <= res.x && res.y - 1.0f <= std::numeric_limits<float>::epsilon() && 0.0f < res.y && res.y <= 1.0f && 0.0f < res.z && res.z <= 1.0f)
			{

				Fragment f;
				//interplolation
				auto inter = PerspectiveCorrectInterpolate(res, v);
				f.viewPosition = { i, j };
				DirectX::XMStoreFloat4(&f.position,
					DirectX::XMVectorAdd(
						DirectX::XMVectorMultiply(DirectX::XMVectorReplicate(inter.z),
							DirectX::XMLoadFloat4(&t.points[2].position)), DirectX::XMVectorAdd(
								DirectX::XMVectorMultiply(DirectX::XMVectorReplicate(inter.x),
									DirectX::XMLoadFloat4(&t.points[0].position)),
								DirectX::XMVectorMultiply(DirectX::XMVectorReplicate(inter.y),
									DirectX::XMLoadFloat4(&t.points[1].position)))
					)
				);
				DirectX::XMStoreFloat4(&f.position,
					DirectX::XMVectorMultiply(DirectX::XMVectorReplicate(inter.w),
						DirectX::XMLoadFloat4(&f.position)));

				DirectX::XMStoreFloat4(&f.color,
					DirectX::XMVectorAdd(
						DirectX::XMVectorMultiply(DirectX::XMVectorReplicate(inter.z),
							DirectX::XMLoadFloat4(&t.points[2].color)), DirectX::XMVectorAdd(
								DirectX::XMVectorMultiply(DirectX::XMVectorReplicate(inter.x),
									DirectX::XMLoadFloat4(&t.points[0].color)),
								DirectX::XMVectorMultiply(DirectX::XMVectorReplicate(inter.y),
									DirectX::XMLoadFloat4(&t.points[1].color)))
					)
				);

				DirectX::XMStoreFloat4(&f.color,
					DirectX::XMVectorMultiply(DirectX::XMVectorReplicate(inter.w),
						DirectX::XMLoadFloat4(&f.color)));

				fragments.emplace_back(std::move(f));
			}
		}
	}
}

DirectX::XMFLOAT4 RasterizationStage::PerspectiveCorrectInterpolate(const DirectX::XMFLOAT3& bc, const std::vector<float>& zs)
{
	float zt = 1 / ((bc.x) / zs[0] + bc.y / zs[1] + bc.z / zs[2]);

	return DirectX::XMFLOAT4{ bc.x / zs[0], bc.y / zs[1], bc.z / zs[2], zt };
}
