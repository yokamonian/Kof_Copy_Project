#include "Sound.h"
#include "pch.h"
HRESULT Sound::Init()
{

	return S_OK;
}

void Sound::Release()
{
	if (wDeviceID > 0)
	{

	}
}

void Sound::Update()
{
	if (!isHit)
	{
		isHit=true;
	}
}

void Sound::Render(HDC hdc)
{
}

Sound::Sound()
{
}

Sound::~Sound()
{
}
