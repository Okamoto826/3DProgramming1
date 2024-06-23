#include "CrystalMauler.h"

void CrystalMauler::Update()
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
		if (m_oldSit & NowCharaSit::Down)
		{
			m_isExpired = true;
			return;
		}
		animeCnt = m_animationInfo.start;
		m_animationInfo.count = 0.0f;
		m_nowSit = NowCharaSit::Idle;
	}
	// UV(切り取るコマ)を設定
	m_polygon.SetUVRect(animeCnt);
	if (m_nowSit != m_oldSit)
	{
		ChangeAnimation();
	}
	m_oldSit = m_nowSit;
	BaseChara::Update();
}


void CrystalMauler::Init()
{
	BaseChara::Init();
	// 板ポリにテクスチャ(マテリアル)をロード
	m_polygon.SetMaterial("Asset/Textures/Chara/CrystalMauler.png");

	//　板ポリの基準点 (真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_polygon.SetSplit(8, 8);
	m_polygon.SetUVRect(0);
	m_polygon.SetScale(3.0);
	m_nowSit = NowCharaSit::Idle;
	ChangeAnimation();

}

void CrystalMauler::ChangeAnimation()
{
	if (m_nowSit & NowCharaSit::Idle)
	{
		m_animationInfo.start = 0;		// 開始コマ
		m_animationInfo.end = 7;		// 終了コマ	
	}
	if (m_nowSit & NowCharaSit::Move)
	{
		m_animationInfo.start = 8;		// 開始コマ
		m_animationInfo.end = 15;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Skill)
	{
		m_animationInfo.start = 16;		// 開始コマ
		m_animationInfo.end = 22;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Skill2)
	{
		m_animationInfo.start = 23;		// 開始コマ
		m_animationInfo.end = 37;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Hit)
	{
		m_animationInfo.start = 38;		// 開始コマ
		m_animationInfo.end = 43;		// 終了コマ
	}
	if (m_nowSit & NowCharaSit::Down)
	{
		m_animationInfo.start = 44;		// 開始コマ
		m_animationInfo.end = 58;		// 終了コマ
	}
	m_animationInfo.count = 0.0f;	//	現在のコマ数カウント
	m_animationInfo.speed = 0.2f;	// アニメーションの速度
}
