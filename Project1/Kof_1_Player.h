
#pragma once
#include "GameNode.h"

class Image;
class Kof_2_Player;
/// <summary>
///	Kof_1_Player : 1p; 화면 기준 좌측 플레이어 클래스
/// </summary>
class Kof_1_Player : public GameNode
{
private:
	float posX;
	float posY;
	float limitPosLeft[3]{ -90.0, -210.0, -110.0 }; // 스테이지 왼쪽 좌표 끝 기준 캐릭터의 좌측 이동 한계치

	Image* img;

	float currKeyFrameX;
	int currKeyFrameY;
	int elapsedFrame;

	int hitFrameCount;		// 공격 발생시 사용되는 카운트
	bool isAttackFrame;		// 카운트가 시작되기 위한 불함수



	// 각 동작별 프레임 간격( EX-> 출력할 프레임의 간격이 80.6 이면 1170/80.6 의 값을 넣어둠 
	float frameSize[3] = { 10.0f, 22.0f,18.0f };
	int charNum = 0;
	int frameSizeIndex = 0;
	int maxframe[3][8] = { { 9,4,4,6,4,1,8,8 }, { 9,5,20,9,7,1,11,21 }, {15,7,7,6,3,1,6,16} };
	int maxframeIndex = 0;// maxframe 배열의 인덱스를 변경할 변수
	COLORREF transColor[3][1] = { RGB(7, 79, 151) ,RGB(108, 156, 114) ,RGB(3, 63, 10) };

	int HP;

	// 각종 bool 변수
	float scale;
	bool isAttack = false;		// 공격여부
	bool isMove = false;		// 이동 여부
	bool isReverse = false;		// 2p인지
	bool isDamaged = false;		// 피격 여부
	bool CheckReverse;			// 2p와 위치가 바뀌었는지 체크
	bool isDie = false;			// 사망 여부
	bool isDieMotion = false;	// 사망시 모션 여부
	bool isWin = false;			// 승리 여부
	bool isWinMotion = false;	// 승리시 모션 여부
	bool isStartMotion = false;	// 시작시 모션 여부
	bool isAttached = false;	// 서로 맞닿았는지 여부
	Kof_2_Player* vsChar2;

	float vsCharPosX;

	float hitBoxWidth;		// 히트 박스 너비
	float hitBoxHeight;		// 히트 박스 높이
	int skillHitFrame;		// 히트박스발동 프레임
	int skillHitEndFrame;	// 히트박스소멸 프레임
	float activeHitBoxPosY;	// 히트박스발동 반경높이 시작값
	float activeHitBoxWidth;	// 히트박스발동 반경너비
	float activeHitBoxHeight;	// 히트박스발동 반경높이
	FRECT hitBox;			// 히트박스
	int playerHp;
	int directionValue = 0;

	//int attackType;
		// 피격 박스 관련 매개 변수
	float damagedBoxPosX;
	float damagedBoxPosY;
	float damagedBoxWidth;	// 피격 박스 너비
	float damagedBoxHeight;	// 피격 박스 높이
	float ReverseBoxAddPos; // 반전됬을때 추가되는 x축값
	FRECT damagedBox;		// 피격박스


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
	float GetPosY() { return  posY; }

	void SetVsCharPosX(float _vsCharPosX) { vsCharPosX = _vsCharPosX; }
	float GetVsCharPosX() { return vsCharPosX; }

	void SetScale(float scale) { this->scale = scale; }
	float GetScale() { return scale; }

	void SetIsReverse(bool _isReverse) { isReverse = _isReverse; }
	bool GetIsReverse() { return  isReverse; }

	COLORREF GetTransColor() { return transColor[charNum][1]; }

	FRECT GetHitBoxPos() { return hitBox; }			// 히트박스 위치값
	FRECT GetDamagedBoxPos() { return  damagedBox;}	// 데미지 박스 위치값

	int GetCharNum() { return charNum; }
	void SetCharNum(int _charNum) { charNum = _charNum; }
	void SetIsDamaged(bool b) { isDamaged = b; }
	bool GetIsAttack() { return isAttack; }

	void SetIsAttackFrame( bool _isAttackFrame) { isAttackFrame = _isAttackFrame;}
	bool GetIsAttackFrame() { return isAttackFrame;}

	void SetIsWin(bool _isWin) { isWin = _isWin; }
	bool GetIsWin() { return isWin; }

	void SetIsDie(bool _isDie) { isDie = _isDie; }
	bool GetIsDie() { return isDie; }



	int GetHP() { return HP; }
	void SetHP(int _HP) { HP = _HP; }

	void SetDamageFrame();
	bool GetIsMove() { return isMove; }
	void SetIsAttached(bool b) { isAttached = b; }
	bool GetIsAttached() { return isAttached; }

	Kof_1_Player();
	~Kof_1_Player();
};
