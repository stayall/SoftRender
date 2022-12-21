#pragma once
#include "BaseWindow.h"

class MainWindow : BaseWindow<MainWindow>
{
	
	virtual PCWSTR ClassName() const override;
	virtual LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};

