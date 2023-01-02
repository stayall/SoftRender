#include "App.h"
#include "Camera.h"
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
    
    auto maxtrix = DirectX::XMMatrixScalingFromVector(DirectX::XMVectorSet(1.0f, 1.0f, 0.5f, 1.0f));
    auto maxtrix1 = DirectX::XMMatrixRotationX(90.0f * 3.1415926535 / 180);
    auto maxtrix2 = DirectX::XMMatrixScalingFromVector(DirectX::XMVectorSet(1.0f, 0.5f, 1.0f, 1.0f));
    Camera cmaera;
    
    auto c = DirectX::XMVector3Transform(DirectX::XMVectorSet(1.0f, 1.0f, -1.0f, 1.0f), cmaera.GetMatrix());
   
    win.Swap();
    //win.Graphic().RestoreWindow();

  
}
