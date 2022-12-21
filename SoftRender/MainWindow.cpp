#include "MainWindow.h"

PCWSTR MainWindow::ClassName() const
{
    return L"Class";
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(m_hwnd, &ps);
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
    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);;
    }
}
