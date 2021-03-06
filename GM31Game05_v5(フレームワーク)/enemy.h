#pragma once

#include "game_object.h"


class CEnemy : public CGameObject //継承(インヘリタンス)
{
private:

	class CModel* m_Model;
	//前方宣言(ポインタ変数の有効)
	int m_Walkcount;

public:
	CEnemy() {}
	~CEnemy() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

};