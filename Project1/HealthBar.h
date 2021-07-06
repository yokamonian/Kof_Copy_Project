#pragma once
#include "GameNode.h"

class Image;
class HealthBar : public GameNode
{
private:
	float posX;
	float posY;
	float posX_HPsub;
	float posX_DAMAGEsub;
	float posX_HPsub2;
	Image* healthbar;
	//Image* damagebar;
	Image* hp_player_01;
	Image* hp_player_02;
	Image* damage_p1;
	Image* damage_p2;
	Image* face;
	float face_size[2] = { 3,3 };
	int face_x = 0;
	int face_x2 = 0;
	int face_y;
	int currKeyFrameX;
	int currKeyFrameX_02;
	int currKeyFrameY;
	int elapsedFrame;
	int printTime_HP;
	float scale;
	int num;
	int redDamage = 0;
	int redDamage2 = 0;
	int hp_1P = 0;
	int hp_2P = 0;


	bool isDamage = false;
	bool isDamage2 = false;
public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetPosX(float x) { posX = x; }
	void SetPosY(float y) { posY = y; }
	void SetScale(float scale) { this->scale = scale; }


	int GetPrintTime_HP() { return printTime_HP; }
	void SetPrintTime_HP(int _printTime_HP) { printTime_HP = _printTime_HP; }

	int GetposX_HPsub() {
		return posX_HPsub;
	}
	void SetposX_HPsub(float _posX_sub) { posX_HPsub = _posX_sub; }

	int GetposX_DAMAGEsub() { return posX_DAMAGEsub; }
	void SetposX_DAMAGEsub(float _posX_DAMAGEsub) { posX_DAMAGEsub = _posX_DAMAGEsub; }

	void SetFace_x(int _face_x) { face_x = _face_x; }
	int GetFace_x() { return face_x; }

	void SetFace_x2(int _face_x2) { face_x2 = _face_x2; }
	int GetFace_x2() { return face_x2; }

	void SetHp_1P(int _hp_1P) { hp_1P = _hp_1P; }
	int GetHp_1P() { return hp_1P; }

	void SetHp_2P(int _hp_2P) { hp_2P = _hp_2P; }
	int GetHp_2P() { return hp_2P; }


	HealthBar();
	~HealthBar();

};

