
#pragma once
#include "GameNode.h"

class Image;
class Kof_2_Player;
/// <summary>
///	Kof_1_Player : 1p; ȭ�� ���� ���� �÷��̾� Ŭ����
/// </summary>
class Kof_1_Player : public GameNode
{
private:
	float posX;
	float posY;
	float limitPosLeft[3]{ -90.0, -210.0, -110.0 }; // �������� ���� ��ǥ �� ���� ĳ������ ���� �̵� �Ѱ�ġ

	Image* img;

	float currKeyFrameX;
	int currKeyFrameY;
	int elapsedFrame;

	int hitFrameCount;		// ���� �߻��� ���Ǵ� ī��Ʈ
	bool isAttackFrame;		// ī��Ʈ�� ���۵Ǳ� ���� ���Լ�



	// �� ���ۺ� ������ ����( EX-> ����� �������� ������ 80.6 �̸� 1170/80.6 �� ���� �־�� 
	float frameSize[3] = { 10.0f, 22.0f,18.0f };
	int charNum = 0;
	int frameSizeIndex = 0;
	int maxframe[3][8] = { { 9,4,4,6,4,1,8,8 }, { 9,5,20,9,7,1,11,21 }, {15,7,7,6,3,1,6,16} };
	int maxframeIndex = 0;// maxframe �迭�� �ε����� ������ ����
	COLORREF transColor[3][1] = { RGB(7, 79, 151) ,RGB(108, 156, 114) ,RGB(3, 63, 10) };

	int HP;

	// ���� bool ����
	float scale;
	bool isAttack = false;		// ���ݿ���
	bool isMove = false;		// �̵� ����
	bool isReverse = false;		// 2p����
	bool isDamaged = false;		// �ǰ� ����
	bool CheckReverse;			// 2p�� ��ġ�� �ٲ������ üũ
	bool isDie = false;			// ��� ����
	bool isDieMotion = false;	// ����� ��� ����
	bool isWin = false;			// �¸� ����
	bool isWinMotion = false;	// �¸��� ��� ����
	bool isStartMotion = false;	// ���۽� ��� ����
	bool isAttached = false;	// ���� �´�Ҵ��� ����
	Kof_2_Player* vsChar2;

	float vsCharPosX;

	float hitBoxWidth;		// ��Ʈ �ڽ� �ʺ�
	float hitBoxHeight;		// ��Ʈ �ڽ� ����
	int skillHitFrame;		// ��Ʈ�ڽ��ߵ� ������
	int skillHitEndFrame;	// ��Ʈ�ڽ��Ҹ� ������
	float activeHitBoxPosY;	// ��Ʈ�ڽ��ߵ� �ݰ���� ���۰�
	float activeHitBoxWidth;	// ��Ʈ�ڽ��ߵ� �ݰ�ʺ�
	float activeHitBoxHeight;	// ��Ʈ�ڽ��ߵ� �ݰ����
	FRECT hitBox;			// ��Ʈ�ڽ�
	int playerHp;
	int directionValue = 0;

	//int attackType;
		// �ǰ� �ڽ� ���� �Ű� ����
	float damagedBoxPosX;
	float damagedBoxPosY;
	float damagedBoxWidth;	// �ǰ� �ڽ� �ʺ�
	float damagedBoxHeight;	// �ǰ� �ڽ� ����
	float ReverseBoxAddPos; // ���������� �߰��Ǵ� x�ప
	FRECT damagedBox;		// �ǰݹڽ�


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

	FRECT GetHitBoxPos() { return hitBox; }			// ��Ʈ�ڽ� ��ġ��
	FRECT GetDamagedBoxPos() { return  damagedBox;}	// ������ �ڽ� ��ġ��

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
