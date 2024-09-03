#include "Player.h"

#include"../../Scene/SceneManager.h"
#include"../Attack/Attack.h"
void Player::Update()
{
	m_move = {};
	UINT oldDirType = m_dirType;
	m_dirType = 0;	// ビット列をクリア

	
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_move.z += 1;
		m_dirType |= DirType::Up;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_move.z -= 1;
		m_dirType |= DirType::Down;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_move.x -= 1;
		m_dirType |= DirType::Left;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_move.x += 1;
		m_dirType |= DirType::Right;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_gravity = -0.1f;
	}

	if (GetAsyncKeyState('Z') & 0x8000)
	{
		if (!m_keyFlg)
		{
			m_keyFlg = true;

			m_attackDir = {};
			if (oldDirType & DirType::Up)	// 上
			{
				m_attackDir.z = 1.0f;
			}
			if (oldDirType & DirType::Down) // 下
			{
				m_attackDir.z = -1.0f;
			}
			if (oldDirType & DirType::Left) // 左
			{
				m_attackDir.x = -1.0f;
			}
			if (oldDirType & DirType::Right) // 右
			{
				m_attackDir.x = 1.0f;
			}
			m_attackDir.Normalize();

			std::shared_ptr<Attack> attack;
			attack= std::make_shared<Attack>();	// 1 メモリ確保
			attack->Init();							// 2 初期化
			attack->SetPos(m_pos + (m_attackDir * 0.4));
			SceneManager::Instance().AddObject(attack);
		}
	}
	else
	{
		m_keyFlg = false;
	}


	// 向きが変わっていればアニメーション情報変更
	if (m_dirType != 0 && m_dirType != oldDirType)
	{
		ChangeAnimation();
	}
	// 向きが変わっていなければ元の向き(退避データ)に戻す
	else
	{
		m_dirType = oldDirType;
	}

	m_move.Normalize();
	m_move *= m_speed;
	m_pos += m_move;
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;
	
	// アニメーション更新
	int animeCnt;
	m_animationInfo.count += m_animationInfo.speed;
	animeCnt = m_animationInfo.start + m_animationInfo.count;
	
	// 最後のコマまで行進し終えたらループさせる
	if (animeCnt > m_animationInfo.end)
	{
		animeCnt = m_animationInfo.start;
		m_animationInfo.count = 0.0f;
	}
	// UV(切り取るコマ)を設定
	m_polygon.SetUVRect(animeCnt);

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
	static const float enableStepHigh = 0.2;
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
}

void Player::PostUpdate()
{
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Player::Init()
{
	// 板ポリにテクスチャ(マテリアル)をロード
	m_polygon.SetMaterial("Asset/Textures/Player.png");

	// 板ポリのサイズを拡大
	m_polygon.SetScale(1.0f);

	//　板ポリの基準点 (真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_polygon.SetSplit(4, 8);

	// 初期アニメーション情報
	m_animationInfo.start = 4;		// 開始コマ
	m_animationInfo.end = 7;		// 終了コマ
	m_animationInfo.count = 0.0f;	//	現在のコマ数カウント
	m_animationInfo.speed = 0.2f;	// アニメーションの速度

	// 向いている方向
	m_dirType = DirType::Down;

	m_pos = {};
	m_speed = 0.1f;

	m_attackDir = {};

	m_gravity = 0.0f;

	// 奥側に座標(ワールド行列)を更新しておく
	m_mWorld = Math::Matrix::Identity;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::ChangeAnimation()
{
	if (m_dirType & DirType::Up)	// 上
	{
		m_animationInfo.start = 24;		// 開始コマ
		m_animationInfo.end = 27;		// 終了コマ	
	}
	if (m_dirType & DirType::Down) // 下
	{
		m_animationInfo.start = 4;		// 開始コマ
		m_animationInfo.end = 7;		// 終了コマ
	}
	if (m_dirType & DirType::Left) // 左
	{
		m_animationInfo.start = 12;		// 開始コマ
		m_animationInfo.end = 15;		// 終了コマ
	}
	if (m_dirType & DirType::Right) // 右
	{
		m_animationInfo.start = 16;		// 開始コマ
		m_animationInfo.end = 19;		// 終了コマ
	}

	if (m_dirType == (DirType::Up | DirType::Left)) // 左上
	{
		m_animationInfo.start = 20;		// 開始コマ
		m_animationInfo.end = 23;		// 終了コマ
	}
	if (m_dirType == (DirType::Down | DirType::Left)) // 左下
	{
		m_animationInfo.start = 0;		// 開始コマ
		m_animationInfo.end = 3;		// 終了コマ
	}
	
	if (m_dirType == (DirType::Up | DirType::Right)) // 右上
	{
		m_animationInfo.start = 28;		// 開始コマ
		m_animationInfo.end = 31;		// 終了コマ
	}
	if (m_dirType == (DirType::Down  | DirType::Right)) // 右下
	{
		m_animationInfo.start = 8;		// 開始コマ
		m_animationInfo.end = 11;		// 終了コマ
	}

	m_animationInfo.count = 0.0f;	//	現在のコマ数カウント
	m_animationInfo.speed = 0.2f;	// アニメーションの速度
}

