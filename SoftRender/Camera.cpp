#include "Camera.h"
#include "SoftMath.h"
#include <cmath>


Camera::Camera() : worldPos{0.0f, 0.0f, 20.0f}, 
    lookDirection{0.0f, 0.0f, -1.0f},
    up{0.0f, 1.0f, 0.0f}
{
    snear = -0.1f;
    sfar = -30.0f;
    aspectRatio = 3.0f;
    fov = 90.0f;
}

DirectX::XMMATRIX Camera::GetMatrix() const
{
    namespace dx = DirectX;
    
    dx::XMVECTOR{ 1.0f, 1.0f, 1.0f, 1.0f };
    float near = snear, far = sfar;
    DirectX::XMMATRIX viewMatrix, orthProjection, preProjection;
    dx::XMFLOAT3 gxt;
    float r, l, t, b, n = near, f = far;
    dx::XMStoreFloat3(&gxt, dx::XMVector3Cross(dx::XMLoadFloat3(&lookDirection), dx::XMLoadFloat3(&up)));

    const auto VR = DirectX::XMMatrixTranslationFromVector(DirectX::XMVectorNegate(dx::XMLoadFloat3(&worldPos)));
    viewMatrix = VR * DirectX::XMMatrixTranspose(dx::XMMatrixSet(
        gxt.x, gxt.y, gxt.z, 0.0f,
        up.x, up.y, up.z, 0.0f,
        -lookDirection.x, -lookDirection.y, -lookDirection.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f));

    b = n * std::tan(toRadian(fov) / 2);
    t = -b;
    r = t * aspectRatio;
    l = -r;

   

    const auto orthTans = dx::XMMatrixTranslationFromVector(dx::XMVectorSet(-l, -b, -n, 0.0f));
    orthProjection = orthTans *
        dx::XMMatrixSet(
            1 / (r - l), 0.0f, 0.0f, 0.0f,
            0.0f, 1 / (t - b), 0.0f, 0.0f,
            0.0f, 0.0f, 1 / (n - f), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);

    preProjection = DirectX::XMMatrixTranspose(
        dx::XMMatrixSet(
            near, 0.0f, 0.0f, 0.0f,
            0.0f, near, 0.0f, 0.0f,
            0.0f, 0.0f, near + far, -near * far,
            0.0f, 0.0f, 1.0f, 0.0f
        )
    );

    //
    return viewMatrix * (preProjection*  orthProjection);
}




DirectX::XMFLOAT4 Camera::tansform(DirectX::FXMVECTOR v) const
{
    DirectX::XMFLOAT4 p;
    DirectX::XMStoreFloat4(&p, DirectX::XMVector4Transform(v, GetMatrix()));
    p = DirectX::XMFLOAT4{ p.x / p.w, p.y / p.w, p.z / p.w, 1 };

    auto sreen = DirectX::XMMatrixScaling(1200, 600, 1);
    DirectX::XMStoreFloat4(&p, DirectX::XMVector4Transform(DirectX::XMLoadFloat4(&p), sreen));
    return p;
}

DirectX::XMMATRIX Camera::GetViewMatrix() const
{
    namespace dx = DirectX;

 
    DirectX::XMMATRIX viewMatrix;
    dx::XMFLOAT3 gxt;
 
    dx::XMStoreFloat3(&gxt, dx::XMVector3Cross(dx::XMLoadFloat3(&lookDirection), dx::XMLoadFloat3(&up)));

    const auto VR = DirectX::XMMatrixTranslationFromVector(DirectX::XMVectorNegate(dx::XMLoadFloat3(&worldPos)));
    viewMatrix = VR * 
        dx::XMMatrixTranspose( dx::XMMatrixSet(
        gxt.x, gxt.y, gxt.z, 0.0f,
        up.x, up.y, up.z, 0.0f,
        -lookDirection.x, -lookDirection.y, -lookDirection.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f));

    return viewMatrix;
}

DirectX::XMMATRIX Camera::GetPreProjectMatrix() const
{
    namespace dx = DirectX;

  
    float near = snear, far = sfar;
    DirectX::XMMATRIX  preProjection;
  

    
    preProjection = DirectX::XMMatrixTranspose(
        dx::XMMatrixSet(
        near, 0.0f, 0.0f, 0.0f,
        0.0f, near, 0.0f, 0.0f,
        0.0f, 0.0f, near + far, -near * far,
        0.0f, 0.0f, 1.0f, 0.0f
    )
    )
        ;
    return preProjection;
}

DirectX::XMMATRIX Camera::GetOrthProjectMatrix() const
{
    namespace dx = DirectX;

    float near = snear, far = sfar;
    DirectX::XMMATRIX orthProjection;
    float r, l, t, b, n = near, f = far;


    b = n * std::tan(toRadian(fov) / 2);
    t = -b;
    r = t * aspectRatio;
    l = -r;
    const auto orthTans = dx::XMMatrixTranslationFromVector(dx::XMVectorSet(-l, -b, -n, 0.0f));
    orthProjection = orthTans *
      
            dx::XMMatrixSet(
            1 / (r - l), 0.0f, 0.0f, 0.0f,
            0.0f, 1 / (t - b), 0.0f, 0.0f,
            0.0f, 0.0f, 1 / (n - f), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
    return orthProjection;
}
