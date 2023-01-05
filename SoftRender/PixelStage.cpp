#include "PixelStage.h"

const float PixelStage::maxDepth = 1.0f;

void PixelStage::SetDepthStencil(int w, int h)
{
	width = w;
	height = h;

	depthStencil.resize(width);
	for (auto& v : depthStencil)
	{
		v.resize(height);
	}
	ClearDepthStencil();
}

bool PixelStage::DepthTest(const Fragment& f)
{
	auto &Depth = depthStencil[f.viewPosition.x][f.viewPosition.y];
	if (f.position.z >= Depth)
	{
		Depth = f.position.z;
	}
	return false;
}

void PixelStage::ClearDepthStencil()
{
	for (auto& vs : depthStencil)
	{
		for (auto& v : vs)
		{
			v = maxDepth;
		}
	}
}

void PixelStage::GenerateFream(const std::vector<Fragment>& fragments)
{
	if (depthStencil.empty())
	{
		return;
	}

	fream.resize(width);
	for (auto& v : fream)
	{
		v.resize(height);
	}

	for (const auto& f : fragments)
	{
		if (DepthTest(f))
		{
			PixelShading(f);
		}
	}
}

void PixelStage::PixelShading(const Fragment &f)
{
}
