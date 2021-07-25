#pragma once
#include "GameNode.h"
class Image;
/// <summary>
/// BackGround : 게임플레이시 등장하는 배경 백그라운드 클래스
/// 6종의 배경 중 임의의 배경 백그라운드를 재생
/// </summary>
class BackGround : public GameNode
{
private:
	float posX;			// x좌표
	float posY;			// y좌표
	Image* img;
	int currKeyFrameX;	// 애니메이션 프레임의 횡(x축) 프레임 수
	int currKeyFrameY;	// 애니메이션 프레임의 종(y축) 프레임 수
	int elapsedFrame;	// 경과된 프레임
	int BgNum;			// 백그라운드 번호
	float scale;		// 크기
	int camerPosX=0;	// 카메라의 x좌표

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


