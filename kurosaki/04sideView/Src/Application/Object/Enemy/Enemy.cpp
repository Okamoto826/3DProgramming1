#include "Enemy.h"

#include"../../Scene/SceneManager.h"
void Enemy::Init()
{
	m_polygon.SetMaterial("Asset/Textures/char.png");

	// 画像分割
	m_polygon.SetSplit(6, 6);

	// 原点変更
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_nowSpl = 0;
	m_gravity = 0;
	m_dir = 1;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Enemy::Update()
{
	int Walk[4] = { 3,4,3,5 };

	m_polygon.SetUVRect(Walk[(int)m_nowSpl]);
	m_nowSpl += 0.05;
	if (m_nowSpl >= 4)
	{
		m_nowSpl = 0;
	}
	
	if(Walk[(int)m_nowSpl]!=3)
	{
		if (m_goal >= 5.0)
		{
			m_dir *= -1;
			m_goal = 0;
		}
		m_pos.x += m_dir * m_speed;
		m_goal += m_speed;
	}

	m_pos.y -= m_gravity;
	m_gravity += 0.005;

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(m_dir,1.0,1.0);
	m_mWorld = scaleMat * transMat;
}

void Enemy::PostUpdate()
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
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);


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

	// ===============================
	//    球判定
	// ===============================

	// 球判定用の変数を設定
	KdCollider::SphereInfo sphere;
	// 球の中心位置を設定(座標)
	sphere.m_sphere.Center = m_pos + Math::Vector3(0, 0.5f, 0);
	// 球の半径を設定
	sphere.m_sphere.Radius = 0.3f;
	// 当たり判定したいタイプを設定
	sphere.m_type = KdCollider::TypeGround;

	// デバッグ用
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	// 球に当たったオブジェクト情報を格納
	std::list<KdCollider::CollisionResult> retSphereList;

	// 当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(sphere, &retSphereList);
	}

	// 球に当たったオブジェクトを検出
	maxOverLap = 0;
	Math::Vector3 hitDir;
	isHit = false;
	for (auto& ret : retSphereList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			isHit = true;
		}
	}
	if (isHit)
	{
		// Z方向への押し返し無効
		hitDir.z = 0;
		// 方向ベクトルは長さを1にしないといけない
		// 正規化(長さを１にする)
		hitDir.Normalize();

		// 押し戻し処理
		m_pos += hitDir * maxOverLap;
	}

}
