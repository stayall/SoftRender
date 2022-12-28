#include "MainWindow.h"





HRESULT MainWindow::InitGraphics()
{
	if (m_hwnd == nullptr)
	{
		return S_FALSE;
	}
	pGraphics = std::make_unique<Graphics>(m_hwnd);

	return S_OK;
}

PCWSTR MainWindow::ClassName() const
{
	return L"Class";
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		

		return 0;
	}
	case WM_PAINT:
	{
		if (pGraphics)
		{
			pGraphics->OnPaint();
		}
		return 0;
	}
	case WM_CLOSE:
	{
		if (MessageBox(m_hwnd, L"Really close", L"Application", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(m_hwnd);
		}
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(69);
		return 0;
	}
	case WM_SIZE:
	{
		if (pGraphics )
		{
		pGraphics->Resize();
		}
		return 0;
	}
	default:
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);;
	}
}
