#include "main.h"
#include "renderer.h"
#include "fade.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "result.h"



void CFade::Init() {
	//初期化
	m_alpha = 1.0f;
	m_fadeInFlg = true;
	m_fadeOutFlg = false;
	m_SceneChangeFlg = false;

	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);


	vertex[1].Position = D3DXVECTOR3(1920.0f, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);


	vertex[2].Position = D3DXVECTOR3(0.0f, 1080.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);


	vertex[3].Position = D3DXVECTOR3(1920.0f, 1080.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	//頂点バッファ作成
	//スコアを変更するときにはこの辺を変えることがある
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));		//構造体の中身を全部0に
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"asset/texture/fade.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	//デバッグしやすくなる
	assert(m_Texture);

}

void CFade::Uninit() {

	m_vertexBuffer->Release();
	m_Texture->Release();

}


void CFade::Update() {
	//フェードイン
	if (m_fadeInFlg == true) {
		if (m_alpha >= 0.0f) {
			m_alpha -= 0.05f;
		}
		else {
			m_fadeInFlg = false;
		}
	}
	//フェードアウト
	if (m_fadeOutFlg == true) {
		if (m_alpha <= 1.0f) {
			m_alpha += 0.03f;
		}
		else {
			m_SceneChangeFlg = true;
			m_fadeOutFlg = false;
		}
	}


}
void CFade::Draw() {


	D3D11_MAPPED_SUBRESOURCE msr;
	CRenderer::GetDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);


	vertex[1].Position = D3DXVECTOR3(1920.0f, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);


	vertex[2].Position = D3DXVECTOR3(0.0f, 1080.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);


	vertex[3].Position = D3DXVECTOR3(1920.0f, 1080.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	CRenderer::GetDeviceContext()->Unmap(m_vertexBuffer, 0);

	//ライト無効
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	//マトリクス設定
	CRenderer::SetWorldViewProjection2D();


	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(
		0, 1, &m_vertexBuffer, &stride, &offset);

	//マテリアルの設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);

	//テクスチャ設定
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);

}

void  CFade::SetFadeOut() {
	m_fadeOutFlg = true;
}

bool  CFade::GetFadeOutFlg() {
	return m_fadeOutFlg;
}

bool  CFade::GetSceneChangeFlg() {
	return m_SceneChangeFlg;
}
