#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "camera.h"
#include "field.h"
#include "skydome.h"
#include "model.h"
#include "player.h"
#include "polygon.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"


void CGame::Init()
{
	CBullet::Load();
	//CExplosion::Load();
	

	AddGameObject<CCamera>(0);

	AddGameObject<CField>(1);
	AddGameObject<CSkydome>(1);
	AddGameObject<CPlayer>(1);

	//AddGameObject<CPolygon>(2);

	AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(-5.0f, 2.0f, 5.0f));
	AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(0.0f, 2.0f, 5.0f));
	AddGameObject<CEnemy>(1)->SetPosition(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

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

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CTitle>();
	}


}