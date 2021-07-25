
#include "Kof_1_Player.h"
#include "Image.h"
#include "Kof_2_Player.h"
#include "macroFuntion.h"

HRESULT Kof_1_Player::Init()
{

	posX = (WINSIZE_X / 4) * 1;
	posY = WINSIZE_Y / 2;

	HP = 100;
	img = new Image();


	hitBox = { 0,0,20,20 };		// 히트박스 초기화
	damagedBox = { 0,0,50,50 };	// 피격박스 초기화
	skillHitFrame = 0.0;			// 히트박스발동 프레임 초기화
	skillHitEndFrame = 0.0;		// 히트박스소멸 프레임 초기화
	activeHitBoxWidth = 0.0;		// 히트박스발동 반경너비 초기화
	activeHitBoxHeight = 0.0;		// 히트박스발동 반경높이 초기화
	activeHitBoxPosY = 0.0;		// 히트박스발동 반경높이 시작점 초기화

	hitFrameCount = 0;			// 히트 카운트 초기화
	isAttackFrame = false;		// 카운트 조절 함수 초기화



	if (charNum == 0)
	{
		img->Init("Image/Robert.bmp",
			posX, posY,
			1450,// 파일의 전체 너비 
			1040, // 파일이 전체 높이 
			frameSize[charNum],// 각 동작별 프레임 간격( EX-> 출력할 프레임의 간격이 80.6 이면 1170/80.6 의 값을 넣어둠 
			8,// 동작 갯수 (현재 서있기/뒤로 걷기 / 앞으로 걷기/ 발/ 주먹/죽기 )  
			true, RGB(7, 79, 151));
		damagedBoxPosX = 105.0;
		damagedBoxPosY = 18.0;
		damagedBoxWidth = 90.0;
		damagedBoxHeight = 198.0;


	}
	else if (charNum == 1)
	{
		img->Init("Image/Vice_01.bmp",
			posX, posY,
			5500,// 파일의 전체 너비 
			1040, // 파일이 전체 높이 
			frameSize[charNum],// 각 동작별 프레임 간격( EX-> 출력할 프레임의 간격이 80.6 이면 1170/80.6 의 값을 넣어둠 
			8,// 동작 갯수 (현재 서있기/뒤로 걷기 / 앞으로 걷기/ 발/ 주먹/죽기 )  
			true, RGB(108, 156, 114));
		damagedBoxPosX = 190.0;
		damagedBoxPosY = 50.0;
		damagedBoxWidth = 105.0;
		damagedBoxHeight = 180.0;
	}
	else if (charNum == 2)
	{
		img->Init("Image/Yasiro.bmp",
			posX, posY,
			7200,// 파일의 전체 너비 
			1136, // 파일이 전체 높이 
			frameSize[charNum],// 각 동작별 프레임 간격( EX-> 출력할 프레임의 간격이 80.6 이면 1170/80.6 의 값을 넣어둠 
			8,// 동작 갯수 (현재 서있기/뒤로 걷기 / 앞으로 걷기/ 발/ 주먹/죽기 )  
			true, RGB(2, 62, 100));
		damagedBoxPosX = 135.0;
		damagedBoxPosY = 10.0;
		damagedBoxWidth = 95.0;
		damagedBoxHeight = 215.0;
	}

	damagedBox;
	currKeyFrameX = 0;
	currKeyFrameY = 0;
	elapsedFrame = 0;
	scale = 1.0f;

	isAttack = false;
	isMove = false;
	isReverse = false;
	CheckReverse = isReverse;
	isDamaged = false;


	return S_OK;
}

void Kof_1_Player::Release()
{

	img->Release();
	delete img;
}

