#include "InputStage.h"

void InputStage::IASetData(const std::vector<Vertex>& v, const std::vector<unsigned short>& n)
{
	objects.emplace_back(std::move(std::make_pair(v, n)));
}

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

const std::vector<Vertex>& InputStage::GetVertexData(int index) const
{
	return objects[index].first;
}

const std::vector<unsigned short>& InputStage::GetIndexData(int index) const
{
	return objects[index].second;
}

size_t InputStage::GetObjectSize() const
{
	return objects.size();
}
