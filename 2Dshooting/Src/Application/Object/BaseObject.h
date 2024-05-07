#pragma once

class BaseObject
{
public:

	BaseObject() {}
	virtual ~BaseObject() {}

	// オブジェクトの種類
	enum class ObjectType
	{
		Enemy,
		Bullet,
		EnemyBullet
	};

	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void Release();

	// Hit時の処理
	virtual void OnHit();
	virtual float GetScale() { return m_scale; };

	void SetTexture(std::string _fileName);

	ObjectType GetObjType() { return m_objType; }
	
	Math::Vector3 GetPos() { return m_pos; }

	bool GetAliveFlg() { return m_bAlive; }

protected:

	KdTexture		m_tex;

	Math::Vector3	m_pos;
	Math::Vector3	m_rad;
	Math::Matrix	m_mat;
	float m_scale;

	bool			m_bAlive = true;

	ObjectType		m_objType;

};