void Kof_1_Player::Update()
{
	// 각종 판정 및 판정에 따른 프레임 상태 변경
	if (!isStartMotion && !isDieMotion)
	{
		changeIndex(7);
		isAttack = true;
	}
	else if (isWin && !isWinMotion)
	{
		currKeyFrameX = 0;
		elapsedFrame = 0;
		changeIndex(7);
		isWinMotion = true;
		isAttack = true;
	}

	if (HP <= 0 && !isDieMotion || isDie && !isDieMotion)
	{
		currKeyFrameX = 0;
		elapsedFrame = 0;
		changeIndex(6);
		isStartMotion = false;
		isDie = true;
		isWin = true;
		isDieMotion = true;
		isWinMotion = true;
		isAttack = true;
	
	}

	elapsedFrame++;
	if (!isDieMotion || !isStartMotion)
	{
		if (elapsedFrame % 7 == 6 && currKeyFrameX < maxframe[charNum][maxframeIndex])
		{
			currKeyFrameX++;
			elapsedFrame = 0;
		}
		else if (elapsedFrame % 7 == 6 && currKeyFrameX == maxframe[charNum][maxframeIndex])
		{

			//공격 모션 모든 화면 다 출력 후 초기화 하려는 부분 

			if (isDie)
			{
				isStartMotion = true;
			}
			else
			{
				currKeyFrameX = 0;
				elapsedFrame = 0;
				if (isWin)
				{
					changeIndex(0);
				}
				if (!isStartMotion)
				{
					changeIndex(0);
					isAttack = false;
					isStartMotion = true;

				}
				if (maxframeIndex == 4 && isAttack || maxframeIndex == 3 && isAttack)
				{
					isAttack = false;//공격 프레임 출력 false 처리
					isMove = false; // 이동 중 공격 했을 경우, 이동 프레임 출력 false 처리
					changeIndex(0);

					// 캐릭별 피격 박스
					if (charNum == 0)
					{
						damagedBoxPosX = 115.0;
						damagedBoxWidth = 80.0;
					}
					else if (charNum == 1)
					{
						damagedBoxPosX = 190.0;
						damagedBoxWidth = 105.0;
					}
					else if (charNum == 2)
					{
						damagedBoxPosX = 110.0;
						damagedBoxWidth = 95.0;
					}
				}
				else if (maxframeIndex == 5)
				{
					isAttack = false;
					changeIndex(0);
				}
			}
		}
	}
	if (!isDie || !isWin)
	{

		damagedBox = { posX + damagedBoxPosX, posY + damagedBoxPosY, posX + damagedBoxPosX + damagedBoxWidth, posY + damagedBoxPosY + damagedBoxHeight };
		if (isReverse)
		{
			if (charNum == 2)
			{
				damagedBox = { posX + damagedBoxPosX + 25 , posY + damagedBoxPosY, posX + 25 + damagedBoxPosX + damagedBoxWidth, posY + damagedBoxPosY + damagedBoxHeight };
			}

		}


		if (!(isReverse))
		{
			if (charNum == 1)
			{
				damagedBox = { posX + damagedBoxPosX + 25 , posY + damagedBoxPosY, posX + 25 + damagedBoxPosX + damagedBoxWidth, posY + damagedBoxPosY + damagedBoxHeight };
			}

		}


		if (isAttackFrame)
		{
			hitFrameCount++; // 함수값이 참일때 카운트 시작 즉, 공격버튼이 눌려지면 카운트 시작
			if (hitFrameCount == skillHitFrame) // 공격이 들어가는 시점에서 히트 박스의 크기를 활성화
			{
				if (!(isReverse))
				{
					hitBox = { damagedBox.right, damagedBox.top + activeHitBoxPosY, damagedBox.right + activeHitBoxWidth, damagedBox.top + activeHitBoxHeight };
				}
				else if (isReverse)
				{
					hitBox = { damagedBox.left + activeHitBoxWidth , damagedBox.top + activeHitBoxPosY, damagedBox.left, damagedBox.top + activeHitBoxHeight };
				}


			}
			else if (hitFrameCount == skillHitEndFrame) // 공격이 회수되는 시점에서 히트박스의 축소
			{
				hitBox = { damagedBox.left + damagedBoxWidth, damagedBox.top, damagedBox.left + damagedBoxWidth, damagedBox.top };

				// 카운트 초기화
				hitFrameCount = 0;
				// 공격 카운트 관련 변수 초기화
				isAttackFrame = false;
			}
		}

		// 피격 설정
		if (isDamaged)
		{

			isDamaged = false;

			hitBox = { damagedBox.left + damagedBoxWidth, damagedBox.top, damagedBox.left + damagedBoxWidth, damagedBox.top };
			hitFrameCount = 0;
			currKeyFrameX = 0;
			elapsedFrame = 0;
			changeIndex(5);
			isAttack = true;
			if (!(isReverse))
			{
				posX -= 10;
				if (posX <= limitPosLeft[charNum] - 10)
					posX = limitPosLeft[charNum];
			}
			/*else if (isReverse)
			{
				posX += 30;
			}
*/
			isAttackFrame = false;

		}







		if (KeyManager::GetSingleton()->IsStayKeyDown('G') && !(isAttack))
		{
			directionValue = 1;
			if (!isMove) // moveCount가 0 일때만, 인덱스 값 변경 및 currKeyFrameX 및 elapsedFrame 초기화
			{
				directionValue = 1;
				CheckReverse = isReverse;
				if (isReverse)
				{
					currKeyFrameX = 0;
					elapsedFrame = 0;
					changeIndex(1);

				}
				else
				{
					currKeyFrameX = 0;
					elapsedFrame = 0;
					changeIndex(2);
				}

			}
			isMove = true;
			if (isMove) // 이동중 공격 되면 멈춰야 해서 조건문 달음
			{

				if (posX <= limitPosLeft[charNum] - 3)
					posX = limitPosLeft[charNum];
				else
				{
					if (isAttached == false)
						posX -= 3;
				}

			}
			if (CheckReverse != isReverse)
			{
				currKeyFrameX = 0;
				elapsedFrame = 0;
				CheckReverse = isReverse;
			}

			if (isReverse)
			{

				changeIndex(1);
			}
			else
			{
				changeIndex(2);
			}
		}
	}




	if (KeyManager::GetSingleton()->IsStayKeyDown('J') && !(isAttack))
	{
		directionValue = -1;
		if (!isMove)
		{
			directionValue = -1;
			if (isReverse)
			{
				currKeyFrameX = 0;
				elapsedFrame = 0;
				changeIndex(2);

			}
			else
			{
				currKeyFrameX = 0;
				elapsedFrame = 0;
				changeIndex(1);
			}
		}
		isMove = true;
		if (isMove)
		{
			if (isAttached == false)
				posX += 3;
		}
		if (CheckReverse != isReverse)
		{
			currKeyFrameX = 0;
			elapsedFrame = 0;
			CheckReverse = isReverse;
		}
		if (isReverse)
		{

			changeIndex(2);
		}
		else
		{

			changeIndex(1);
		}
	}



if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))
{

	if (!(isAttack))
	{
		currKeyFrameX = 0;
		elapsedFrame = 0;
		maxframeIndex = 4;
		img->SetKeyFrameWidth(frameSize[charNum]);
		currKeyFrameY = 4;
		isAttackFrame = true;

		if (!(isReverse))
		{
			if (charNum == 0)
			{
				skillHitFrame = 6;
				skillHitEndFrame = 20;
				activeHitBoxWidth = 90;
				activeHitBoxPosY = 30;
				activeHitBoxHeight = 50;
			}
			else if (charNum == 1)
			{
				skillHitFrame = 13;
				skillHitEndFrame = 27;
				activeHitBoxWidth = 127;
				activeHitBoxPosY = 30;
				activeHitBoxHeight = 48;
				damagedBoxPosX = 184.0;
				damagedBoxWidth = 125.0;
			}
			else if (charNum == 2)
			{
				skillHitFrame = 6;
				skillHitEndFrame = 17;
				activeHitBoxWidth = 75;
				activeHitBoxPosY = 60;
				activeHitBoxHeight = 82;
				damagedBoxPosX = 120.0;
			}
		}
		else if (isReverse)
		{
			if (charNum == 0)
			{
				skillHitFrame = 6;
				skillHitEndFrame = 20;
				activeHitBoxWidth = -90;
				activeHitBoxPosY = 30;
				activeHitBoxHeight = 50;
			}
			else if (charNum == 1)
			{
				skillHitFrame = 13;
				skillHitEndFrame = 27;
				activeHitBoxWidth = -135;
				activeHitBoxPosY = 30;
				activeHitBoxHeight = 48;
				damagedBoxPosX = 200.0;
				damagedBoxWidth = 125.0;
			}
			else if (charNum == 2)
			{
				skillHitFrame = 6;
				skillHitEndFrame = 17;
				activeHitBoxWidth = -60;
				activeHitBoxPosY = 60;
				activeHitBoxHeight = 82;
			}
		}
	}
	isAttack = true;

}

