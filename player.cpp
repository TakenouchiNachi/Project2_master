//ソースファイルの読み込み
#include<math.h>
#include<Novice.h>

//ヘッダーファイルの読み込み
#include"camera.h"
#include"enum.h"
#include"structuer.h"
#include"common.h"

//初期化関数
void PlayerInitialize(GameObject* go) {

	//自機の初期化
	go->player.BaseInfoInitialize(
		//初期座標(x,y)
		640.0f,
		360.0f,

		//横幅、縦幅
		32.0f,
		32.0f,

		//加速度(x,y)
		0.0f,
		0.0f,

		//速度(x,y)
		0.0f,
		0.0f,

		//ベクトル(x,y)
		0.0f,
		0.0f,

		//スピード
		2.0f,

		//画像
		Novice::LoadTexture("./image./player.png"),

		//色
		WHITE,

		//オブジェクトタイプ（可動or不可動）
		Else
	);

	//プレイヤー関連のフラグの初期化
	go->player.IsHoldObject = false;

	
	/*========================================
			  フリッカーの初期化
	========================================*/
	go->player.flickr.BaseInfoInitialize(
		//初期座標(x,y)
		640.0f,
		360.0f,

		//横幅、縦幅
		16.0f,
		16.0f,

		//加速度(x,y)
		0.0f,
		0.0f,

		//速度(x,y)
		0.0f,
		0.0f,

		//ベクトル(x,y)
		0.0f,
		0.0f,

		//スピード
		0.0f,

		//画像
		Novice::LoadTexture("./image./flickr.png"),

		//色
		WHITE,

		//オブジェクトタイプ（可動or不可動）
		Else
	);

	//フリッカー関連フラグの初期化
	go->player.flickr.IsHit = false;
	go->player.flickr.IsMovableObjHit = false;
	go->player.flickr.IsShot = false;
	go->player.flickr.RangeLimit = 300;
	go->player.flickr.ChargeTime = 0;
}


//フリッカーの発射方向を決める関数
void FlickrShotDirection(GameObject* go, Key* key) {

	//垂直・水平方向
	if (key->keys[DIK_W]) {
		go->player.flickr.Vector.y = 1.0f;
		go->player.flickr.Vector.x = 0.0f;
	}
	if (key->keys[DIK_S]) {
		go->player.flickr.Vector.y = -1.0f;
		go->player.flickr.Vector.x = 0.0f;
	}
	if (key->keys[DIK_A]) {
		go->player.flickr.Vector.x = -1.0f;
		go->player.flickr.Vector.y = 0.0f;

	}
	if (key->keys[DIK_D]) {
		go->player.flickr.Vector.x = 1.0f;
		go->player.flickr.Vector.y = 0.0f;

	}

	//斜め方向
	if (key->keys[DIK_W] && key->keys[DIK_A]) {
		go->player.flickr.Vector.y = 1.0f;
		go->player.flickr.Vector.x = -1.0f;
	}
	if (key->keys[DIK_W] && key->keys[DIK_D]) {
		go->player.flickr.Vector.y = 1.0f;
		go->player.flickr.Vector.x = 1.0f;
	}
	if (key->keys[DIK_S] && key->keys[DIK_A]) {
		go->player.flickr.Vector.y = -1.0f;
		go->player.flickr.Vector.x = -1.0f;
	}
	if (key->keys[DIK_S] && key->keys[DIK_D]) {
		go->player.flickr.Vector.y = -1.0f;
		go->player.flickr.Vector.x = 1.0f;
	}
}


