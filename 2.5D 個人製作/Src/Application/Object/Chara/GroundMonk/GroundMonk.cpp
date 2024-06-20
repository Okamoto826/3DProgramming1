#include "GroundMonk.h"

void GroundMonk::Update()
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

	BaseChara::Update();
}


void GroundMonk::Init()
{
	BaseChara::Init();
	// 板ポリにテクスチャ(マテリアル)をロード
	m_polygon.SetMaterial("Asset/Textures/Chara/GroundMonk.png");

	//　板ポリの基準点 (真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_polygon.SetSplit(9, 9);
	m_polygon.SetUVRect(0);
	m_polygon.SetScale(3.0);
	m_nowSit = NowCharaSit::Idle;
	m_pos = { -1,-2.5,0 };
	ChangeAnimation();

}

void GroundMonk::ChangeAnimation()
{
	if (m_nowSit & NowCharaSit::Idle)
	{
		m_animationInfo.start = 0;		// 開始コマ
		m_animationInfo.end = 5;		// 終了コマ	
	}
	if (m_nowSit & NowCharaSit::Move)
	{
		m_animationInfo.start = 6;		// 開始コマ
		m_animationInfo.end = 13;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Skill)
	{
		m_animationInfo.start = 14;		// 開始コマ
		m_animationInfo.end = 25;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Skill2)
	{
		m_animationInfo.start = 26;		// 開始コマ
		m_animationInfo.end = 50;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Hit)
	{
		m_animationInfo.start = 51;		// 開始コマ
		m_animationInfo.end = 56;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Down)
	{
		m_animationInfo.start = 57;		// 開始コマ
		m_animationInfo.end = 74;		// 終了コマ
	}

	m_animationInfo.count = 0.0f;	//	現在のコマ数カウント
	m_animationInfo.speed = 0.2f;	// アニメーションの速度
}