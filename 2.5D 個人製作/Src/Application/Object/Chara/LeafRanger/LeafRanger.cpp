#include "LeafRanger.h"
#include"Arrow.h"
#include"../../../Scene/SceneManager.h"

void LeafRanger::Update()
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

	// 弓発射
	if (animeCnt==30&&m_animationInfo.oldCount!=30)
	{
		std::shared_ptr<Arrow> arrow;
		arrow = std::make_shared<Arrow>();
		arrow->SetPos(m_pos + Math::Vector3(0.35, 0.8, 0));
		SceneManager::Instance().AddObject(arrow);
		KdAudioManager::Instance().Play("Asset/Sound/arrow.wav", false)->SetVolume(0.3);
	}

	//if (GetAsyncKeyState(VK_SPACE))OnHit(50.f);


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
		sphere.m_sphere.Center = m_pos + Math::Vector3(1.5, 0.5f, 0);
		// 球の半径を設定
		sphere.m_sphere.Radius = 3.f;
		// 当たり判定したいタイプを設定
		sphere.m_type = KdCollider::TypeDamage;

		
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
					m_nowSit= NowCharaSit::Idle;
					Atack();
				}
			}
			
		}
	}
	

	if (m_nowSit & NowCharaSit::Move)
	{
		m_pos.x += 0.03;
	}
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
	BaseChara::Update();

	if (GetAsyncKeyState('W') & 0x8000)
	{
		Atack();
	}
}


void LeafRanger::Init()
{
	BaseChara::Init();
	// 板ポリにテクスチャ(マテリアル)をロード
	m_polygon.SetMaterial("Asset/Textures/Chara/leafranger.png");

	//　板ポリの基準点 (真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_polygon.SetSplit(9, 9);
	m_polygon.SetUVRect(0);
	m_polygon.SetScale(3.0);
	m_nowSit = NowCharaSit::Idle;
	m_hp = 100;

	ChangeAnimation();
	
}

void LeafRanger::ChangeAnimation()
{
	if (m_nowSit & NowCharaSit::Idle)
	{
		m_animationInfo.start = 0;		// 開始コマ
		m_animationInfo.end = 11;		// 終了コマ	
	}
	if (m_nowSit & NowCharaSit::Move)
	{
		m_animationInfo.start = 12;		// 開始コマ
		m_animationInfo.end = 21;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Skill)
	{
		m_animationInfo.start = 22;		// 開始コマ
		m_animationInfo.end = 36;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Skill2)
	{
		m_animationInfo.start = 37;		// 開始コマ
		m_animationInfo.end = 53;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Hit)
	{
		m_animationInfo.start = 54;		// 開始コマ
		m_animationInfo.end = 59;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Down)
	{
		m_animationInfo.start = 60;		// 開始コマ
		m_animationInfo.end = 78;		// 終了コマ
	}

	m_animationInfo.count = 0.0f;	//	現在のコマ数カウント
	m_animationInfo.speed = 0.2f;	// アニメーションの速度
}

void LeafRanger::Atack()
{
	m_MP++;
	if(m_atkCoolTime >= 120)
	{
		m_nowSit = NowCharaSit::Skill;
		if (m_MP > 300)
		{
			m_nowSit = NowCharaSit::Skill2;
			m_MP = 0;
		}
		m_atkCoolTime = 0;
		
	}
}

void LeafRanger::OnHit(float _dmg)
{
	if (m_nowSit & NowCharaSit::Hit)return;
	else
	{
		m_nowSit = NowCharaSit::Hit;
		m_hp -= _dmg;
		if (m_hp <= 0)
		{
			m_nowSit = NowCharaSit::Down;
		}
	}
}
