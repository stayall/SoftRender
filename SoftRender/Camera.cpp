#include "Camera.h"
#include "SoftMath.h"
#include <cmath>


Camera::Camera() : worldPos{0.0f, 0.0f, -10.0f}, 
    lookDirection{0.0f, 0.0f, -1.0f},
    up{0.0f, 1.0f, 0.0f}
{
    snear = -5.0f;
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
    viewMatrix = VR * dx::XMMatrixSet(
        gxt.x, gxt.y, gxt.z, 0.0f,
        up.x, up.y, up.z, 0.0f,
        -lookDirection.x, -lookDirection.y, -lookDirection.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    t = -n * std::tan(toRadian(fov) / 2);
    b = -t;
    r = t * aspectRatio;
    l = -r;

    auto pre = DirectX::XMMatrixLookAtRH(DirectX::XMLoadFloat3(&worldPos), DirectX::XMLoadFloat3(&lookDirection), DirectX::XMLoadFloat3(&up));
    auto pro = DirectX::XMMatrixPerspectiveFovRH(fov, aspectRatio, -snear, -sfar);

    const auto orthTans = dx::XMMatrixTranslationFromVector(dx::XMVectorSet(-l , -b ,  -n , 1.0f));
    orthProjection = orthTans *
    dx::XMMatrixSet(
        1 / (r - l), 0.0f, 0.0f, 0.0f,
        0.0f, 1 / (t - b), 0.0f, 0.0f,
        0.0f, 0.0f, 1 / (n - f), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    preProjection = dx::XMMatrixSet(
        near, 0.0f, 0.0f, 0.0f,
        0.0f, near, 0.0f, 0.0f,
        0.0f, 0.0f, near + far, -near * far,
        0.0f, 0.0f, 1.0f, 0.0f
    );

    //
    return viewMatrix * preProjection*  orthProjection;
}