//オブジェクトの発射方向を決める関数
void MovableObjectShotDirection(GameObject* go, Key* key) {

	//垂直・水平方向
	if (key->keys[DIK_W]) {
		go->movableobject.Vector.y = 1.0f;
		go->movableobject.Vector.x = 0.0f;
	}
	if (key->keys[DIK_S]) {
		go->movableobject.Vector.y = -1.0f;
		go->movableobject.Vector.x = 0.0f;
	}
	if (key->keys[DIK_A]) {
		go->movableobject.Vector.x = -1.0f;
		go->movableobject.Vector.y = 0.0f;

	}
	if (key->keys[DIK_D]) {
		go->movableobject.Vector.x = 1.0f;
		go->movableobject.Vector.y = 0.0f;

	}

	//斜め方向
	if (key->keys[DIK_W] && key->keys[DIK_A]) {
		go->movableobject.Vector.y = 1.0f;
		go->movableobject.Vector.x = -1.0f;
	}
	if (key->keys[DIK_W] && key->keys[DIK_D]) {
		go->movableobject.Vector.y = 1.0f;
		go->movableobject.Vector.x = 1.0f;
	}
	if (key->keys[DIK_S] && key->keys[DIK_A]) {
		go->movableobject.Vector.y = -1.0f;
		go->movableobject.Vector.x = -1.0f;
	}
	if (key->keys[DIK_S] && key->keys[DIK_D]) {
		go->movableobject.Vector.y = -1.0f;
		go->movableobject.Vector.x = 1.0f;
	}
}

//フリッカーの発射処理
void FlickrShot(GameObject* go,Key* key) {

	//チャージ開始
	if (key->keys[DIK_J] && go->player.flickr.ChargeTime <= 20) {

		go->player.flickr.ChargeTime++;
		go->player.flickr.RangeLimit += 15;

		//フリッカーの発射方向を更新する関数
		FlickrShotDirection(go, key);

		//チャージ中は移動速度0
		go->player.Speed = 0.0f;

	}
	
	else if (!key->keys[DIK_J] && key->preKeys[DIK_J] || go->player.flickr.ChargeTime >= 20) {
		
		//発射フラグを立てる
		go->player.flickr.IsShot = true;

		//位置をプレイヤーに合わせる
		go->player.flickr.WorldPos = go->player.WorldPos;

		//タイマーをリセット
		go->player.flickr.ChargeTime = 0;

		//移動速度を戻す
		go->player.Speed = 2.0f;
	}
}

//フリッカートオブジェクトとの当たり判定
void FlickrCollision(GameObject* go) {

	//マップとの当たり判定
	for (int i = 0; i < VerBlockNum; ++i) {
		for (int j = 0; j < HolBlockNum; ++j) {

			//マップ番号が0以外（オブジェクトがある）なら当たり判定をとる
			if (go->mapchip[i][j].Map != 0) {

				if (go->player.flickr.CollisionLeftTop.x < go->mapchip[i][j].CollisionRightBottom.x && go->mapchip[i][j].CollisionLeftTop.x < go->player.flickr.CollisionRightBottom.x &&
					go->player.flickr.CollisionLeftTop.y < go->mapchip[i][j].CollisionRightBottom.y && go->mapchip[i][j].CollisionLeftTop.y < go->player.flickr.CollisionRightBottom.y) {


					//当たっていたらフラグを立てる
					go->player.flickr.IsHit = true;

					//どのマップチップと当たっているのか保存する
					go->mapchip[i][j].IsHit = true;
				}
			}
		}
	}

	//可動オブジェクトとの当たり判定
	if (go->player.flickr.CollisionLeftTop.x < go->movableobject.CollisionRightBottom.x && go->movableobject.CollisionLeftTop.x < go->player.flickr.CollisionRightBottom.x &&
		go->player.flickr.CollisionLeftTop.y < go->movableobject.CollisionRightBottom.y && go->movableobject.CollisionLeftTop.y < go->player.flickr.CollisionRightBottom.y) {

		//当たっていたらフラグを立てる
		go->player.flickr.IsMovableObjHit = true;
	}

	if (go->player.flickr.CollisionLeftTop.x < go->enemy.CollisionRightBottom.x && go->enemy.CollisionLeftTop.x < go->player.flickr.CollisionRightBottom.x &&
		go->player.flickr.CollisionLeftTop.y < go->enemy.CollisionRightBottom.y && go->enemy.CollisionLeftTop.y < go->player.flickr.CollisionRightBottom.y) {

		//当たっていたらフラグを立てる
		go->player.flickr.IsHit = true;

	}
}

