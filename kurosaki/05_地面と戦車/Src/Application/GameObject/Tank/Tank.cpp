#include "Tank.h"
#include"../../main.h"

void Tank::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/tank/tank.gltf");
	
}

void Tank::Update()
{
	Math::Vector3 moveVec; // 向きたい方向
	bool moveFlg = false; // 状態フラグ

	// WASD
	if (GetAsyncKeyState('W') & 0x8000)
	{
		moveVec += { 0,0,1 };
		moveFlg = true;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		moveVec += { -1,0,0 };
		moveFlg = true;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		moveVec += { 0,0,-1 };
		moveFlg = true;
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		moveVec += { 1,0,0 };
		moveFlg = true;
	}

	if (moveFlg == true)
	{
		// 移動中
		// 回転処理


		// 今戦車が向いている方向
		// ①キャラの回転行列を作成
		Math::Matrix nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
		// ②現在の方向を求める
		Math::Vector3 nowVec = Math::Vector3::TransformNormal({ 0,0,1 }, nowRotMat);
		
		// もう一つ
		//Math::Vector3 nowVec = m_mWorld.Backward();

		// 向きたい方向
		Math::Vector3 toVec = moveVec;
		// 方向をベクトルで管理する場合、ベクトルの長さは1にする必要がある
		toVec.Normalize();

		// 内積...ベクトルAとベクトルBとコサインなす角
		float d = nowVec.Dot(toVec);

		// 丸め誤差...小数点以下を省略した際に生じる誤差
		// 内積は1～-1が出る
		// 1～-1でdの値をクランプ（遮断）する
		d = std::clamp(d, -1.0f, 1.0f);

		// アークコサインで角度に変換
		float ang = DirectX::XMConvertToDegrees(acos(d));

		// ゆっくり回転する
		if (ang >= 0.1)
		{
			if (ang > 5)
			{
				ang = 5.0f;
			}

			// 外積...ベクトルAとベクトルB②垂直なベクトル
			Math::Vector3 c = toVec.Cross(nowVec);

			if (c.y > 0)
			{
				m_angle -= ang;
				if (m_angle < 0)m_angle += 360;
			}
			else
			{
				m_angle += ang;
				if (m_angle > 360)m_angle -= 360;
			}

			Application::Instance().m_log.AddLog("m_angle=%.2f ang=%.2f\n", m_angle, ang);

			// 回転行列
			Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

			m_mWorld = rotMat;
		}
	}
}

void Tank::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}
