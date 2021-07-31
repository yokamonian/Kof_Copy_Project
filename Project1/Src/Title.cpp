#include "Title.h"
#include "Image.h"

HRESULT Title::Init()
{
	posX = WINSTART_X;
	posY = WINSTART_Y;
	scale = 1;
	currKeyFrameX = 1;
	currKeyFrameY = 0;

	title = new Image();
	titleBg = new Image();
	title_02 = new Image();
	ending_1P = new Image();
	ending_2P = new Image();
	ending_draw = new Image();

	titleBg->Init("Image/C00.bmp", posX, posY, 1280, 720, 1, 1, true, RGB(0, 0, 255));
	title->Init("Image/Title.bmp", posX, posY, 4400, 225, 11, 1, true, RGB(0, 0, 255));

	title_02->Init("Image/B_horz.bmp", posX, posY, 12800, 720, 10, 1, true, RGB(0, 0, 255));

	ending_1P->Init("Image/A_01_horz.bmp", posX, posY, 12800, 720, 10, 1, true, RGB(0, 0, 255));
	ending_2P->Init("Image/D_01_horz.bmp", posX, posY, 12800, 720, 10, 1, true, RGB(0, 0, 255));
	ending_draw->Init("Image/C_02_horz.bmp", posX, posY, 12800, 720, 10, 1, true, RGB(0, 0, 255));
	return S_OK;
}

void Title::Release()
{
	title->Release();
	delete title;

	titleBg->Release();
	delete titleBg;

	title_02->Release();
	delete title_02;
}

void Title::Update()
{
	if (!isTitleMaXFrame == true && !isEnd1P && !isEnd2P && !isDraw)
	{
		elapsedFrame++;
		if (elapsedFrame % frameSpeed[frameSpeedIdex] == frameSpeed[frameSpeedIdex] - 1 && currKeyFrameX != 10)
		{
			currKeyFrameX++;
			elapsedFrame = 0;
		}
		else if (elapsedFrame %frameSpeed[frameSpeedIdex] == frameSpeed[frameSpeedIdex] - 1 && currKeyFrameX == 10)
		{
			currKeyFrameX = 0;
			elapsedFrame = 0;
			if (!isintro)
			{
				frameSpeedIdex = 1;
				isintro = true;
			}
			else if (isintro && !isTitleMaXFrame)
			{
				currKeyFrameX = 10;
				isTitleMaXFrame = true;
			}
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE)&&!isTitle)
	{
		isTitle = true;
		currKeyFrameX = 0;
		elapsedFrame = 0;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_SPACE))
	{

		/*currKeyFrameX = 0;
		elapsedFrame = 0;*/
	}

	if (isEnd1P || isEnd2P)
	{
		elapsedFrame++;
		if (elapsedFrame % 12 == 11 && currKeyFrameX != 10)
		{
			currKeyFrameX++;
			elapsedFrame = 0;
		}
		else if (elapsedFrame % 12 == 11 && currKeyFrameX == 10)
		{
			currKeyFrameX = 10;
			elapsedFrame = 0;

		}
	}

	if (isDraw)
	{
		elapsedFrame++;
		if (elapsedFrame % 12 == 11 && currKeyFrameX != 10)
		{
			currKeyFrameX++;
			elapsedFrame = 0;
		}
		else if (elapsedFrame % 12 == 11 && currKeyFrameX == 10)
		{
			currKeyFrameX = 10;
			elapsedFrame = 0;

		}
	}



}

void Title::Render(HDC hdc)
{
	if (!isintro && !isEnd1P && !isEnd2P && !isDraw)
	{
		title_02->FrameRender(hdc, posX + 100, posY + 40, currKeyFrameX, currKeyFrameY, 0.62);

	}
	else if (isintro && !isEnd1P && !isEnd2P && !isDraw)
	{
		//titleBg->FrameRender(hdc, posX, posY, 1, 1, 5.5);
		title->FrameRender(hdc, posX + 40, posY, currKeyFrameX, currKeyFrameY, 2.26);
	}
	else if (isEnd1P)
	{
		ending_1P->FrameRender(hdc, posX, posY, currKeyFrameX, currKeyFrameY, 0.8015);
	}
	else if (isEnd2P)
	{
		ending_2P->FrameRender(hdc, posX, posY, currKeyFrameX, currKeyFrameY, 0.8015);
	}
	else if (isDraw)
	{
		ending_draw->FrameRender(hdc, posX, posY, currKeyFrameX, currKeyFrameY, 0.8015);
	}
}


Title::Title()
{
}

Title::~Title()
{
}
