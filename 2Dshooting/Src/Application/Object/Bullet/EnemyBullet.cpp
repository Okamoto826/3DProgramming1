#include "../../Scene/GameScene.h"
#include "EnemyBullet.h"
#include"../Player/Player.h"

void EnemyBullet::Update()
{
	m_pos += m_movePow;

	if (m_pos.x < -700.0f) m_bAlive = false;

	std::shared_ptr<Player> player = m_pOwner->GetPlayer();
	
			// 対象座標 - 自分座標 = 対象へのベクトル
			Math::Vector3 v;
			v = { player->GetPos().x - m_pos.x, player->GetPos().y - 85 * player->GetScale() - m_pos.y, player->GetPos().z - m_pos.z };

			// 球判定　・・・　ベクトルの長さで判定する
			if (v.Length() < 8 + 140 * player->GetScale())
			{
				player->OnHit();
				OnHit();
			}

			
		
	

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
}

void EnemyBullet::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 0, 0, 16, 16 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 16, 16, &rc);
}

void EnemyBullet::Init(Math::Vector3 _pos)
{
	m_tex.Load("Asset/Textures/EnemyBullet.png");

	m_pos = _pos;
	m_rad = { 16.0f / 2.0f, 16.0f / 2.0f, 0.0f };
	m_movePow = { 0.0f, 0.0f, 0.0f };
	m_mat = Math::Matrix::Identity;
	m_objType = ObjectType::EnemyBullet;
	m_bAlive = true;
}

void EnemyBullet::OnHit()
{
	m_bAlive = false;
}

void EnemyBullet::Release()
{

}
