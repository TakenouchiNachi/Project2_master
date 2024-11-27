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

            if (RectangleObjectCollision(&go->player, &go->enemy.hand[Right]) == 1) {

                //ダメ―ジフラグを立てる
                if (!go->player.GetDamage) {

                    go->player.GetDamage = true;
                }

                //プレイヤーのLifeを減らす
                go->player.HP--;
            }
        }
    }


    //左手との当たり判定
    if (go->enemy.hand[Left].IsAlive) {

        if (go->enemy.hand[Left].IsAggression) {

            if (RectangleObjectCollision(&go->player, &go->enemy.hand[Left]) == 1) {

                //ダメ―ジフラグを立てる
                if (!go->player.GetDamage) {

                    go->player.GetDamage = true;
                }

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

        //プレイヤーがつかんでいないなら
        if (!go->enemy.RightBullet[i].IsAttracted) {

            if (go->enemy.RightBullet[i].IsShot && go->enemy.RightBullet[i].IsAggression) {

                if (Distance(go->player.WorldPos, go->enemy.RightBullet[i].WorldPos) <= go->player.Width + go->enemy.RightBullet[i].Width) {

                    //弾のフラグを折る
                    go->enemy.RightBullet[i].IsAggression = false;
                    go->enemy.RightBullet[i].IsShot = false;

                    //ダメ―ジフラグを立てる
                    if (!go->player.GetDamage) {

                        go->player.GetDamage = true;

                    }

                    //プレイヤーのLifeを減らす
                    go->player.HP--;
                }
            }
        }
    }

    //左手に属する弾との当たり判定
    for (int i = 0; i < EnemyBulletNum; ++i) {

        //プレイヤーがつかんでいないなら
        if (!go->enemy.LeftBullet[i].IsAttracted) {

            if (go->enemy.LeftBullet[i].IsShot && go->enemy.LeftBullet[i].IsAggression) {

                if (Distance(go->player.WorldPos, go->enemy.LeftBullet[i].WorldPos) <= go->player.Width + go->enemy.LeftBullet[i].Width) {

                    //弾のフラグを折る
                    go->enemy.LeftBullet[i].IsAggression = false;
                    go->enemy.LeftBullet[i].IsShot = false;

                    if (!go->player.GetDamage) {

                        //ダメ―ジフラグを立てる
                        go->player.GetDamage = true;
                    }

                    //プレイヤーのLifeを減らす
                    go->player.HP--;
                }
            }
        }
    }
}

//プレイヤーと敵の当たり判定（突撃）
void Col_Player_Enemy(GameObject* go) {

    /*   手との当たり判定   */
    
    //プレイヤーが攻撃判定を持っている時
    if (go->player.IsAggression) {

        for (int i = 0; i < 2; i++) {

            //手がダウン状態なら
            if (go->enemy.hand[i].IsDown) {

                //衝突判定をとる
                if (RectangleObjectCollision(&go->player, &go->enemy.hand[i]) == 1) {

                    go->enemy.hand[i].IsAlive = false;
                }
            }
        }
    }

    /*   顔との当たり判定   */

    //プレイヤーが攻撃判定を持っている時
    if (go->player.IsAggression) {

        //顔しか残っていないなら
        if (go->enemy.Condition == HeadOnly) {

            //衝突判定をとる
            if (RectangleObjectCollision(&go->player, &go->enemy) == 1) {

                go->enemy.IsAlive = false;
            }
        }
    }
}

//投擲物と敵との当たり判定
void Col_PlayerThrowObj_Hand(GameObject* go) {

    /*   右手との当たり判定   */
    for (int i = 0; i < EnemyBulletNum; ++i) {

        /*  右弾  */
        //プレイヤーへの攻撃性がないとき
        if (!go->enemy.RightBullet[i].IsAggression && go->enemy.RightBullet[i].IsShot_p) {

            //当たったらダウン状態にさせる
            if (RectangleObjectCollision(&go->enemy.hand[Right], &go->enemy.RightBullet[i])) {
                go->enemy.hand[Right].IsDown = true;

                //フラグを折る
                go->enemy.RightBullet[i].IsShot_p = false;
            }

        }
    }

    for (int i = 0; i < EnemyBulletNum; ++i) {

        /*  左弾  */
        if (!go->enemy.LeftBullet[i].IsAggression && go->enemy.LeftBullet[i].IsShot_p) {

            //当たったらダウン状態にさせる
            if (RectangleObjectCollision(&go->enemy.hand[Left], &go->enemy.LeftBullet[i])) {
                go->enemy.hand[Left].IsDown = true;

                //フラグを折る
                go->enemy.LeftBullet[i].IsShot_p = false;
            }

        }
    }


    /*   左手との当たり判定   */
    for (int i = 0; i < EnemyBulletNum; ++i) {

        /*  右弾  */
        //プレイヤーへの攻撃性がないとき
        if (!go->enemy.RightBullet[i].IsAggression && go->enemy.RightBullet[i].IsShot_p) {

            //当たったらダウン状態にさせる
            if (RectangleObjectCollision(&go->enemy.hand[Right], &go->enemy.RightBullet[i])) {
                go->enemy.hand[Left].IsDown = true;

                //フラグを折る
                go->enemy.LeftBullet[i].IsShot_p = false;
            }

        }
    }

    for (int i = 0; i < EnemyBulletNum; ++i) {

        /*  左弾  */
        if (!go->enemy.LeftBullet[i].IsAggression && go->enemy.LeftBullet[i].IsShot_p) {

            //当たったらダウン状態にさせる
            if (RectangleObjectCollision(&go->enemy.hand[Right], &go->enemy.LeftBullet[i])) {
                go->enemy.hand[Left].IsDown = true;

                //フラグを折る
                go->enemy.LeftBullet[i].IsShot_p = false;
            }

        }
    }
}

//まとめ関数
void Col_Update(GameObject* go) {
    Col_Player_Hands(go);
    Col_Player_Bullet(go);
    Col_Player_Enemy(go);
    Col_PlayerThrowObj_Hand(go);
}