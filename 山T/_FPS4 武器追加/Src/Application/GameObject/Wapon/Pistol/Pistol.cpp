#include "Pistol.h"

void Pistol::Update()
{
	// 基底クラスの更新処理(ワールド行列作成)
	WeaponBase::Update();
}

void Pistol::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Weapon/Pistol/Pistol.gltf");
	}

	Math::Vector3 m_localPos = { 0.35f, -0.25f, 0.2f };
	m_localMat = Math::Matrix::CreateTranslation(m_localPos);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}
