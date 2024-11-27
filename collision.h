#pragma once

#include"structuer.h"
#include"common.h"

/*=====================================================
              当たり判定の関数をまとめる
 =====================================================*/

 //手とプレイヤーの当たり判定
void Col_Player_Hands(GameObject* go);

//弾とプレイヤーの当たり判定
void Col_Player_Bullet(GameObject* go);

//プレイヤーと敵の当たり判定（突撃）
void Col_Player_Enemy(GameObject* go);

//投擲物と敵との当たり判定
void Col_PlayerThrowObj_Hand(GameObject* go);

//まとめ関数
void Col_Update(GameObject* go);