#pragma once
#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "game_object.h"

class CScene
{

protected:
	std::list<CGameObject*> m_GameObject[3];

public:
	CScene(){}
	virtual ~CScene(){}

	virtual void Init() = 0;			//�������z�֐�

	virtual void Uninit()
	{
		for (int i = 0; i < 3; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Uninit();
				if(object != nullptr)delete object;
			
			}
			m_GameObject[i].clear();	//���X�g�̃N���A
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < 3; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();		//���Ԑ��i�|�����[�t�B�Y���j
			}
			//list��������ɓ��Ă͂܂�v�f�����폜����
			m_GameObject[i].remove_if([](CGameObject* object) { return object->Destroy(); });	//�����_��
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < 3; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}

	}

	//template�֐��͈����Ƃ��āu�^�v��n�����Ƃ��ł���
	//cpp�ŏ����Ă͂����Ȃ�
	template <typename T>
	T* AddGameObject(int Layer)
	{

		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
		
	}

	template <typename T>
	T* GetGameObject(int Layer)
	{

		for (CGameObject* object : m_GameObject[Layer]) {
			//typeid=�^�𒲂ׂ�֐�,#include <typeinfo>�K�v
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}
		return nullptr;

	}

	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*>objects;	//STL�̔z��

		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}

		return objects;
	}

};