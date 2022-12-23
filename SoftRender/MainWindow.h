#pragma once
#include "BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
	MainWindow() = default;
	MainWindow(const MainWindow& rhs) = delete;
	MainWindow& operator=(const MainWindow& rhs) = delete;
	virtual PCWSTR ClassName() const override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};

