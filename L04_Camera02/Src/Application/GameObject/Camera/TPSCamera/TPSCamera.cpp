#include "TPSCamera.h"

void TPSCamera::Init()
{
	// 基準点(ターゲット)からどれだけ離れているか
	m_LocalPos = Math::Matrix::CreateTranslation(0, 1.5f, -10.f);

	// マウスカーソルを画面中央に固定
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void TPSCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix _targetMat = Math::Matrix::Identity;

	const std::shared_ptr<const KdGameObject> _spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		Math::Vector3 _targetPos = _spTarget->GetPos();
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転
	UpdateRotateMouse();
	m_Rotation = GetRotationMatrix();
	m_mWorld = m_LocalPos * m_Rotation * _targetMat;

	// ↓めり込み防止のための座標補正計算↓
	// ①当たり判定（レイ判定用）用の情報計算
	KdCollider::RayInfo _rayInfo;
	// レイの発射位置を設定
	_rayInfo.m_pos = GetPos();
	// レイの当たり判定を取りたいオブジェクトタイプの設定
	_rayInfo.m_type = KdCollider::TypeGround;
	// レイの発射方向を設定
	_rayInfo.m_dir = Math::Vector3::Down;
	// レイの長さを設定
	_rayInfo.m_range = 1000.f;

	if (_spTarget)
	{
		Math::Vector3 _targetPos = _spTarget->GetPos();
		_targetPos.y += 0.1;
		_rayInfo.m_dir = _targetPos - GetPos();
		_rayInfo.m_range = _rayInfo.m_dir.Length();
		_rayInfo.m_dir.Normalize();
	}

	// ②HIT判定対象のオブジェクトに総当たり
	for (std::weak_ptr<KdGameObject> wpObj : m_wpHitObjectList)
	{
		std::shared_ptr<KdGameObject>_spObj = wpObj.lock();
		if (_spObj)
		{
			std::list<KdCollider::CollisionResult>_results;
			_spObj->Intersects(_rayInfo, &_results);

			// ③結果を使って座標を補正する
			// レイに当たったリストから一番近いオブジェクトを検出
			float			_maxOverLap = 0;
			Math::Vector3	_hitPos = Math::Vector3::Zero;
			bool			_hit = false;

			for (auto& ret : _results)
			{
				// レイを遮断し、オーバーした長さが一番長いものを探す
				if (_maxOverLap < ret.m_overlapDistance)
				{
					_maxOverLap = ret.m_overlapDistance;
					_hitPos		= ret.m_hitPos;
					_hit		= true;
				}
			}
			// 何かしらにあたっている
			if (_hit)
			{
				Math::Vector3 hitPos = _hitPos;
				hitPos += _rayInfo.m_dir * 0.4;
				// 座標を補正
				SetPos(hitPos);
			}
		}
	}

	CameraBase::Update();
}

void TPSCamera::UpdateRotateMouse()
{
	// マウスでカメラを回転させる処理
	POINT nowPos;
	GetCursorPos(&nowPos);

	POINT mouseMove{};
	mouseMove.x = nowPos.x - m_FixMousePos.x;
	mouseMove.y = nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	// 実際にカメラを回転させる処理
	m_DegAng.x += mouseMove.y * 0.15f;
	m_DegAng.y += mouseMove.x * 0.15f;

	// 回転制御
	m_DegAng.x = std::clamp(m_DegAng.x, -FLT_MAX, FLT_MAX);
}
