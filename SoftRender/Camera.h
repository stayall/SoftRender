#pragma once
#include <DirectXMath.h>

//Orthograpic and Perspective 
class Camera
{
public:
	Camera();
	DirectX::XMMATRIX GetMatrix() const;
	DirectX::XMFLOAT4 tansform(DirectX::XMVECTOR v) const;
	DirectX::XMMATRIX GetViewMatrix() const;
	DirectX::XMMATRIX GetPreProjectMatrix() const;
	DirectX::XMMATRIX GetOrthProjectMatrix() const;

	//TODO:camera move;
	//void update();
private:
	//FIEXD: big question
	//float far;
	float snear;
	float sfar;
	float fov;
	float aspectRatio;
	DirectX::XMFLOAT3 worldPos;
	DirectX::XMFLOAT3 lookDirection;
	DirectX::XMFLOAT3 up;
	

};

