
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "debugimgui.h"
#include "imgui.h"
#include "model.h"
#include "player.h"
#include "game.h"
#include "title.h"

CScene* CManager::m_Scene = nullptr;

void CManager::Init()
{

	CRenderer::Init();
	CDebugGui::Init();
	CInput::Init();

	//m_Scene = new CScene();
	//m_Scene = new CGame();
	//m_Scene->Init();

	SetScene<CTitle>();

}

void CManager::Uninit()
{

	m_Scene->Uninit();
	delete m_Scene;

	CInput::Uninit();
	CDebugGui::Finalize();
	CRenderer::Uninit();
}

void CManager::Update()
{
	CInput::Update();
	CDebugGui::Update();

	m_Scene->Update();
}

void CManager::Draw()
{

	CRenderer::Begin();
	CDebugGui::Begin();

	LIGHT light;
	light.Enable = false;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetLight(light);

	m_Scene->Draw();
	
	ImGui::Begin("Debug");
	
	CPlayer* pPlayer = m_Scene->GetGameObject<CPlayer>(1);
	if (pPlayer != NULL)
	{
		ImGui::Text("PlayerSize");
		static float a = 1.0f;
		pPlayer->SetScale(D3DXVECTOR3(a, a, a));
		ImGui::SliderFloat("a", &a, 0.0f, 2.0f);
	}
	
	ImGui::End();
	

	CDebugGui::End();
	CRenderer::End();
}
