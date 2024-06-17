#include "LeafRanger.h"

void LeafRanger::Update()
{
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;

	// アニメーション更新
	int animeCnt;
	m_animationInfo.count += m_animationInfo.speed;
	animeCnt = m_animationInfo.start + m_animationInfo.count;

	// 最後のコマまで行進し終えたらループさせる
	if (animeCnt > m_animationInfo.end)
	{
		animeCnt = m_animationInfo.start;
		m_animationInfo.count = 0.0f;
	}
	// UV(切り取るコマ)を設定
	m_polygon.SetUVRect(animeCnt);
}


void LeafRanger::Init()
{
	BaseChara::Init();
	// 板ポリにテクスチャ(マテリアル)をロード
	m_polygon.SetMaterial("Asset/Textures/leafranger.png");

	//　板ポリの基準点 (真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_polygon.SetSplit(9, 9);
	m_polygon.SetUVRect(0);
	m_polygon.SetScale(2.0);
	m_nowSit = NowCharaSit::Down;
	m_pos={ 0,0,-1 };
	ChangeAnimation();
	
}

void LeafRanger::ChangeAnimation()
{
	if (m_nowSit & NowCharaSit::Idle)	
	{
		m_animationInfo.start = 0;		// 開始コマ
		m_animationInfo.end = 11;		// 終了コマ	
	}
	if (m_nowSit & NowCharaSit::Move) 
	{
		m_animationInfo.start = 12;		// 開始コマ
		m_animationInfo.end = 21;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Skill) 
	{
		m_animationInfo.start = 22;		// 開始コマ
		m_animationInfo.end = 36;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Skill2) 
	{
		m_animationInfo.start = 37;		// 開始コマ
		m_animationInfo.end = 53;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Hit) 
	{
		m_animationInfo.start = 54;		// 開始コマ
		m_animationInfo.end = 59;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Down) 
	{
		m_animationInfo.start = 60;		// 開始コマ
		m_animationInfo.end = 78;		// 終了コマ
	}

	m_animationInfo.count = 0.0f;	//	現在のコマ数カウント
	m_animationInfo.speed = 0.2f;	// アニメーションの速度
}
