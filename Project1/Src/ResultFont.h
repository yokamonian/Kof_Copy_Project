#pragma once
#include "GameNode.h"
class Image;
/// <summary>
/// ResultFont : 게임 결과 판정을 알려주는 글자를 표시한다.
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

