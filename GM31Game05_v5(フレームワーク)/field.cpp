
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
	//�@���x�N�g���̐ݒ�
	for (int i = 0; i < (TILE_X + 1)*(TILE_Z + 1); i++)
	{
		pVtx_B[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	//���ˌ��̐ݒ�(�F)
	for (int i = 0; i < (TILE_X + 1)*(TILE_Z + 1); i++)
	{
		pVtx_B[i].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@����
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
	//vertex[0].TexCoord	= D3DXVECTOR2(0.0f, 0.0f);				//1�ȏ�ɂ���ƃ��[�v����
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

	//unsigned int pIdx[(4 + (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1)];	//�C���f�b�N�X�o�b�t�@�̐擪�|�C���^�̓��ꕨ

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(unsigned int ) * ((4 + (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1));
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = pIdx;									

	//�C���f�b�N�X�f�[�^���o�b�t�@�֊i�[
	for (int i = 0, j = 0, k = (TILE_X + 1), s = 0; i < ((4 + (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1)); i++)
	{

		if (i % 2 == 0)
		{
			pIdx[i] = k;
			k++;									//k�̓C���f�b�N�X�o�b�t�@�̑傫���l�̂ق�
		}
		else
		{
			pIdx[i] = j;
			j++;									//j�̓C���f�b�N�X�o�b�t�@�̏������l�̂ق�
		}

		if (i != 0 && i + 2 * s % ((TILE_X + 1) * 2) == 0) //�k�ރ|���S���̊i�[
		{
			pIdx[i + 1] = j - 1;
			pIdx[i + 2] = k;
			i += 2;
			s++;									//s�͏k�ރ|���S���̃J�E���^
		}
	}

	//CRenderer::GetDeviceContext()->Map(m_IndexBuffer,0,D3D11_MAP_WRITE_DISCARD,0,&Msr);

	//pIdx = (WORD*)Msr.pData;


	//CRenderer::GetDeviceContext()->Unmap(m_IndexBuffer, 0);

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);

	//�e�N�X�`���ǂݍ���
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
	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//IndexBuffer setting
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);

	//�e�N�X�`���ݒ�
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�^
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	CRenderer::GetDeviceContext()->DrawIndexed(((4 + (TILE_X - 1) * 2)*TILE_Z + 2 * (TILE_Z - 1))/2, 0, 0);

}

/*
class CTerrain : public CGameObject //�p��
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

		 //4�̒��_�̒l���擾����
		 double topLeftValue = map[topIndex][leftIndex];         //����̒��_�̒l
		 double topRightValue = map[topIndex][rightIndex];       //�E��̒��_�̒l
		 double bottomLeftValue = map[bottomIndex][leftIndex];   //�����̒��_�̒l
		 double bottomRightValue = map[bottomIndex][rightIndex]; //�E���̒��_�̒l

		 //�����`�̒��S�̒l��ݒ肷��
		 int centerXIndex = (leftIndex + rightIndex) / 2;
		 int centerYIndex = (topIndex + bottomIndex) / 2;
		 double centerValue = (topLeftValue + topRightValue + bottomLeftValue + bottomRightValue) / 4;

		 map[centerYIndex][centerXIndex] = centerValue;

		 //4�ӂ̒��S�l��ݒ肷��
		 //��Ӓ��S
		 double topSideValue = (topLeftValue + topRightValue) / 2.0;
		 map[topIndex][centerXIndex] = topSideValue;

		 //���Ӓ��S
		 double leftSideValue = (topLeftValue + bottomLeftValue) / 2.0;
		 map[centerYIndex][leftIndex] = leftSideValue;

		 //�E�Ӓ��S
		 double rightSideValue = (topRightValue + bottomRightValue) / 2.0;
		 map[centerYIndex][rightIndex] = rightSideValue;

		 //���Ӓ��S
		 double bottomSideValue = (bottomLeftValue + bottomRightValue) / 2.0;
		 map[bottomIndex][centerXIndex] = bottomSideValue;


		 //���݂̎l�p�`�̑傫�����擾����
		 int squareSize = rightIndex - leftIndex;

		 //���菬�����l�p�`�̈�ӂ̒������擾����
		 int innerSquareSize = squareSize / 2;

		 //�������菬�����l�p�`�̑傫����1�i�_4����Ȃ�l�p�`�j�Ȃ�A�����𒆒f����
		 if (innerSquareSize <= 1) { return; }

		 //���ݏ������Ă���l�p�`���
		 //���菬����4�̎l�p�`�ɑ΂��āA���l�̏������s��
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
		//length*length��2�����z��𐶐�����
		double map = new double[length][length];

		//4�̒��_�̒l��ݒ肷��
		map[0][0] = topLeftValue;
		map[0][length - 1] = topRightValue;
		map[length - 1][0] = bottomLeftValue;
		map[length - 1][length - 1] = bottomRightValue;

		//�ċA�����ɂ��A�e�_�̒l�����߂�
		generateTerrainHelper(0, length - 1, 0, length - 1, map);

		return map;
	}

	 static void Generate()
	 {

		 //����
		 double map[Num][Num] = generateTerrain(
			 getTopLeft(),
			 getTopRight(),
			 getBottomLeft(),
			 getBottomRight(),
			 5);

	 }


	

};
*/