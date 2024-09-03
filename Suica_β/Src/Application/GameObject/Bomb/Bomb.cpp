#include "Bomb.h"

#include "../../GameObject/Effect/Explosion/Explosion.h"
//#include "../../GameObject/Effect/Fuse/Fuse.h"
#include "Application/Scene/SceneManager.h"
#include "Application/Scene/GameScene/EventManager.h"

void Bomb::Update()
{
	if (m_animation01)
	{
		EventManager::Instance().SetItemBreak(true);

		m_pos += m_dist;

		m_frame--;
		if (m_frame <= 0)
		{
			m_isExpired = true;
		}
	}

	if (m_animation02)
	{
		EventManager::Instance().SetItemBreak(true);

		if (!m_effect)
		{
			KdEffekseerManager::GetInstance().Play("bakuhatu/fire.efkefc", m_pos, m_effSize, 1.0f, false);
			m_effect = true;
		}

		m_frame--;

		if (m_frame <= 0)
		{
			m_isExpired = true;
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_lKeyFlg == false)
		{
			m_lKeyFlg = true;

			if (abs(EventManager::Instance().GetPlayerPos().x - m_pos.x) < 2)
			{
				//スコア加算
				EventManager::Instance().SubScore();

				EventManager::Instance().ResetCombo();

				m_animation02 = true;

				EventManager::Instance().SetMake(true);

			}
		}
	}
	else
	{
		m_lKeyFlg = false;
	}

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (m_rKeyFlg == false)
		{
			m_rKeyFlg = true;

			if (abs(EventManager::Instance().GetPlayerPos().x - m_pos.x) < 2)
			{
				//スコア加算
				EventManager::Instance().AddScore();

				EventManager::Instance().AddCombo();

				m_animation01 = true;

				EventManager::Instance().SetMake(true);
			}
		}
	}
	else
	{
		m_rKeyFlg = false;
	}
}

void Bomb::PostUpdate()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_modelSize);

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = scaleMat * transMat;
}

void Bomb::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Bomb/bomb.gltf");

		m_dist = { -3.0f,1.0f,0.5f };
	}
}

void Bomb::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
