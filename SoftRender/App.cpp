#include "App.h"
#include "Triangle.h"
App::App() 
{
    

    if (!win.Create(L"Render", WS_OVERLAPPEDWINDOW))
    {
      
    }
    win.InitGraphics();
    ShowWindow(win.Window(), SW_SHOW);
    win.Graphic().StoreWindow();
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
    Triangle t({ 100, 100, 0 }, { 100, 500, 0 }, { 500, 500, 0 });
    //win.Graphic().Clear();
    Triangle t1({ 500, 200, 0 }, { 600, 100, 0 }, { 500, 500, 0 });
    t.DrawCall(win.Graphic());
    t1.DrawCall(win.Graphic());
   
    win.Swap();
    //win.Graphic().RestoreWindow();

  
}
