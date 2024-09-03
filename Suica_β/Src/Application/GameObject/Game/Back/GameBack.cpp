#include "GameBack.h"

void GameBack::Init()
{
	//ポリゴン生成
	m_spPoly = std::make_shared<KdSquarePolygon>();

	m_spBackPoly = std::make_shared<KdSquarePolygon>();

	//読み込み
	m_spPoly->SetMaterial("Asset/Textures/Game/Back/SummerBack1.png");
	m_spPoly->SetScale({120.f, 50.f});

	m_spBackPoly->SetMaterial("Asset/Textures/Game/Back/SummerBack.png");
	m_spBackPoly->SetScale({ 120.f, 50.f });

	m_pos = m_localPos;
	m_secPos = m_localPos + Math::Vector3{ 120,0,0 };
}

void GameBack::Update()
{
	//回転移動補正値
	const float revisionMove = 100.f;

	Math::Vector3 targetPos = {};

	std::shared_ptr<KdGameObject> spTarget = m_wpTarget.lock();

	if (spTarget)
	{
		targetPos = spTarget->GetMatrix().Translation();
	}

	if (abs(targetPos.x - m_pos.x) > 115)
	{
		m_pos.x = targetPos.x + 115;
	}
	if (abs(targetPos.x - m_secPos.x) > 115)
	{
		m_secPos.x = targetPos.x + 115;
	}

	//画面揺らし
	m_pos.x += sin(DirectX::XMConvertToRadians(m_frame))/revisionMove;
	m_pos.y += cos(DirectX::XMConvertToRadians(m_frame))/revisionMove;

	m_secPos.x += sin(DirectX::XMConvertToRadians(m_frame)) / revisionMove;
	m_secPos.y += cos(DirectX::XMConvertToRadians(m_frame)) / revisionMove;

	//行列作成
	Math::Matrix rotateMat, transMat;

	rotateMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(70));
	transMat = Math::Matrix::CreateTranslation(m_pos);

	//行列作成
	m_mWorld = rotateMat * transMat;

	m_secMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(70)) * Math::Matrix::CreateTranslation(m_secPos);

	//フレーム加算
	m_frame++;

	//補正用変数
	const int revisionFrame = 360;

	//フレーム補正
	if (m_frame > revisionFrame)
	{
		m_frame -= revisionFrame;
	}

}

void GameBack::DrawUnLit()
{
	//描画
	m_spPoly->SetScale({ 120.f, 50.f });
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);

	//描画
	m_spPoly->SetScale({ -120.f, 50.f });
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_secMat);

	//最背景
	Math::Matrix mat = Math::Matrix::CreateTranslation({ 0 + m_wpTarget.lock()->GetMatrix().Translation().x,0,40 });
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spBackPoly, mat);
}
