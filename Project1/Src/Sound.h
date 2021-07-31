#pragma once
#include "pch.h"//���̺귯�� �߰�
#include "GameNode.h"
//main�� ���ο����� ��𼭵� ������ ����� �� 

/// <summary>
/// Sound : ���� ���� Ŭ����.(�̱���)
/// </summary>
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



	Sound();
	~Sound();
};

