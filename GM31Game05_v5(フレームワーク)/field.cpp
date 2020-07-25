
#include "main.h"
#include "renderer.h"
#include "field.h"
//#include "scene.h"

#define TILE_WIDTH 1.0f
#define TILE_HEIGHT 1.0f
#define TILE_X 100
#define TILE_Z 100
VERTEX_3D pVtx_B[(TILE_X + 1) *(TILE_Z + 1)];
unsigned int pIdx[(4 + (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1)];
void CField::Init()
{
	
	VERTEX_3D vertex[4];
	//VERTEX_3D pVtx_B[(TILE_X+1) *(TILE_Z+1) ];
	for (int i = 0, k = 0; i <= TILE_Z; i++)
	{
		for (int j = 0; j <= TILE_X; j++)
		{
			pVtx_B[k].Position = D3DXVECTOR3((-TILE_WIDTH * (TILE_X / 2.0f)) + j * TILE_WIDTH, 0.0f, (TILE_HEIGHT*(TILE_Z / 2.0f)) + (-i * TILE_HEIGHT));
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
	//vertex[0].Position	= D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
	//vertex[0].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//vertex[0].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[0].TexCoord	= D3DXVECTOR2(0.0f, 0.0f);				//1以上にするとループする
	//
	//vertex[1].Position	= D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	//vertex[1].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//vertex[1].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[1].TexCoord	= D3DXVECTOR2(50.0f, 0.0f);
	//
	//vertex[2].Position	= D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	//vertex[2].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//vertex[2].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[2].TexCoord	= D3DXVECTOR2(0.0f, 50.0f);
	//
	//vertex[3].Position	= D3DXVECTOR3(10.0f, 0.0f, -10.0f);
	//vertex[3].Normal	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//vertex[3].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[3].TexCoord	= D3DXVECTOR2(50.0f, 50.0f);
	D3D11_MAPPED_SUBRESOURCE Msr;
	//CRenderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Msr);

	//CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//unsigned int pIdx[(4 + (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1)];	//インデックスバッファの先頭ポインタの入れ物

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(unsigned int ) * ((4 + (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1));
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = pIdx;									

	//インデックスデータをバッファへ格納
	for (int i = 0, j = 0, k = (TILE_X + 1), s = 0; i < ((4 + (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1)); i++)
	{

		if (i % 2 == 0)
		{
			pIdx[i] = k;
			k++;									//kはインデックスバッファの大きい値のほう
		}
		else
		{
			pIdx[i] = j;
			j++;									//jはインデックスバッファの小さい値のほう
		}

		if (i != 0 && i + 2 * s % ((TILE_X + 1) * 2) == 0) //縮退ポリゴンの格納
		{
			pIdx[i + 1] = j - 1;
			pIdx[i + 2] = k;
			i += 2;
			s++;									//sは縮退ポリゴンのカウンタ
		}
	}

	//CRenderer::GetDeviceContext()->Map(m_IndexBuffer,0,D3D11_MAP_WRITE_DISCARD,0,&Msr);

	//pIdx = (WORD*)Msr.pData;


	//CRenderer::GetDeviceContext()->Unmap(m_IndexBuffer, 0);

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
	CRenderer::GetDeviceContext()->DrawIndexed(((4 + (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1))/2, 0, 0);

}

/*
class CTerrain : public CGameObject //継承
{

private:

	 static const int Num = 4;

	 static double getTopLeft()		{	return 350.0;	}

	 static double getTopRight()	{	return 120.0;	}

	 static double getBottomLeft()	{	return 100.0;	}

	 static double getBottomRight()	{	return 200.0;	}

	 static double map[Num][Num] ;

	 static void generateTerrainHelper(
		 int leftIndex,
		 int rightIndex,
		 int topIndex,
		 int bottomIndex,
		 double map[Num][Num])
	 {

		 //4つの頂点の値を取得する
		 double topLeftValue = map[topIndex][leftIndex];         //左上の頂点の値
		 double topRightValue = map[topIndex][rightIndex];       //右上の頂点の値
		 double bottomLeftValue = map[bottomIndex][leftIndex];   //左下の頂点の値
		 double bottomRightValue = map[bottomIndex][rightIndex]; //右下の頂点の値

		 //正方形の中心の値を設定する
		 int centerXIndex = (leftIndex + rightIndex) / 2;
		 int centerYIndex = (topIndex + bottomIndex) / 2;
		 double centerValue = (topLeftValue + topRightValue + bottomLeftValue + bottomRightValue) / 4;

		 map[centerYIndex][centerXIndex] = centerValue;

		 //4辺の中心値を設定する
		 //上辺中心
		 double topSideValue = (topLeftValue + topRightValue) / 2.0;
		 map[topIndex][centerXIndex] = topSideValue;

		 //左辺中心
		 double leftSideValue = (topLeftValue + bottomLeftValue) / 2.0;
		 map[centerYIndex][leftIndex] = leftSideValue;

		 //右辺中心
		 double rightSideValue = (topRightValue + bottomRightValue) / 2.0;
		 map[centerYIndex][rightIndex] = rightSideValue;

		 //下辺中心
		 double bottomSideValue = (bottomLeftValue + bottomRightValue) / 2.0;
		 map[bottomIndex][centerXIndex] = bottomSideValue;


		 //現在の四角形の大きさを取得する
		 int squareSize = rightIndex - leftIndex;

		 //一回り小さい四角形の一辺の長さを取得する
		 int innerSquareSize = squareSize / 2;

		 //もし一回り小さい四角形の大きさが1（点4つからなる四角形）なら、処理を中断する
		 if (innerSquareSize <= 1) { return; }

		 //現在処理している四角形より
		 //一回り小さい4つの四角形に対して、同様の処理を行う
		 for (int x = 0; x < 2; x++)
		 {
			 for (int y = 0; y < 2; y++)
			 {
				 int innerLeftIndex = leftIndex + innerSquareSize * x;
				 int innerRightIndex = leftIndex + innerSquareSize * (x + 1);
				 int innerTopIndex = topIndex + innerSquareSize * y;
				 int innerBottomIndex = topIndex + innerSquareSize * (y + 1);
				 generateTerrainHelper
				 (innerLeftIndex,
					 innerRightIndex,
					 innerTopIndex,
					 innerBottomIndex,
					 map);
			 }
		 }

	 }

public:
	CTerrain(){}
	~CTerrain(){}

	 static double generateTerrain(	
		double topLeftValue,
		double topRightValue,
		double bottomLeftValue,
		double bottomRightValue,
		int length) 
	 {
		 CTerrain* terrain = new CTerrain();
		Num = length;
		//length*lengthの2次元配列を生成する
		double map = new double[length][length];

		//4つの頂点の値を設定する
		map[0][0] = topLeftValue;
		map[0][length - 1] = topRightValue;
		map[length - 1][0] = bottomLeftValue;
		map[length - 1][length - 1] = bottomRightValue;

		//再帰処理により、各点の値を求める
		generateTerrainHelper(0, length - 1, 0, length - 1, map);

		return map;
	}

	 static void Generate()
	 {

		 //生成
		 double map[Num][Num] = generateTerrain(
			 getTopLeft(),
			 getTopRight(),
			 getBottomLeft(),
			 getBottomRight(),
			 5);

	 }


	

};
*/