#include"structuer.h"
#include"enemy.h"
#include"common.h"

/*=====================================================
              当たり判定の関数をまとめる
 =====================================================*/


//手とプレイヤーの当たり判定
void Col_Player_Hands(GameObject* go) {

    //右手との当たり判定
    if (go->enemy.hand[Right].IsAlive) {

        if (go->enemy.hand[Right].IsAggression) {

            if (RectangleObjectCollision(&go->player, &go->enemy.hand[Right]) == true) {

                //プレイヤーのLifeを減らす
                go->player.HP--;
            }
        }
    }


    //左手との当たり判定
    if (go->enemy.hand[Left].IsAlive) {

        if (go->enemy.hand[Left].IsAggression) {

            if (RectangleObjectCollision(&go->player, &go->enemy.hand[Left]) == true) {

                //プレイヤーのLifeを減らす
                go->player.HP--;
            }
        }
    }
}

//弾とプレイヤーの当たり判定
void Col_Player_Bullet(GameObject* go) {

    //右手に属する弾との当たり判定
    for (int i = 0; i < EnemyBulletNum; ++i) {

        if (go->enemy.RightBullet[i].IsShot && go->enemy.RightBullet[i].IsAggression) {

            if (Distance(go->player.WorldPos, go->enemy.RightBullet[i].WorldPos) <= go->player.Width + go->enemy.RightBullet[i].Width) {

                //弾のフラグを折る
                go->enemy.RightBullet[i].IsAggression = false;
                go->enemy.RightBullet[i].IsShot = false;

                //プレイヤーのLifeを減らす
                go->player.HP--;
            }
        }
    }

    //左手に属する弾との当たり判定
    for (int i = 0; i < EnemyBulletNum; ++i) {

        if (go->enemy.LeftBullet[i].IsShot && go->enemy.LeftBullet[i].IsAggression) {

            if (Distance(go->player.WorldPos, go->enemy.LeftBullet[i].WorldPos) <= go->player.Width + go->enemy.LeftBullet[i].Width) {

                //弾のフラグを折る
                go->enemy.LeftBullet[i].IsAggression = false;
                go->enemy.LeftBullet[i].IsShot = false;

                //プレイヤーのLifeを減らす
                go->player.HP--;
            }
        }
    }
}

//まとめ関数
void Col_Update(GameObject* go) {
    Col_Player_Hands(go);
    Col_Player_Bullet(go);
}