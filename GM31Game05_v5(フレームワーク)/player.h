#pragma once

#include "game_object.h"


class CPlayer : public CGameObject //�p��(�C���w���^���X)
{
private:

	CModel* m_Model;

	D3DXQUATERNION m_Quaternion;
	int m_Walkcount;
public:
	CPlayer(){}
	~CPlayer(){}

	void Init();
	void Uninit();
	void Update();
	void Draw();

};