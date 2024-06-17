#include "BaseChara.h"

void BaseChara::Update()
{
}

void BaseChara::PostUpdate()
{
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void BaseChara::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void BaseChara::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void BaseChara::Init()
{
	m_pos = {};
	m_dir = {};
	m_nowSit = 0;

	// 奥側に座標(ワールド行列)を更新しておく
	m_mWorld = Math::Matrix::Identity;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

