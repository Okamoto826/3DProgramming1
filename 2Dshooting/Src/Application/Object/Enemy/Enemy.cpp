#include "Enemy.h"
#include"../Player/Player.h"
#include "../../Scene/GameScene.h"
#include "../../Object/Bullet/EnemyBullet.h"

void Enemy::Update()
{
	
	m_drawCount++;
	m_moveCount += 6;
	if (m_nowMode == NowMode::idle)
	{
		m_pos += m_movePow;
		m_movePow.y = float(1 * sin(DirectX::XMConvertToRadians(m_moveCount)));
		if (m_pos.x < m_MiniX) m_pos.x = m_MiniX;
		if (m_drawCount > 47)
		{
			m_drawCount = 0;
		}
		std::shared_ptr<Player> player = m_pOwner->GetPlayer();

		// 対象座標 - 自分座標 = 対象へのベクトル
		Math::Vector3 v;
		v = { player->GetPos().x - m_pos.x, player->GetPos().y - 85 * player->GetScale() - m_pos.y, player->GetPos().z - m_pos.z };

		// 球判定　・・・　ベクトルの長さで判定する
		if (v.Length() <800&&m_pos.x<650)
		{
			if(m_coolTime>=120)
			{
				m_nowMode = NowMode::skill;
			}
		}
	}
	
	if (m_nowMode == NowMode::down)
	{
		if (m_drawCount > 47)
		{
			std::shared_ptr<Player> player = m_pOwner->GetPlayer();
			player->BreakEnemy();
			m_bAlive = false;
		}
	}


	if (m_nowMode == NowMode::skill)
	{
		if (m_drawCount == 24)
		{
			std::shared_ptr<Player> player = m_pOwner->GetPlayer();

			std::shared_ptr<EnemyBullet> Enemybullet;
			Enemybullet = std::make_shared<EnemyBullet>();
			Math::Vector3 setPos = { float(m_pos.x),float(m_pos.y - 20), m_pos.z };
			Enemybullet->Init(setPos);
			float angle = atan2(player->GetPos().y - m_pos.y - 20, player->GetPos().x - m_pos.x);
			Enemybullet->SetMovePow({ cos(angle)*4,sin(angle)*4,0});
			Enemybullet->SetOwner(m_pOwner);
			m_pOwner->AddObject(Enemybullet);
		}
		if (m_drawCount > 47)
		{
			m_coolTime = 0;
			m_nowMode = NowMode::idle;
			
		}
	}
	
	
	m_coolTime++;

		
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Enemy::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 120 * (m_drawCount / 6), 0, 120, 240 };
	if(m_nowMode==NowMode::idle)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 120, 240, &rc);
	}
	if (m_nowMode == NowMode::skill)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_skillTex, 0, 0, 120, 240, &rc);
	}
	if(m_nowMode==NowMode::down)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_downTex, 0, 0, 120, 240, &rc);
	}
}

void Enemy::Init()
{
	m_tex.Load("Asset/Textures/Wisp/WispMove.png");
	m_skillTex.Load("Asset/Textures/Wisp/WispSkill.png");
	m_downTex.Load("Asset/Textures/Wisp/WispDown.png");
	m_drawCount = 0;
	m_moveCount = rand()%360;
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_movePow = { -2.0f, 0.0f, 0.0f };
	m_mat = Math::Matrix::Identity;
	m_objType = ObjectType::Enemy;		// 種類「敵」
	m_bAlive = true;
	m_nowMode = NowMode::idle;
	m_MiniX = rand() % 100 + 180;
	m_coolTime = 0;
}

void Enemy::OnHit()
{
	if (m_nowMode == NowMode::down)return;

	m_drawCount = 0;
	m_nowMode = NowMode::down;

}

void Enemy::Release()
{

}
