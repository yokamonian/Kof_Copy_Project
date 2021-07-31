#include "MainGame.h"
#include "Image.h"
#include "Kof_1_Player.h"
#include "Kof_2_Player.h"
#include "BackGround.h"
#include "Select.h"
#include "Timer.h"
#include "HealthBar.h"
#include "ResultFont.h"
#include "Title.h"
#include "Camera.h"
//#include "Sound.h"



HRESULT MainGame::Init()
{
	// backBuffer:; 1P, 2P간 위치값 변경에 따른 화면 이동을 위해 두개의 buffer 사용.
	if (!isSelect)
	{
		backBuffer = new Image();
		backBuffer->Init(WINSIZE_X, WINSIZE_Y);
		

		CopyBuffer1P = new Image();
		CopyBuffer1P->Init(WINSIZE_X, WINSIZE_Y);
		CopyBuffer1P->SetIsTrans(true);

		CopyBuffer2P = new Image();
		CopyBuffer2P->Init(WINSIZE_X, WINSIZE_Y);
		CopyBuffer2P->SetIsTrans(true);
		CopyBufferBG = new Image();
		CopyBufferBG->Init(WINSIZE_X, WINSIZE_Y);

		title = new Title();
		title->Init();
		select = new Select();
		select->Init();

		KeyManager::GetSingleton()->Init();

		hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
		SetTimer(g_hWnd, 1, 1000, NULL);
		SetTimer(g_hWnd, 2, 1000, NULL);

		ResultNum = 0;

	}
	// BG
	else {
		resultFont = new ResultFont();
		resultFont->Init();
		horz = new BackGround();
		horz->Init();
		char1PNum = select->GetChoiceNum1P();
		char2PNum = select->GetChoiceNum2P();

		countDown = new Timer();
		countDown->Init();

		hp_bar = new HealthBar();
		hp_bar->SetFace_x(select->GetChoiceNum1P());
		hp_bar->SetFace_x2(select->GetChoiceNum2P());
		hp_bar->Init();


		player1 = new Kof_1_Player();
		player1->SetCharNum(select->GetChoiceNum1P());
		player1->Init();

		player1->SetPosX(WINSIZE_X - 900);
		player1->SetPosY(WINSIZE_Y - 300);
		player1->SetScale(2.1f);
		
		CopyBuffer1P->SetTransColor(player1->GetTransColor());
		
		player2 = new Kof_2_Player();
		player2->SetCharNum(select->GetChoiceNum2P());
		if (select->GetChoiceNum1P() == select->GetChoiceNum2P())
		{
			player2->SetTransColorNum(1);
		}
		player2->Init();
		player2->SetPosX(WINSIZE_X - 500);
		player2->SetPosY(WINSIZE_Y - 300);
		player2->SetScale(2.1f);
		
		CopyBuffer2P->SetTransColor(player2->GetTransColor());
		camera = new Camera();
		camera->Init();


		betwinDistanceNum = VsCharNum(char1PNum, char2PNum);


		//camera->SetCharposX(player1->GetPosX());
	}
	isInit = true;

	return S_OK;
}

void MainGame::Release()
{
	if (!isSelect)
	{
		title->Release();
		delete title;
		
		select->Release();
		delete select;
		
		KillTimer(g_hWnd, 0);
		KillTimer(g_hWnd, 1);
		

		KeyManager::GetSingleton()->Release();
		KeyManager::GetSingleton()->ReleaseSingleton();

		CopyBuffer1P->Release();
		delete CopyBuffer1P;
		CopyBuffer2P->Release();
		delete CopyBuffer2P;

		CopyBufferBG ->Release();
		delete CopyBufferBG;

		backBuffer->Release();
		delete backBuffer;
	}
	else {

		hp_bar->Release();
		delete hp_bar;


		player1->Release();
		delete player1;
		countDown->Release();
		delete countDown;
		player2->Release();
		delete player2;
	
		resultFont->Release();
		delete resultFont;

		horz->Release();
		delete horz;

		camera->Release();
			delete camera;
		
	}
}

