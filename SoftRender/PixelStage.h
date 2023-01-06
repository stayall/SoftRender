#pragma once
#include <vector>

#include "VertexData.h"


class PixelStage
{
public:
	void SetDepthStencil(int width, int height);
	void SetViewport(int width, int height);
	int GetViewportWidth() const;
	int GetViewportHeight() const;
	bool DepthTest(const Fragment& f);
	void ClearDepthStencil();
	void GenerateFream(const std::vector<Fragment>& fragments);
	void PixelShading(const Fragment &f);
	void ClearColor(const Color = {0.0f, 0.0f, 0.0f, 1.0f});
	const std::vector<std::vector<Color>>& GetFream() const;
private:
	static const float maxDepth;
	float backgroundColor = 0.2f;
	int depthStencilWidth, depthStencilHeight;
	int viewPortWidth, viewPortHeight;
	std::vector<std::vector<float>> depthStencil;
	std::vector<std::vector<Color>> fream;
};

