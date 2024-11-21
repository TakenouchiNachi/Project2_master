#pragma once

//敵の行動パターンの列挙型
enum {
	None,
	daipan,
	locketpunch
};

//敵の状態（両手・片手・頭のみ）
enum {
	BothHands,
	OneHand,
	HeadOnly
};

//手の左右の
enum {
	Right,
	Left
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
//全体フレーム
const float DaiPanWholeFrame = 380.0f;
void Daipan(GameObject* go, float WholeFrame, float TransrateFrame, float OccurrenceFrame, float LastingFlame);

//ロケットパンチ7
const float LocketPunchWholeFrame = 600.0f;
void LocketPunch(GameObject* go, float WholeFrame, float TransrateFrame, float OccurrenceFrame, float LastingFlame);




//更新処理
void EnemyUpdate(GameObject* go, CameraRelated* cr);

//描画関数
void EnemyDraw(GameObject* go);

void EnemyDebugPrintf(GameObject* go);
