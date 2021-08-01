#pragma once
#include "GameNode.h"
class Image;
/// <summary>
/// ResultFont : ���� ��� ������ �˷��ִ� ���ڸ� ǥ���Ѵ�.
/// </summary>
class ResultFont : public GameNode
{
private:

	float posX;
	float posY;
	float scale;
	int currKeyFrameX;
	int currKeyFrameY;


	Image* Player_1p_win;
	Image* Player_2p_win;
	Image* KO;
	Image* Time_Over;
	Image* Draw;
	int resultNum = 0;

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;


	int GetResultNum() { return resultNum; }
	void SetResultNum(int _resultNum) { resultNum = _resultNum; }

	ResultFont();
	~ResultFont();
};

