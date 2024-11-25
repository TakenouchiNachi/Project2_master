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

//まとめ関数
void Col_Update(GameObject* go);