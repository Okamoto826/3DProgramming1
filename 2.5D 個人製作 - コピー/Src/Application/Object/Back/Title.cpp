#include "Title.h"
#include"../../Object/Chara/LeafRanger/LeafRangerTitle.h"
#include"../../Scene/SceneManager.h"
void Title::Init()
{
	m_titleTex.Load("Asset/Textures/Title.png");
	m_enterTex.Load("Asset/Textures/Enter.png");
	/*std::shared_ptr<LeafRangerTitle> leafRangerTitle;
	leafRangerTitle = std::make_shared<LeafRangerTitle>();
	SceneManager::Instance().AddObject(leafRangerTitle);*/
}

void Title::DrawSprite()
{
	alfa++;
	Math::Rectangle rc = { 0,0,(long)m_titleTex.GetWidth(),(long)m_titleTex.GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_titleTex, 0, 100, rc.width, rc.height, &rc, nullptr, { 0.5f,0.5f });
	rc = { 0,0,(long)m_enterTex.GetWidth(),(long)m_enterTex.GetHeight() };
	Math::Color color = { 1,1,1,sin(DirectX::XMConvertToRadians(alfa)+0)/2+(float)0.7 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_enterTex, 0, -20, rc.width, rc.height, &rc, &color, { 0.5f,0.5f });
}
