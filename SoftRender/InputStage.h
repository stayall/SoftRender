#pragma once
#include <vector>

#include <DirectXMath.h>

#include "IndexTriangleList.h" 
#include "VertexData.h"

template <class T>
class InputStage
{
public:


	void IASetIndexVertexData(std::vector<T> v);
	void IASetIndex(std::vector<unsigned short> n);

	std::vector<Vertex>& GetInputData() ;
private:
	IndexTriangleList<T> inputData;
	std::vector<Vertex> VertexData;
};


template<class T>
inline void InputStage<T>::IASetIndexVertexData(std::vector<T> v)
{
	inputData.AddVertexes(v);
}

template<class T>
inline void InputStage<T>::IASetIndex(std::vector<unsigned short> n)
{
	inputData.AddIndex(n);
}

template<class T>
inline std::vector<Vertex>& InputStage<T>::GetInputData()
{
	return inputData;
}
