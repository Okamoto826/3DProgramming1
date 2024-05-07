#include "Title.h"

void TitleScene::PreUpdate()
{
}

void TitleScene::Update()
{
	for (int i = 0; i < 2; i++)
	{
		m_back[i].m_pos.x -= 4;
		if (m_back[i].m_pos.x < -1276)m_back[i].m_pos.x = 1280;
		m_back[i].m_mat = Math::Matrix::CreateTranslation(m_back[i].m_pos);
	}
	m_TitleMat = Math::Matrix::CreateTranslation(m_TitlePos);
	m_EnterMat = Math::Matrix::CreateTranslation(m_EnterPos);
	m_drawCount++;
	if (m_drawCount > 47)
	{
		m_drawCount = 0;
	}
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale(-m_scale, m_scale, 1);
	m_mat = m_scaleMat * transMat;
}

void TitleScene::Draw()
{
	for (int i = 0; i < 2; i++)
	{
		Math::Rectangle rc;
		KdShaderManager::Instance().m_spriteShader.SetMatrix(m_back[i].m_mat);

		rc = { 0, 0, 1280, 720 };

		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_back[i].m_tex, 0, 0, 1280, 720, &rc);

	}
	Math::Rectangle playerrc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	playerrc = { 0 + 360 * (m_drawCount / 6), 0, 360, 340 };

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 360, 340, &playerrc);

	Math::Rectangle titlerc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_TitleMat);

	titlerc = { 0, 0, 669, 241 };

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_TitleTex, 0, 0, 669, 241, &titlerc);
	
	Math::Rectangle enterrc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_EnterMat);

	enterrc = { 0, 0, 266, 62 };

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_EnterTex, 0, 0, 266, 62, &enterrc);
}

void TitleScene::Init()
{
	m_TitleTex.Load("Asset/Textures/Title.png");
	m_TitlePos = { 0,100,0 };
	m_EnterTex.Load("Asset/Textures/Enter.png");
	m_EnterPos = { 0,-100,0 };
	for (int i = 0; i < 2; i++)
	{
		m_back[i].m_tex.Load("Asset/Textures/Back.png");
		m_back[i].m_pos = { float(0 + 1280 * i), 0, 0 };
	}
	m_drawCount = 0;
	m_scale = 0.5;
	m_tex.Load("Asset/Textures/Wyvern/WyvernMove.png");
	m_pos = { -500,0,0 };			// 0, 0, 0 で初期化
	m_mat = Math::Matrix::Identity;

}

void TitleScene::Release()
{
}
