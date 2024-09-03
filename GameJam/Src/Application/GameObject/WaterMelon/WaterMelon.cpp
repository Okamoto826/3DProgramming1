#include "WaterMelon.h"

void WaterMelon::Update()
{
	if (m_animation01)
	{
		if (!m_effFlg)
		{
			KdEffekseerManager::GetInstance().Play("sphere/Simple_Sprite_BillBoard.efkefc", m_pos, 1.0f, 1.0f, false);
			m_effFlg = true;
		}

		TurnAnimation(Turn::turn01, Turn::turn02, 120.0f, true);
		TurnAnimation(Turn::turn02, Turn::turn03, 75.0f, false);
		TurnAnimation(Turn::turn03, Turn::turn04, 90.0f, true);

		if (m_turnFlg & Turn::turn04)
		{
			m_animation01 = false;
		}
	}

	if (m_animation02)
	{
		m_left.pos += m_dist;
		m_right.pos += m_dist;

		m_frame--;
		if (m_frame <= 0)
		{
			m_isExpired = true;
		}
	}

	if (!m_keyFlg)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			m_keyFlg = true;
			m_animation01 = true;
		}

		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			m_keyFlg = true;
			m_animation02 = true;
		}
	}
}

void WaterMelon::PostUpdate()
{
	m_left.LocalPos = Math::Matrix::CreateTranslation(m_left.pos + m_pos);

	m_left.Rotation = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_left.deg));

	m_left.mat = m_left.Rotation * m_left.LocalPos;


	m_right.LocalPos = Math::Matrix::CreateTranslation(m_right.pos + m_pos);

	m_right.Rotation = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_right.deg));

	m_right.mat = m_right.Rotation * m_right.LocalPos;
}

void WaterMelon::Init()
{
	if (!m_left.spModel)
	{
		m_left.spModel = std::make_shared<KdModelWork>();
		m_left.spModel->SetModelData("Asset/Models/WaterMelon/WaterMelonHalf2.gltf");

		m_left.pos = m_pos;
	}

	if (!m_right.spModel)
	{
		m_right.spModel = std::make_shared<KdModelWork>();
		m_right.spModel->SetModelData("Asset/Models/WaterMelon/WaterMelonHalf3.gltf");

		m_right.pos = m_pos;
	}

	m_frame = 30;

	m_dist = { -3.0f,1.0f,0.5f };

	m_turnFlg = Turn::turn01;
}

void WaterMelon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_left.spModel, m_left.mat);

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_right.spModel, m_right.mat);
}

void WaterMelon::TurnAnimation(WaterMelon::Turn _turn, WaterMelon::Turn _turnNext, float _maxAng, bool _dir)
{
	if (_dir)
	{
		if (m_turnFlg & _turn)
		{
			if (m_left.deg < _maxAng)
			{
				m_left.deg += angSpeed;
				m_left.pos.x -= posSpeed;
			}

			if (m_right.deg > -_maxAng)
			{
				m_right.deg -= angSpeed;
				m_right.pos.x += posSpeed;
			}

			if (m_left.deg >= _maxAng)
			{
				m_turnFlg = _turnNext;
			}
		}
	}
	else
	{
		if (m_turnFlg & _turn)
		{
			if (m_left.deg > _maxAng)
			{
				m_left.deg -= angSpeed;
				m_left.pos.x += posSpeed;
			}

			if (m_right.deg < -_maxAng)
			{
				m_right.deg += angSpeed;
				m_right.pos.x -= posSpeed;
			}

			if (m_left.deg <= _maxAng)
			{
				m_turnFlg = _turnNext;
			}
		}
	}
}