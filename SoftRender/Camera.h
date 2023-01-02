#pragma once
#include <DirectXMath.h>


//Orthograpic and Perspective 
class Camera
{
public:
	Camera();
	DirectX::XMMATRIX GetMatrix() const;

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

