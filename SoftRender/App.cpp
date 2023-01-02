#include "App.h"
#include "Camera.h"
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
    
    auto p1 = DirectX::XMVectorSet(100.0f, 100.0f, -0.0f, 1.0f);
    auto p2 = DirectX::XMVectorSet(-100.0f, -100.0f, -0.0f, 1.0f);
    auto p3 = DirectX::XMVectorSet(100.0f, -100.0f, -0.0f, 1.0f);
    DirectX::XMFLOAT4 p4, p5, p6;
    Camera camera;
    auto matrx = camera.GetMatrix();
    auto srceen = DirectX::XMMatrixScalingFromVector(DirectX::XMVectorSet(1200, 500.f, 1.0f, 1.0f));
    DirectX::XMStoreFloat4(&p4, DirectX::XMVector4Transform(p1, camera.GetMatrix()));
    DirectX::XMStoreFloat4(&p5, DirectX::XMVector4Transform(p2, camera.GetMatrix()));
    DirectX::XMStoreFloat4(&p6, DirectX::XMVector4Transform(p3, camera.GetMatrix()));
    p4 = DirectX::XMFLOAT4{ p4.x / p4.w, p4.y / p4.w, p4.z / p4.w, 1 };
    p5 = DirectX::XMFLOAT4{ p5.x / p5.w, p5.y / p5.w, p5.z / p5.w, 1 };
    p6 = DirectX::XMFLOAT4{ p6.x / p6.w, p6.y / p6.w, p6.z / p6.w, 1 };
    p1 = DirectX::XMLoadFloat4(&p4);
    p2 = DirectX::XMLoadFloat4(&p5);
    p3 = DirectX::XMLoadFloat4(&p6);

    DirectX::XMStoreFloat4(&p4, DirectX::XMVector4Transform(p1, srceen));
    DirectX::XMStoreFloat4(&p5, DirectX::XMVector4Transform(p2, srceen));
    DirectX::XMStoreFloat4(&p6, DirectX::XMVector4Transform(p3, srceen));
    Triangle t{ DirectX::XMLoadFloat4(&p4), DirectX::XMLoadFloat4(&p5), DirectX::XMLoadFloat4(&p6) };
    t.DrawCall(win.Graphic());
    win.Swap();
    //win.Graphic().RestoreWindow();

  
}
