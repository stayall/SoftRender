#pragma once
#include <Windows.h>
#include <string>
#include <optional>

template<class DERIVE_TYPE>
class BaseWindow
{
public:
	BaseWindow() : m_hwnd(nullptr) {};
	virtual ~BaseWindow() = default;

	static LRESULT CALLBACK WindProcHandle(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		DERIVE_TYPE* pthis = reinterpret_cast<DERIVE_TYPE*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	
			return pthis->HandleMessage(uMsg, wParam, lParam);
	
	}

	static LRESULT	CALLBACK WindProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		DERIVE_TYPE* pthis = nullptr;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
			SetLastError(0);
			pthis = reinterpret_cast<DERIVE_TYPE*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindProcHandle));
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pthis));
		
			pthis->m_hwnd = hwnd;

		
		}
		
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
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

		m_hwnd = CreateWindowEx(dwExStyle, ClassName(), lpWindowName, dwStyle,
			x, y, nWidth, nHeight,
			hWndParent, hMenu, GetModuleHandle(nullptr), this);

		return m_hwnd ? TRUE : FALSE;
	}

	static std::optional<LRESULT> ProceseMessage()
	{
		MSG msg = {};

		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return { msg.wParam };
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return { };
	}

	HWND Window() const { return m_hwnd; }
protected:
	virtual PCWSTR ClassName() const = 0;
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	HWND m_hwnd;
};


