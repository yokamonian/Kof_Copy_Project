#pragma once
#include "GameNode.h"

class Kof_1_Player;
class Kof_2_Player;
class Image;
class BackGround;
class Timer;
class Select;
class HealthBar;
class ResultFont;
class Title;
class Camera;
/// <summary>
///	MainGame : 씬 매니저 클래스가 만들어지지 않은 프로젝트로써, 게임플레이의 모든 씬이 들어있는 클래스.
/// </summary>

class MainGame : public GameNode
{
private:
	bool isInit;
	HANDLE hTimer;

	Image* backBuffer;
	Image* CopyBuffer1P;
	Image* CopyBuffer2P;
	Image* CopyBufferBG;
	Timer* countDown;

	Title* title;
	BackGround* horz;
	
	HealthBar* hp_bar;
	ResultFont* resultFont;
	Select* select;
	Camera* camera;
	Kof_1_Player* player1;
	Kof_2_Player* player2;

	int char1PNum;
	int char2PNum;
	bool isSelect=false;
	bool isTitle = false;
	bool isMainAttached = false;
	int ResultNum = 0;
	bool isTwins = false;
	bool isEnd = false;
	bool isDraw = false;
	int endCount = 0;

	float betwinDistance[2][9] = { { 95.0f, -5.0f, 85.0f, 215.0f, 320.0f, 195.0f, 105.0f, 5.0f, 95.0f },
									{ -90.0f, -210.0f, -115.0f, 20.0f, -100.0f, 10.0f, -80.0f, -200.0f, -90.0f } };
	float endPosX[2][3] = { {-87, -205, -104}, {WINSIZE_X -210,WINSIZE_X -315,WINSIZE_X -230} };

	int betwinDistanceNum;
	
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	//virtual HRESULT cInit();

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);
	
	int VsResultNum(int _printTime, int hp1P, int hp2P);
	//bool CheckTimeOver(_printTim)
	int VsCharNum(int Char1P, int Char2P);



	MainGame();
	~MainGame();
};

