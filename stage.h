#pragma once

//ソースファイルの読み込み
#include<math.h>
#include<Novice.h>

//ヘッダーファイルの読み込み
#include"structuer.h"

//初期化関数
void StageInitialize(GameObject* go);

//ステージ情報の更新
void StageGenerate(GameObject* go);

//保持している時の処理の関数
void  MovableObjectHold(GameObject* go);

//可動オブジェクトの更新処理関数
void MovableObjectUpdate(GameObject* go,Key* key);

//描画関数
void StageDraw(GameObject* go);

//可動オブジェクトの描画関数
void MovableObjectDraw(GameObject* go);