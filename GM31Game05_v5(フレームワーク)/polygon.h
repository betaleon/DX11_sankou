#pragma once
#include "game_object.h"


// globals
#define TEXTURE_FILENAME_MAX (64)
/*
typedef enum TextureIndex
{
	TEXTURE_TITLE_LOGO_3,
	TEXTURE_TITLE_LOGO_2,
	TEXTURE_TITLE_LOGO_1,

	TEXTURE_INDEX_MAX

};
*/
// texture data struct
typedef struct TextureFile_tag
{
	char filename[TEXTURE_FILENAME_MAX];  // path to the texture
	int width;  // width of texture
	int height; // height of texture
} TextureFile;


class CPolygon : public CGameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

public:
	VERTEX_3D m_vertex[4];
	CPolygon(){}
	~CPolygon() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(const char *filename , int width, int height);

};

