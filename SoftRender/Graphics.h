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
	void SetPixel(float x, float y, unsigned char u, unsigned char g, unsigned char b);
	
	void Clear(COLORREF color = RGB(255, 255, 255));

	void CheckWidthHeight()
	{
		RECT clientRect;
		GetClientRect(m_hwnd, &clientRect);
		width = clientRect.right - clientRect.left;
		height = clientRect.bottom - clientRect.top;
	}

	void StoreWindow()
	{
		HDC hDC = GetDC(m_hwnd);
		memoryDC = CreateCompatibleDC(hDC);
		memoryBitmap = CreateCompatibleBitmap(hDC, width, height);
		SelectObject(memoryDC, memoryBitmap);
		BitBlt(memoryDC, 0, 0, width, height, hDC, 0, 0, SRCCOPY);
		ReleaseDC(m_hwnd, hDC);
	}

	void RestoreWindow()
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(m_hwnd, &ps);
		if (memoryDC)
			BitBlt(hDC, 0, 0, width, height, memoryDC, 0, 0, SRCCOPY);
		EndPaint(m_hwnd, &ps);
	}
private:
	HRESULT CreateGraphicsResource();
	void DiscardGraphicsResource();
	void OnPaint();
	void Resize();

	
private:
	HWND m_hwnd;
	int m_width;
	int m_height;
	HBITMAP memoryBitmap = nullptr;
	HDC memoryDC = nullptr	;
	int width = 0, height = 0;
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
};

