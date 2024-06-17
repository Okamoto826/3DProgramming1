#include "LeafRanger.h"

void LeafRanger::Update()
{
	m_pos.x += 0.01;
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}


void LeafRanger::Init()
{
	BaseChara::Init();
	// 板ポリにテクスチャ(マテリアル)をロード
	m_polygon.SetMaterial("Asset/Textures/Leaf.png");

	//　板ポリの基準点 (真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	//m_polygon.SetScale(2.0f);
	/*m_polygon.SetSplit(17, 22);
	m_polygon.SetUVRect(1);*/
	
}

void LeafRanger::ChangeAnimation()
{
}
