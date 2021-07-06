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
		DWORD	resID;		// 리소스의 고유한 아이디
		HDC		hMemDC;		// 그리기를 주관하는 핸들(메모리 관리)
		HBITMAP	hBitmap;	// 이미지 정보
		HBITMAP hOldBit;	// 기존 이미지 정보
		float	width;		// 이미지 가로 크기
		int		height;		// 이미지 세로 크기
		BYTE	loadType;	// 로드 타입

		float	x;					// 출력 위치 좌표
		float	y;					// 출력 위치 좌표
		int		currentKeyFrameX;	// 현재 키프레임 인덱스
		int		currentKeyFrameY;
		int		maxKeyFrameX;		// 최대 키프레임 수
		int		maxKeyFrameY;
		float	keyFrameWidth;		// 키프레임 당 크기
		int		keyFrameHeight;
		float	keyFrameWidth_hp;	// hp 키프레임 너비
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
	IMAGE_INFO* imageInfo;	// 이미지정보 구조체 포인터
	char* fileName;			// 파일 경로 + 이름
	bool isTrans;			// 투명화 여부
	COLORREF transColor;	// 투명화할 색
	bool isReverse;
	bool isInit;
public:
	// 빈 비트맵 이미지를 만든다.
	HRESULT Init(float width, int height);

	// 리소스로부터 데이터를 읽어서 만든다.
	HRESULT Init(const DWORD resID, float width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);

	// 파일로부터 데이터를 읽어서 만든다.
	HRESULT Init(const char* fileName, float width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);

	// 이미지 + 키프레임 초기화
	HRESULT Init(const char* fileName, float x, float y,
		float width, int height,
		float keyFrameX, int keyFrameY,
		bool trans = FALSE, COLORREF transColor = FALSE);



	// 메모리 해제
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

