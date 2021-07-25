
#pragma once
#include "GameNode.h"

class Image;
class Kof_1_Player;
/// <summary>
///	Kof_2_Player : 2p; 화면 기준 우측 플레이어 클래스
/// 기반 클래스 변수나 함수는 대부분 동일. Reverse관련된 부분만 반대값.
/// </summary>
class Kof_2_Player : public GameNode
{
private:

	float posX;
	float posY;
	float limitPosRight[3] = { WINSIZE_X - 210, WINSIZE_X - 315, WINSIZE_X - 230 };

	Image* img;
	RECT hpBar;
	float currKeyFrameX;
	int currKeyFrameY;
	int elapsedFrame;
	int hitFrameCount;		// 공격 발생시 사용되는 카운트
	bool isAttackFrame;		// 카운트가 시작되기 위한 불함수
	float frameSize[3] = { 10.0f, 22.0f,18.0f };
	int charNum = 0;
	int maxframe[3][8] = { { 9,4,4,6,4,1,8,8 }, { 9,5,20,9,7,1,11,21 }, {15,7,7,6,3,1,6,16} };
	int maxframeIndex = 0;// maxframe 배열의 인덱스를 변경할 변수

	COLORREF transColor[2][3] = { { RGB(7, 79, 151) ,RGB(108, 156, 114) , RGB(2, 62, 100) },
								 {  RGB(248, 176, 104) ,RGB(147, 99, 141) , RGB(253, 193, 155) } };// 쌍둥이 일때 컬러 바꾸기 
	int transColorNum = 0;;
	int HP;
	float scale;
	int attackCount = 0;// 공격 모션을 다했는지 체크 및 프레임 출력 관련 초기화 제어 변수  
	int moveCount = 0;// 이동 모션 프레임 출력 관련 초기화 제어 변수
	bool isAttack = false;
	bool isMove = false;
	bool isReverse = false;
	bool isDamaged = false;
	bool isHit = false;
	bool isDie = false;
	bool isDieMotion = false;
	bool isWin = false;
	bool isWinMotion = false;
	bool isStartMotion = false;
	bool isAttached = false;
	// 히트박스 관련 매개변수
	float hitBoxWidth;		// 히트 박스 너비
	float hitBoxHeight;		// 히트 박스 높이
	int skillHitFrame;		// 히트박스발동 프레임
	int skillHitEndFrame;	// 히트박스소멸 프레임
	float activeHitBoxPosY;	// 히트박스발동 반경높이 시작값
	float activeHitBoxWidth;	// 히트박스발동 반경너비
	float activeHitBoxHeight;	// 히트박스발동 반경높이
	FRECT hitBox;			// 히트박스
	int playerHp;
	//int attackDamage;
	bool CheckReverse;

	// 피격 박스 관련 매개 변수
	float damagedBoxPosX;
	float damagedBoxPosY;
	float damagedBoxWidth;	// 피격 박스 너비
	float damagedBoxHeight;	// 피격 박스 높이
	FRECT damagedBox;


	Kof_1_Player* vsChar1;
	float vsCharPosX;
	int directionValue = 0;

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, HDC hdc2 = NULL);


	int GetDirectionValue() { return directionValue; }
	void changeIndex(int _index);

	void SetPosX(float x) { posX = x; }
	void SetPosY(float y) { posY = y; }
	float GetPosX() { return posX; }
	float GetPosY() { return posY; }

	void SetVsCharPosX(float _vsCharPosX) { vsCharPosX = _vsCharPosX; }
	float GetVsCharPosX() { return vsCharPosX; }

	void SetScale(float scale) { this->scale = scale; }
	float GetScale() { return scale; }

	void SetIsReverse(bool _isReverse) { isReverse = _isReverse; }
	bool GetIsReverse() { return  isReverse; }

	COLORREF GetTransColor() { return transColor[transColorNum][charNum]; }
	void SetTransColorNum(int _transColorNum) {	transColorNum = _transColorNum;	}

	FRECT GetHitBoxPos() { return hitBox; }			// 히트박스 위치값

	void SetIsDamaged(bool b) { isDamaged = b; }
	bool GetIsDamaged(){ return isDamaged; }
	FRECT GetDamagedBoxPos() { return damagedBox; }	// 데미지 박스 위치값

	void SetCharNum(int _charNum) { charNum=_charNum; }
	int GetCharNum() { return charNum; }
	bool GetIsAttack() { return isAttack; }

	int GetPlayerHp() { return playerHp; }


	void SetIsAttackFrame(bool _isAttackFrame) { isAttackFrame = _isAttackFrame; }
	bool GetIsAttackFrame() { return isAttackFrame; }


	void SetIsWin(bool _isWin) { isWin = _isWin; }
	bool GetIsWin() { return isWin; }


	void SetIsDie(bool _isDie) { isDie = _isDie; }
	bool GetIsDie() { return isDie; }

	void SetDamageFrame();
	int GetHP() { return HP; }
	void SetHP(int _HP) { HP = _HP; }
	bool GetIsMove() { return isMove; }
	void SetIsAttached(bool b) { isAttached = b; }
	bool GetIsAttached() { return isAttached; }

	Kof_2_Player();
	~Kof_2_Player();
};
