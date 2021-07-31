
#pragma once
#include "GameNode.h"

class Image;
/// <summary>
/// Timer : ���� �÷��� ��, ī��Ʈ�Ǵ� Ÿ�̸� Ŭ����
/// </summary>
class Timer : public GameNode
{
private:
	float posX;				// x�� ��ǥ
	float posY;				// y�� ��ǥ
	Image* CountDown_Num;	// Ÿ�̸� ���� ���� �̹���
	
	int currKeyFrameX2;
	int currKeyFrameY2;
	COLORREF transColor[3] = { RGB(63, 72, 204) ,RGB(64, 64, 192) ,RGB(167, 182, 93) };

	int elapsedFrame;
	int printTime;
	int CountNum;
	float scale;
public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetPosX(float x) { posX = x; }
	void SetPosY(float y) { posY = y; }
	void SetScale(float scale) { this->scale = scale; }
	void SetPrintTime(int _printTime) { printTime = _printTime; }
	int GetPrintTime() { return printTime; }
	void SetCountNum(int _CountNum) { CountNum = _CountNum; }

	Timer();
	~Timer();


};

