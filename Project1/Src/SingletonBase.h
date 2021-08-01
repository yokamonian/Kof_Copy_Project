// SingletonBase.h

#pragma once

/// <summary>
/// SingletonBase : 프로젝트에서 사용되는 기본 매니저들을 관리하기 위해 만들어진 싱글톤 패턴 클래스.
/// 싱글톤 패턴으로 생성이후 클래스 선언을 하지 않고도 어디에서도 접근할 수 있다.
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class SingletonBase
{
protected:
	static T* instance;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* GetSingleton();	// instance를 외부에 노출
	void ReleaseSingleton();	// 메모리 할당된 instance 해제
};

// 싱글톤 초기화
template <typename T>
T* SingletonBase<T>::instance = 0;

template <typename T>
T* SingletonBase<T>::GetSingleton()
{
	if (!instance)
	{
		instance = new T;	
	}

	return instance;
}

template <typename T>
void SingletonBase<T>::ReleaseSingleton()
{
	if (instance)
	{
		delete instance;		
		instance = 0;			
	}
}