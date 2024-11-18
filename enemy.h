#pragma once

//敵の行動パターンの列挙型Roketto
enum {
	None
};

//敵の状態（両手・片手・頭のみ）
enum {
	BothHands,
	OneHand,
	HeadOnly
};

//ソースファイルの読み込み
#include<math.h>

//ヘッダーファイルの読み込み
#include"structuer.h"

//初期化関数
void EnemyInitialize(GameObject* go);

//行動パターンを決める関数
//順番
void DecisionMoveType_Ver1(GameObject* go);


/*=================================
		　 攻撃パターン
 =================================*/
//台パン
void Daipan(GameObject* go);

//ロケットパンチ
void LocketPunch(GameObject* go);

//更新処理
void EnemyUpdate(GameObject* go, CameraRelated* cr);


//描画関数
void EnemyDraw(GameObject* go);
