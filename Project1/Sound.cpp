#include "Sound.h"
#include "pch.h"
HRESULT Sound::Init()
{
		
	

	//mciOpenParam.lpstrElementName = "HitSound"; // ���ϸ�

	//mciOpenParam.lpstrDeviceType = "waveaudio"; //����� ����̽�����

	////erroCode = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpenParam);

	//wDeviceID = mciOpenParam.wDeviceID; // ����̽� ID
	//mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT |MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)

	//	(LPVOID)& mciOpenParam);


	return S_OK;
}

void Sound::Release()
{
	if (wDeviceID > 0)
	{
		//mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	}
}

void Sound::Update()
{
	if (!isHit)
	{
		
		//

		//Sound1 = LoadWAV(g_hWnd, "HitSound");
		//Sound1 = mciSendCommand(3, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL); //���
		//Sound1 = mciSendCommand(3, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciPlayParams);
		//mciSendCommand(wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& mciOpenParms);
	




	/*	MCI_PLAY_PARMS mciPlay;
		dwID = mciOpen.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);*/
	
		isHit=true;
	}
	//PlaySound(SystemAsterisk, 0, SND_ASYNC or SND_ALIAS);

	//mciSendCommandW(m_dwDeviceID, MCI_PLAY, MCI_NOTIFY,           // Play
	//	(DWORD)(LPVOID)& m_mciPlayParms);

	//mciSendCommandW(m_dwDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT,  // Play & Repeat
	//	(DWORD)(LPVOID)& m_mciPlayParms);

	//mciSendCommandW(m_dwDeviceID, MCI_RESUME, 0, NULL);           // Resume

	//3 - 6. Stop, Pause
	//	mciSendCommandW(m_dwDeviceID, MCI_CLOSE, 0, NULL);            // Stop

	//mciSendCommandW(m_dwDeviceID, MCI_PAUSE, MCI_NOTIFY,
	//	(DWORD)(LPVOID)& m_mciPlayParms);              // Pause



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



	
//	mciSendCommed �Լ� ����
//	// ���� ����
//
//// ���
//
////MCI_NOTIFY : �⺻, M CI_DGV_PLAY_REPEAT : �ݺ�
////�ٽý���
//mciSendCommandW(dwID, MCI_RESUM E, 0, NULL);
//// �Ͻ�����
//mciSendCommand(dwID, MCI_PAUSE, M CI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
//// ����
//mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
////���Ǹ��� �Ҹ� ���
//Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
//�̰����� ���� ���� ��� ��ġ�� ó�� ���ۺκ����� �Ű��ְ� �ٽ� �ش� �������� �����ÿ� �ٽ� ���
////�޸� ����
//ex)
//if (wDeviceID > 0)                                //�Ҹ��� ����߾������� �������� ����


//
//
//-------- - ��ü-------- -
//MCI_OPEN_PARMS mciOpen;
//MCI_PLAY_PARMS mciPlay;
//MCI_STATUS_PARMS mciStatus;
//-------- - ����-------- -
//UINT wDeviceID = 0;
//----------�Լ�----------
////MCI���� �Լ�
//
//
//
// //���� ����
//
// //���� ��� wav���� �ε�
//
//
//
//------����------
//MCI_OPEN  ����̽� ����
//MCI_PLAY  ���
//MCI_STOP  ����
//MCI_RESUME  �簳
//MCI_PAUSE  �Ͻ�����
//MCI_SETAUDIO  ���� ����
//MCI_SEEK  ��� ��ġ ����
//MCI_STATUS  ���� ��������
//MCI_CLOSE  ����̽� �ݱ�

