// SingletonBase.h

#pragma once

/// <summary>
/// SingletonBase : ������Ʈ���� ���Ǵ� �⺻ �Ŵ������� �����ϱ� ���� ������� �̱��� ���� Ŭ����.
/// �̱��� �������� �������� Ŭ���� ������ ���� �ʰ� ��𿡼��� ������ �� �ִ�.
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
	static T* GetSingleton();	// instance�� �ܺο� ����
	void ReleaseSingleton();	// �޸� �Ҵ�� instance ����
};

// �̱��� �ʱ�ȭ
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