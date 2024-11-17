#pragma once

//ソースファイルの読み込み
#include<math.h>

//ヘッダーファイルの読み込み
#include"structuer.h"

//初期化関数
void PlayerInitialize(GameObject* go);

//プレイヤーの動き
void PlayerMove(GameObject* go,Key* key);

//フリッカーの発射方向を決める関数
void FlickrShotDirection(GameObject* go, Key* key);

//オブジェクトの発射方向を決める関数
void MovableObjectShotDirection(GameObject* go, Key* key);

//フリッカーの発射処理
void FlickrShot(GameObject* go,Key* key);

//フリッカートオブジェクトとの当たり判定
void FlickrCollision(GameObject* go);

//引き寄せる・引き寄せられる処理
void FlickrAttract(RectangleObject* obj,GameObject* go);

//プレイヤーのワイヤー移動のX成分
void PlayerWireMoveX(GameObject* go);

//プレイヤーのワイヤー移動のY成分
void PlayerWireMoveY(GameObject* go);


//移動終了後のマップチップとフリッカーのフラグを管理する関数
void FlickrAttractVer(GameObject* go, int x, int y);

//フリッカーの処理
void FlickrUpdate(GameObject* go, Key* key);

//保持しているオブジェクトの発射
void MovableObjectShot(GameObject* go, Key* key);

//プレイヤーの更新処理
void PlayerUpdate(GameObject* go,CameraRelated* cr, Key* key);

//描画関数
void PlayerDraw(GameObject* go);

void FlickrDraw(GameObject* go);