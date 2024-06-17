#include "Attack.h"

#include"../../Scene/SceneManager.h"

void Attack::Update()
{
	m_animaCnt += m_animeSpeed;


	m_polygon.SetUVRect(int(m_animaCnt));

	if (m_animaCnt >= 9)m_isExpired = true;	// 存在消滅

	// 球判定用の変数を設定
	KdCollider::SphereInfo sphere;
	// 球の中心位置を設定(座標)
	sphere.m_sphere.Center = m_mWorld.Translation() + Math::Vector3{0, 0.3, 0};
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

	//// 球に当たったオブジェクトを検出
	//maxOverLap = 0;
	//Math::Vector3 hitDir;
	//isHit = false;
	//for (auto& ret : retSphereList)
	//{
	//	if (maxOverLap < ret.m_overlapDistance)
	//	{
	//		maxOverLap = ret.m_overlapDistance;
	//		hitDir = ret.m_hitDir;
	//		isHit = true;
	//	}
	//}
	//if (isHit)
	//{
	//	// Z方向への押し返し無効
	//	hitDir.z = 0;
	//	// 方向ベクトルは長さを1にしないといけない
	//	// 正規化(長さを１にする)
	//	hitDir.Normalize();

	//	// 押し戻し処理
	//	m_pos += hitDir * maxOverLap;
	//}

}

void Attack::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Attack::Init()
{
	// 板ポリにテクスチャ(マテリアル)をロード
	m_polygon.SetMaterial("Asset/Textures/Attack.png");

	// 板ポリのサイズを拡大
	m_polygon.SetScale(1.0f);

	//　板ポリの基準点 (真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_polygon.SetSplit(9, 1);

	m_animaCnt = 0;
	m_animeSpeed = 1.0f;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}
