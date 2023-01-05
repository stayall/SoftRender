#pragma once
#include <vector>

#include "VertexData.h"


class PixelStage
{
public:
	void SetDepthStencil(int width, int height);
	bool DepthTest(const Fragment& f);
	void ClearDepthStencil();
	void GenerateFream(const std::vector<Fragment>& fragments);
	void PixelShading(const Fragment &f);
private:
	static const float maxDepth;
	int width, height;
	std::vector<std::vector<float>> depthStencil;
	std::vector<std::vector<float>> fream;
};

