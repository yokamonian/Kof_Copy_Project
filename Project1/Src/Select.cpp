#include "Select.h"
#include "MainGame.h"
#include "Image.h"
#include <ctime>


HRESULT Select::Init()
{
	isSelect = false;
	posX = WINSTART_X;
	posY = WINSTART_Y + 38;

	// 초기 캐릭터 선택 초상화
	ChoiceNum1P = 0;
	ChoiceNum2P = 2;

	// 포인터 좌표
	posX1P = selectposX[ChoiceNum1P];
	posY1P = selectposY[ChoiceNum1P];
	posX2P = selectposX[ChoiceNum2P];
	posY2P = selectposY[ChoiceNum2P];

	srand(time(NULL));
	
	// 이미지 관련 초기화
	select = new Image();
	select->Init("Image/Select.bmp",
		posX, posY, 500, 400, 1, 1,true, RGB(255, 0, 255));

	selectIcon1P = new Image();

	selectIcon1P->Init("Image/SelectIcon.bmp",
		posX, posY, 160, 64, 4, 1,true,RGB(255,255,255) );

	selectIcon2P = new Image();
	selectIcon2P->Init("Image/SelectIcon.bmp",
		posX, posY, 160, 64 , 4, 1,true, RGB(255, 255, 255));

	charImg = new Image();
	charImg->Init("Image/SelectFace.bmp",
		posX, posY,520 , 262, 4, 2,true, RGB(255, 255, 255));
	selectBg = new Image();
	selectBg->Init("Image/SelectBg.bmp",
		posX, posY, 318, 120, 1, 1,true, RGB(255, 255, 255));

	currKeyFrameX1P = 0;
	currKeyFrameX2P = 2;
	currKeyFrameX1PIcon=0;
	currKeyFrameX2PIcon=2;
	currKeyFrameY = 0;
	isChoice1P = false;
	isChoice2P = false;

	scale = 1.0f;
	isInit = true;
	return S_OK;
}

void Select::Release()
{
	select->Release();
	delete select;
	selectIcon1P->Release();
	delete selectIcon1P;
	selectIcon2P->Release();
	delete selectIcon2P;
	charImg->Release();
	delete charImg;
	selectBg->Release();
	delete selectBg;


}

void Select::Update()
{
	// 캐릭터 선택 이전
	if (isSelect == false)
	{
		// 1P 기준, 이동 관련 키 세팅(좌우)
		if (KeyManager::GetSingleton()->IsOnceKeyDown('G') && !(isChoice1P) || KeyManager::GetSingleton()->IsOnceKeyDown('H') && !(isChoice1P))
		{
			if (ChoiceNum1P <= 0)
			{
				ChoiceNum1P = 3;
			}
			else ChoiceNum1P = ((ChoiceNum1P - 1) % 4);

			currKeyFrameX1P = ChoiceNum1P;
			posX1P = selectposX[ChoiceNum1P];
			posY1P = selectposY[ChoiceNum1P];
		}

		// 1P 기준, 이동 관련 키 세팅(상하)
		if (KeyManager::GetSingleton()->IsOnceKeyDown('J') && !(isChoice1P) || KeyManager::GetSingleton()->IsOnceKeyDown('Y') && !(isChoice1P))
		{
			ChoiceNum1P = (ChoiceNum1P + 1) % 4;

			currKeyFrameX1P = ChoiceNum1P;
			posX1P = selectposX[ChoiceNum1P];
			posY1P = selectposY[ChoiceNum1P];
		}

		// 1P 기준, 선택 관련 키 세팅
		if (KeyManager::GetSingleton()->IsOnceKeyDown('A') || KeyManager::GetSingleton()->IsOnceKeyDown('S'))
		{
			if (!isChoice1P)
			{
				currKeyFrameX1PIcon = 1;
				isChoice1P = true;
			}
			else
			{
				isChoice1P = false;
				currKeyFrameX1PIcon = 0;
			}
		}

		// 2P 기준, 이동 관련 키 세팅(좌우)
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD4) && !(isChoice2P) || KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD5) && !(isChoice2P))
		{
			if (ChoiceNum2P <= 0)
			{
				ChoiceNum2P = 3;
			}
			else ChoiceNum2P = ((ChoiceNum2P - 1) % 4);

			currKeyFrameX2P = ChoiceNum2P;
			posX2P = selectposX[ChoiceNum2P];
			posY2P = selectposY[ChoiceNum2P];
		}
		// 2P 기준, 이동 관련 키 세팅(상하)
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD6) && !(isChoice2P) || KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD8) && !(isChoice2P))
		{
			ChoiceNum2P = (ChoiceNum2P + 1) % 4;

			currKeyFrameX2P = ChoiceNum2P;

			posX2P = selectposX[ChoiceNum2P];
			posY2P = selectposY[ChoiceNum2P];
		}

		// 2P 기준, 선택 관련 키 세팅
		if (KeyManager::GetSingleton()->IsOnceKeyDown('O') || KeyManager::GetSingleton()->IsOnceKeyDown('P'))
		{
			if (!isChoice2P)
			{
				currKeyFrameX2PIcon = 3;
				isChoice2P = true;
			}
			else
			{
				isChoice2P = false;
				currKeyFrameX2PIcon = 2;
			}
		}


		if (isChoice1P&&isChoice2P)
		{
			if (ChoiceNum1P == 3)
			{
				ChoiceNum1P = rand() % 3;
			}

			if (ChoiceNum2P == 3)
			{
				ChoiceNum2P = rand() % 3;
			}

			isSelect = true;
		}

	}
}

void Select::Render(HDC hdc)
{
	if (isInit)
	{
		
		selectBg->FrameRender(hdc, posX , posY,
			0, 0, scale * 3.74);


		select->FrameRender(hdc, posX+10, posY-190,
			0, 0, scale*2);

		selectIcon1P->FrameRender(hdc, posX1P, posY1P,
			currKeyFrameX1PIcon, currKeyFrameY, scale * 1.8f);

		selectIcon2P->FrameRender(hdc, posX2P, posY2P ,
			currKeyFrameX2PIcon, currKeyFrameY, scale * 1.8f);


		charImg->FrameRender(hdc, posX+46, posY + 100,
			currKeyFrameX1P, currKeyFrameY, scale*2.2);
		
		charImg->FrameRender(hdc, posX+700, posY+100,
			currKeyFrameX2P, currKeyFrameY+1, scale*2.2);


		// 큰 이미지 아이콘
		selectIcon1P->FrameRender(hdc, posX-30 , posY -90 , 
			currKeyFrameX1PIcon, currKeyFrameY, scale * 9.4f);
		selectIcon2P->FrameRender(hdc, posX + 676, posY -90,
			currKeyFrameX2PIcon, currKeyFrameY, scale * 9.4f);
		
	}
}

Select::Select()
{
}


Select::~Select()
{
}
