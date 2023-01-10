#pragma once
#include <vector>

#include <d2d1.h>
#include <Windows.h>
#include <DirectXMath.h>
#include <memory>

#include "Camera.h"
#include "InputStage.h"
#include "VertexStage.h"
#include "RasterizationStage.h"
#include "PixelStage.h"



#pragma comment(lib, "d2d1")

class Graphics
{
	friend class MainWindow;
	using PixelBits = UINT32;
public:
	

	Graphics(HWND hwnd);
	Graphics(const Graphics& rhs) = delete;
	Graphics &operator=(const Graphics& rhs) = delete;
	~Graphics();
	void SetPixel(float x, float y, unsigned char u, unsigned char g, unsigned char b);
	void Clear(COLORREF color = RGB(255, 255, 0));
	DirectX::XMMATRIX GetSreenMatrix() const;
	static DirectX::XMFLOAT4 HomogeneousDivision(const DirectX::XMFLOAT4 &v);
	template<class T>
	void SetIndexData(const T& data);

	void DrawCall(size_t index);
	void SetRenderTarget();
	void Swap();

	//TODO: separate interface implemnet in outside

public :
	
	 void CheckWidthHeight();
	__declspec(deprecated("** this is a deprecated function **")) void StoreWindow();
	__declspec(deprecated("** this is a deprecated function **")) void RestoreWindow();

	void CreateWindowBitmap();
	void SwapBitMapBuffer();

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
	UINT32* pData = nullptr;
	
	InputStage inputs;
	PixelStage ps;
	size_t currentDrawIndex = 0;
};

template<class T>
inline void Graphics::SetIndexData(const T& data)
{
	inputs.IASetData(data.GetVertexData(), data.GetIndex());
	//inputs.IASetVertexData(data.GetVertexData());
	//inputs.IASetIndex(data.GetIndex());
}
