#include "ResultBack.h"
#include "../../../Scene/SceneManager.h"

void ResultBack::Init()
{
	m_sp_tex->Load(BackPng);

	ResultBase::Init();

	m_color.A(MinColor);
}

void ResultBack::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & KEY)
	{
		if (!m_b_titleBackKey)
		{
			// タイトルへ
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
		}
	}
	else { m_b_titleBackKey = false; }

	if (m_b_backAlphaStart)
	{
		float alpha = m_color.A();
		if (alpha < MaxColor) { m_color.A(alpha + StartBackAlphaTrans); }
		else { m_b_backAlphaStart = false; }
	}
	else
	{
		m_backAlphaDeg += BackAlphaDegTrans;
		DegNormalize(&m_backAlphaDeg);
		m_color.A(cos(DirectX::XMConvertToRadians(m_backAlphaDeg)) * BackAlphaDegRange + BackAlphaDegRange + BackMinAlpha);
	}
}
