#include "main.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "title.h"
#include "game.h"
#include "polygon.h"

void CTitle::Init()
{
	AddGameObject<CPolygon>(2);
}

void CTitle::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger('A'))
	{
		CManager::SetScene<CGame>();
	}

}