if (KeyManager::GetSingleton()->IsOnceKeyDown('S'))
{
	if (!(isAttack))// isAttack = false 일때, currKeyFrameX 및 elapsedFrame 초기화
	{
		currKeyFrameX = 0;
		elapsedFrame = 0;
		changeIndex(3);

		isAttackFrame = true;
		if (!(isReverse))
		{
			if (charNum == 0)
			{
				skillHitFrame = 9;
				skillHitEndFrame = 39;
				activeHitBoxWidth = 110.0;
				activeHitBoxPosY = 67.0;
				activeHitBoxHeight = 105.0;
				damagedBoxPosX = 70.0;
				damagedBoxWidth = 110.0;
			}
			else if (charNum == 1)
			{
				skillHitFrame = 49;
				skillHitEndFrame = 56;
				activeHitBoxWidth = 133.0;
				activeHitBoxPosY = 45.0;
				activeHitBoxHeight = 75.0;
				damagedBoxPosX = 240.0;
				damagedBoxWidth = 120.0;
			}
			else if (charNum == 2)
			{
				skillHitFrame = 17;
				skillHitEndFrame = 23;
				activeHitBoxWidth = 145.0;
				activeHitBoxPosY = 50.0;
				activeHitBoxHeight = 80.0;
				damagedBoxPosX = 175.0;
				damagedBoxWidth = 75.0;

			}
		}
		else if (isReverse)
		{
			if (charNum == 0)
			{
				skillHitFrame = 9;
				skillHitEndFrame = 39;
				activeHitBoxWidth = -110.0;
				activeHitBoxPosY = 67.0;
				activeHitBoxHeight = 105.0;
				damagedBoxPosX = 125.0;
				damagedBoxWidth = 100.0;
			}
			else if (charNum == 1)
			{
				skillHitFrame = 49;
				skillHitEndFrame = 56;
				activeHitBoxWidth = -133.0;
				activeHitBoxPosY = 45.0;
				activeHitBoxHeight = 75.0;
				damagedBoxPosX = 140.0;
				damagedBoxWidth = 120.0;

			}
			else if (charNum == 2)
			{
				skillHitFrame = 17;
				skillHitEndFrame = 23;
				activeHitBoxWidth = -145.0;
				activeHitBoxPosY = 50.0;
				activeHitBoxHeight = 80.0;
				damagedBoxPosX = 70.0;
				damagedBoxWidth = 75.0;
			}
		}

	}
	isAttack = true;
}

