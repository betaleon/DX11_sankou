#pragma once
#include "game_object.h"

#define FIGURE_NUM 3
#define SCORE_SPEED 3.0f

class CScore :public CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	float m_Score;
	float m_FinalScore;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void AddScore(int value) { m_FinalScore += value/2.0f; };
	float GetScore() { return m_FinalScore; };
};