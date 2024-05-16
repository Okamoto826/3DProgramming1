#include "hamuhamu.h"

HamuHamu::~HamuHamu()
{
}

void HamuHamu::Init()
{
	m_spPoly = std::make_shared<KdSquarePolygon>();
	m_spPoly->SetMaterial
	("Asset/Data/LessonData/Character/Hamu.png");

}

void HamuHamu::Update()
{
	//ハム太郎の更新
	{
		//キャラクタの移動速度(マネしちゃだめ)
		float moveSpd = 0.05f;
		Math::Vector3 nowPos = m_mWorld.Translation();

		//移動する方向ベクトル 大きさは１で固定！！
		Math::Vector3 moveVec = Math::Vector3::Zero;
		float len = moveVec.Length();

		if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
		if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
		if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
		if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }
		//正規化
		moveVec.Normalize();
		moveVec *= moveSpd;

		nowPos += moveVec;

		//キャラクターのワールド行列を作る処理
		m_mWorld = Math::Matrix::CreateTranslation(nowPos);
		
	}
}

void HamuHamu::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader
		.DrawPolygon(*m_spPoly, m_mWorld);
}
