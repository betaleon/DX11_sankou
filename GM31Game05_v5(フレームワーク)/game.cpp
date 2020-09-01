#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "camera.h"
#include "field.h"
#include "skydome.h"
#include "model.h"
#include "player.h"
#include "polygon.h"
#include "score.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "fade.h"


void CGame::Init()
{
	CBullet::Load();
	//CExplosion::Load();
	

	AddGameObject<CCamera>(0);

	AddGameObject<CField>(1);
	AddGameObject<CSkydome>(1);
	AddGameObject<CPlayer>(1);

	//AddGameObject<CPolygon>(2);
	for (int i = 0; i < 100; i++)
	{
		AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(rand()%500-300.0f, 2.0f, rand()%500-300.0f));
	}


	AddGameObject<CScore>(2);
	AddGameObject<CFade>(2);

}

void CGame::Uninit()
{
	CScene::Uninit();

	CBullet::Unload();
	//CExplosion::Unload();
}

void CGame::Update()
{
	CScene::Update();
	CFade* pFade = GetGameObject<CFade>(2);

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		pFade->SetFadeOut();
		//CManager::SetScene<CResult>();
	}

	if (pFade->GetSceneChangeFlg() == TRUE)
	{
		CManager::SetScene<CResult>();
	}

}