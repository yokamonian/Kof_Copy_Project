#pragma once
#include "pch.h"//���̺귯�� �߰�
#include "GameNode.h"
//main�� ���ο����� ��𼭵� ������ ����� �� 

class Sound : public GameNode
{
private:

	MCI_OPEN_PARMS mciOpenParam;
	
	MCI_OPEN_PARMS      mciOpenParms; //������ �ε�
	MCI_PLAY_PARMS mciPlayParams;
	//MCI_PLAY_PARMS       mciPlay; //������ ���
	MCI_STATUS_PARMS   mciStatus; //������ ����
	UINT wDeviceID = 0;
	//DWORD wDeviceID;
	int erroCode;

	DWORD Sound1;
	



	bool isHit = false;
public: 


	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	//DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave)
	//{
	//	DWORD Result;
	//	mciOpenParam.lpstrDeviceType = "WaveAudio";
	//	//mciOpenParms.lpstrDeviceType
	//  //WaveAudio ��� MPEGVideo�� ����ϸ� mp3 ������ ����մϴ�.
	//	mciOpenParam.lpstrElementName = lpszWave;
	//	//mciOpenParms.lpstrElementName 
	//	Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)& mciOpenParam);
	//	if (Result)
	//		return Result;
	//	wDeviceID = mciOpenParam.wDeviceID;
	//	mciPlay.dwCallback = (DWORD)hWnd;
	//	if (Result)
	//		return Result;
	//	return 0;
	//}



	Sound();
	~Sound();
};

