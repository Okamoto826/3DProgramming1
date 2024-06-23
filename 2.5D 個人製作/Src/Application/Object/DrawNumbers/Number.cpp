#include "Number.h"

void Number::DrawSprite()
{
	m_mWorld = m_sMat * m_rMat * m_tMat;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, m_texWide, m_texHeight, &m_rectAngle);

	m_mWorld = Math::Matrix::Identity;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);
}

void Number::SetNumber(int num,int digit,Math::Vector3 pos, ObjType obj)
{
	m_rectAngle = { m_texWide * num,0,m_texWide,m_texHeight };
	m_tMat = Math::Matrix::CreateTranslation(pos.x + (digit* m_texWide), pos.y, pos.z);
	m_objType = obj;
}

void Number::Init()
{
	m_texHeight=100;						//表示したい画像のYの大きさ
	m_texWide=70;							//表示したい画像のXの大きさ
	m_rectAngle = { m_texWide,0,m_texWide,m_texHeight };
	m_tex.Load("Asset/Textures/UI/num.png");	//画像
	m_pos = {};							//座標
	m_color={1,1,1,1};					//色

	m_sMat = Math::Matrix::Identity;	//拡縮
	m_rMat = Math::Matrix::Identity;	//回転
	m_tMat = Math::Matrix::Identity;	//移動
}
