#include "main.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "title.h"
#include "game.h"
#include "camera.h"
#include "field.h"
#include "skydome.h"
#include "tutorial.h"
#include "polygon.h"
#include "player.h"
#include "fade.h"

int  g_TutorialPosY = 0;
float RadForTutorial = 0;
#define TUTORIAL_PRESS_MOVE 50

typedef enum TextureIndexTutorial
{
	TEXTURE_TUTORIAL,
	TEXTURE_TUTORIAL_PRESS,

	TEXTURE_INDEX_MAX

};

// texture path
TextureFile TextureFilesTutorial[TEXTURE_INDEX_MAX] = {

	{"asset/texture/tutorial.png",		1920,  1080,0,0},

	{"asset/texture/Title_press.png",	960,540,0,200},
};
class CPolygon* g_PolygonTutorial[2];

void CTutorial::Init()
{


	for (int i = 0;
		i < TEXTURE_INDEX_MAX;
		i++)
	{
		g_PolygonTutorial[i] = AddGameObject<CPolygon>(2);
		g_PolygonTutorial[i]->SetTexture(TextureFilesTutorial[i].filename,
			TextureFilesTutorial[i].width,
			TextureFilesTutorial[i].height,
			TextureFilesTutorial[i].posx,
			TextureFilesTutorial[i].posy);

	}

	AddGameObject<CFade>(2);

}

void CTutorial::Update()
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
	RadForTutorial += 1.0f;
	g_TutorialPosY = sinf(D3DXToRadian(RadForTutorial))*TUTORIAL_PRESS_MOVE;
	g_PolygonTutorial[TEXTURE_TUTORIAL_PRESS]->SetTransform(
		TextureFilesTutorial[TEXTURE_TUTORIAL_PRESS].width,
		TextureFilesTutorial[TEXTURE_TUTORIAL_PRESS].height,
		TextureFilesTutorial[TEXTURE_TUTORIAL_PRESS].posx,
		g_TutorialPosY + TextureFilesTutorial[TEXTURE_TUTORIAL_PRESS].posy);

}

