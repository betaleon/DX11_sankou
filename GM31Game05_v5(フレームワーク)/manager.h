#pragma once

class CPlayer;

class CManager
{

	static class CScene* m_Scene;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static class CScene* GetScene() { return m_Scene; }
	
	template <typename T>
	static void SetScene()
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		T* scene = new T();
		scene->Init();

		m_Scene = scene;

	}
};