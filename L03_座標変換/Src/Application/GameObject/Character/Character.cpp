#include "Character.h"
#include"../../main.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
	m_nameTex.Load("Asset/Data/LessonData/Character/name.png");
}

void Character::Update()
{
	
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{// 1.マウス位置の取得
		POINT _mousePos;
		GetCursorPos(&_mousePos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &_mousePos);

		std::shared_ptr<KdCamera> _spCam = m_wpCamera.lock();
		if (_spCam)
		{
			// 2.レイの発射方向を定める(_rayDir)
			Math::Vector3 _camPos = _spCam->GetCameraMatrix().Translation();
			Math::Vector3 _rayDir = Math::Vector3::Zero;
			float _rayRange = 1000.0f;
			_spCam->GenerateRayInfoFromClientPos(_mousePos,_camPos,_rayDir,_rayRange );
		
			// 3.レイの衝突位置を求める
			const std::shared_ptr<KdGameObject> _spTerrain = m_wpTerrain.lock();
			if (_spTerrain)
			{
				Math::Vector3 _endRayPos = _camPos + _rayDir * _rayRange;
				KdCollider::RayInfo _rayInfo(KdCollider::TypeGround, _camPos, _endRayPos);

				// 実際の当たり判定処理
				std::list<KdCollider::CollisionResult> _results;
				_spTerrain->Intersects(_rayInfo, &_results);

				// 結果が1つでも返ってきていたら
				if (_results.size())
				{
					for (KdCollider::CollisionResult result : _results)
					{
						m_TargetPos=result.m_hitPos;
					}
				}
			}
		
		}
	}

	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	nowPos = GetPos(); //m_mWorld.Translation();

	Math::Vector3 moveVec = m_TargetPos-nowPos;
	if (moveVec.Length() < moveSpd)moveSpd = moveVec.Length();
	
	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;


	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	std::shared_ptr<KdCamera> _spCam = m_wpCamera.lock();
	if(_spCam)
	{
	_spCam->ConvertWorldToScreenDetail(m_mWorld.Translation(), nowPos);
		KdShaderManager::Instance().
			m_spriteShader.DrawTex
			(&m_nameTex,nowPos.x, nowPos.y);
	}
}
