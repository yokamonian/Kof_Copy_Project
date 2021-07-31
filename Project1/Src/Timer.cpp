#include "Timer.h"

#include "Image.h"

HRESULT Timer::Init()
{

	posX = (WINSIZE_X / 2)+3;
	posY = (WINSIZE_Y / 10)*1.5;
	CountDown_Num = new Image();

	CountNum = 0;
	CountDown_Num->Init("Image/Timer.bmp", posX, posY, 140, 75, 10, 3, true, transColor[CountNum]);

	printTime = 45;

	currKeyFrameY = 0;
	elapsedFrame = 0;
	scale = 1.7f;

	return S_OK;
}

void Timer::Release()
{
	CountDown_Num->Release();
	delete CountDown_Num;

}

void Timer::Update()
{
	if (printTime > 10)
	{
		currKeyFrameX = printTime % 10;
		currKeyFrameX2 = (printTime - (printTime % 10)) / 10;
	}
	else
	{
		CountNum = 1;
		CountDown_Num->SetTransColor(transColor[CountNum]);
		currKeyFrameY = 1;
		currKeyFrameX = printTime % 10;
		currKeyFrameX2 = (printTime - (printTime % 10)) / 10;
	}



}

void Timer::Render(HDC hdc)
{
	CountDown_Num->FrameRender(hdc, posX - 25, posY,
		currKeyFrameX2, currKeyFrameY, scale);
	CountDown_Num->FrameRender(hdc, posX, posY,
		currKeyFrameX, currKeyFrameY, scale);
}

Timer::Timer()
{
}

Timer::~Timer()
{
}
