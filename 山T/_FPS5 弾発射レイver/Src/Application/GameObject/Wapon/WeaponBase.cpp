#include "WeaponBase.h"

void WeaponBase::Update()
{
	const std::shared_ptr<const KdGameObject> _spParent = m_wpParent.lock();
	if (_spParent)
	{
		Math::Matrix _parentMat = Math::Matrix::Identity;
		_parentMat = _spParent->GetMatrix();

		m_mWorld = m_localMat * _parentMat;
	}

	
}

void WeaponBase::DrawLit()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}
