#include "InputStage.h"

void InputStage::IASetVertexData(const std::vector<Vertex> &v)
{
	vertexes.insert(vertexes.end(), v.begin(), v.end());
}


void InputStage::IASetIndex(const std::vector<unsigned short> &n)
{
	indices.insert(indices.end(), n.begin(), n.end());
}

std::vector<Vertex>& InputStage::GetVertexData()
{
	return vertexes;
}

std::vector<unsigned short>& InputStage::GetIndexData()
{
	return indices;
}
