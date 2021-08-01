#pragma once
#include "pch.h"

/// <summary>
/// GameNode : 게임 내에 대부분의 클래스의 상위 클래스이며 초기화, 해제, 업데이트, 랜더의 가상함수를 가지고 있다. 
/// </summary>
class GameNode
{
public:
	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	GameNode();
	~GameNode();
};