void MainGame::Update()
{
	// 캐릭터 선택 완료 시
	if (isSelect)
	{
		if (player1)	player1->Update();
		camera->SetCharposX((float)player1->GetPosX());
		camera->Update();
		horz->SetcamerPosX(camera->GetPosLeft());// 백그라운드
		if (player2)	player2->Update();
		if (ResultNum == 0)
		{
			ResultNum = VsResultNum(countDown->GetPrintTime(), player1->GetHP(), player2->GetHP());
			if (horz) horz->Update();
			if (countDown) countDown->Update();
			
			
			player1->SetVsCharPosX(player2->GetPosX());
			hp_bar->SetHp_1P(player1->GetHP());


			player2->SetVsCharPosX(player1->GetPosX());
			hp_bar->SetHp_2P(player2->GetHP());

			if (player1->GetIsAttack())
			{
				if (player1->GetIsReverse() == false)
				{
					if (player1->GetHitBoxPos().right > player2->GetDamagedBoxPos().left)
					{
						// 피격시 실행문
						if ((player1->GetIsAttackFrame()))
						{
							player2->SetIsDamaged(true);
							player2->SetHP(player2->GetHP() - 10);
							player1->SetDamageFrame();
						}
						else if (!(player1->GetIsAttackFrame()))
						{
							player2->SetIsDamaged(false);
						}


					}
				}
				else if (player1->GetIsReverse())
				{
					if (player1->GetHitBoxPos().left < player2->GetDamagedBoxPos().right)
					{
						if ((player1->GetIsAttackFrame()))
						{
							player2->SetIsDamaged(true);
							player2->SetHP(player2->GetHP() - 10);
							player1->SetDamageFrame();
						}
						else if (!(player1->GetIsAttackFrame()))
						{
							player2->SetIsDamaged(false);
						}
					}
				}
			}
			if (player2->GetIsAttack())
			{
				if (player2->GetIsReverse())
				{
					if (player2->GetHitBoxPos().left < player1->GetDamagedBoxPos().right)
					{
						// 피격시 실행문
						if ((player2->GetIsAttackFrame()))
						{
							player1->SetIsDamaged(true);
							player1->SetHP(player1->GetHP() - 10);
							player2->SetDamageFrame();
						}
						else if (!(player2->GetIsAttackFrame()))
						{
							player1->SetIsDamaged(false);
						}
					}
				}
				else if (player2->GetIsReverse() == false)
				{
					if (player2->GetHitBoxPos().right > player1->GetDamagedBoxPos().left)
					{
						if ((player2->GetIsAttackFrame()))
						{
							player1->SetIsDamaged(true);
							player1->SetHP(player1->GetHP() - 10);
							player2->SetDamageFrame();
						}
						else if (!(player2->GetIsAttackFrame()))
						{
							player1->SetIsDamaged(false);
						}
					}
				}
			}
			
			if (!((player1->GetIsMove()) && (player2->GetIsMove())))// 플레이어가 무브 버튼을 안누를 상태 동시에 
			{
				if (isMainAttached)
				{
					if (!(player1->GetIsMove()))
					{
						player2->SetIsAttached(false);
						player1->SetIsAttached(false);
					}

					if (!(player2->GetIsMove()))
					{
						player2->SetIsAttached(false);
						player1->SetIsAttached(false);
					}

					
					isMainAttached = false;
				}

				if (!isMainAttached)
				{
					if (player1->GetIsMove()) // 1p 만 누른 상태 
					{
						if (player1->GetDirectionValue() == -1)// 플레이어 방향이 오른 쪽으로 가는 방향 6번 버튼  
						{
							if (player1->GetPosX() > player2->GetPosX() + betwinDistance[1][betwinDistanceNum])// 부딪힘; 
							{
								if (player2->GetDirectionValue() == 1)
								{
									player1->SetPosX(player2->GetPosX() + (betwinDistance[1][betwinDistanceNum]/2));
								}
								if (player2->GetPosX() > endPosX[1][char2PNum])// 2p 가 오른 쪽 벽에 부딪힌 상태 
								{
									player2->SetPosX(endPosX[1][char2PNum] + 3);// 2p 값 고정 
									player1->SetIsAttached(true);// 1P도 움직이지 못하게 이동 
								}
								else
								{
									player2->SetPosX(player2->GetPosX() + 3);//벽에 안닿았을때, 이동 처리 2P만 움직임 ( 1P는 무브키로 이동하기에 고칠 필요 없음)
								}
							}
						}


					}

					if (player2->GetIsMove())//
					{
						if (player2->GetDirectionValue() == 1)// 2피 방향이 왼쪽 
						{
							if (player2->GetPosX() < player1->GetPosX() + betwinDistance[0][betwinDistanceNum])// 캐릭터 끼리 부딪힘
							{
								if (player1->GetDirectionValue() == -1)
								{
									player2->SetPosX(player1->GetPosX() + (betwinDistance[0][betwinDistanceNum]/2));
								}

								if (player1->GetPosX() < endPosX[0][char1PNum])// 
								{
									player1->SetPosX(endPosX[0][char1PNum] - 3);
									player2->SetIsAttached(true);
								}
								else
								{
									player1->SetPosX(player1->GetPosX() - 3);//벽에 안닿았을때, 이동 처리 1P만 움직임 ( 2P는 무브키로 이동하기에 고칠 필요 없음)
								}
							}

						}

						


					}

				}

			}
			else
			{
				if ((player1->GetDamagedBoxPos().right > player2->GetDamagedBoxPos().left)
					|| (player2->GetDamagedBoxPos().left < player1->GetDamagedBoxPos().right))
				{
					player1->SetIsAttached(true);
					player2->SetIsAttached(true);
					isMainAttached = true;
				}

				if (isMainAttached)
				{
					if (player1->GetDirectionValue() == 1)
					{
						player2->SetIsAttached(false);
						player1->SetIsAttached(false);
					}

					if ( player2->GetDirectionValue() == -1)
					{
						player2->SetIsAttached(false);
						player1->SetIsAttached(false);
					}

					
				}

			}
			
			
			ResultNum = VsResultNum(countDown->GetPrintTime(), player1->GetHP(), player2->GetHP());
			resultFont->SetResultNum(ResultNum);
		}
		hp_bar->SetHp_1P(player1->GetHP());
		hp_bar->SetHp_2P(player2->GetHP());
		// 1P 승리 시
		if (ResultNum == 1 || ResultNum == 4)
		{
			player1->SetIsWin(true);
			if (ResultNum == 4)
			{
				player2->SetIsDie(true);
			}
			title->SetIsEnd1P(true);
			isEnd = true;

		}
		// 2P 승리 시
		else if(ResultNum == 2 || ResultNum == 5)
		{
			player2->SetIsWin(true);
			if (ResultNum == 5)
			{
				player1->SetIsDie(true);
			}
			title->SetIsEnd2P(true);
			isEnd = true;

		}
		// 드로우 판정 시
		else if (ResultNum == 3 || ResultNum == 6)
		{
			player2->SetIsWin(true);
			player1->SetIsWin(true);
			title->SetIsDraw(true);
			isEnd = true;
		}


		hp_bar->Update();

		if (endCount >= 4)
		{
			title->Update();
		}

	}
	else if(!isSelect)
	{
		if (!isSelect)
		{
			if (title->GetIsTitle())
			{ 
				select->Update();			
				isSelect = select->GetIsSelect();
			}
			else
			{
				if (title) title->Update();
			}
			
		}

		if (isSelect)
		{
			Init();
		}

	}


	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	if (!isSelect)
	{
		if (title->GetIsTitle())
		{
			if (select)	select->Render(backBuffer->GetMemDC());
		}
		else
		{
		if (title) title->Render(backBuffer->GetMemDC());
		}
	}
	else if(isSelect && endCount < 4)
	{
		if (horz)	horz->Render(CopyBufferBG->GetMemDC());	
		CopyBufferBG->Render(backBuffer->GetMemDC(), 0, 0);
		if (player1)	player1->Render(CopyBuffer1P->GetMemDC(), backBuffer->GetMemDC());
		if (player2)	player2->Render(CopyBuffer2P->GetMemDC(), backBuffer->GetMemDC());
		if (hp_bar) hp_bar->Render(backBuffer->GetMemDC());
		if (countDown) countDown->Render(backBuffer->GetMemDC());
		if (resultFont) resultFont->Render(backBuffer->GetMemDC());
		if (horz)	horz->Render(CopyBufferBG->GetMemDC());
		
	}

	if (endCount >= 4)
	{
		title->Render(backBuffer->GetMemDC());
	}

	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		if (isInit)
			this->Update();

		if (wParam == 1)
		{
			if (countDown)
			{
				if (countDown->GetPrintTime() > 0)
					countDown->SetPrintTime(countDown->GetPrintTime() - 1);
				else
					countDown->SetPrintTime(0);
			}
		}
		if (wParam == 2)
		{
			if (isEnd)
			{
				endCount++;
			}

		}

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (isInit)
			this->Render(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

int MainGame::VsResultNum(int _printTime, int hp1P, int hp2P)
{
	//0-> 아직 승부 결과 없음;
	// 1 -> 시간전 1P 승리
	// 2 -> 시간전 2P 승리
	// 3 -> 시간전 무승부
	// 4 -> 시간 후  1P 승리
	// 5-> 시간후 1P 승리
	// 6 -> 시간후 무승부


	if (_printTime > 0)
	{
		if (hp1P > 0)
		{
			if (hp2P <= 0)
			{
				return 1; 
			}
		}
		else
		{
		
			if (hp2P > 0)
			{
				return 2;
			}
			else return 3;
			
		}
	}
	else
	{
		if (hp1P > hp2P)
		{
			return 4;

		}
		else if (hp1P < hp2P)
		{

			return 5;

		}
		else if (hp1P == hp2P) return 6;
	}

	return 0;
}

int MainGame::VsCharNum(int Char1P, int Char2P)
{
	if (Char1P == 0)
	{
		if (Char2P == 0) return 0; 
		else if (Char2P == 1) return 1;
		else return 2;
	}
	else if (Char1P == 1)
	{
		if (Char2P == 0) return 3;
		else if (Char2P == 1) return 4;
		else return 5;
	}
	else if (Char1P == 2)
	{
		if (Char2P == 0) return 6;
		else if (Char2P == 1) return 7;
		else return 8;
	}
}



MainGame::MainGame()
	: isInit(false)
{
}


MainGame::~MainGame()
{
}
