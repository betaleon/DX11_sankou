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

	virtual void Init() = 0;			//純粋仮想関数

	virtual void Uninit()
	{
		for (int i = 0; i < 3; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Uninit();
				if(object != nullptr)delete object;
			
			}
			m_GameObject[i].clear();	//リストのクリア
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < 3; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();		//多態性（ポリモーフィズム）
			}
			//listから条件に当てはまる要素だけ削除する
			m_GameObject[i].remove_if([](CGameObject* object) { return object->Destroy(); });	//ラムダ式
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

	//template関数は引数として「型」を渡すことができる
	//cppで書いてはいけない
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
			//typeid=型を調べる関数,#include <typeinfo>必要
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
		std::vector<T*>objects;	//STLの配列

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