#include "Kof_2_Player.h"
#include "Image.h"
#include "Kof_1_Player.h"
#include "macroFuntion.h"



HRESULT Kof_2_Player::Init()
{

	posX = (WINSIZE_X / 4) * 3;
	posY = WINSIZE_Y / 2;

	HP = 100;
	img = new Image();
	playerHp = 100;

	hpBar = { 150, 150, 200, 50 };
	// �ǰݹڽ� �ʱ�ȭ
	hitBox = { 1500,0,50,50 };
	damagedBox = { 1500,0,50,50 };	// �ǰݹڽ� �ʱ�ȭ
	if (charNum == 0)
	{
		img->Init("Image/Robert.bmp",
			posX, posY,
			1450,// ������ ��ü �ʺ� 
			1040, // ������ ��ü ���� 
			frameSize[charNum],// �� ���ۺ� ������ ����( EX-> ����� �������� ������ 80.6 �̸� 1170/80.6 �� ���� �־�� 
			8,// ���� ���� (���� ���ֱ�/�ڷ� �ȱ� / ������ �ȱ�/ ��/ �ָ�/�ױ� )  
			true, transColor[transColorNum][charNum]);// RGB(7, 79, 151)
		damagedBoxPosX = 105.0;
		damagedBoxPosY = 18.0;
		damagedBoxWidth = 90.0;
		damagedBoxHeight = 198.0;
	}
	else if (charNum == 1)
	{
		img->Init("Image/Vice_01.bmp",
			posX, posY,
			5500,// ������ ��ü �ʺ� 
			1040, // ������ ��ü ���� 
			frameSize[charNum],// �� ���ۺ� ������ ����( EX-> ����� �������� ������ 80.6 �̸� 1170/80.6 �� ���� �־�� 
			8,// ���� ���� (���� ���ֱ�/�ڷ� �ȱ� / ������ �ȱ�/ ��/ �ָ�/�ױ� )  
			true, transColor[transColorNum][charNum]);
		damagedBoxPosX = 203.0;
		damagedBoxPosY = 50.0;
		damagedBoxWidth = 105.0;
		damagedBoxHeight = 180.0;
	}
	else if (charNum == 2)
	{
		img->Init("Image/Yasiro.bmp",
			posX, posY,
			7200,// ������ ��ü �ʺ� 
			1136, // ������ ��ü ���� 
			frameSize[charNum],// �� ���ۺ� ������ ����( EX-> ����� �������� ������ 80.6 �̸� 1170/80.6 �� ���� �־�� 
			8,// ���� ���� (���� ���ֱ�/�ڷ� �ȱ� / ������ �ȱ�/ ��/ �ָ�/�ױ� )  
			true, transColor[transColorNum][charNum]);
		damagedBoxPosX = 135.0;
		damagedBoxPosY = 10.0;
		damagedBoxWidth = 95.0;
		damagedBoxHeight = 215.0;
	}
	damagedBox;
	CheckReverse = true;
	currKeyFrameX = 0;
	currKeyFrameY = 0;
	elapsedFrame = 0;
	scale = 1.0f;

	isAttack = false;
	isMove = false;
	isReverse = true;

	return S_OK;
}

void Kof_2_Player::Release()
{
	img->Release();
	delete img;
}

void Kof_2_Player::Update()
{

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


			if (isDie)
			{
				isStartMotion = true;
			}
			else {
				currKeyFrameX = 0;
				elapsedFrame = 0;

				if (isWin && !isDie)
				{
					changeIndex(0);
				}
				if (!isStartMotion)
				{
					changeIndex(0);
					isAttack = false;
					isStartMotion = true;

				}

				//���� ��� ��� ȭ�� �� ��� �� �ʱ�ȭ �Ϸ��� �κ� 
				if (maxframeIndex == 4 && isAttack || maxframeIndex == 3 && isAttack)
				{

					isAttack = false;//���� ������ ��� false ó��
					isMove = false;
					changeIndex(0);

					if (charNum == 0)
					{
						
					}
					else if (charNum == 1)
					{
						damagedBoxPosX = 203.0;
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
		hpBar = { 150, 150, playerHp * 2, 50 };

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
				damagedBox = { posX + damagedBoxPosX - 50 , posY + damagedBoxPosY, posX - 50 + damagedBoxPosX + damagedBoxWidth, posY + damagedBoxPosY + damagedBoxHeight };
			}
		}

		// ���� ��ư�� ������ �� Ȱ��ȭ �Ǵ� �Լ� - ��Ʈ �ڽ� ���� �� ����
		if (isAttackFrame)
		{
			hitFrameCount++; // �Լ����� ���϶� ī��Ʈ ���� ��, ���ݹ�ư�� �������� ī��Ʈ ����

			if (hitFrameCount == skillHitFrame) // ������ ���� �������� ��Ʈ �ڽ��� ũ�⸦ Ȱ��ȭ
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
			else if (hitFrameCount == skillHitEndFrame) // ������ ȸ���Ǵ� �������� ��Ʈ�ڽ��� ���
			{
				hitBox = { damagedBox.left + damagedBoxWidth, damagedBox.top, damagedBox.left + damagedBoxWidth, damagedBox.top };
				// ī��Ʈ �ʱ�ȭ
				hitFrameCount = 0;
				// ���� ī��Ʈ ���� ���� �ʱ�ȭ
				isAttackFrame = false;
			}
		}
		if (isDamaged)
		{

			isDamaged = false;
			currKeyFrameX = 0;
			elapsedFrame = 0;
			changeIndex(5);
			isAttack = true;
			if (isReverse)
			{
				posX += 10;
				if (posX >= limitPosRight[charNum] + 10)
					posX = limitPosRight[charNum];
			}
			/*else if (isReverse)
			{
				posX += 30;
			}
*/
		}

		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD4) && !(isAttack))
		{

			if (!isMove) // moveCount�� 0 �϶���, �ε��� �� ���� �� currKeyFrameX �� elapsedFrame �ʱ�ȭ
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
			if (isMove) // �̵��� ���� �Ǹ� ����� �ؼ� ���ǹ� ����
			{
				if (isAttached == false)
					posX -= 3;
			}
			else
			{
				if (posX <= -190)
					posX = -190;
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

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD6) && !(isAttack))
	{
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
			if (isMove)
			{
				if (posX >= limitPosRight[charNum] + 3)
					posX = limitPosRight[charNum];
				else
				{
					if (isAttached == false)
						posX += 3;
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
				changeIndex(2);
			}
			else
			{
				changeIndex(1);
			}
		}

	}


