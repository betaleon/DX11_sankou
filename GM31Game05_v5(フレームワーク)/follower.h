#pragma once

#include "game_object.h"


class CFollower : public CGameObject //�p��(�C���w���^���X)
{
private:

	CModel* m_Model;

	D3DXQUATERNION m_Quaternion;
	int m_Walkcount;
public:
	CFollower() {}
	~CFollower() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

};