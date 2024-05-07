#include "../../Scene/GameScene.h"
#include "Bullet.h"

void Bullet::Update()
{
	m_pos += m_movePow;

	if (m_pos.x > 720.0f+m_rad.y+m_scale) m_bAlive = false;

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
			if (v.Length() < 40.0f+16*m_scale)
			{
				obj->OnHit();
				OnHit();
			}

			break;
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
				OnHit();
			}

			break;
		}
	}
	m_drawCount++;
	if (m_drawCount > 15)m_drawCount = 0;
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale(m_scale);
	m_mat = m_scaleMat * transMat;
}

void Bullet::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 32*(m_drawCount/4), 0, 32, 32};
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 32, 32, &rc);
}

void Bullet::Init(Math::Vector3 _pos)
{
	m_tex.Load("Asset/Textures/Bles.png");

	m_pos = _pos;
	m_rad = { 16.0f, 16.0f, 0.0f };
	m_movePow = { 10.0f, 0.0f, 0.0f };
	m_mat = Math::Matrix::Identity;
	m_objType = ObjectType::Bullet;
	m_bAlive = true;
}

void Bullet::OnHit()
{
	m_bAlive = false;
}

void Bullet::Release()
{

}