if (KeyManager::GetSingleton()->IsOnceKeyUp('G') && !(isAttack) || KeyManager::GetSingleton()->IsOnceKeyUp('J') && !(isAttack))
{
	// 무브 키 손에서 떼었을때, 인덱스 값 서있기로 변경, moveCount 값 초기화 
	if (!isAttack)
	{
		isAttached = false;
		currKeyFrameX = 0;
		elapsedFrame = 0;
		changeIndex(0);
		isMove = false;
	}
}


}

void Kof_1_Player::Render(HDC hdc, HDC hdc2)
{
	if (img)
	{

		if (isReverse)
		{
			img->FrameRender(hdc, posX, posY,
				currKeyFrameX, currKeyFrameY, scale, isReverse);


			if (charNum == 2)
			{
				img->CopyRender(hdc, hdc2, posX - 250, posY - 60, scale);
			}
			else
			{
				img->CopyRender(hdc, hdc2, posX, posY - 30, scale);
			}
		}
		else
		{

			if (charNum == 2)
			{
				img->FrameRender(hdc2, posX - 250, posY - 60,
					currKeyFrameX, currKeyFrameY, scale, isReverse);
			}
			else
			{
				img->FrameRender(hdc2, posX, posY - 30,
					currKeyFrameX, currKeyFrameY, scale, isReverse);
			}
			//RenderRect(hdc2, damagedBox);
			//RenderRect(hdc2, hitBox);
		}
	}
}

void Kof_1_Player::changeIndex(int _index)
{

	maxframeIndex = _index;
	img->SetKeyFrameWidth(frameSize[charNum]);
	currKeyFrameY = _index;

}

void Kof_1_Player::SetDamageFrame()
{
	hitBox = { damagedBox.left + damagedBoxWidth, damagedBox.top, damagedBox.left + damagedBoxWidth, damagedBox.top };
	hitFrameCount = 0;
	isAttackFrame = false;
}

Kof_1_Player::Kof_1_Player()
{
}


Kof_1_Player::~Kof_1_Player()
{
}