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
	: m_hwnd(hwnd)
{
	if (FAILED(D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
	{

	}
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
