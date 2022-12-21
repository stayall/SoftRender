#include "MainWindow.h"

PCWSTR MainWindow::ClassName() const
{
    return L"Class";
}

LRESULT MainWindow::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_CLOSE:
    {
        if (MessageBox(hwnd, L"Really close", L"Application", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(69);
        return 0;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);;
    }
}
