#pragma once
#include "GameNode.h"
class Image;
/// <summary>
/// BackGround : �����÷��̽� �����ϴ� ��� ��׶��� Ŭ����
/// 6���� ��� �� ������ ��� ��׶��带 ���
/// </summary>
class BackGround : public GameNode
{
private:
	float posX;			// x��ǥ
	float posY;			// y��ǥ
	Image* img;
	int currKeyFrameX;	// �ִϸ��̼� �������� Ⱦ(x��) ������ ��
	int currKeyFrameY;	// �ִϸ��̼� �������� ��(y��) ������ ��
	int elapsedFrame;	// ����� ������
	int BgNum;			// ��׶��� ��ȣ
	float scale;		// ũ��
	int camerPosX=0;	// ī�޶��� x��ǥ

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


