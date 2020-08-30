#include "main.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "title.h"
#include "camera.h"
#include "field.h"
#include "skydome.h"
#include "game.h"
#include "polygon.h"
#include "player.h"
CPlayer* player;
void CTitle::Init()
{

	AddGameObject<CCamera>(0);

	AddGameObject<CField>(1);
	AddGameObject<CSkydome>(1);
	player = AddGameObject<CPlayer>(1);

	// texture path
	TextureFile TextureFilesTitle[] = {
		{"asset/texture/Title_logo_3.png",	1920,  1080},
		{"asset/texture/Title_logo_2.png",	1920,  1080},
		{"asset/texture/Title_logo_1.png",	1920,  1080},


	};
	for (int i = 0;
		i < sizeof(TextureFilesTitle) / sizeof(TextureFilesTitle[0]);
		i++)
	{
		auto polygon = AddGameObject<CPolygon>(2);
		polygon->SetTexture(TextureFilesTitle[i].filename, 
			TextureFilesTitle[i].width, 
			TextureFilesTitle[i].height);

	}



	
}

void CTitle::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		CManager::SetScene<CGame>();
	}

}