//引き寄せる・引き寄せられる処理
void FlickrAttract(RectangleObject* obj,GameObject*go) {

	//オブジェクトを引き付ける
	if (obj->ObjectType == Movable) {

		//移動方向のベクトルを作成
		obj->Vector.x = go->player.WorldPos.x - obj->WorldPos.x;
		obj->Vector.y = go->player.WorldPos.y - obj->WorldPos.y;

		obj->WorldPos.x += NormalizeX(obj->Vector.x, obj->Vector.y) * 10.0f;
		obj->WorldPos.y += NormalizeY(obj->Vector.x, obj->Vector.y) * 10.0f;
	}

	//プレイヤーの移動
	else if (obj->ObjectType == ImMovable) {

		//移動方向のベクトルを作成

		go->player.Vector.x = go->player.flickr.WorldPos.x - go->player.WorldPos.x;
		go->player.Vector.y = go->player.flickr.WorldPos.y - go->player.WorldPos.y;
	}


	//移動終了後の処理
	if (obj->ObjectType == Movable) {

		//オブジェクトとプレイヤーの距離が一定距離より短くなったらフラグを折る

			if (sqrtf((obj->Vector.x * obj->Vector.x) + (obj->Vector.y * obj->Vector.y)) <= BlockSize) {
				go->player.flickr.IsMovableObjHit = false;
				go->player.flickr.IsShot = false;

				//限界射程を初期化する
				go->player.flickr.RangeLimit = 300;

				//ホールドフラグを立てる
				go->player.IsHoldObject = true;
			}
	}
	else if (obj->ObjectType == ImMovable) {

		//オブジェクトとプレイヤーの距離が一定距離より短くなったらフラグを折る
		if (sqrtf((go->player.Vector.x * go->player.Vector.x) + (go->player.Vector.y * go->player.Vector.y)) <= BlockSize) {
			go->player.flickr.IsHit = false;
			go->player.flickr.IsShot = false;

			//限界射程を初期化する
			go->player.flickr.RangeLimit = 300;

		}
	}
}



//移動終了後のマップチップとフリッカーのフラグを管理する関数
void FlickrAttractVer(GameObject* go, int x, int y) {

	float differX = go->player.WorldPos.x - go->mapchip[y][x].WorldPos.x;
	float differY = go->player.WorldPos.y - go->mapchip[y][x].WorldPos.y;


	if (sqrtf((differX * differX) + (differY * differY))<=BlockSize) {
		go->player.flickr.IsHit = false;
		go->player.flickr.IsShot = false;

	}
}

//プレイヤーのワイヤー移動のX成分
void PlayerWireMoveX(GameObject* go) {
	//プレイヤーが移動する処理
	if (go->player.flickr.IsHit) {
		for (int i = 0; i < VerBlockNum; ++i) {
			for (int j = 0; j < HolBlockNum; ++j) {

				if (go->mapchip[i][j].IsHit) {
					FlickrAttract(&go->mapchip[i][j], go);
					go->player.WorldPos.x += NormalizeX(go->player.Vector.x, go->player.Vector.y) * 10.0f;
					FlickrAttractVer(go, j, i);
					break;
				}
			}
		}

		//ボスに向かって移動
		FlickrAttract(&go->enemy, go);
		go->player.WorldPos.x += NormalizeX(go->player.Vector.x, go->player.Vector.y) * 10.0f;
	}

}

//プレイヤーのワイヤー移動のY成分
void PlayerWireMoveY(GameObject* go) {
	//プレイヤーが移動する処理
	if (go->player.flickr.IsHit) {
		for (int i = 0; i < VerBlockNum; ++i) {
			for (int j = 0; j < HolBlockNum; ++j) {

				if (go->mapchip[i][j].IsHit) {
					FlickrAttract(&go->mapchip[i][j], go);
					go->player.WorldPos.y += NormalizeY(go->player.Vector.x, go->player.Vector.y) * 10.0f;
					FlickrAttractVer(go, j, i);

					break;
				}
			}
		}

		//ボスに向かって移動
		FlickrAttract(&go->enemy, go);
		go->player.WorldPos.y += NormalizeY(go->player.Vector.x, go->player.Vector.y) * 10.0f;
	}

}

