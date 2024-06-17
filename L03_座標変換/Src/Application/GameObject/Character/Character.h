#pragma once

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;
	void DrawSprite()		override;

	void SetCamera(std::shared_ptr<KdCamera> camera)
	{
		m_wpCamera = camera;
	}

	void SetTerrain(std::shared_ptr<KdGameObject> terrain)
	{
		m_wpTerrain = terrain;
	}

private:
	Math::Vector3 nowPos;
	Math::Vector3 m_TargetPos;
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;
	KdTexture m_nameTex;
	std::weak_ptr<KdCamera>					m_wpCamera;
	std::weak_ptr<KdGameObject>					m_wpTerrain;
};