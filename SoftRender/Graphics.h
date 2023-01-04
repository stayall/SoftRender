#pragma once
#include <vector>

#include <d2d1.h>
#include <Windows.h>
#include <DirectXMath.h>
#include <memory>

#include "Camera.h"
#include "IndexTriangleList.h"
#include "VertexData.h"



#pragma comment(lib, "d2d1")

class Graphics
{
	friend class MainWindow;

public:
	template<class T>
	class Triangle
	{

	public:
		Triangle() = default;
		Triangle(T p1, T p2, T p3);
		~Triangle() = default;
		DirectX::XMFLOAT3 InTriangle(float x, float y);
		bool BackFaceCulling(DirectX::FXMVECTOR &viewDirection);
	private:
		T points[3];
	};

	Graphics(HWND hwnd);
	Graphics(const Graphics& rhs) = delete;
	Graphics &operator=(const Graphics& rhs) = delete;
	~Graphics();
	void SetPixel(float x, float y, unsigned char u, unsigned char g, unsigned char b);
	void Clear(COLORREF color = RGB(255, 255, 0));
	DirectX::XMMATRIX GetSreenMatrix() const;

	void InputDataProcess();
	static DirectX::XMFLOAT4 HomogeneousDivision(const DirectX::XMFLOAT4 &v);

	template<class T>
	void IASetIndexVertexData(std::vector<T> v);
	void IASetIndex(std::vector<unsigned short> n);
public :
	void CheckWidthHeight();
	void StoreWindow();
	void RestoreWindow();
private:
	//anthoer bit
	HRESULT CreateGraphicsResource();
	void DiscardGraphicsResource();
	void OnPaint();
	void Resize();

	
private:
	HWND m_hwnd;
	HBITMAP memoryBitmap = nullptr;
	HDC memoryDC = nullptr	;
	int width = 0, height = 0;
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	Camera camera;

	IndexTriangleList<Vertex> inputData;
	std::vector<Triangle<Vertex>> primitives;
};

template<class T>
inline void Graphics::IASetIndexVertexData(std::vector<T> v)
{
	inputData.AddVertexes(v);
}

template<class T>
inline Graphics::Triangle<T>::Triangle(T p1, T p2, T p3)
{
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;
}

template<class T>
inline DirectX::XMFLOAT3 Graphics::Triangle<T>::InTriangle(float x, float y)
{
	DirectX::XMFLOAT3 P0P1, P0P2, PP0;
	DirectX::XMStoreFloat3(&P0P1, DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[1].position.x, points[1].position.y, 0.0f, 0.0f), DirectX::XMVectorSet(points[0].position.x, points[0].position.y, 0.0f, 0.0f)));
	DirectX::XMStoreFloat3(&P0P2, DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[2].position.x, points[2].position.y, 0.0f, 0.0f), DirectX::XMVectorSet(points[0].position.x, points[0].position.y, 0.0f, 0.0f)));
	DirectX::XMStoreFloat3(&PP0, DirectX::XMVectorSet(points[0].position.x - x, points[0].position.y - y, 0.0f, 0.0f));

	DirectX::XMFLOAT3 cross;
	DirectX::XMStoreFloat3(&cross, DirectX::XMVector3Cross(DirectX::XMVectorSet(P0P1.x, P0P2.x, PP0.x, 0.0f), DirectX::XMVectorSet(P0P1.y, P0P2.y, PP0.y, 0.0f)));
	float a, b, c;
	b = cross.x / cross.z;
	c = cross.y / cross.z;

	return { 1 - c - b, b, c };

}



template<class T>
inline bool Graphics::Triangle<T>::BackFaceCulling(DirectX::FXMVECTOR& viewDirection)
{
	const auto P0P1 = DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[1].position.x, points[1].position.y, 0.0f, 0.0f), DirectX::XMVectorSet(points[0].position.x, points[0].position.y, 0.0f, 0.0f));
	const auto P1P2 = DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[2].position.x, points[2].position.y, 0.0f, 0.0f), DirectX::XMVectorSet(points[1].position.x, points[1].position.y, 0.0f, 0.0f));
	//DirectX::XMStoreFloat3(&P2P0, DirectX::XMVectorSubtract(DirectX::XMVectorSet(points[0].x, points[0].y, 0.0f, 0.0f), DirectX::XMVectorSet(points[2].x, points[2].y, 0.0f, 0.0f)));

	const auto cross = DirectX::XMVector3Cross(P0P1, P1P2);
	//getView
	float dot;
	DirectX::XMStoreFloat(&dot, DirectX::XMVector3Dot(viewDirection, cross));

	return dot < 0 ? false : true;

}
