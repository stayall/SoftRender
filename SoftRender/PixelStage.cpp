#include <limits.h>
#include "PixelStage.h"
const float PixelStage::maxDepth = -std::numeric_limits<float>::infinity();

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

int PixelStage::GetViewportWidth() const
{
	return viewPortWidth;
}

int PixelStage::GetViewportHeight() const
{
	return viewPortHeight;
}

bool PixelStage::DepthTest(const Fragment& f)
{
	auto &Depth = depthStencil[f.viewPosition.x][f.viewPosition.y];
	if (f.position.z >= Depth)
	{
		Depth = f.position.z;
		return true;
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
	if (depthStencil.empty() || fream.empty())
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
	fream[f.viewPosition.x][f.viewPosition.y] = f.color;
}

void PixelStage::ClearColor(Color color)
{
	for (auto& w : fream)
	{
		for (auto& h : w)
		{
			h = color;
		}
	}
}

const std::vector<std::vector<Color>>& PixelStage::GetFream() const
{
	return fream;
}
