#include "BackGround.h"
#include "Image.h"
#include <ctime>


HRESULT BackGround::Init()
{
	posX = WINSTART_X;
	posY = WINSTART_Y + 38;
	srand(time(NULL));
	BgNum = rand()%6;
	img = new Image();
	if (BgNum == 0)
	{
		img->Init("Image/BG_horz.bmp",
			posX, posY, 6016, 224, 8, 1);
	}
	else if (BgNum == 1)
	{
		img->Init("Image/2_horz.bmp",
			posX, posY, 6008, 224, 8, 1);
	}
	else if (BgNum == 2)
	{
		img->Init("Image/3_horz.bmp",
			posX, posY, 6016, 224, 8, 1);
	}
	else if (BgNum == 3)
	{
		img->Init("Image/5_horz.bmp",
			posX, posY, 6000, 224, 8, 1);
	}
	else if (BgNum == 4)
	{
		img->Init("Image/6_horz.bmp",
			posX, posY, 6016, 224, 8, 1);
	}
	else if (BgNum == 5)
	{
		img->Init("Image/7_horz.bmp",
			posX, posY, 6016, 224, 8, 1);
	}

	currKeyFrameX = 0;
	currKeyFrameY = 0;
	elapsedFrame = 0;
	scale = 2.0f;

	return S_OK;
}

void BackGround::Release()
{
	img->Release();
	delete img;
}

void BackGround::Update()
{
	elapsedFrame++;
	if (elapsedFrame % 7 == 6 && currKeyFrameX != 8)
	{
		currKeyFrameX++;
		elapsedFrame = 0;
	}
	else if (elapsedFrame % 3 == 2 && currKeyFrameX == 8)
	{
		currKeyFrameX = 0;
		elapsedFrame = 0;
	}

}

void BackGround::Render(HDC hdc)
{
	if (img)
	{

		img->FrameRender(hdc, posX, posY,
			currKeyFrameX, currKeyFrameY, scale,false, 0, camerPosX);		
	}
}

BackGround::BackGround()
{
}


BackGround::~BackGround()
{
}
