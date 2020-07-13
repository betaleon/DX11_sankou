#pragma once

#include "game_object.h"


class CPlayer : public CGameObject //Œp³(ƒCƒ“ƒwƒŠƒ^ƒ“ƒX)
{
private:

	CModel* m_Model;

public:
	CPlayer(){}
	~CPlayer(){}

	void Init();
	void Uninit();
	void Update();
	void Draw();

};