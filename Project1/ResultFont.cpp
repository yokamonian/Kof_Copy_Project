#pragma once
#include "ResultFont.h"
#include "Image.h"
HRESULT ResultFont::Init()
{
	posX = 0;
	posY = 0;
	scale = 1;
	currKeyFrameX = 1;
	currKeyFrameY = 0;

	Player_1p_win = new Image();
	Player_2p_win = new Image();
	KO = new Image();
	Time_Over = new Image();
	Draw = new Image();

	Player_1p_win->Init("Image/1P_win.bmp", posX, posY, 500, 120, 1, 1, true, RGB(114, 226, 255));
	Player_2p_win->Init("Image/2P_win.bmp", posX, posY, 500, 120, 1, 1, true, RGB(114, 226, 255));
	KO->Init("Image/Ko.bmp", posX, posY, 500, 120, 1, 1, true, RGB(114, 226, 255));
	Time_Over->Init("Image/TimeOver.bmp", posX, posY, 550, 120, 1, 1, true, RGB(114, 226, 255));
	Draw->Init("Image/draw.bmp", posX, posY, 550, 120, 1, 1, true, RGB(114, 226, 255));

	return S_OK;
}

void ResultFont::Release()
{
	Player_1p_win->Release();
	delete Player_1p_win;
	Player_2p_win->Release();
	delete Player_2p_win;
	KO->Release();
	delete KO;
	Time_Over->Release();
	delete Time_Over;
	Draw->Release();
	delete Draw;
}

void ResultFont::Update()
{

	//0-> 아직 승부 결과 없음;
	// 1 -> 시간전 1P 승리
	// 2 -> 시간전 2P 승리
	// 3 -> 시간전 무승부
	// 4 -> 시간 후  1P 승리
	// 5-> 시간후 1P 승리
	// 6 -> 시간후 무승부
}

void ResultFont::Render(HDC hdc)
{



	if (resultNum == 1)
	{
		KO->FrameRender(hdc, posX + 15, posY + 170, 1, 1, 2);
		Player_1p_win->FrameRender(hdc, posX + 90, posY + 120, 1, 1, 0.7);
	}
	else if (resultNum == 2)
	{
		KO->FrameRender(hdc, posX + 15, posY + 170, 1, 1, 2);
		Player_2p_win->FrameRender(hdc, posX + 560, posY + 120, 1, 1, 0.7);
	}
	else if (resultNum == 3)
	{
		KO->FrameRender(hdc, posX + 15, posY + 170, 1, 1, 2);
	}
	else if (resultNum == 4)
	{
		Time_Over->FrameRender(hdc, posX + 225, posY + 210, 1, 1, scale);
		Player_1p_win->FrameRender(hdc, posX + 90, posY + 120, 1, 1, 0.7);
	}
	else if (resultNum == 5)
	{
		Time_Over->FrameRender(hdc, posX + 225, posY + 210, 1, 1, scale);
		Player_2p_win->FrameRender(hdc, posX + 560, posY + 120, 1, 1, 0.7);
	}
	else if (resultNum == 6)
	{
		Time_Over->FrameRender(hdc, posX + 225, posY + 210, 1, 1, scale);
		Draw->FrameRender(hdc, posX + 225, posY + 310, 1, 1, scale);
	}




}

ResultFont::ResultFont()
{
}

ResultFont::~ResultFont()
{
}
