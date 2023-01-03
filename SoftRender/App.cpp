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

DirectX::XMFLOAT4 tans(DirectX::XMVECTOR v)
{
    Camera camera;
    auto srceen = DirectX::XMMatrixScalingFromVector(DirectX::XMVectorSet(1200, 500.0f, 1.0f, 1.0f));
    DirectX::XMFLOAT4 p4;
    DirectX::XMStoreFloat4(&p4, DirectX::XMVector4Transform(v, camera.GetViewMatrix()));
    DirectX::XMStoreFloat4(&p4, DirectX::XMVector4Transform(DirectX::XMLoadFloat4(&p4), camera.GetPreProjectMatrix()));
    p4 = DirectX::XMFLOAT4{ p4.x / p4.w, p4.y / p4.w, p4.z / p4.w, 1 };
    DirectX::XMStoreFloat4(&p4, DirectX::XMVector4Transform(DirectX::XMLoadFloat4(&p4), camera.GetOrthProjectMatrix()));
    DirectX::XMStoreFloat4(&p4, DirectX::XMVector4Transform(DirectX::XMLoadFloat4(&p4), srceen));
    return p4;

}
void App::DoFream()
{
   
    auto p1 = DirectX::XMVectorSet(1.0f, 1.0f, -1, 1.0f);
    
    auto p2 = DirectX::XMVectorSet(-1, -1, -1, 1.0f);
    auto p3 = DirectX::XMVectorSet(1.0f, -1.0f, -1, 1.0f);
    DirectX::XMFLOAT4 p4, p5, p6;
    p5 = tans(p2);
    p4 = tans(p1);
    p6 = tans(p3);
    Triangle t{ DirectX::XMLoadFloat4(&p4), DirectX::XMLoadFloat4(&p5), DirectX::XMLoadFloat4(&p6) };
    t.DrawCall(win.Graphic());
    win.Swap();
    //win.Graphic().RestoreWindow();

  
}
