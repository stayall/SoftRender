#include "App.h"


App::App() 
{
    

    if (!win.Create(L"Render", WS_OVERLAPPEDWINDOW))
    {
      
    }
    win.InitGraphics();
    ShowWindow(win.Window(), SW_SHOW);
    

    auto p1 = DirectX::XMVectorSet(1.0f, 1.0f, -1, 1.0f);

    auto p2 = DirectX::XMVectorSet(-1, -1, -1, 1.0f);
    auto p3 = DirectX::XMVectorSet(1.0f, -1.0f, -1, 1.0f);

    std::vector<Vertex> s = { {{1.0f, 1.0f, -1.0f}}, {{-1.0f, -1.0f, -1.0f}}, {{1.0f, -1.0f, -1.0}} };
    
    win.Graphic().IASetIndexVertexData(s);
    win.Graphic().IASetIndex({0, 1, 2});
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
    DirectX::XMVECTOR v;
    v = DirectX::XMVector3Transform({ 1.0f, 1.0f, 1.0f, 1.0f }, DirectX::XMMatrixScaling(1.0, 1.0, 1.0));
    
    win.Graphic().InputDataProcess();
    win.Swap();
   

  
}
