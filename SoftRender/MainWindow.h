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
	virtual PCWSTR ClassName() const override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

private:
	std::unique_ptr<Graphics> pGraphics;
};

