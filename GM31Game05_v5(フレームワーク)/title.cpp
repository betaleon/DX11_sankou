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
#include "fade.h"

int g_TitlePosX=0,g_TitlePosY=0;
float RadForTitle = 0,RadForTitle2 = 0;
#define TITLE_HORSE_MOVE 100
#define TITLE_PRESS_MOVE 50

typedef enum TextureIndex
{
	TEXTURE_TITLE_LOGO_3,
	TEXTURE_TITLE_LOGO_2,
	TEXTURE_TITLE_LOGO_1,
	TEXTURE_TITLE_PRESS,

	TEXTURE_INDEX_MAX

};

// texture path
TextureFile TextureFilesTitle[] = {
	{"asset/texture/Title_logo_3.png",	1920,  1080,0,0},
	{"asset/texture/Title_logo_2.png",	1920,  1080,0,0},
	{"asset/texture/Title_logo_1.png",	1920,  1080,0,0},
	{"asset/texture/Title_press.png",	960,	540,0,200},


};
class CPolygon* g_polygon[sizeof(TextureFilesTitle) / sizeof(TextureFilesTitle[0])];

void CTitle::Init()
{

	AddGameObject<CCamera>(0);

	AddGameObject<CField>(1);
	AddGameObject<CSkydome>(1);
	AddGameObject<CPlayer>(1);

	for (int i = 0;
		i < sizeof(TextureFilesTitle) / sizeof(TextureFilesTitle[0]);
		i++)
	{
		g_polygon[i] = AddGameObject<CPolygon>(2);
		g_polygon[i]->SetTexture(TextureFilesTitle[i].filename, 
			TextureFilesTitle[i].width, 
			TextureFilesTitle[i].height,
			TextureFilesTitle[i].posx,
			TextureFilesTitle[i].posy);
		
	}

	AddGameObject<CFade>(2);
	
}

void CTitle::Update()
{
	CScene::Update();
	CFade* pFade = GetGameObject<CFade>(2);

	//pFade->GetFadeOutFlg();

	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		pFade->SetFadeOut();
		//CManager::SetScene<CGame>();
	}

	if (pFade->GetSceneChangeFlg() == TRUE)
	{
		CManager::SetScene<CGame>();
	}
	RadForTitle+=1.0f;
	g_TitlePosX = sinf(D3DXToRadian(RadForTitle))*TITLE_HORSE_MOVE;

	g_polygon[TEXTURE_TITLE_LOGO_2]->SetTransform(
		TextureFilesTitle[TEXTURE_TITLE_LOGO_2].width,
		TextureFilesTitle[TEXTURE_TITLE_LOGO_2].height,
		g_TitlePosX+TextureFilesTitle[TEXTURE_TITLE_LOGO_2].posx,
		TextureFilesTitle[TEXTURE_TITLE_LOGO_2].posy);

	RadForTitle2 += 2.0f;
	g_TitlePosY = sinf(D3DXToRadian(RadForTitle2))*TITLE_PRESS_MOVE;
	g_polygon[TEXTURE_TITLE_PRESS]->SetTransform(
		TextureFilesTitle[TEXTURE_TITLE_PRESS].width,
		TextureFilesTitle[TEXTURE_TITLE_PRESS].height,
		TextureFilesTitle[TEXTURE_TITLE_PRESS].posx,
		g_TitlePosY+TextureFilesTitle[TEXTURE_TITLE_PRESS].posy);

}

