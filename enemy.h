#pragma once


//ソースファイルの読み込み
#include<math.h>

//ヘッダーファイルの読み込み
#include"structuer.h"

//初期化関数
void EnemyInitialize(GameObject* go);


//更新処理
void EnemyUpdate(GameObject* go);


//描画関数
void EnemyDraw(GameObject* go);