if (KeyManager::GetSingleton()->IsOnceKeyDown('O'))
{

	if (!(isAttack))
	{
		currKeyFrameX = 0;
		elapsedFrame = 0;
		changeIndex(4);
		isAttackFrame = true;

		if (isReverse)
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
				activeHitBoxWidth = -75;
				activeHitBoxPosY = 60;
				activeHitBoxHeight = 82;
			}
		}
		else if (!(isReverse))
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
				activeHitBoxWidth = 130;
				activeHitBoxPosY = 20;
				activeHitBoxHeight = 40;
				damagedBoxPosX = 140.0;
				damagedBoxWidth = 125.0;
			}
			else if (charNum == 2)
			{
				skillHitFrame = 6;
				skillHitEndFrame = 17;
				activeHitBoxWidth = 75;
				activeHitBoxPosY = 60;
				activeHitBoxHeight = 82;
			}
		}
	}
	isAttack = true;
}

if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
{
	if (!(isAttack))// isAttack = false �϶�, currKeyFrameX �� elapsedFrame �ʱ�ȭ
	{
		currKeyFrameX = 0;
		elapsedFrame = 0;
		changeIndex(3);
		isAttackFrame = true;
		if (isReverse)
		{
			if (charNum == 0)
			{
				skillHitFrame = 6;
				skillHitEndFrame = 27;
				activeHitBoxWidth = -110.0;
				activeHitBoxPosY = 67.0;
				activeHitBoxHeight = 105.0;
				damagedBoxPosX = 125.0;
				damagedBoxWidth = 100.0;
			}
			else if (charNum == 1)
			{
				skillHitFrame = 34;
				skillHitEndFrame = 41;
				activeHitBoxWidth = -138.0;
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
				damagedBoxPosX = 65.0;
				damagedBoxWidth = 75.0;
			}
		}

		else if (!(isReverse))
		{
			if (charNum == 0)
			{
				skillHitFrame = 6;
				skillHitEndFrame = 27;
				activeHitBoxWidth = 110.0;
				activeHitBoxPosY = 67.0;
				activeHitBoxHeight = 105.0;
				damagedBoxPosX = 70.0;
				damagedBoxWidth = 110.0;
			}
			else if (charNum == 1)
			{
				skillHitFrame = 34;
				skillHitEndFrame = 56;
				activeHitBoxWidth = 133.0;
				activeHitBoxPosY = 45.0;
				activeHitBoxHeight = 75.0;
				damagedBoxPosX = 258.0;
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
	}
	isAttack = true;
}

if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_NUMPAD4) || KeyManager::GetSingleton()->IsOnceKeyUp(VK_NUMPAD6))
{
	// ���� Ű �տ��� ��������, �ε��� �� ���ֱ�� ����, moveCount �� �ʱ�ȭ 
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


void Kof_2_Player::Render(HDC hdc, HDC hdc2)
{
	if (img)
	{

		if (isReverse)
		{
			img->FrameRender(hdc, posX, posY,
				currKeyFrameX, currKeyFrameY, scale, isReverse, transColorNum);

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

		}
		//RenderRect(hdc2, damagedBox);
		//RenderRect(hdc2, hitBox);
	}


}

void Kof_2_Player::changeIndex(int _index)
{
	maxframeIndex = _index;
	img->SetKeyFrameWidth(frameSize[charNum]);
	currKeyFrameY = _index;

}

void Kof_2_Player::SetDamageFrame()
{
	hitBox = { damagedBox.left + damagedBoxWidth, damagedBox.top, damagedBox.left + damagedBoxWidth, damagedBox.top };
	hitFrameCount = 0;
	isAttackFrame = false;
}

Kof_2_Player::Kof_2_Player()
{
}


Kof_2_Player::~Kof_2_Player()
{
}