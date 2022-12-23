#include "App.h"

App::App() 
{
    

    if (!win.Create(L"Render", WS_OVERLAPPEDWINDOW))
    {
      
    }

    ShowWindow(win.Window(), SW_SHOW);
}

int App::Go()
{
    while (true)
    {
        if (const auto r = MainWindow::ProceseMessage())
        {
            return *r;
        }

        DoFream();
    }

    return 0;
}

void App::DoFream()
{
}
