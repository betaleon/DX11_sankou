#include "main.h"
#include "renderer.h"
#include "score.h"
#include "scene.h"
#include "manager.h"

#define SCORE_POS_X 500
#define SCORE_POS_Y 600
#define SCORE_WIDTH 100/5.0F
#define SCORE_HEIGHT 50/2.0F

void CScore::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(- 1.0f, 1.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);				//1以上にするとループする
	
	vertex[1].Position = D3DXVECTOR3(+ 1.0f, 1.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	
	vertex[2].Position = D3DXVECTOR3(- 1.0f, -1.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	
	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;				//重要

	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	//重要

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"asset/texture/score.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);

	//m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	
	m_Score = 0;
	m_FinalScore = 0;
}

void CScore::Uninit()
{

	m_VertexBuffer->Release();
	m_Texture->Release();

}

void CScore::Update()
{
	if (m_Score < m_FinalScore)
	{ m_Score += SCORE_SPEED; }
	else
	{ m_Score = m_FinalScore; }
}

void CScore::Draw()
{
	int fig = 0;
	int s = m_Score;
	float x = SCORE_POS_X;
	float y = SCORE_POS_Y;
	do
	{
		int n = s % 10;
		float u = n % 5 * 0.2f;
		float v = n / 5 * 0.5f;
		D3D11_MAPPED_SUBRESOURCE msr;
		CRenderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = D3DXVECTOR3(x - (SCORE_WIDTH / 2) , y - (SCORE_HEIGHT / 2) , 0.0f);
		//vertex[0].Position = D3DXVECTOR3(500, 500, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(u, v);

		vertex[1].Position = D3DXVECTOR3(x + (SCORE_WIDTH / 2)  , y - (SCORE_HEIGHT / 2) , 0.0f);
		//vertex[1].Position = D3DXVECTOR3(600, 500, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(u + 0.2f, v);

		vertex[2].Position = D3DXVECTOR3(x - (SCORE_WIDTH / 2) , y + (SCORE_HEIGHT / 2) , 0.0f);
		//vertex[2].Position = D3DXVECTOR3(500,600, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(u, v + 0.5f);

		vertex[3].Position = D3DXVECTOR3(x + (SCORE_WIDTH / 2), y + (SCORE_HEIGHT / 2) , 0.0f);
		//vertex[3].Position = D3DXVECTOR3(600,600, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(u + 0.2f, v + 0.5f);

		CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

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

		//次の位を表示するために10で割る
		s *= 0.1F;

		//表示位置を左にずらす
		x -= SCORE_WIDTH;

		fig++;
	} while (fig < FIGURE_NUM);
}
