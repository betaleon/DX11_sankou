#pragma once
#include "game_object.h"

class CFade : public CGameObject {
private:
	ID3D11Buffer*				m_vertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
	float m_alpha;
	bool  m_fadeOutFlg;
	bool  m_fadeInFlg;
	bool  m_SceneChangeFlg;
public:
	CFade() {}
	~CFade() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetFadeOut();
	bool GetFadeOutFlg();
	bool GetSceneChangeFlg();
};