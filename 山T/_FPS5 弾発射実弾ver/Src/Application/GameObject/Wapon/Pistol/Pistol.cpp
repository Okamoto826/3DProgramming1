#include "Pistol.h"
#include"../../Effect/Explosion/Explosion.h"
#include"../../../Scene/SceneManager.h"
#include"../../Bullet/Bullet.h"

void Pistol::Update()
{

	Math::Matrix _parentMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject> _spParent = m_wpParent.lock();
	if (_spParent)
	{
		_parentMat = _spParent->GetMatrix();
	}

	// 銃口位置をデバッグ表示
	Math::Vector3 _muzzlePos = (m_localMuzzleMat * _parentMat).Translation();

	m_pDebugWire->AddDebugSphere(_muzzlePos, 0.05, kBlueColor);

	// 発射
	if (m_shotFlg)
	{

	
		// レイ判定用に必要パラメーターを設定する構造体を宣言
		KdCollider::RayInfo rayInfo;

		// レイの発(座標)を設定
		rayInfo.m_pos = _parentMat.Translation();

		// レイの方向を設定
		rayInfo.m_dir = _parentMat.Backward();

		// レイの長さを設定
		rayInfo.m_range =1000.f;

		// 当たり判定したいタイプを設定
		rayInfo.m_type = KdCollider::TypeDamage;

		

		// レイに当たったオブジェクト情報を格納するリスト
		std::list<KdCollider::CollisionResult> retRayList;

		// 作成したレイ情報でオブジェクトリストと当たり判定をする
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			obj->Intersects(rayInfo, &retRayList);
		}

		// レイに当たったリストから一番近いオブジェクトを検出
		bool hit = false;
		float maxOverLap = 0;
		Math::Vector3 hitPos = {};	// レイが遮断された(Hitした)座標

		for (auto& ret : retRayList)
		{
			// レイが当たった場合の貫通した長さが一番長いものを探す
			if (maxOverLap < ret.m_overlapDistance)
			{
				maxOverLap = ret.m_overlapDistance;
				hitPos = ret.m_hitPos;
				hit = true;
			}
		}
		if(m_rayBulletFlg)
		{

			// 当たっていたら
			if (hit)
			{
				std::shared_ptr<Explosion> explosion = std::make_shared<Explosion>();
				explosion->Init();
				explosion->SetPos(hitPos);
				SceneManager::Instance().AddObject(explosion);
			}
		}

		else
		{
			// レイの着弾点を利用して弾を飛ばすベクトルを算出
			Math::Vector3 _bulletDir;
			_bulletDir = hitPos - _muzzlePos;
			// 発射
			std::shared_ptr<Bullet> _bullet = std::make_shared<Bullet>();
			_bullet->Init();
			_bullet->Shot(_muzzlePos, _bulletDir);
			SceneManager::Instance().AddObject(_bullet);
		}


		

		// 弾の発射が終わったらフラグを見発射に戻す
		m_shotFlg = false;
		m_rayBulletFlg = false;
	}

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
	Math::Vector3 m_localMuzzlePos = { 0.f,0.18f,0.7f };
	m_localMuzzleMat = Math::Matrix::CreateTranslation(m_localMuzzlePos) * m_localMat;
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Pistol::ShotBullet(const bool rayFlg)
{
	m_shotFlg = true;
	m_rayBulletFlg = rayFlg;
}
