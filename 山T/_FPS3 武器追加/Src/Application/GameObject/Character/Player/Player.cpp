#include "Player.h"
#include "../../Camera/CameraBase.h"
#include "../../../main.h"
#include"../../../Scene/SceneManager.h"

void Player::Init()
{
	// 頭の高さ
	m_adjustHeight = 3.0f;

	// 座標
	m_pos = Math::Vector3::Zero;
	m_pos.y += m_adjustHeight;

	// 重力
	m_gravityPow = 0.04f;
	m_gravity = 0.0f;

	m_moveDir = { 0.f, 0.f, 0.f };
	m_degAng = { 0.f, 0.f, 0.f };

	// 移動速度
	m_moveSpeed = 0.1f;
	m_jumpPow = 0.7f;

	// カーソルを中央に固定
	m_fixMousePos = { 640, 360 };
	ClientToScreen(Application::Instance().GetWindowHandle(), &m_fixMousePos);
	SetCursorPos(m_fixMousePos.x, m_fixMousePos.y);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::Update()
{
	Math::Color color{};
	
	// X
	color = { 1.0f, 0.0f, 0.0f };
	m_pDebugWire->AddDebugLine
	({ m_pos.x - 5.0f, m_pos.y - m_adjustHeight, m_pos.z }, { 1.0f, 0.0f, 0.0f }, 10.0f, color);
	
	// Z
	color = { 0.0f, 1.0f, 1.0f };
	m_pDebugWire->AddDebugLine
	({ m_pos.x, m_pos.y - m_adjustHeight, m_pos.z - 5.0f }, { 0.0f, 0.0f, 1.0f }, 10.0f, color);

	// 進行方向をクリア
	m_moveDir = Math::Vector3::Zero;

	if (!(GetAsyncKeyState(VK_LSHIFT) & 0x8000))
	{
		UpdateRotateByMouse();
	}

	// キャラ制御（進行ベクトルへの情報を更新）
	if (GetAsyncKeyState('W') & 0x8000) m_moveDir.z += +1.0f;
	if (GetAsyncKeyState('S') & 0x8000) m_moveDir.z += -1.0f;
	if (GetAsyncKeyState('A') & 0x8000) m_moveDir.x += -1.0f;
	if (GetAsyncKeyState('D') & 0x8000) m_moveDir.x += +1.0f;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_keyFlg)m_gravity = -m_jumpPow;
		m_keyFlg = true;
	}
	else m_keyFlg = false;

	m_moveDir = m_moveDir.TransformNormal(m_moveDir, GetRotationYMatrix());
	m_moveDir.Normalize();
	m_pos += m_moveDir * m_moveSpeed;

	// 重力をキャラに反映
	m_pos.y -= m_gravity;
	m_gravity += m_gravityPow;

	// moveDir
	color = { 0.0f, 1.0f, 0.0f };
	m_pDebugWire->AddDebugLine
	({ m_pos.x, m_pos.y - m_adjustHeight, m_pos.z }, m_moveDir, m_moveSpeed * 50.0f, color);
}

void Player::PostUpdate()
{
	m_mWorld = GetRotationMatrix() * Math::Matrix::CreateTranslation(m_pos);

	//=======================================================
	// 当たり判定・・・レイ判定　ここから
	//=======================================================

	// レイ判定用に必要パラメーターを設定する構造体を宣言
	KdCollider::RayInfo rayInfo;

	// レイの発射方向(座標)を設定
	rayInfo.m_pos = m_pos;
	rayInfo.m_pos.y -= m_adjustHeight;

	// 少し高いところから飛ばす
	//rayInfo.m_pos.y += 0.1f;

	// 段差の許容範囲を設定
	static const float enableStepHigh = 0.5f;
	rayInfo.m_pos.y += enableStepHigh;

	// レイの方向を設定
	rayInfo.m_dir = Math::Vector3::Down;

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
		m_pos.y += m_adjustHeight;
		m_gravity = 0;
	}

}

void Player::UpdateRotateByMouse()
{
	HWND hWnd = Application::Instance().GetWindowHandle();

	m_fixMousePos = { 640, 360 };

	// マウスでカメラを回転させる処理
	POINT _nowPos;
	GetCursorPos(&_nowPos);
	ScreenToClient(hWnd, &_nowPos);

	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_fixMousePos.x;
	_mouseMove.y = _nowPos.y - m_fixMousePos.y;

	ClientToScreen(hWnd, &m_fixMousePos);
	SetCursorPos(m_fixMousePos.x, m_fixMousePos.y);

	// 実際にカメラを回転させる処理(0.15はただの補正値)
	m_degAng.x += _mouseMove.y * 0.15f;
	m_degAng.y += _mouseMove.x * 0.15f;

	// 回転制御
	m_degAng.x = std::clamp(m_degAng.x, -80.f, 80.f);
}
