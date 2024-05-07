#pragma once
struct TitleBack
{
	Math::Vector3	m_pos;
	KdTexture		m_tex;
	Math::Matrix	m_mat;
};
class TitleScene
{
public:

	TitleScene() { }
	~TitleScene() { Release(); }	// 破棄時に解放

	void PreUpdate();	// 更新を呼ぶ前の処理
	void Update();		// 更新
	void Draw();		// 描画

	void Init();		// 初期化



private:

	void Release();		// 終了処理 ※勝手に呼ばれたくないのでprivate
	KdTexture m_TitleTex;
	KdTexture m_EnterTex;
	Math::Vector3 m_TitlePos;
	Math::Vector3 m_EnterPos;
	Math::Matrix m_TitleMat;
	Math::Matrix m_EnterMat;

	Math::Matrix  m_scaleMat;
	int m_drawCount;
	KdTexture		m_tex;
	Math::Vector3	m_pos;
	Math::Matrix	m_mat;
	float m_scale;

	int Timer;

	TitleBack m_back[2];


};