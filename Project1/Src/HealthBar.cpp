#include "HealthBar.h"
#include "Image.h"

HRESULT HealthBar::Init()
{
	hp_1P = 100;
	hp_2P = 100;


	posX = 0;
	posY = 38;
	healthbar = new Image();
	damage_p1 = new Image();
	damage_p2 = new Image();
	hp_player_01 = new Image();
	hp_player_02 = new Image();

	face = new Image();

	int num = 0;
	int posX_02;



	face->Init("Image/face.bmp", posX + 10, posY - 5, 390, 242, 3, 2, true, RGB(255, 255, 255));

	damage_p1->Init("Image/damage_p1.bmp", posX, posY, 340, 15, 1, 1, true, RGB(255, 255, 255));
	damage_p2->Init("Image/damage_p2.bmp", posX, posY, 1004, 524, 1, 1, true, RGB(255, 255, 255));

	hp_player_01->Init("Image/hp_p1.bmp", posX, posY, 340, 15, 1, 1, true, RGB(255, 255, 255));
	hp_player_02->Init("Image/hp_p2.bmp", posX, posY, 1004, 524, 1, 1, true, RGB(255, 255, 255));

	healthbar->Init("Image/HP_bar.bmp", posX, posY, 1004, 524, 1, 1, true, RGB(108, 156, 114));
	hp_player_02->SetkeyFrameWidth_hp(1004.0f);
	currKeyFrameX = 1;
	currKeyFrameX_02 = 0;
	currKeyFrameY = 0;
	elapsedFrame = 0;
	scale = 1.0f;


	posX_HPsub = (float)(100 - hp_1P)*3.4f;
	posX_HPsub2 = (float)(hp_2P * 3.4);

	damage_p1->SetkeyFrameWidth_hp(340 - posX_HPsub);
	hp_player_01->SetkeyFrameWidth_hp(340 - posX_HPsub);

	hp_player_02->SetkeyFrameWidth_hp(550.0f + posX_HPsub2);
	damage_p2->SetkeyFrameWidth_hp(550.0f + posX_HPsub2);



	return S_OK;
}

void HealthBar::Release()
{
	healthbar->Release();
	delete healthbar;
	damage_p1->Release();
	delete damage_p1;
	damage_p2->Release();
	delete damage_p2;
	hp_player_01->Release();
	delete hp_player_01;
	hp_player_02->Release();
	delete hp_player_02;
}

void HealthBar::Update()
{
	if (hp_1P >= 0)
	{
		if ((100 - hp_1P)*3.4f != posX_HPsub)
		{
			posX_HPsub = (float)(100 - hp_1P)*3.4f;
			hp_player_01->SetkeyFrameWidth_hp(340 - posX_HPsub);
			isDamage = true;
		}

		if (isDamage)
		{
			redDamage++;

			if (redDamage >= 80)
			{
				posX_DAMAGEsub = (float)(100 - hp_1P)*3.4f;
				damage_p1->SetkeyFrameWidth_hp(340 - posX_HPsub);
				redDamage = 0;
				isDamage = false;
			}
		}

	}

	if (hp_2P >= 0)
	{
		if ((hp_2P * 3.4) != posX_HPsub2)
		{
			posX_HPsub2 = (float)(hp_2P * 3.4);
			hp_player_02->SetkeyFrameWidth_hp(550.0f + posX_HPsub2);

			isDamage2 = true;
		}
		if (isDamage2)
		{
			redDamage2++;
			if (redDamage2 >= 80)
			{
				damage_p2->SetkeyFrameWidth_hp(550.0f + posX_HPsub2);
				redDamage2 = 0;
				isDamage2 = false;
			}
		}
	}

}


void HealthBar::Render(HDC hdc)
{
	face->FrameRender(hdc, posX, posY, face_x, currKeyFrameY, scale);
	face->FrameRender(hdc, posX + 875, posY, face_x2, currKeyFrameY + 1, scale);

	damage_p1->HealthRender(hdc, posX + posX_DAMAGEsub + 110, posY + 52, currKeyFrameX, currKeyFrameY, scale);
	hp_player_01->HealthRender(hdc, posX + posX_HPsub + 110, posY + 52, currKeyFrameX, currKeyFrameY, scale);

	damage_p2->HealthRender(hdc, posX, posY, currKeyFrameX, currKeyFrameY, scale, true);
	hp_player_02->HealthRender(hdc, posX, posY, currKeyFrameX, currKeyFrameY, scale, true);
	healthbar->FrameRender(hdc, posX, posY, currKeyFrameX, currKeyFrameY, scale);
}


HealthBar::HealthBar()
{
}

HealthBar::~HealthBar()
{

}
