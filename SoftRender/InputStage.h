#pragma once
#include <vector>

#include <DirectXMath.h>

#include "VertexData.h"


class InputStage
{
public:
	void IASetData(const std::vector<Vertex>& v, const std::vector<unsigned short>& n);

	__declspec(deprecated("** this is a deprecated function **")) void IASetVertexData(const std::vector<Vertex> &v);
	__declspec(deprecated("** this is a deprecated function **")) void IASetIndex(const std::vector<unsigned short> &n);
	__declspec(deprecated("** this is a deprecated function **"))std::vector<Vertex>& GetVertexData();
	__declspec(deprecated("** this is a deprecated function **"))std::vector<unsigned short>& GetIndexData();
	
	const std::vector<Vertex>& GetVertexData(int index) const;
	const std::vector<unsigned short>& GetIndexData(int index) const;
	size_t GetObjectSize() const;
private:
	std::vector<Vertex> vertexes;
	std::vector<unsigned short> indices;
	std::vector<std::pair<std::vector<Vertex>, std::vector<unsigned short>>> objects;
};




