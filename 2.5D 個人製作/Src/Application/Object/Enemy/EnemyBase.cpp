#include "EnemyBase.h"
#include"../../Scene/SceneManager.h"
void EnemyBase::Update()
{
	if (d == 0)
	{
		m_pos.y -= m_gravity;
		m_gravity += 0.005;
	}
	m_atkCoolTime++;
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void EnemyBase::PostUpdate()
{
	// ================================================
	// レイ判定
	// ================================================

	// レイ判定用に変数を作成
	KdCollider::RayInfo ray;
	// レイの発射位置を指定
	ray.m_pos = m_pos;
	// レイの発射方向
	ray.m_dir = Math::Vector3::Down;
	// 少し高いところから飛ばす
	ray.m_pos.y += 0.1f;
	// 段差の許容範囲を設定
	float enableStepHigh = 0.2;
	ray.m_pos.y += enableStepHigh;

	// レイの長さを設定
	ray.m_range = m_gravity + enableStepHigh;
	// 当たり判定をしたいタイプを設定
	ray.m_type = KdCollider::TypeGround;

	// デバッグ用
	//m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);


	// レイに当たったオブジェクト情報を格納
	std::list<KdCollider::CollisionResult> retRayList;

	// 当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(ray, &retRayList);
	}

	// レイに当たったリストから一番近いオブジェクトを検出
	float maxOverLap = 0;
	Math::Vector3 hitPos;
	bool isHit = false;
	for (auto& ret : retRayList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			isHit = true;
		}
	}
	if (isHit)
	{
		// 一番近くの地面に当たっている
		m_pos = hitPos + Math::Vector3(0, -0.1f, 0);
		m_gravity = 0;
	}
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void EnemyBase::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void EnemyBase::DrawLit()
{
	d -= 0.01;
	if (d < 0)d = 0;
	if (d != 0)
	{
		KdShaderManager::Instance().m_StandardShader.SetDissolve(d);
	}
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void EnemyBase::Init()
{
	m_pos = { 0,-2.5,0 };
	m_dir = {};
	m_nowSit = 0;
	m_gravity = 0.0f;
	m_atkCoolTime = 0;
	d = 1;
	// 奥側に座標(ワールド行列)を更新しておく
	m_mWorld = Math::Matrix::Identity;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_objectType = ObjectType::Enemy;
}

void EnemyBase::ChangeAnimation()
{
}

void EnemyBase::Atack()
{
}

void EnemyBase::OnHit(float _dmg)
{
}

