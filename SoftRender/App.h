#pragma once
#include <Windows.h>
#include "MainWindow.h"

class App
{
public:
	App();
	int Go();

private:
	void DoFream();
	MainWindow win;
};

