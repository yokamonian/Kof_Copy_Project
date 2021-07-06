#pragma once
#include "GameNode.h"
class Image;
class BackGround : public GameNode
{
private:
	float posX;
	float posY;
	Image* img;
	int currKeyFrameX;
	int currKeyFrameY;
	int elapsedFrame;
	int BgNum;
	float scale;
	int camerPosX=0;

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetPosX(float x) { posX = x; }
	void SetPosY(float y) { posY = y; }
	void SetScale(float scale) { this->scale = scale; }

	void SetcamerPosX(float _camerPosX) { camerPosX = _camerPosX; }

	BackGround();
	~BackGround();
};


