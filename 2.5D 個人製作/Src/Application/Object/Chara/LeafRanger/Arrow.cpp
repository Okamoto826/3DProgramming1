#include "Arrow.h"
#include"../../../Scene/SceneManager.h"

void Arrow::Init()
{
	// 板ポリにテクスチャ(マテリアル)をロード
	m_polygon.SetMaterial("Asset/Textures/Weapon/leafrangerweapon.png");
	m_polygon.SetSplit(3, 4); m_polygon.SetScale(3.0);
	m_polygon.SetUVRect(5);
	
	m_pos = {};
	m_speed = { 0.1,0,0 };
	m_gravity = 0.f;
	m_timeCnt = 0;
	m_nowSt = NowSt::Move;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Arrow::Update()
{
	m_timeCnt += 1;
	if (m_timeCnt >= m_lifeTime)m_isExpired = true;

	if(m_nowSt==NowSt::Move)
	{
		m_gravity += 0.00025;
		m_speed.y = -m_gravity;
		m_pos += m_speed;

		m_mWorld = Math::Matrix::CreateTranslation(m_pos);
	}
}

void Arrow::PostUpdate()
{
	// ===============================
	//    球判定
	// ===============================

	// 球判定用の変数を設定
	KdCollider::SphereInfo sphere;
	// 球の中心位置を設定(座標)
	sphere.m_sphere.Center = m_pos;
	// 球の半径を設定
	sphere.m_sphere.Radius = 0.1f;
	// 当たり判定したいタイプを設定
	sphere.m_type = KdCollider::TypeGround | KdCollider::TypeDamage;

	// デバッグ用
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	// 球に当たったオブジェクト情報を格納
	std::list<KdCollider::CollisionResult> retSphereList;

	// 当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, &retSphereList))
		{
			// 当たったのが敵かどうか
			if (obj->GetObjectType() == KdGameObject::ObjectType::Enemy)
			{
				// 敵確定
				obj->OnHit(50.f);
				OnHit();
			}
		}
	}

	
}

void Arrow::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Arrow::OnHit()
{
	m_nowSt = NowSt::Hit;
	m_polygon.SetUVRect(0);
	m_isExpired = true;
}
