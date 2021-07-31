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
		// �޸� ����
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





//���� �ҽ��� ���� ����// �ҽ��� ũ�Ⱑ ��Ƽ��Ÿ������ ����������
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
		// �޸� ����
		Release();
		return E_FAIL;
	}
	isInit = true;
	return S_OK;
}


//���� �ҽ��� ���� ����// �ҽ��� ũ�Ⱑ floatŸ������ ����������
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
	// �߰�
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
		// �޸� ����
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
			hdc, //����� ������ DC
			destX, destY, // ����� ���� ������
			imageInfo->width, imageInfo->height,// ��� �� �̹����� �׸� ������

			imageInfo->hMemDC,// ������ �̹��� DC
			0, 0,// ������
			imageInfo->width, imageInfo->height,// ������
			transColor
		);
	}
	else
	{
		// �޸𸮿� �ִ� �����͸� ȭ�鿡 ��Ӻ����Ѵ�.
		BitBlt(hdc,				// ���� ������ DC
			destX, destY,		// ���� ���� ��ġ
			imageInfo->width,	// �������� ����� ���� ũ��
			imageInfo->height,	// �������� ����� ���� ũ��
			imageInfo->hMemDC,	// ���� DC
			0, 0,				// �������� ���� ���� ��ġ
			SRCCOPY);			// ���� �ɼ�
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
	// ���� Ű������ �ε����� �ִ� Ű������ �ε������� Ŭ ��
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
			StretchBlt(hdc, // �������϶�, ���� �ص� DC 
				0, 0,//  ������� DC�̱⿡ �׳� 0,0�� ���
				imageInfo->keyFrameWidth,// �����ؼ� ����� ũ��
				imageInfo->keyFrameHeight,

				imageInfo->hMemDC,// ���� �� �̹��� DC
				imageInfo->keyFrameWidth * (imageInfo->currentKeyFrameX + 1) - 1, //������ ���Ѿ� �ϱ⿡, +1 �������� ���� ���̳ʽ��� ��Ʈ������ ������ EX) 100���� 99,98 �ȼ��� ������ �������� ������
				imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
				-imageInfo->keyFrameWidth,// ���̳ʽ��� �����;� ������ ���� ���̿� ���̳ʽ� ���� �־���
				imageInfo->keyFrameHeight, SRCCOPY);
		}
		else
		{
			StretchBlt(hdc, // �������϶�, ���� �ص� DC 
				0, 0,//  ������� DC�̱⿡ �׳� 0,0�� ���
				imageInfo->keyFrameWidth,// �����ؼ� ����� ũ��
				imageInfo->keyFrameHeight,

				imageInfo->hMemDC,// ���� �� �̹��� DC
				imageInfo->keyFrameWidth * (imageInfo->currentKeyFrameX + 1) - 1, //������ ���Ѿ� �ϱ⿡, +1 �������� ���� ���̳ʽ��� ��Ʈ������ ������ EX) 100���� 99,98 �ȼ��� ������ �������� ������
				imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
				-imageInfo->keyFrameWidth,// ���̳ʽ��� �����;� ������ ���� ���̿� ���̳ʽ� ���� �־���
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
	if (isTrans)//1�������� �¿� ��ȯ���Ѽ� ������ DC�� transColor���� �־���
	{
		GdiTransparentBlt(
			hdc2, // �׷��� DC(����� backbuffer)
			destX, destY, // ����� ������
			imageInfo->keyFrameWidth * scale,// �׷��� ������ ũ��
			imageInfo->keyFrameHeight * scale,

			hdc, //CopyBuffer
			0, 0,//0,0�� ���� �صҾ��⿡ 0,0 ���� ����
			imageInfo->keyFrameWidth,// �̹� 1�������� �¿� �����ϸ鼭 �������� �̵��߱⿡, �������� �̵��� �ʿ� ����
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
