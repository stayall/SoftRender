#pragma once
#include <vector>

#include <DirectXMath.h>

#include "IndexTriangleList.h" 
#include "VertexData.h"


class InputStage
{
public:
	void IASetIndexVertexData(const std::vector<Vertex> &v);
	void IASetIndex(const std::vector<unsigned short> &n);

	std::vector<Vertex>& GetVertexData();
	std::vector<unsigned short>& GetIndexData();
private:
	std::vector<Vertex> vertexes;
	std::vector<unsigned short> indices;
};




