#include "main.h"
#include "renderer.h"
#include "polygon.h"

#define BASE_X (SCREEN_WIDTH / 2)
#define BASE_Y (SCREEN_HEIGHT/ 2)

#define POSITION_X 0
#define POSITION_Y 0

#define SCALE_X 1500.0f
#define SCALE_Y 1000.0f

// texture file count
//static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFiles) / sizeof(g_TextureFiles[0]);
// static const int TEXTURE_FILE_COUNT = ARRAYSIZE(g_TextureFiles); // required Windows.h

// check if texture enum length == texture file count
//static_assert(TEXTURE_INDEX_MAX == TEXTURE_FILE_COUNT, "TEXTURE_INDEX_MAX != TEXTURE_FILE_COUNT");



// stores texture data
//static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT] = {};


void CPolygon::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(BASE_X - SCALE_X/2+POSITION_X, BASE_Y - SCALE_Y/2+ POSITION_Y, 0.0f);
	vertex[0].Normal	= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= D3DXVECTOR2( 0.0f, 0.0f);
									   
	vertex[1].Position = D3DXVECTOR3(BASE_X + SCALE_X / 2 + POSITION_X, BASE_Y - SCALE_Y / 2 + POSITION_Y, 0.0f);
	vertex[1].Normal	= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	vertex[1].Diffuse	= D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f );
	vertex[1].TexCoord	= D3DXVECTOR2( 1.0f, 0.0f);
									   
	vertex[2].Position = D3DXVECTOR3(BASE_X - SCALE_X / 2 + POSITION_X, BASE_Y + SCALE_Y / 2 + POSITION_Y, 0.0f);
	vertex[2].Normal	= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	vertex[2].Diffuse	= D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f );
	vertex[2].TexCoord	= D3DXVECTOR2( 0.0f, 1.0f );

	vertex[3].Position = D3DXVECTOR3(BASE_X + SCALE_X / 2 + POSITION_X, BASE_Y + SCALE_Y / 2 + POSITION_Y, 0.0f);
	vertex[3].Normal	= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	vertex[3].Diffuse	= D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f );
	vertex[3].TexCoord	= D3DXVECTOR2( 1.0f, 1.0f );

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void CPolygon::Uninit()
{

	m_VertexBuffer->Release();
	if(m_Texture!=nullptr)
		m_Texture->Release();

}

void CPolygon::Update()
{


}

void CPolygon::Draw()
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);
	//マトリクス設定
	CRenderer::SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);

	//テクスチャ設定
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトポロジ型
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);

}

void CPolygon::SetTexture(const char * filename, int width, int height)
{
	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		filename,
		NULL,
		NULL,
		&m_Texture,
		NULL);
}
