#include "../../Scene/GameScene.h"
#include "Bullet.h"

void Bullet::Update()
{
	if(m_nowMode==NowMode::idle)
	{
		m_pos += m_movePow;

		if (m_pos.x > 720.0f + m_rad.y * m_scale) m_bAlive = false;

		for (auto& obj : m_pOwner->GetObjList())
		{
			// ↓これはないほうが軽い
			//if (obj->GetObjType() == ObjectType::Bullet) continue;
			//if (obj->GetObjType() == ObjectType::Player) continue;
			// ※このifの後に処理があるならcontinueした方が良い
			if (obj->GetObjType() == ObjectType::Enemy)
			{
				// 対象座標 - 自分座標 = 対象へのベクトル
				Math::Vector3 v;
				v = obj->GetPos() - m_pos;

				// 球判定　・・・　ベクトルの長さで判定する
				if (v.Length() < 40.0f + 16 * m_scale)
				{
					obj->OnHit();
					OnHit();
				}
			}
			if (obj->GetObjType() == ObjectType::EnemyBullet)
			{
				// 対象座標 - 自分座標 = 対象へのベクトル
				Math::Vector3 v;
				v = obj->GetPos() - m_pos;

				// 球判定　・・・　ベクトルの長さで判定する
				if (v.Length() < 8.0f + 16 * m_scale)
				{
					obj->OnHit();
				}
			}
		}
		if (m_lifeCount > 90)
		{
			m_scale *= 0.98;
		}
		if (m_lifeCount > 120)
		{
			m_bAlive = false;
		}
	}

	if (m_nowMode == NowMode::Exp)
	{
		m_scale += 0.2;
		for (auto& obj : m_pOwner->GetObjList())
		{
			// ↓これはないほうが軽い
			//if (obj->GetObjType() == ObjectType::Bullet) continue;
			//if (obj->GetObjType() == ObjectType::Player) continue;
			// ※このifの後に処理があるならcontinueした方が良い
			if (obj->GetObjType() == ObjectType::Enemy)
			{
				// 対象座標 - 自分座標 = 対象へのベクトル
				Math::Vector3 v;
				v = obj->GetPos() - m_pos;

				// 球判定　・・・　ベクトルの長さで判定する
				if (v.Length() < 40.0f + 16 * m_scale)
				{
					obj->OnHit();
					OnHit();
				}
			}
			if (obj->GetObjType() == ObjectType::EnemyBullet)
			{
				// 対象座標 - 自分座標 = 対象へのベクトル
				Math::Vector3 v;
				v = obj->GetPos() - m_pos;

				// 球判定　・・・　ベクトルの長さで判定する
				if (v.Length() < 8.0f + 16 * m_scale)
				{
					obj->OnHit();
				}
			}
		}

	}
	m_drawCount++;
	m_lifeCount++;
	
	if (m_drawCount > 15)
	{
		m_drawCount = 0;
		if (m_nowMode == NowMode::Exp)m_bAlive = false;
	}
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale(m_scale);
	m_mat = m_scaleMat * transMat;
}

void Bullet::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 32*(m_drawCount/4), 0, 32, 32};
	if(m_nowMode==NowMode::idle)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 32, 32, &rc);
	}
	if (m_nowMode == NowMode::Exp)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_expTex, 0, 0, 32, 32, &rc);
	}
}

void Bullet::Init(Math::Vector3 _pos)
{
	m_tex.Load("Asset/Textures/Bles.png");
	m_expTex.Load("Asset/Textures/Exp.png");

	m_pos = _pos;
	m_rad = { 16.0f, 16.0f, 0.0f };
	m_movePow = { 5.0f, 0.0f, 0.0f };
	m_mat = Math::Matrix::Identity;
	m_objType = ObjectType::Bullet;
	m_bAlive = true;
	m_nowMode = NowMode::idle;
	m_lifeCount = 0;
}

void Bullet::OnHit()
{
	if(m_nowMode==NowMode::idle)
	{
		if (m_scale < 2.2)
		{
			m_bAlive = false;
		}
		else
		{
			m_nowMode = NowMode::Exp;
			m_drawCount = 0;
		}
	}
}

void Bullet::Release()
{

}
