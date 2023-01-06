#include "App.h"

#include "IndexTriangleList.h"

App::App() 
{
    

    if (!win.Create(L"Render", WS_OVERLAPPEDWINDOW))
    {
      
    }
    win.InitGraphics();
    ShowWindow(win.Window(), SW_SHOW);
    

    auto p1 = DirectX::XMFLOAT3{ 1.0f, 1.0f, -1.0f };

    auto p2 = DirectX::XMFLOAT3{ -1, -1, -1.0f};
    auto p3 = DirectX::XMFLOAT3{ 1.0f, -1.0f, -1.0f };


    std::vector<Data> p = { {p1, Color{1.0f, 1.0f, 0.0f, 1.0f}}, 
        {p2, Color{1.0f, 0.0f, 0.0f, 1.0f}},
        {p3, Color{0.0f, 1.0f, 1.0f, 1.0f}} };
    std::vector<unsigned short> i= { 0, 1, 2 };
    IndexTriangleList<Data> id(p, i);

    win.Graphic().SetIndexData(id);
    win.Graphic().SetRenderTarget();
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
    
    win.Graphic().DrawCall();
    
  
    win.Swap();

  
}
