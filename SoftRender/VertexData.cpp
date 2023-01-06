#include "VertexData.h"

InputData::operator Vertex() const
{
	Vertex v;
	v.position = { position.x, position.y, position.z, 1.0f };
	
	return v;
}