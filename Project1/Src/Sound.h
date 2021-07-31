#pragma once
#include "pch.h"//라이브러리 추가
#include "GameNode.h"
//main문 내부에서든 어디서든 음악을 재생할 때 

/// <summary>
/// Sound : 사운드 관련 클래스.(미구현)
/// </summary>
class Sound : public GameNode
{
private:

	MCI_OPEN_PARMS mciOpenParam;
	
	MCI_OPEN_PARMS      mciOpenParms; //파일을 로드
	MCI_PLAY_PARMS mciPlayParams;
	//MCI_PLAY_PARMS       mciPlay; //파일을 재생
	MCI_STATUS_PARMS   mciStatus; //파일의 상태
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



	Sound();
	~Sound();
};

