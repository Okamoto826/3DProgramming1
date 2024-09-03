#include "Player.h"

#include"../../Camera/CameraBase.h"

void Player::Init()
{
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::Update()
{
	
	m_moveDir = {};
	
	if (GetAsyncKeyState('D')) { m_moveDir.x = 1.0f; }
	if (GetAsyncKeyState('A')) { m_moveDir.x = -1.0f; }
	if (GetAsyncKeyState('W')) { m_moveDir.z = 1.0f; }
	if (GetAsyncKeyState('S')) { m_moveDir.z = -1.0f; }

	/*std::shared_ptr<CameraBase> _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		m_moveDir = m_moveDir.TransformNormal(m_moveDir, _spCamera->GetRotationYMatrix());
	}*/

	m_moveDir.Normalize();
	m_pos += m_moveDir * m_moveSpeed;
	
	UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();
	// キャラクターのワールド行列を創る処理
	Math::Matrix _trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_mRotation*_trans;
}

void Player::UpdateRotateByMouse()
{
	// マウスでカメラを回転させる処理
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_FixMousePos.x;
	_mouseMove.y = _nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	// 実際にカメラを回転させる処理(0.15はただの補正値)
	m_DegAng.x += _mouseMove.y * 0.15f;
	m_DegAng.y += _mouseMove.x * 0.15f;

	// 回転制御
	m_DegAng.x = std::clamp(m_DegAng.x, -45.f, 45.f);
}
