#pragma once
#include "GameNode.h"
#include "pch.h"

class Image;
class Title : public GameNode
{
private:
	float posX;
	float posY;
	int currKeyFrameX;
	int currKeyFrameY;
	bool isintro = false;
	bool isTitleMaXFrame = false;
	bool isTitle = false;
	int elapsedFrame = 0;
	bool isEnd1P = false;
	bool isEnd2P = false;
	bool isDraw = false;
	float scale;
	int frameSpeed[2] = { 20,10 };
	int frameSpeedIdex = 0;
	Image* titleBg;
	Image* title;
	Image* title_02;
	Image* ending_1P;//A
	Image* ending_2P;//D
	Image* ending_draw; //C

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetIsTitle(bool _isTitle) { isTitle = _isTitle; }
	bool GetIsTitle() { return isTitle; }


	void SetIsEnd1P(bool _isEnd1P) { isEnd1P = _isEnd1P; }
	bool GetIsEnd1P() { return isEnd1P; }

	void SetIsEnd2P(bool _isEnd2P) { isEnd2P = _isEnd2P; }
	bool GetIsEnd2P() { return isEnd2P; }

	void SetIsDraw(bool _isDraw) { isDraw = _isDraw; }
	bool GetIsDraw() { return isDraw; }


	Title();
	~Title();
};

