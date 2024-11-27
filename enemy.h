#pragma once

//敵の行動パターンの列挙型
enum {
	None,
	daipan,
	locketpunch,
	bulletshot
};

//敵の状態（両手・片手・頭のみ）
enum {
	BothHands,
	OneHand,
	HeadOnly
};

//手の左右
enum {
	Right,
	Left
};


//手のダウン時間
const int HandDownTime = 480;

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

//ロケットパンチ
const float LocketPunchWholeFrame = 400.0f;
void LocketPunch(GameObject* go, float WholeFrame, float TransrateFrame, float OccurrenceFrame, float LastingFlame);

//弾撃ち（利用可能）
//弾の数
const int EnemyBulletNum = 4;
const float BulletShotWholeFrame = 330.0f;
void BulletShot(GameObject* go, float WholeFrame, float TransrateFrame, float OccurrenceFrame, Vector2 FixedPos);
void BulletMove(GameObject* go, int VectorUpdateFlame);

//画像の角度を変更する関数
void DegreeUpdate(GameObject* go);

//更新処理
void EnemyUpdate(GameObject* go, CameraRelated* cr);

//描画関数
void EnemyDraw(GameObject* go);

void EnemyDebugPrintf(GameObject* go);