//フリッカーの処理をまとめた関数
void FlickrUpdate(GameObject* go, Key* key) {

	//位置情報の更新
	SetFourVertexes(&go->player.flickr);

	//発射処理
	if (!go->player.flickr.IsShot && !go->player.IsHoldObject) {
		FlickrShot(go, key);
	}

	//紐の当たり判定の移動処理
	if (go->player.flickr.IsShot && !go->player.flickr.IsHit && !go->player.flickr.IsMovableObjHit) {
		go->player.flickr.WorldPos.x += NormalizeX(go->player.flickr.Vector.x, go->player.flickr.Vector.y) * 15.0f;
		go->player.flickr.WorldPos.y += NormalizeY(go->player.flickr.Vector.x, go->player.flickr.Vector.y) * 15.0f;
	}
	
	//オブジェクトを持っているフラグがtrueならオブジェクトをプレイヤーの位置に固定
	if (go->player.flickr.IsMovableObjHit) {
		go->player.flickr.WorldPos = go->movableobject.WorldPos;
	}


	//可動オブジェクトを引っ張る処理
	if (go->player.flickr.IsMovableObjHit) {
		FlickrAttract(&go->movableobject, go);
		FlickrAttract(&go->enemy, go);
	}

	//フラグがおれているとき、判定円をプレイヤーのポジションに移動
	if (!go->player.flickr.IsMovableObjHit && !go->player.flickr.IsShot) {
		go->player.flickr.WorldPos = go->player.WorldPos;
	}

	//紐の当たり判定
	if (go->player.flickr.IsShot) {
		FlickrCollision(go);
	}

	//射程限界になったらフラグを折る
	if (Distance(go->player.WorldPos.x, go->player.WorldPos.y,go->player.flickr.WorldPos.x, go->player.flickr.WorldPos.y) >= go->player.flickr.RangeLimit) {
		go->player.flickr.IsShot = false;

		//限界射程を初期化する
		go->player.flickr.RangeLimit = 300;
	}
}

//保持しているオブジェクトの発射
void MovableObjectShot(GameObject* go, Key* key) {

	if (go->player.IsHoldObject && key->keys[DIK_J]) {
			MovableObjectShotDirection(go, key);

			go->player.IsHoldObject = false;
			go->movableobject.IsShot = true;
	}

	if (go->movableobject.IsShot) {

		go->movableobject.WorldPos.x += NormalizeX(go->movableobject.Vector.x, go->movableobject.Vector.y) * 8.0f;
		go->movableobject.WorldPos.y += NormalizeY(go->movableobject.Vector.x, go->movableobject.Vector.y) * 8.0f;
	}


}

