#pragma once

//class Player;
//class Enemy;
class BaseObject;

class GameScene
{
public:

	GameScene() { }
	~GameScene() { Release(); }	// 破棄時に解放

	void PreUpdate();	// 更新を呼ぶ前の処理
	void Update();		// 更新
	void Draw();		// 描画

	void Init();		// 初期化

	// オブジェクトリストを取得
	std::vector<std::shared_ptr<BaseObject>> GetObjList() { return m_objList; }

	// オブジェクトリストにオブジェクト追加
	void AddObject(std::shared_ptr<BaseObject> _obj) { m_objList.push_back(_obj); }

private:

	void Release();		// 終了処理 ※勝手に呼ばれたくないのでprivate

	//Player* m_player = nullptr;	// 派生クラスのポインタ

	//BaseObject* m_player = nullptr;	// 基底クラスのポインタ
	//std::shared_ptr<Player> m_player = nullptr;	// スマートポインタ
	//std::shared_ptr<BaseObject> m_player = nullptr;	// スマートポインタ(ポリモーフィズム適用版)
	
	// 04/22
	//std::shared_ptr<BaseObject> m_enemy = nullptr;	// スマポ（ポリモ(ry )

	// 全オブジェクトのリストを可変長配列で管理
	// BaseObject型のshared_ptrを持った可変長配列vectorを宣言
	std::vector<std::shared_ptr<BaseObject>> m_objList;

	
};