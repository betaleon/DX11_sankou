#pragma once

#include "game_object.h"


class CExplosion : public CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer;
	ID3D11ShaderResourceView*	m_Texture;

	int m_Count;
public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

};