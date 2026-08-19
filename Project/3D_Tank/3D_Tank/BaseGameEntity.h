#pragma once
#pragma warning(disable:4786)

#include <string>
#include <cassert>
#include "Pawn.h"
// 説明: ゲームオブジェクトの基底クラス

struct Telegram;

class BaseGameEntity : public Pawn {
public:
	enum {default_entity_type = -1};

	BaseGameEntity(int id): Pawn() { setID(id); }
	virtual ~BaseGameEntity() {}

	/////////////////////////////////////

	// virtual bool handleMessage(const Telegram& msg) { return false; }

	static int getNextValidID() { return m_iNextValidID; }
	static void resetNextValidID() { m_iNextValidID = 0; }

	int getID()const { return m_ID; }

protected:
	int m_ID; // 各エンティティに一意の識別番号を割り当てる

	static int m_iNextValidID; // 次に割り当てる有効なID。BaseGameEntityの生成ごとに更新する

	void setID(int val); // IDを正しく設定するため、コンストラクター内で呼び出す
	                     // 指定値が次の有効なID以上であることを検証し、
						 // IDを設定して次の有効なIDをインクリメントする

};

