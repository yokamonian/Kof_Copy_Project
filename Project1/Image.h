#pragma once
#include "pch.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,
		FILE,
		EMPTY,
		END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;		// ���ҽ��� ������ ���̵�
		HDC		hMemDC;		// �׸��⸦ �ְ��ϴ� �ڵ�(�޸� ����)
		HBITMAP	hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		float	width;		// �̹��� ���� ũ��
		int		height;		// �̹��� ���� ũ��
		BYTE	loadType;	// �ε� Ÿ��

		float	x;					// ��� ��ġ ��ǥ
		float	y;					// ��� ��ġ ��ǥ
		int		currentKeyFrameX;	// ���� Ű������ �ε���
		int		currentKeyFrameY;
		int		maxKeyFrameX;		// �ִ� Ű������ ��
		int		maxKeyFrameY;
		float	keyFrameWidth;		// Ű������ �� ũ��
		int		keyFrameHeight;
		float	keyFrameWidth_hp;	// hp Ű������ �ʺ�
		float	posX_hp;
		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			x = 0.0f;
			y = 0.0f;
			currentKeyFrameX = 0;
			currentKeyFrameY = 0;
			maxKeyFrameX = 0;
			maxKeyFrameY = 0;
			keyFrameWidth = 0.0f;
			keyFrameHeight = 0;
			keyFrameWidth_hp = 0.0f;
			posX_hp = 0.0f;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;	// �̹������� ����ü ������
	char* fileName;			// ���� ��� + �̸�
	bool isTrans;			// ����ȭ ����
	COLORREF transColor;	// ����ȭ�� ��
	bool isReverse;
	bool isInit;
public:
	// �� ��Ʈ�� �̹����� �����.
	HRESULT Init(float width, int height);

	// ���ҽ��κ��� �����͸� �о �����.
	HRESULT Init(const DWORD resID, float width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �����͸� �о �����.
	HRESULT Init(const char* fileName, float width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);

	// �̹��� + Ű������ �ʱ�ȭ
	HRESULT Init(const char* fileName, float x, float y,
		float width, int height,
		float keyFrameX, int keyFrameY,
		bool trans = FALSE, COLORREF transColor = FALSE);



	// �޸� ����
	void Release();
	void SetKeyFrameWidth(float _keyFrameWidth) {
		imageInfo->keyFrameWidth = imageInfo->width / _keyFrameWidth;
	}
	void Render(HDC hdc, int destX, int destY);
	void HealthRender(HDC hdc, int posX_hp, int destY,
		int currentKeyFrameX, int currentKeyFrameY, float scale = 1.0f, bool isReverse = false);
	void CopyRender(HDC hdc, HDC hdc2,int destX, int destY, float scale);
	void FrameRender(HDC hdc, int destX, int destY,
		int currentKeyFrameX, int currentKeyFrameY, float scale = 1.0f, bool isReverse = false, int transColorNum = 0, float CameraPosX = 0.0f);

	float GetKeyFrameWidth() { if(imageInfo) return imageInfo->keyFrameWidth; else return 0;}
	float GetKeyFrameHeight() { if (imageInfo) return imageInfo->keyFrameHeight; else return 0; }
	void SetIsTrans(bool _isTrans) { isTrans = _isTrans; }		
	void SetTransColor(COLORREF _transColor){ transColor= _transColor;}
	HDC GetMemDC() { return imageInfo->hMemDC; }
	void SetIsReverse(bool _isReverse) { isReverse = _isReverse; }

	void SetkeyFrameWidth_hp(float idx) {
		imageInfo->keyFrameWidth_hp = idx;
	}
	float GetkeyFRrameWidth_hp() { if (imageInfo) return imageInfo->keyFrameWidth; else return 0; }


	Image();
	~Image();
};

