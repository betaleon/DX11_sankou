
#include "main.h"
#include "renderer.h"
#include "field.h"
//#include "scene.h"

#define TILE_WIDTH	10.0f
#define TILE_HEIGHT 10.0f
#define TILE_X 100
#define TILE_Z 100
VERTEX_3D pVtx_B[(TILE_X + 1) *(TILE_Z + 1)];
unsigned int pIdx[((4 + (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1))];

void	diamondSquare(int Array[TILE_X+1][TILE_Z+1], int size);
void	squareStep(int Array[TILE_X+1][TILE_Z+1], int x, int z, int reach);
void	diamondStep(int Array[TILE_X+1][TILE_Z+1], int x, int z, int reach);
float	random(int range);

void CField::Init()
{
	int Array[TILE_X+1][TILE_Z+1] = {};
	diamondSquare(Array,TILE_X);
	for (int i = 0, k = 0; i <= TILE_Z; i++)
	{
		for (int j = 0; j <= TILE_X; j++)
		{
			pVtx_B[k].Position = D3DXVECTOR3((-TILE_WIDTH * (TILE_X / 2.0f)) + j * TILE_WIDTH, Array[i][j], (TILE_HEIGHT*(TILE_Z / 2.0f)) + (-i * TILE_HEIGHT));
			pVtx_B[k].TexCoord = D3DXVECTOR2((1.0f*j) / (1.0f*TILE_X), (1.0f*i) / (1.0f*TILE_Z));
			k++;
		}
	}
	//法線ベクトルの設定
	for (int i = 0; i < (TILE_X + 1)*(TILE_Z + 1); i++)
	{
		pVtx_B[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	//反射光の設定(色)
	for (int i = 0; i < (TILE_X + 1)*(TILE_Z + 1); i++)
	{
		pVtx_B[i].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * (TILE_X + 1)*(TILE_Z + 1);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = pVtx_B;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);							

	//インデックスデータをバッファへ格納
	for (int i = 0, j = 0, k = (TILE_X + 1), s = 0; i < ((4 + (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1)); i++)
	{

		if (i % 2 == 0)
		{
			pIdx[i+s] = k;
			k++;											//kはインデックスバッファの大きい値のほう
		}
		else
		{
			pIdx[i+s] = j;	
			j++;											//jはインデックスバッファの小さい値のほう
		}

		if ((i + 1) % ((TILE_X + 1) * 2) == 0)	//縮退ポリゴンの格納
		{
			pIdx[i + s + 1] = j-1;
			pIdx[i + s + 2] = k;
			s += 2;											//sは縮退ポリゴンのカウンタ
		}
	}
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(unsigned int) * ((4 + (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1));
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = pIdx;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"asset/texture/grass.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);

	m_Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);

}

void CField::Uninit()
{

	m_VertexBuffer->Release();
	m_Texture->Release();

}

void CField::Update()
{


}

void CField::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//IndexBuffer setting
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
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
	CRenderer::GetDeviceContext()->DrawIndexed((4+( (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1)), 0, 0);

}



void diamondSquare(int Array[TILE_X+1][TILE_Z+1], int size)
{
	int half = size / 2;
	if (half < 1)
		return;
	//square steps
	for (int z = half; z < TILE_Z; z += size)
		for (int x = half; x < TILE_X; x += size)
			squareStep(Array, x % TILE_X, z % TILE_Z, half);
	// diamond steps
	int col = 0;
	for (int x = 0; x < TILE_X; x += half)
	{
		col++;
		//If this is an odd column.
		if (col % 2 == 1)
			for (int z = half; z < TILE_Z; z += size)
				diamondStep(Array, x % TILE_X, z % TILE_Z, half);
		else
			for (int z = 0; z < TILE_Z; z += size)
				diamondStep(Array, x % TILE_X, z % TILE_Z, half);
	}
	diamondSquare(Array, size / 2);
}

void squareStep(int Array[TILE_X+1][TILE_Z+1], int x, int z, int reach)
{
	int count = 0;
	float avg = 10.0f;
	if (x - reach >= 0 && z - reach >= 0)
	{
		avg += Array[x - reach][z - reach];
		count++;
	}
	if (x - reach >= 0 && z + reach < TILE_Z)
	{
		avg += Array[x - reach][z + reach];
		count++;
	}
	if (x + reach < TILE_X && z - reach >= 0)
	{
		avg += Array[x + reach][z - reach];
		count++;
	}
	if (x + reach < TILE_X && z + reach < TILE_Z)
	{
		avg += Array[x + reach][z + reach];
		count++;
	}
	avg += random(reach);
	avg /= count;
	Array[x][z] = round(avg);
}

void diamondStep(int Array[TILE_X+1][TILE_Z+1], int x, int z, int reach)
{
	int count = 0;
	float avg = 10.0f;
	if (x - reach >= 0)
	{
		avg += Array[x - reach][z];
		count++;
	}
	if (x + reach < TILE_X)
	{
		avg += Array[x + reach][z];
		count++;
	}
	if (z - reach >= 0)
	{
		avg += Array[x][z - reach];
		count++;
	}
	if (z + reach < TILE_Z)
	{
		avg += Array[x][z + reach];
		count++;
	}
	avg += random(reach);
	avg /= count;
	Array[x][z] = (int)avg;
}

float random(int range)
{
	return (rand() % (range * 2)) - range;
}