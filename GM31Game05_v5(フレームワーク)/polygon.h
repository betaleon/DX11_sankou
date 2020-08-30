#pragma once
#include "game_object.h"


// globals
#define TEXTURE_FILENAME_MAX (64)
// texture data struct
typedef struct TextureFile_tag
{
	char filename[TEXTURE_FILENAME_MAX];  // path to the texture
	int width;  // width of texture
	int height; // height of texture
	int posx;	//pos x
	int posy;	//pos y
} TextureFile;


class CPolygon : public CGameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

public:
	VERTEX_3D m_vertex[4];
	int m_posx, m_posy;
	CPolygon(){}
	~CPolygon() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(const char *filename , int width, int height,int posx,int posy);
	void SetTransform(int width, int height,int posx,int posy);
};

