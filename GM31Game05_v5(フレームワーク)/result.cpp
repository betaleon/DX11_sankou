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
#include "result.h"

int g_ResultPosY = 0;
float RadForResult = 0;
#define RESULT_PRESS_MOVE 50

typedef enum TextureIndexResult
{
	TEXTURE_RESULT_BACK,
	TEXTURE_RESULT_PRESS,
	TEXTURE_RESULT_A,
	TEXTURE_RESULT_B,
	TEXTURE_RESULT_C,

	TEXTURE_INDEX_MAX

};

// texture path
TextureFile TextureFilesResult[] = {

	{"asset/texture/result_back.png",	1920,  1080,0,0},
	{"asset/texture/result_press.png",	1920,  1080,0,0},
	{"asset/texture/result_A.png",	400,  400,0,0},
	{"asset/texture/result_B.png",	400,  400,0,0},
	{"asset/texture/result_C.png",	400,  400,0,0},

};

class CPolygon*  g_PolygonResult[sizeof(TextureFilesResult) / sizeof(TextureFilesResult[0])];

void CResult::Init()
{
	for (int i = 0;
		i < sizeof(TextureFilesResult) / sizeof(TextureFilesResult[0]);
		i++)
	{
		g_PolygonResult[i] = AddGameObject<CPolygon>(2);
		g_PolygonResult[i]->SetTexture(TextureFilesResult[i].filename,
			TextureFilesResult[i].width,
			TextureFilesResult[i].height,
			TextureFilesResult[i].posx,
			TextureFilesResult[i].posy);

	}
	AddGameObject<CFade>(2);
}

void CResult::Update()
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
		CManager::SetScene<CTitle>();
	}
	//RadForTitle += 1.0f;
	//g_TitlePosX = 0;//sinf(D3DXToRadian(RadForTitle));

	g_PolygonResult[TEXTURE_RESULT_BACK]->SetTransform(
		TextureFilesResult[TEXTURE_RESULT_BACK].width,
		TextureFilesResult[TEXTURE_RESULT_BACK].height,
		TextureFilesResult[TEXTURE_RESULT_BACK].posx,
		TextureFilesResult[TEXTURE_RESULT_BACK].posy);



	RadForResult += 2.0f;
	g_ResultPosY = sinf(D3DXToRadian(RadForResult))*RESULT_PRESS_MOVE;
	g_PolygonResult[TEXTURE_RESULT_PRESS]->SetTransform(
		TextureFilesResult[TEXTURE_RESULT_PRESS].width,
		TextureFilesResult[TEXTURE_RESULT_PRESS].height,
		TextureFilesResult[TEXTURE_RESULT_PRESS].posx,
		g_ResultPosY + TextureFilesResult[TEXTURE_RESULT_PRESS].posy);
}
