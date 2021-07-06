#include "Camera.h"
#include "Image.h"

HRESULT Camera::Init()
{
	posX = WINSTART_X;
	posY = WINSTART_Y;
	scale = 1;
	currKeyFrameX = 1;
	currKeyFrameY = 0;

	charposX = (WINSIZE_X / 4) * 1;
	charposY;

	Pos={ (charposX -( WINSIZE_X / 2)), WINSTART_Y, (charposX +( WINSIZE_X / 2)) ,WINSIZE_Y };
	
	return S_OK;
}

void Camera::Release()
{
	
}

void Camera::Update()
{
	
	Pos.left = charposX / 6;

	if (Pos.left <= 0)
	{
		Pos.left = 0;
	}
	else if (Pos.left >= 248)
	{
    	Pos.left = 248;
	}



}

void Camera::Render(HDC hdc)
{
		//Camera_02->FrameRender(hdc, posX + 100, posY + 40, currKeyFrameX, currKeyFrameY, 0.62);

	
}


Camera::Camera()
{
}

Camera::~Camera()
{
}
