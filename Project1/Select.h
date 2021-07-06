#pragma once
#include "GameNode.h"
class MainGame;
class Image;
class Select : public GameNode
{
private:
	float posX;
	float posY;
	float posX1P;
	float posY1P;
	float posX2P;
	float posY2P;
	float selectposX[4] = { 375,635,504,630 }; //504//630
	float selectposY[4] = { 249, 90,170 ,249}; //170//249

	Image* select;
	Image* selectIcon1P;
	Image* selectIcon2P;
	Image* charImg;
	Image* selectBg;

	int currKeyFrameX1PIcon;
	int currKeyFrameX2PIcon;

	int currKeyFrameX1P;
	int currKeyFrameX2P;
	int currKeyFrameY;
	
	int ChoiceNum1P = 0;
	int ChoiceNum2P = 2;

	float scale;
	bool isChoice1P;
	bool isChoice2P;
	
	bool isSelect;


	bool isInit = false;
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