//プレイヤーの動き
void PlayerMove(GameObject* go, Key* key) {

	//移動処理
	if (!go->player.flickr.IsHit) {

		if (key->keys[DIK_W]) {
			go->player.WorldPos.y += go->player.Speed;
		}
		if (key->keys[DIK_S]) {
			go->player.WorldPos.y -= go->player.Speed;
		}
	}

	//マップ番号の取得
	SetFourVertexes(&go->player);

	//めり込みを直す
	//上
	if (go->mapchip[go->player.MapCollisionLeftTop.y][go->player.MapCollisionLeftTop.x].Map != 0 || go->mapchip[go->player.MapCollisionRightTop.y][go->player.MapCollisionRightTop.x].Map != 0) {
		go->player.WorldPos.y = float((go->player.MapCollisionLeftTop.y + 1) * BlockSize + go->player.Height / 2.0f);
	}

	//下
	if (go->mapchip[go->player.MapCollisionLeftBottom.y][go->player.MapCollisionLeftBottom.x].Map != 0 || go->mapchip[go->player.MapCollisionRightBottom.y][go->player.MapCollisionRightBottom.x].Map != 0) {
		go->player.WorldPos.y = float((go->player.MapCollisionLeftBottom.y) * BlockSize - go->player.Height / 2.0f);
	}

	//ワイヤーの上下移動
	PlayerWireMoveY(go);


	//マップ番号の取得
	SetFourVertexes(&go->player);

	//めり込みを直す
	//上
	if (go->mapchip[go->player.MapCollisionLeftTop.y][go->player.MapCollisionLeftTop.x].Map != 0 || go->mapchip[go->player.MapCollisionRightTop.y][go->player.MapCollisionRightTop.x].Map != 0) {
		go->player.WorldPos.y = float((go->player.MapCollisionLeftTop.y + 1) * BlockSize + go->player.Height / 2.0f);
	}

	//下
	if (go->mapchip[go->player.MapCollisionLeftBottom.y][go->player.MapCollisionLeftBottom.x].Map != 0 || go->mapchip[go->player.MapCollisionRightBottom.y][go->player.MapCollisionRightBottom.x].Map != 0) {
		go->player.WorldPos.y = float((go->player.MapCollisionLeftBottom.y) * BlockSize - go->player.Height / 2.0f);
	}


	//移動処理
	if (!go->player.flickr.IsHit) {

		if (key->keys[DIK_A]) {
			go->player.WorldPos.x -= go->player.Speed;
		}
		if (key->keys[DIK_D]) {
			go->player.WorldPos.x += go->player.Speed;
		}
	}

	//マップ番号の取得
	SetFourVertexes(&go->player);

	if (go->mapchip[go->player.MapCollisionLeftTop.y][go->player.MapCollisionLeftTop.x].Map != 0 || go->mapchip[go->player.MapCollisionLeftBottom.y][go->player.MapCollisionLeftBottom.x].Map != 0) {
		go->player.WorldPos.x = float((go->player.MapCollisionLeftBottom.x + 1) * BlockSize + go->player.Width / 2.0f);
	}

	//右のめり込みを直す
	if (go->mapchip[go->player.MapCollisionRightTop.y][go->player.MapCollisionRightTop.x].Map != 0 || go->mapchip[go->player.MapCollisionRightBottom.y][go->player.MapCollisionRightBottom.x].Map != 0) {
		go->player.WorldPos.x = float((go->player.MapCollisionRightBottom.x) * BlockSize - go->player.Width / 2.0f);
	}

	//ワイヤーの左右移動
	PlayerWireMoveX(go);


	//マップ番号の取得
	SetFourVertexes(&go->player);

	if (go->mapchip[go->player.MapCollisionLeftTop.y][go->player.MapCollisionLeftTop.x].Map != 0 || go->mapchip[go->player.MapCollisionLeftBottom.y][go->player.MapCollisionLeftBottom.x].Map != 0) {
		go->player.WorldPos.x = float((go->player.MapCollisionLeftBottom.x + 1) * BlockSize + go->player.Width / 2.0f);
	}

	//右のめり込みを直す
	if (go->mapchip[go->player.MapCollisionRightTop.y][go->player.MapCollisionRightTop.x].Map != 0 || go->mapchip[go->player.MapCollisionRightBottom.y][go->player.MapCollisionRightBottom.x].Map != 0) {
		go->player.WorldPos.x = float((go->player.MapCollisionRightBottom.x) * BlockSize - go->player.Width / 2.0f);
	}
}

//プレイヤーの更新処理
void PlayerUpdate(GameObject* go,CameraRelated* cr, Key* key) {

	//Movement
	PlayerMove(go, key);

	//基本情報の更新
	SetFourVertexes(&go->player);
	RenderingPipeline(&go->player, cr);
}

//描画関数
void PlayerDraw(GameObject* go) {

	go->player.RectObjDraw();
}

void FlickrDraw(GameObject* go) {

	if (go->player.flickr.IsShot) {
		go->player.flickr.RectObjDraw();
	}
}