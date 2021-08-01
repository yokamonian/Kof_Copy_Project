#pragma once
#include "pch.h"

/// <summary>
/// GameNode : ���� ���� ��κ��� Ŭ������ ���� Ŭ�����̸� �ʱ�ȭ, ����, ������Ʈ, ������ �����Լ��� ������ �ִ�. 
/// </summary>
class GameNode
{
public:
	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	GameNode();
	~GameNode();
};

