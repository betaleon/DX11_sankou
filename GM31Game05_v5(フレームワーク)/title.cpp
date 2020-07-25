#include "main.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "title.h"
#include "game.h"

void CTitle::Init()
{

}

void CTitle::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger('A'))
	{
		CManager::SetScene<CGame>();
	}

}