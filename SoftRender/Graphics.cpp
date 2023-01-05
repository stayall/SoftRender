#include "Graphics.h"


template<class T>
void SafeRelease(T** p)
{
	if (*p)
	{
		(*p)->Release();
		*p = nullptr;
	}
}

Graphics::Graphics(HWND hwnd)
	: m_hwnd(hwnd), pRenderTarget(nullptr)
{
	if (FAILED(D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
	{

	}

	RECT rc;
	GetClientRect(hwnd, &rc);
	width = rc.right;
	height = rc.bottom;
}

Graphics::~Graphics()
{
	DeleteObject(memoryBitmap);
	DeleteDC(memoryDC);
}

void Graphics::SetPixel(float x, float y, unsigned char r, unsigned char g, unsigned char b)
{
	auto hdc = GetDC(m_hwnd);
	RECT rc;
	rc.bottom = 200;
	rc.top = 400;
	rc.left = 200;
	rc.right = 400;
	FillRect(hdc, &rc, (HBRUSH)RGB(0, 0, 0));
	
	return;
	for (int i = 1; i < width; i++)
	{
		for (int j = 1; j < height; j++)
		{
			RECT rc;
			rc.bottom = j;
			rc.top = j + 1;
			rc.left = i;
			rc.right = i + 1;
			FillRect(hdc, &rc, (HBRUSH)RGB(0, 0, 0));
			//SetPixelV(memoryDC, static_cast<int>(i), static_cast<int>(j), RGB(0, 0, 0));
		}
	}
	ReleaseDC(m_hwnd, hdc);
	return;
	SetPixelV(memoryDC, static_cast<int>(x), static_cast<int>(height - y), RGB(r, g, b));
}
	

void Graphics::Clear(COLORREF color)
{
	HRESULT hr;
	hr = CreateGraphicsResource();
	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hwnd, &ps);
		pRenderTarget->BeginDraw();

		FillRect(hdc, &ps.rcPaint, (HBRUSH)0x5200);
		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

		hr = pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResource();
		}

		EndPaint(m_hwnd, &ps);
	}
}

DirectX::XMMATRIX Graphics::GetSreenMatrix() const
{
	return DirectX::XMMatrixScaling(static_cast<float>(width), static_cast<float>(height), 1.0f);
}



DirectX::XMFLOAT4 Graphics::HomogeneousDivision(const DirectX::XMFLOAT4 &v)
{
	return {v.x / v.w, v.y / v.w, v.z / v.w, 1.0f };
}




void Graphics::CheckWidthHeight()
{
	RECT clientRect;
	GetClientRect(m_hwnd, &clientRect);
	width = clientRect.right - clientRect.left;
	height = clientRect.bottom - clientRect.top;
}

void Graphics::StoreWindow()
{
	if (memoryBitmap)
	{
		DeleteObject(memoryBitmap);
	}
	HDC hDC = GetDC(m_hwnd);
	memoryDC = CreateCompatibleDC(hDC);
	memoryBitmap = CreateCompatibleBitmap(hDC, width, height);
	SelectObject(memoryDC, memoryBitmap);
	BitBlt(memoryDC, 0, 0, width, height, hDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hwnd, hDC);
}

void Graphics::RestoreWindow()
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(m_hwnd, &ps);
	if (memoryDC)
		BitBlt(hDC, 0, 0, width, height, memoryDC, 0, 0, SRCCOPY);
	EndPaint(m_hwnd, &ps);
}



HRESULT Graphics::CreateGraphicsResource()
{
	HRESULT hr = S_OK;
	if (pRenderTarget == nullptr)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);


		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&pRenderTarget
		);

		if (SUCCEEDED(hr))
		{
			
		}
	}
	return hr;
}

void Graphics::DiscardGraphicsResource()
{
	SafeRelease(&pRenderTarget);
}

void Graphics::OnPaint()
{
	HRESULT hr;
	hr = CreateGraphicsResource();
	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hwnd, &ps);
		pRenderTarget->BeginDraw();
		
		FillRect(hdc, &ps.rcPaint, (HBRUSH)0x5200);
		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

		hr = pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResource();
		}

		EndPaint(m_hwnd, &ps);
	}
}

void Graphics::Resize()
{
	if (pRenderTarget != nullptr)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		pRenderTarget->Resize(size);
		InvalidateRect(m_hwnd, nullptr, FALSE);
	}
}
