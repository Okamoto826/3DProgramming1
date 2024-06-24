#include "Goblin.h"
#include"../../../Scene/SceneManager.h"

void Goblin::Update()
{
	// 召喚中はリターン
	if (d != 0)return;

	// アニメーション更新
	int animeCnt;
	m_animationInfo.count += m_animationInfo.speed;
	animeCnt = m_animationInfo.start + m_animationInfo.count;

	// 最後のコマまで行進し終えたらループさせる
	if (animeCnt > m_animationInfo.end)
	{
		if (m_oldSit & NowCharaSit::Down)
		{
			m_isExpired = true;
			return;
		}
		animeCnt = m_animationInfo.start;
		m_animationInfo.count = 0.0f;
		m_nowSit = NowCharaSit::Idle;
	}
	// UV(切り取るコマ)を設定
	m_polygon.SetUVRect(animeCnt);

	//　攻撃
	if (animeCnt == 6 && m_animationInfo.oldCount != 6)
	{


		// 球判定用の変数を設定
		KdCollider::SphereInfo sphere;
		// 球の中心位置を設定(座標)
		sphere.m_sphere.Center = m_pos + Math::Vector3(-0.7, 0.7, 0);
		// 球の半径を設定
		sphere.m_sphere.Radius = 0.3f;
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
				if (obj->GetObjectType() == KdGameObject::ObjectType::Player)
				{
					// 敵確定
					obj->OnHit(50.f);
				}
			}
		}
	}

	m_animationInfo.oldCount = animeCnt;
	// キャラの状態が切り替わっていたら変数リセット
	if (m_nowSit != m_oldSit)
	{
		ChangeAnimation();
	}
	m_oldSit = m_nowSit;

	if (m_nowSit & NowCharaSit::Idle)m_nowSit = NowCharaSit::Move;

	if (m_nowSit & NowCharaSit::Idle || m_nowSit & NowCharaSit::Move)
	{
		// 攻撃範囲内の敵を見つける
		// ===============================
		//    球判定
		// ===============================

		// 球判定用の変数を設定
		KdCollider::SphereInfo sphere;
		// 球の中心位置を設定(座標)
		sphere.m_sphere.Center = m_pos + Math::Vector3(0, 0.5, 0);
		// 球の半径を設定
		sphere.m_sphere.Radius = 0.4f;
		// 当たり判定したいタイプを設定
		sphere.m_type = KdCollider::TypeDamage;

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
				if (obj->GetObjectType() == KdGameObject::ObjectType::Player)
				{
					m_nowSit = NowCharaSit::Idle;
					Atack();
				}
			}
		}
	}


	if (m_nowSit & NowCharaSit::Move)
	{
		m_pos.x -= 0.03;
	}



	EnemyBase::Update();
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		OnHit(500.f);
	}
}

void Goblin::PostUpdate()
{
	EnemyBase::PostUpdate();
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = rotMat * transMat;
}


void Goblin::Init()
{
	EnemyBase::Init();
	// 板ポリにテクスチャ(マテリアル)をロード
	m_polygon.SetMaterial("Asset/Textures/Enemy/Goblin.png");

	//　板ポリの基準点 (真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_polygon.SetSplit(8, 4);
	m_polygon.SetUVRect(0);
	m_polygon.SetScale(3.0);
	m_nowSit = NowCharaSit::Idle;
	m_hp = 50;

	ChangeAnimation();
	// 当たり判定用
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape
	("EnemyCollision", { 0,0.5f,0 }, 0.2, KdCollider::TypeDamage);
}

void Goblin::ChangeAnimation()
{
	if (m_nowSit & NowCharaSit::Idle)
	{
		m_animationInfo.start = 16;		// 開始コマ
		m_animationInfo.end = 19;		// 終了コマ	
	}
	if (m_nowSit & NowCharaSit::Move)
	{
		m_animationInfo.start = 8;		// 開始コマ
		m_animationInfo.end = 15;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Skill)
	{
		m_animationInfo.start = 0;		// 開始コマ
		m_animationInfo.end = 7;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Skill2)
	{
		m_animationInfo.start = 0;		// 開始コマ
		m_animationInfo.end = 7;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Hit)
	{
		m_animationInfo.start = 20;		// 開始コマ
		m_animationInfo.end = 23;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Down)
	{
		m_animationInfo.start = 24;		// 開始コマ
		m_animationInfo.end = 27;		// 終了コマ
	}

	m_animationInfo.count = 0.0f;	//	現在のコマ数カウント
	m_animationInfo.speed = 0.2f;	// アニメーションの速度
}

void Goblin::Atack()
{

	if (m_atkCoolTime >= 180)
	{
		m_nowSit = NowCharaSit::Skill;
		m_atkCoolTime = 0;
	}
}

void Goblin::OnHit(float _dmg)
{


	if(m_nowSit & NowCharaSit::Idle||m_nowSit&NowCharaSit::Move)
	{
		m_nowSit = NowCharaSit::Hit;
	}
	m_hp -= _dmg;
	if (m_hp <= 0)
	{
		m_nowSit = NowCharaSit::Down;
	}
	
}