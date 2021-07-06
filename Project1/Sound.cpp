#include "Sound.h"
#include "pch.h"
HRESULT Sound::Init()
{
		
	

	//mciOpenParam.lpstrElementName = "HitSound"; // 파일명

	//mciOpenParam.lpstrDeviceType = "waveaudio"; //오디오 디바이스지정

	////erroCode = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)& mciOpenParam);

	//wDeviceID = mciOpenParam.wDeviceID; // 디바이스 ID
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
		//Sound1 = mciSendCommand(3, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL); //재생
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



	
//	mciSendCommed 함수 사용법
//	// 파일 열기
//
//// 재생
//
////MCI_NOTIFY : 기본, M CI_DGV_PLAY_REPEAT : 반복
////다시시작
//mciSendCommandW(dwID, MCI_RESUM E, 0, NULL);
//// 일시정지
//mciSendCommand(dwID, MCI_PAUSE, M CI_NOTIFY, (DWORD)(LPVOID)& mciPlay);
//// 정지
//mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
////조건마다 소리 출력
//Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
//이것으로 음원 파일 재생 위치를 처음 시작부분으로 옮겨주고 다시 해당 조건으로 왔을시에 다시 재생
////메모리 삭제
//ex)
//if (wDeviceID > 0)                                //소리를 사용했었을때를 조건으로 동작


//
//
//-------- - 객체-------- -
//MCI_OPEN_PARMS mciOpen;
//MCI_PLAY_PARMS mciPlay;
//MCI_STATUS_PARMS mciStatus;
//-------- - 변수-------- -
//UINT wDeviceID = 0;
//----------함수----------
////MCI사운드 함수
//
//
//
// //변수 선언
//
// //현재 경로 wav파일 로드
//
//
//
//------사용법------
//MCI_OPEN  디바이스 열기
//MCI_PLAY  재생
//MCI_STOP  정지
//MCI_RESUME  재개
//MCI_PAUSE  일시정지
//MCI_SETAUDIO  볼륨 설정
//MCI_SEEK  재생 위치 설정
//MCI_STATUS  상태 가져오기
//MCI_CLOSE  디바이스 닫기

