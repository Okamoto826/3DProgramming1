#include "Enemy.h"

void Enemy::Update()
{
	m_pos += m_movePow;
	//if (m_pos.x < 200.0f ) m_pos.x = 200.0f;


	m_drawCount++;
	m_moveCount+=6;
	m_movePow.y = float(1 * sin(DirectX::XMConvertToRadians(m_moveCount)));
	if (m_drawCount > 47)
	{
		if (m_nowMode == NowMode::skill)
		{
			m_nowMode = NowMode::idle;
		}
	
		m_drawCount = 0;
	}
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Enemy::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 120 * (m_drawCount / 6), 0, 120, 240 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 120, 240, &rc);
}

void Enemy::Init()
{
	m_tex.Load("Asset/Textures/Wisp/WispMove.png");
	m_skillTex.Load("Asset/Textures/Wisp/WispSkill.png");
	m_drawCount = 0;
	m_moveCount = rand()%360;
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_movePow = { -2.0f, 0.0f, 0.0f };
	m_mat = Math::Matrix::Identity;
	m_objType = ObjectType::Enemy;		// 種類「敵」
	m_bAlive = true;
}

void Enemy::OnHit()
{
	m_bAlive = false;
}

void Enemy::Release()
{

}
