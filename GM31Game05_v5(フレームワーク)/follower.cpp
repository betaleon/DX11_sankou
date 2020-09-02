#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
//#include "player.h"
#include "follower.h"
#include "input.h"
#include "scene.h"
#include "imgui.h"
#include "score.h"
#include "bullet.h"
#include "manager.h"
#include "title.h"
#include "enemy.h"
#include "explosion.h"
#include <typeinfo>
#include <string.h>

void CFollower::Init()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\horse_v5.obj");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXQuaternionIdentity(&m_Quaternion);

	m_Walkcount = 0;
}

void CFollower::Uninit()
{

	m_Model->Unload();
	delete m_Model;

}

void CFollower::Update()
{

	//auto a = typeid(*CManager::GetScene()).name();
	if (typeid(*CManager::GetScene()).hash_code() == typeid(CTitle).hash_code())
	{
		m_Position = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Rotation.y -= 0.005f;
	}
	else
	{
		if (CInput::GetKeyPress('A'))
		{
			m_Rotation.y -= 0.05f;
			D3DXQUATERNION quat;
			D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(-1.0F));
			m_Quaternion *= quat;
		}
		if (CInput::GetKeyPress('D'))
		{
			m_Rotation.y += 0.05f;
			D3DXQUATERNION quat;
			D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(-1.0F));
			m_Quaternion *= quat;
		}

		D3DXVECTOR3 forward = GetForward();//前方向ベクトル

		if (CInput::GetKeyPress('W'))
		{
			m_Walkcount++;
			if (m_Walkcount == 10)
			{
				m_Position += forward * 3.0f;
				D3DXQUATERNION quat;
				D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXToRadian(-90.0F));
				m_Quaternion *= quat;
				m_Walkcount = 0;
			}
		}

		if (CInput::GetKeyPress('S'))
		{
			m_Walkcount++;
			if (m_Walkcount == 10)
			{
				m_Position -= forward * 3.0f;
				D3DXQUATERNION quat;
				D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXToRadian(90.0F));
				m_Quaternion *= quat;
				m_Walkcount = 0;
			}
		}
		CScore* score = CManager::GetScene()->GetGameObject<CScore>(2);
		
		CScene* scene = CManager::GetScene();
		
		std::vector<CEnemy*> enemyList = scene->GetGameObjects<CEnemy>(1);
		
		for (CEnemy* enemy : enemyList)
		{
			D3DXVECTOR3 enemyPosition = enemy->GetPosition();
		
			D3DXVECTOR3 direction = m_Position - enemyPosition;
			float length = D3DXVec3Length(&direction);
		
			if (length < 3.0f)
			{
				scene->AddGameObject<CExplosion>(1)->SetPosition(m_Position);
				//scene->AddGameObject<CFollower>(1)->SetPosition(m_Position);
				score->AddScore(1);
				enemy->SetDestroy();
				//SetDestroy();
				//return;
			}
		}
	}

}

void CFollower::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}