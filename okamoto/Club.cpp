#include "Club.h"

void Club::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Club/Club.gltf");
	}
	m_basePos = {0.3f,6.5f,0.35f};
	m_baseXRot = 30;
	m_baseYRot = 0;
	ResetPos();
}

void Club::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (LKeyFlg == false && m_nowSit == NowSit::Idle)
		{
			LKeyFlg = true;
			m_nowSit = NowSit::LAtack;
			m_parentPos = { 0.f,6.5f,0.35f };
			m_XRot = 0;
			m_coolTimer = 0;
		}
	}
	else LKeyFlg = false;

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (RKeyFlg == false && m_nowSit == NowSit::Idle)
		{
			RKeyFlg = true;
			m_nowSit = NowSit::RAtack;
			m_parentPos = { 0.3f,6.5f,0.35f };
			m_XRot = 0;
			m_YRot = 80;
			m_XFlg = true;
			m_coolTimer = 0;
		}
	}
	else RKeyFlg = false;

	if (m_nowSit == NowSit::LAtack)
	{
		
		m_XRot += 11;
		
		if (m_XRot > 110)
		{
			m_XRot = 110;
			
			m_coolTimer++;
		}
		if (m_coolTimer > 15)
		{
			ResetPos();
		}
	}

	if (m_nowSit == NowSit::RAtack)
	{
		if (m_XFlg)m_XRot += 4;
		else m_XRot -= 6;
		m_YRot -= 12;
		m_parentPos.x -= 0.1;
		if (m_XRot > 110)
		{
			m_XRot = 110;
			m_XFlg = false;
		}
		if (m_XRot < 90)m_XRot = 90;
		if (m_YRot < -60)
		{
			m_YRot = -60;
			m_parentPos.x += 0.1;
			m_coolTimer++;
		}
		if (m_coolTimer > 15)
		{
			ResetPos();
		}
	}


	Math::Matrix XRotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_XRot));
	Math::Matrix YRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_YRot));
	Math::Matrix TransMat = Math::Matrix::CreateTranslation(m_parentPos);
	m_mWorld =XRotMat * YRotMat * TransMat;

	


}

void Club::DrawLit()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Club::ResetPos()
{
	m_parentPos = m_basePos;
	m_XRot = m_baseXRot;
	m_YRot = m_baseYRot;
	m_nowSit = NowSit::Idle;
}
