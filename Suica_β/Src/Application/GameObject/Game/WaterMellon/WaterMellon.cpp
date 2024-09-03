#include "WaterMellon.h"

void WaterMellon::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/WaterMellon/WaterMellon.gltf");

	m_pos = { 0,-4,12 };
}

void WaterMellon::Update()
{
	m_mWorld = Math::Matrix::CreateScale(2) * Math::Matrix::CreateTranslation(m_pos);
}

void WaterMellon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void WaterMellon::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}