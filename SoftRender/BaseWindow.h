#pragma once
#include <Windows.h>

template<class DERIVE_TYPE>
class BaseWindow
{
public:
	BaseWindow() : m_hwnd(nullptr) {};

	static LRESULT	CALLBACK WindProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		DERIVE_TYPE* pthis = nullptr;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);

			pthis = reinterpret_cast<DERIVE_TYPE*>(pCreate->lpCreateParams);
			SetClassLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG*>(pthis));

		}
		else
		{
			pthis = GetClassLongPtr(hwnd, GWLP_USERDATA);
		}

		if (pthis)
		{
			return pthis->HandleMessage(hwnd, uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	BOOL Create(
		PCWSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExStyle = 0,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU hMenu = 0
	)
	{
		WNDCLASS wc = {};
		wc.lpfnWndProc = DERIVE_TYPE::WindProc;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.lpszClassName = ClassName();
		RegisterClass(&wc);

		HWND hWnd = CreateWindowEx(0, CLASS_NAME, lpWindowName, dwExStyle,
			x, y, nWidth, nHeight,
			hWndParent, hMenu, GetModuleHandle(nullptr), this);
	}
protected:
	virtual PCWSTR ClassName() const = 0;
	virtual LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	HWND m_hwnd;
};

