#pragma once

#include "game_object.h"


class CEnemy : public CGameObject //�p��(�C���w���^���X)
{
private:

	class CModel* m_Model;
	//�O���錾(�|�C���^�ϐ��̗L��)
	int m_Walkcount;

public:
	CEnemy() {}
	~CEnemy() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

};