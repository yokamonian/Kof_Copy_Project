#include "Image.h"



HRESULT Image::Init(float width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
	imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		// 메모리 해제
		Release();
		return E_FAIL;
	}
	isInit = true;
	return S_OK;
}

HRESULT Image::Init(const DWORD resID, float width, int height, bool trans, COLORREF transColor)
{
	return E_NOTIMPL;
}





//원본 소스로 부터 복사// 소스의 크기가 인티저타입으로 나누어질때
HRESULT Image::Init(const char * fileName, float width, int height, bool trans, COLORREF transColor)  
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	isTrans = trans;
	this->transColor = transColor;
	isReverse = true;
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		// 메모리 해제
		Release();
		return E_FAIL;
	}
	isInit = true;
	return S_OK;
}


//원본 소스로 부터 복사// 소스의 크기가 float타입으로 나누어질때
HRESULT Image::Init(const char * fileName,
	float x, float y, float width, int height,
	float keyFrameX, int keyFrameY,
	bool trans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	// 추가
	imageInfo->x = x - (width / 2);
	imageInfo->y = y - (height / 2);
	imageInfo->currentKeyFrameX = 0;
	imageInfo->currentKeyFrameY = 0;
	imageInfo->maxKeyFrameX = keyFrameX - 1;
	imageInfo->maxKeyFrameY = keyFrameY - 1;
	imageInfo->keyFrameWidth = width / keyFrameX;
	imageInfo->keyFrameHeight = height / keyFrameY;

	isTrans = trans;
	this->transColor = transColor;
	isReverse = true;
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		// 메모리 해제
		Release();
		return E_FAIL;
	}
	isInit = true;
	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);

		delete imageInfo;
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc, //출력할 윈도우 DC
			destX, destY, // 출력할 곳의 시작점
			imageInfo->width, imageInfo->height,// 출력 할 이미지를 그릴 사이즈

			imageInfo->hMemDC,// 복사할 이미지 DC
			0, 0,// 시작점
			imageInfo->width, imageInfo->height,// 사이즈
			transColor
		);
	}
	else
	{
		// 메모리에 있는 데이터를 화면에 고속복사한다.
		BitBlt(hdc,				// 복사 목적지 DC
			destX, destY,		// 복사 시작 위치
			imageInfo->width,	// 원본에서 복사될 가로 크기
			imageInfo->height,	// 원본에서 복사될 세로 크기
			imageInfo->hMemDC,	// 원본 DC
			0, 0,				// 원본에서 복사 시작 위치
			SRCCOPY);			// 복사 옵션
	}

}


void Image::HealthRender(HDC hdc, int posX_hp, int destY, int currentKeyFrameX, int currentKeyFrameY, float scale, bool isReverse)
{

	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;

	if (imageInfo->currentKeyFrameX > imageInfo->maxKeyFrameX)
	{
		imageInfo->currentKeyFrameX = imageInfo->maxKeyFrameX;
	}
	if (imageInfo->currentKeyFrameY > imageInfo->maxKeyFrameY)
	{
		imageInfo->currentKeyFrameY = imageInfo->maxKeyFrameY;
	}

	if (isReverse)
	{

		GdiTransparentBlt(
			hdc,
			posX_hp, destY,
			imageInfo->keyFrameWidth_hp,
			imageInfo->keyFrameHeight * scale,

			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->keyFrameWidth_hp,
			imageInfo->keyFrameHeight,
			transColor
		);


	}
	else
	{
		GdiTransparentBlt(
			hdc,
			posX_hp, destY,
			imageInfo->keyFrameWidth_hp,
			imageInfo->keyFrameHeight * scale,

			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			340,
			imageInfo->keyFrameHeight,
			transColor
		);


	}

}



void Image::FrameRender(HDC hdc, int destX, int destY,
	int currentKeyFrameX, int currentKeyFrameY, float scale/* = 1.0f*/, bool isReverse, int transColorNum, float CameraPosX )
{
	// 현재 키프레임 인덱스가 최대 키프레임 인덱스보다 클 때
	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;

	if (imageInfo->currentKeyFrameX > imageInfo->maxKeyFrameX)
	{
		imageInfo->currentKeyFrameX = imageInfo->maxKeyFrameX;
	}
	if (imageInfo->currentKeyFrameY > imageInfo->maxKeyFrameY)
	{
		imageInfo->currentKeyFrameY = imageInfo->maxKeyFrameY;
	}

	if (isTrans && isReverse == false)
	{
		
		GdiTransparentBlt(
			hdc,
			destX, destY,
			imageInfo->keyFrameWidth * scale,
			imageInfo->keyFrameHeight * scale,

			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX ,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			transColor
		);


	}
	else if (isReverse)
	{
		if (transColorNum == 0)
		{
			StretchBlt(hdc, // 리버스일때, 복사 해둘 DC 
				0, 0,//  미출력할 DC이기에 그냥 0,0에 출력
				imageInfo->keyFrameWidth,// 복사해서 출력할 크기
				imageInfo->keyFrameHeight,

				imageInfo->hMemDC,// 복사 할 이미지 DC
				imageInfo->keyFrameWidth * (imageInfo->currentKeyFrameX + 1) - 1, //반전을 시켜야 하기에, +1 지점에서 부터 마이너스로 비트정보를 가져오 EX) 100에서 99,98 픽셀의 정보를 역순으로 가져옴
				imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
				-imageInfo->keyFrameWidth,// 마이너스로 가져와야 함으로 복사 길이에 마이너스 값을 넣어줌
				imageInfo->keyFrameHeight, SRCCOPY);
		}
		else
		{
			StretchBlt(hdc, // 리버스일때, 복사 해둘 DC 
				0, 0,//  미출력할 DC이기에 그냥 0,0에 출력
				imageInfo->keyFrameWidth,// 복사해서 출력할 크기
				imageInfo->keyFrameHeight,

				imageInfo->hMemDC,// 복사 할 이미지 DC
				imageInfo->keyFrameWidth * (imageInfo->currentKeyFrameX + 1) - 1, //반전을 시켜야 하기에, +1 지점에서 부터 마이너스로 비트정보를 가져오 EX) 100에서 99,98 픽셀의 정보를 역순으로 가져옴
				imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
				-imageInfo->keyFrameWidth,// 마이너스로 가져와야 함으로 복사 길이에 마이너스 값을 넣어줌
				imageInfo->keyFrameHeight, NOTSRCCOPY);
		}
	}
	else
	{
		GdiTransparentBlt(
			hdc,
			destX, destY,
			imageInfo->keyFrameWidth * scale,
			imageInfo->keyFrameHeight * scale, 

			imageInfo->hMemDC,
			(imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX) + CameraPosX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			transColor
		);


	}

}
void Image::CopyRender(HDC hdc, HDC hdc2, int destX, int destY, float scale)
{
	if (isTrans)//1차적으로 좌우 변환시켜서 저장한 DC에 transColor값을 넣어줌
	{
		GdiTransparentBlt(
			hdc2, // 그려줄 DC(현재는 backbuffer)
			destX, destY, // 출력할 시작점
			imageInfo->keyFrameWidth * scale,// 그려낼 사이즈 크기
			imageInfo->keyFrameHeight * scale,

			hdc, //CopyBuffer
			0, 0,//0,0에 복사 해둠었기에 0,0 복사 시작
			imageInfo->keyFrameWidth,// 이미 1차적으로 좌우 반전하면서 프레임을 이동했기에, 프레임을 이동할 필요 없음
			imageInfo->keyFrameHeight,
			transColor
		);

	}


}

Image::Image()
{
}


Image::~Image()
{
}
