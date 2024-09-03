#include "Bullet.h"

void Bullet::Update()
{
	m_pos += m_moveDir * m_moveSpeed;

	Math::Matrix _transMat;
	_transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_rotBulletMat*_transMat;
}

void Bullet::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Weapon/Bullet/Arrow.gltf");
	}
}

void Bullet::DrawLit()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Bullet::Shot(const Math::Vector3 muzzlePos, const Math::Vector3 shotDir)
{
	// 弾の初期座標をコピー
	m_pos = muzzlePos;

	// 進行ベクトルをコピー
	m_moveDir = shotDir;
	m_moveDir.Normalize();

	//========================================================================
	// 小銃へのベクトルと弾の進行方向のベクトルから弾の向き(回転行列)を作成
	//========================================================================
	
	//①ベクトルA・・・弾の現在の進行ベクトル
	Math::Vector3 _vecA = m_mWorld.Backward();

	//②ベクトルB・・・照準への進行ベクトル
	Math::Vector3 _vecB = m_moveDir;
	_vecB.Normalize();

	//①と②のベクトルの内積から角度を算出
	float _dot = _vecA.Dot(_vecB);	// 内積を算出
	float _angle = acos(_dot);		// 内積から２つのベクトルの角度を算出

	//①と②のベクトルの外積を利用して、回転するためのベクトル(回転軸)を作成
	Math::Vector3 _rotaxis = _vecA.Cross(_vecB);

	//内積で算出した角度分、外積で算出したベクトルで回転する行列を作成
	// = 弾がレティクルの方向を向く
	m_rotBulletMat = Math::Matrix::CreateFromAxisAngle(_rotaxis, _angle);

}
