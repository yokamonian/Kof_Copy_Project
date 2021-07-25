#pragma once
#include "GameNode.h"
class MainGame;
class Image;
/// <summary>
///	Select : 게임 플레이 시, 캐릭터 선택 관련 클래스.
/// </summary>
class Select : public GameNode
{
private:
	// 좌표 관련
	float posX;				// 화면 내 상대적 X좌표
	float posY;				// 화면 내 상대적 Y좌표 
	float posX1P;			// 1P의 선택 포인터 X좌표
	float posY1P;			// 1P의 선택 포인터 Y좌표
	float posX2P;			// 2P의 선택 포인터 X좌표
	float posY2P;			// 2P의 선택 포인터 Y좌표
	float selectposX[4] = { 375,635,504,630 }; //504//630 선택 가능한 캐릭터의 X좌표
	float selectposY[4] = { 249, 90,170 ,249}; //170//249 선택 가능한 캐릭터의 Y좌표

	// 이미지 관련
	Image* select;			// 캐릭터 선택창 이미지
	Image* selectIcon1P;	// 1P 선택 아이콘
	Image* selectIcon2P;	// 2P 선택 아이콘
	Image* charImg;			// 캐릭터 초상화
	Image* selectBg;		// 캐릭터 선택창 백그라운트 이미지

	// 프레임 관련
	int currKeyFrameX1PIcon;	
	int currKeyFrameX2PIcon;	

	int currKeyFrameX1P;		
	int currKeyFrameX2P;
	int currKeyFrameY;
	
	int ChoiceNum1P = 0;
	int ChoiceNum2P = 2;

	// Bool 변수
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


