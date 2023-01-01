#pragma once

#include <memory>

#include "BaseWindow.h"
#include "Graphics.h"


class MainWindow : public BaseWindow<MainWindow>
{
public:
	MainWindow() = default;
	MainWindow(const MainWindow& rhs) = delete;
	MainWindow& operator=(const MainWindow& rhs) = delete;
	HRESULT InitGraphics();
	Graphics& Graphic();
	virtual PCWSTR ClassName() const override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	void Swap()
	{
		InvalidateRect(m_hwnd, NULL, false);
	}
private:
	std::unique_ptr<Graphics> pGraphics;
};

