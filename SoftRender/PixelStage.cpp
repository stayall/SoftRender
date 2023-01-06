#include "PixelStage.h"

const float PixelStage::maxDepth = 1.0f;

void PixelStage::SetDepthStencil(int w, int h)
{
	depthStencilWidth = w;
	depthStencilHeight = h;

	depthStencil.resize(depthStencilWidth);
	for (auto& v : depthStencil)
	{
		v.resize(depthStencilHeight);
	}
	ClearDepthStencil();
}

void PixelStage::SetViewport(int w, int h)
{
	viewPortWidth = w;
	viewPortHeight = h;

	fream.resize(viewPortWidth);
	for (auto& v : fream)
	{
		v.resize(viewPortHeight);
	}

	ClearColor();
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

void PixelStage::ClearColor(const float color = 0.0f)
{
	for (auto& w : fream)
	{
		for (auto& h : w)
		{
			h = color;
		}
	}
}

const std::vector<std::vector<float>>& PixelStage::GetFream() const
{
	return fream;
}
