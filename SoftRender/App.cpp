#include "App.h"


App::App() 
{
    

    if (!win.Create(L"Render", WS_OVERLAPPEDWINDOW))
    {
      
    }
    win.InitGraphics();
    ShowWindow(win.Window(), SW_SHOW);
    //win.Graphic().StoreWindow();

    auto p1 = DirectX::XMVectorSet(1.0f, 1.0f, -1, 1.0f);

    auto p2 = DirectX::XMVectorSet(-1, -1, -1, 1.0f);
    auto p3 = DirectX::XMVectorSet(1.0f, -1.0f, -1, 1.0f);

    std::vector<Vertex> s = { {{1.0f, 1.0f, -1.0f}}, {{-1.0f, -1.0f, -1.0f}}, {{1.0f, -1.0f, -1.0}} };
    
    win.Graphic().IASetIndexVertexData(s);
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
   
    
    
    win.Swap();
   

  
}
