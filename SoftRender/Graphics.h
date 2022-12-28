#pragma once
#include <d2d1.h>
#include <Windows.h>

#pragma comment(lib, "d2d1")

class Graphics
{
	friend class MainWindow;
public:
	Graphics(HWND hwnd);
	Graphics(const Graphics& rhs) = delete;
	Graphics &operator=(const Graphics& rhs) = delete;

private:
	HRESULT CreateGraphicsResource();
	void DiscardGraphicsResource();
	void OnPaint();
	void Resize();

private:
	HWND m_hwnd;
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
};

