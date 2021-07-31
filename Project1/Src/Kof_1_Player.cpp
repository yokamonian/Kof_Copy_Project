
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


	hitBox = { 0,0,20,20 };		// ��Ʈ�ڽ� �ʱ�ȭ
	damagedBox = { 0,0,50,50 };	// �ǰݹڽ� �ʱ�ȭ
	skillHitFrame = 0.0;			// ��Ʈ�ڽ��ߵ� ������ �ʱ�ȭ
	skillHitEndFrame = 0.0;		// ��Ʈ�ڽ��Ҹ� ������ �ʱ�ȭ
	activeHitBoxWidth = 0.0;		// ��Ʈ�ڽ��ߵ� �ݰ�ʺ� �ʱ�ȭ
	activeHitBoxHeight = 0.0;		// ��Ʈ�ڽ��ߵ� �ݰ���� �ʱ�ȭ
	activeHitBoxPosY = 0.0;		// ��Ʈ�ڽ��ߵ� �ݰ���� ������ �ʱ�ȭ

	hitFrameCount = 0;			// ��Ʈ ī��Ʈ �ʱ�ȭ
	isAttackFrame = false;		// ī��Ʈ ���� �Լ� �ʱ�ȭ



	if (charNum == 0)
	{
		img->Init("Image/Robert.bmp",
			posX, posY,
			1450,// ������ ��ü �ʺ� 
			1040, // ������ ��ü ���� 
			frameSize[charNum],// �� ���ۺ� ������ ����( EX-> ����� �������� ������ 80.6 �̸� 1170/80.6 �� ���� �־�� 
			8,// ���� ���� (���� ���ֱ�/�ڷ� �ȱ� / ������ �ȱ�/ ��/ �ָ�/�ױ� )  
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
			5500,// ������ ��ü �ʺ� 
			1040, // ������ ��ü ���� 
			frameSize[charNum],// �� ���ۺ� ������ ����( EX-> ����� �������� ������ 80.6 �̸� 1170/80.6 �� ���� �־�� 
			8,// ���� ���� (���� ���ֱ�/�ڷ� �ȱ� / ������ �ȱ�/ ��/ �ָ�/�ױ� )  
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
			7200,// ������ ��ü �ʺ� 
			1136, // ������ ��ü ���� 
			frameSize[charNum],// �� ���ۺ� ������ ����( EX-> ����� �������� ������ 80.6 �̸� 1170/80.6 �� ���� �־�� 
			8,// ���� ���� (���� ���ֱ�/�ڷ� �ȱ� / ������ �ȱ�/ ��/ �ָ�/�ױ� )  
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
	// ���� ���� �� ������ ���� ������ ���� ����
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

			//���� ��� ��� ȭ�� �� ��� �� �ʱ�ȭ �Ϸ��� �κ� 

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
					isAttack = false;//���� ������ ��� false ó��
					isMove = false; // �̵� �� ���� ���� ���, �̵� ������ ��� false ó��
					changeIndex(0);

					// ĳ���� �ǰ� �ڽ�
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

		// �ǰ� ����
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
	if (!(isAttack))// isAttack = false �϶�, currKeyFrameX �� elapsedFrame �ʱ�ȭ
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