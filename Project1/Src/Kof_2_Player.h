
#pragma once
#include "GameNode.h"

class Image;
class Kof_1_Player;
/// <summary>
///	Kof_2_Player : 2p; ȭ�� ���� ���� �÷��̾� Ŭ����
/// ��� Ŭ���� ������ �Լ��� ��κ� ����. Reverse���õ� �κи� �ݴ밪.
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
	int hitFrameCount;		// ���� �߻��� ���Ǵ� ī��Ʈ
	bool isAttackFrame;		// ī��Ʈ�� ���۵Ǳ� ���� ���Լ�
	float frameSize[3] = { 10.0f, 22.0f,18.0f };
	int charNum = 0;
	int maxframe[3][8] = { { 9,4,4,6,4,1,8,8 }, { 9,5,20,9,7,1,11,21 }, {15,7,7,6,3,1,6,16} };
	int maxframeIndex = 0;// maxframe �迭�� �ε����� ������ ����

	COLORREF transColor[2][3] = { { RGB(7, 79, 151) ,RGB(108, 156, 114) , RGB(2, 62, 100) },
								 {  RGB(248, 176, 104) ,RGB(147, 99, 141) , RGB(253, 193, 155) } };// �ֵ��� �϶� �÷� �ٲٱ� 
	int transColorNum = 0;;
	int HP;
	float scale;
	int attackCount = 0;// ���� ����� ���ߴ��� üũ �� ������ ��� ���� �ʱ�ȭ ���� ����  
	int moveCount = 0;// �̵� ��� ������ ��� ���� �ʱ�ȭ ���� ����
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
	// ��Ʈ�ڽ� ���� �Ű�����
	float hitBoxWidth;		// ��Ʈ �ڽ� �ʺ�
	float hitBoxHeight;		// ��Ʈ �ڽ� ����
	int skillHitFrame;		// ��Ʈ�ڽ��ߵ� ������
	int skillHitEndFrame;	// ��Ʈ�ڽ��Ҹ� ������
	float activeHitBoxPosY;	// ��Ʈ�ڽ��ߵ� �ݰ���� ���۰�
	float activeHitBoxWidth;	// ��Ʈ�ڽ��ߵ� �ݰ�ʺ�
	float activeHitBoxHeight;	// ��Ʈ�ڽ��ߵ� �ݰ����
	FRECT hitBox;			// ��Ʈ�ڽ�
	int playerHp;
	//int attackDamage;
	bool CheckReverse;

	// �ǰ� �ڽ� ���� �Ű� ����
	float damagedBoxPosX;
	float damagedBoxPosY;
	float damagedBoxWidth;	// �ǰ� �ڽ� �ʺ�
	float damagedBoxHeight;	// �ǰ� �ڽ� ����
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

	FRECT GetHitBoxPos() { return hitBox; }			// ��Ʈ�ڽ� ��ġ��

	void SetIsDamaged(bool b) { isDamaged = b; }
	bool GetIsDamaged(){ return isDamaged; }
	FRECT GetDamagedBoxPos() { return damagedBox; }	// ������ �ڽ� ��ġ��

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
