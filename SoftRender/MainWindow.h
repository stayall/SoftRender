#pragma once
#include "BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
	
	virtual PCWSTR ClassName() const override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};

