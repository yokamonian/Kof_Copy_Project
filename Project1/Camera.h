
#pragma once
#include "GameNode.h"
#include "pch.h"

class Image;
class Camera : public GameNode
{
private:
	float posX;
	float posY;
	FRECT Pos;
	float charposX;
	float charposY;
	int currKeyFrameX;
	int currKeyFrameY;
	bool isintro = false;
	bool isTitleMaXFrame = false;
	bool isTitle = false;
	int elapsedFrame = 0;
	bool isEnd1P = false;
	bool isEnd2P = false;
	float scale;
	int frameSpeed[2] = { 20,10 };
	int frameSpeedIdex = 0;
	

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetPosX(float x) { posX = x; }
	void SetPosY(float y) { posY = y; }
	float GetPosX() { return posX; }
	float GetPosY() { return  posY; }
	void SetCharposX(float _charposX) { charposX = _charposX; }
	float GetCharposX() { return charposX; }

	void SetPosLeft(float _posLeft) { Pos.left = _posLeft; }
	float GetPosLeft() { return Pos.left; }


	Camera();
	~Camera();
};

