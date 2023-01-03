#pragma once
#include <vector>

#include <d2d1.h>
#include <Windows.h>
#include <DirectXMath.h>

#include "Camera.h"
#include "IndexTriangleList.h"
#include "VertexData.h"

#pragma comment(lib, "d2d1")

class Graphics
{
	friend class MainWindow;
public:
	Graphics(HWND hwnd);
	Graphics(const Graphics& rhs) = delete;
	Graphics &operator=(const Graphics& rhs) = delete;
	void SetPixel(float x, float y, unsigned char u, unsigned char g, unsigned char b);
	void Clear(COLORREF color = RGB(255, 255, 0));
	DirectX::XMMATRIX GetSreenMatrix() const;

	template<class T>
	void IASetIndexVertexData(std::vector<T> v);
	void IASetIndex(std::vector<unsigned short> n);
private:
	void CheckWidthHeight();
	void StoreWindow();
	void RestoreWindow();
private:
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
};

template<class T>
inline void Graphics::IASetIndexVertexData(std::vector<T> v)
{
	inputData.AddVertexes(v);
}
