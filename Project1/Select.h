#pragma once
#include "GameNode.h"
class MainGame;
class Image;
/// <summary>
///	Select : ���� �÷��� ��, ĳ���� ���� ���� Ŭ����.
/// </summary>
class Select : public GameNode
{
private:
	// ��ǥ ����
	float posX;				// ȭ�� �� ����� X��ǥ
	float posY;				// ȭ�� �� ����� Y��ǥ 
	float posX1P;			// 1P�� ���� ������ X��ǥ
	float posY1P;			// 1P�� ���� ������ Y��ǥ
	float posX2P;			// 2P�� ���� ������ X��ǥ
	float posY2P;			// 2P�� ���� ������ Y��ǥ
	float selectposX[4] = { 375,635,504,630 }; //504//630 ���� ������ ĳ������ X��ǥ
	float selectposY[4] = { 249, 90,170 ,249}; //170//249 ���� ������ ĳ������ Y��ǥ

	// �̹��� ����
	Image* select;			// ĳ���� ����â �̹���
	Image* selectIcon1P;	// 1P ���� ������
	Image* selectIcon2P;	// 2P ���� ������
	Image* charImg;			// ĳ���� �ʻ�ȭ
	Image* selectBg;		// ĳ���� ����â ��׶��Ʈ �̹���

	// ������ ����
	int currKeyFrameX1PIcon;	
	int currKeyFrameX2PIcon;	

	int currKeyFrameX1P;		
	int currKeyFrameX2P;
	int currKeyFrameY;
	
	int ChoiceNum1P = 0;
	int ChoiceNum2P = 2;

	// Bool ����
	bool isChoice1P;
	bool isChoice2P;

	bool isSelect;
	bool isInit = false;
	
	float scale;
public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetPosX(float x) { posX = x; }
	void SetPosY(float y) { posY = y; }
	void SetScale(float scale) { this->scale = scale; }
	void SetIsSelect(bool _isSelect) { isSelect = _isSelect; }
	bool GetIsSelect() { return isSelect; }

	void SetChoiceNum1P(int _ChoiceNum1P) { ChoiceNum1P = _ChoiceNum1P; }
	int GetChoiceNum1P() { return ChoiceNum1P; }

	void SetChoiceNum2P(int _ChoiceNum2P) { ChoiceNum2P = _ChoiceNum2P; }
	int GetChoiceNum2P() { return ChoiceNum2P; }
	

	Select();
	~Select();
};


