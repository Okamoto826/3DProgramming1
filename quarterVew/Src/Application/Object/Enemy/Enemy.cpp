#include "Enemy.h"
#include"../Player/Player.h"
#include"../../Scene/SceneManager.h"
void Enemy::Update()
{
	// アニメーション更新 =================================================
	m_animationInfo.count += m_animationInfo.speed;
	if (m_animationInfo.count >= 4)m_animationInfo.count = 0.0f;

	// UV(切り取るコマ)を設定
	m_polygon->SetUVRect(m_animationInfo.Run[int(m_animationInfo.count)]);
	// ======================================================================

	m_speed = 0.05f;
	m_move = {};

	if (m_player.expired() == false)
	{
		Math::Vector3 playerPos = m_player.lock()->GetPos();
		m_move = playerPos - m_pos;
		if (m_move.Length() < 3.0f)m_chaseFlg = true;
		else m_chaseFlg = false;

		if (m_move.Length() < m_speed)m_speed = m_move.Length();
	}


	if(m_chaseFlg)
	{
		m_move.y = 0;
		m_move.Normalize();
		m_move *= m_speed;
		m_pos += m_move;
	}
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;
	//=======================================================
	// 当たり判定・・・レイ判定　ここから
	//=======================================================

	// レイ判定用に必要パラメーターを設定する構造体を宣言
	KdCollider::RayInfo rayInfo;

	// レイの発射方向(座標)を設定
	rayInfo.m_pos = m_pos;

	// 少し高いところから飛ばす
	//rayInfo.m_pos.y += 0.1f;

	// 段差の許容範囲を設定
	static const float enableStepHigh = 0.2f;
	rayInfo.m_pos.y += enableStepHigh;

	// レイの方向を設定
	rayInfo.m_dir = { 0.0f,-1.0f,0.0f };

	// レイの長さを設定
	rayInfo.m_range = m_gravity + enableStepHigh;

	// 当たり判定したいタイプを設定
	rayInfo.m_type = KdCollider::TypeGround;

	// デバッグ用の情報としてライン描画を追加
	m_pDebugWire->AddDebugLine
	(
		// 線の開始位置
		rayInfo.m_pos,
		// 線の方向
		rayInfo.m_dir,
		// 線の長さ
		rayInfo.m_range
	);

	// レイに当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retRayList;

	// 作成したレイ情報でオブジェクトリストと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(rayInfo, &retRayList);
	}

	// レイに当たったリストから一番近いオブジェクトを検出
	bool hit = false;
	float maxOverLap = 0;
	Math::Vector3 groundPos = {};	// レイが遮断された(Hitした)座標

	for (auto& ret : retRayList)
	{
		// レイが当たった場合の貫通した長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			groundPos = ret.m_hitPos;
			hit = true;
		}
	}

	// 当たっていたら
	if (hit)
	{
		m_pos = groundPos;
		m_gravity = 0;
	}

	//=======================================================
	// 当たり判定・・・レイ判定　ここまで
	//=======================================================

	// デバッグ用 球
	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3(0, 0.5f, 0),m_searchArea,kRedColor);

	
}

void Enemy::PostUpdate()
{
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Enemy::Init()
{
	if (!m_polygon)
	{
		m_polygon = std::make_shared<KdSquarePolygon>();
		m_polygon->SetMaterial("Asset/Textures/Enemy.png");
		m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
		m_polygon->SetSplit(6, 6);
	}

	m_pos = {};
	m_move = {};
	m_speed = 0.05f;
	m_gravity = 0.0f;


	// 初期アニメーション情報
	m_animationInfo.count = 0.0f;	//	現在のコマ数カウント
	m_animationInfo.speed = 0.1f;	// アニメーションの速度

	// 奥側に座標(ワールド行列)を更新しておく
	m_mWorld = Math::Matrix::Identity;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Enemy::SetPlayer(std::weak_ptr<Player> _player)
{
	if (_player.expired() == false)
	{
		m_player = _player;
	}
}

void Enemy::ChangeAnimation()
{
}
