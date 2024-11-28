//ソースファイルの読み込み
#include<math.h>
#include<Novice.h>

//ヘッダーファイルの読み込み
#include"camera.h"
#include"enum.h"
#include"enemy.h"
#include"structuer.h"
#include"common.h"
#include"sceneChange.h"

//初期化関数
void PlayerInitialize(GameObject* go) {

	//自機の初期化
	go->player.BaseInfoInitialize(
		//初期座標(x,y)
		WorldWidth / 2.0f,
		100.0f,

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
		4.0f,

		//画像
		Novice::LoadTexture("./image./player_ver5.png"),

		//画像の幅
		32.0f,
		32.0f,

		//色
		0xf8f8f8ff,

		//オブジェクトタイプ（可動or不可動）
		Else
	);

	//プレイヤー関連のフラグの初期化
	go->player.GetDamage = false;
	go->player.CanShotFlickr = true;
	go->player.IsAggression = false;
	go->player.IsHoldObject = false;
	go->player.IsAlive = true;
	go->player.HP = 5;


		go->player.HPGH.BaseInfoInitialize(
			//初期座標(x,y)
			0.0f,
			360.0f,

			//横幅、縦幅
			50.0f,
			50.0f,

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
			Novice::LoadTexture("./image./Number.png"),

			//画像の幅
			300.0f,
			300.0f,

			//色
			WHITE,

			//オブジェクトタイプ（可動or不可動）
			Else
		);

		go->player.HPGH.ImagePos = { 1200.0f,0.0f };

		go->player.RemainingLifeGH.BaseInfoInitialize(
			//初期座標(x,y)
			640.0f,
			360.0f,

			//横幅、縦幅
			80.0f,
			50.0f,

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
			Novice::LoadTexture("./image./LifeLimit.png"),

			//画像の幅
			500.0f,
			300.0f,

			//色
			WHITE,

			//オブジェクトタイプ（可動or不可動）
			Else
		);

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

		//画像の幅
		0.0f,
		0.0f,

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
void MovableObjectShotDirection(RectangleObject* go, Key* key) {

	//垂直・水平方向
	if (key->keys[DIK_W]) {
		go->Vector.y = 1.0f;
		go->Vector.x = 0.0f;
	}
	if (key->keys[DIK_S]) {
		go->Vector.y = -1.0f;
		go->Vector.x = 0.0f;
	}
	if (key->keys[DIK_A]) {
		go->Vector.x = -1.0f;
		go->Vector.y = 0.0f;

	}
	if (key->keys[DIK_D]) {
		go->Vector.x = 1.0f;
		go->Vector.y = 0.0f;

	}

	//斜め方向
	if (key->keys[DIK_W] && key->keys[DIK_A]) {
		go->Vector.y = 1.0f;
		go->Vector.x = -1.0f;
	}
	if (key->keys[DIK_W] && key->keys[DIK_D]) {
		go->Vector.y = 1.0f;
		go->Vector.x = 1.0f;
	}
	if (key->keys[DIK_S] && key->keys[DIK_A]) {
		go->Vector.y = -1.0f;
		go->Vector.x = -1.0f;
	}
	if (key->keys[DIK_S] && key->keys[DIK_D]) {
		go->Vector.y = -1.0f;
		go->Vector.x = 1.0f;
	}
}

//フリッカーの発射処理
void FlickrShot(GameObject* go,Key* key,Sounds* sounds) {

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

		SoundPlaySE(sounds->flickrShotPlayHandle, sounds->flickrShotSoundHandle, 0.5f);

		//位置をプレイヤーに合わせる
		go->player.flickr.WorldPos = go->player.WorldPos;

		//タイマーをリセット
		go->player.flickr.ChargeTime = 0;

		//移動速度を戻す
		go->player.Speed = 4.0f;
	}
}

//フリッカーとオブジェクトとの当たり判定
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


	//敵の弾とフリッカーの当たり判定
	//右の弾
	for (int i = 0; i < EnemyBulletNum; ++i) {
		if (RectangleObjectCollision(&go->enemy.RightBullet[i], &go->player.flickr)) {

			//敵が発射している状態の時
			if (go->enemy.RightBullet[i].IsShot) {

				//当たっていたらフラグを立てる
				go->enemy.RightBullet[i].IsAttracted = true;

				//弾に当たっていたらフラグを折る
				go->player.flickr.IsShot = false;

				//弾の攻撃性をなくす
				go->enemy.RightBullet[i].IsAggression = false;
			}
		}
	}
	//左の弾
	for (int i = 0; i < EnemyBulletNum; ++i) {
		if (RectangleObjectCollision(&go->enemy.LeftBullet[i], &go->player.flickr)) {

			//敵が発射している状態の時
			if (go->enemy.LeftBullet[i].IsShot) {

				//当たっていたらフラグを立てる
				go->enemy.LeftBullet[i].IsAttracted = true;

				//弾に当たっていたらフラグを折る
				go->player.flickr.IsShot = false;

				//弾の攻撃性をなくす
				go->enemy.LeftBullet[i].IsAggression = false;
			}
		}
	}


	//敵とフリッカーの当たり判定
	if (go->player.flickr.CollisionLeftTop.x < go->enemy.CollisionRightBottom.x && go->enemy.CollisionLeftTop.x < go->player.flickr.CollisionRightBottom.x &&
		go->player.flickr.CollisionLeftTop.y < go->enemy.CollisionRightBottom.y && go->enemy.CollisionLeftTop.y < go->player.flickr.CollisionRightBottom.y) {

		//当たっていたらフラグを立てる
		go->player.flickr.IsHit = true;
		
	}

	//手との当たり判定
	for (int i = 0; i < 2; ++i) {

		if (go->enemy.hand[i].IsAlive) {

			if (RectangleObjectCollision(&go->player.flickr, &go->enemy.hand[i])) {
				//当たっていたらフラグを立てる
				go->player.flickr.IsHit = true;

			}
		}
	}
}

//引き寄せる・引き寄せられる処理
void FlickrAttract(RectangleObject* obj, GameObject* go) {

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

		if (sqrtf((obj->Vector.x * obj->Vector.x) + (obj->Vector.y * obj->Vector.y)) <= 20) {

		

			//限界射程を初期化する
			go->player.flickr.RangeLimit = 300;

			//ホールドフラグを立てる
			//go->player.IsHoldObject = true;

			//「引き付けた」フラグを折る
			obj->IsAttracted = false;

			//「プレイヤーが持っている」フラグを立てる
			obj->IsHeld = true;

			
		}
	}
	else if (obj->ObjectType == ImMovable) {

		//オブジェクトとプレイヤーの距離が一定距離より短くなったらフラグを折る
		if (sqrtf((go->player.Vector.x * go->player.Vector.x) + (go->player.Vector.y * go->player.Vector.y)) <= BlockSize) {
			go->player.flickr.IsHit = false;
			go->player.flickr.IsShot = false;

			//攻撃判定をとる
			//go->player.IsAggression = false;

			//限界射程を初期化する
			go->player.flickr.RangeLimit = 300;

		}
	}
}

//保持しているオブジェクト(弾)の処理
void ObjectHold(GameObject* go) {

	//右弾
	for (int i = 0; i < EnemyBulletNum; ++i) {

		//弾をつかんだらIsShotをfalseにする
		if (go->enemy.RightBullet[i].IsAttracted) {
			go->enemy.RightBullet[i].IsShot = false;
		}

		//もし「プレイヤーが保持している」フラグがtrueなら
		if (go->enemy.RightBullet[i].IsHeld) {

			//座標を固定
			go->enemy.RightBullet[i].WorldPos.x = go->player.WorldPos.x;
			go->enemy.RightBullet[i].WorldPos.y = go->player.WorldPos.y + 20.0f;

		}
	}

	//左弾
	for (int i = 0; i < EnemyBulletNum; ++i) {

		//弾をつかんだらIsShotをfalseにする
		if (go->enemy.LeftBullet[i].IsAttracted) {
			go->enemy.LeftBullet[i].IsShot = false;
		}

		//もし「プレイヤーが保持している」フラグがtrueなら
		if (go->enemy.LeftBullet[i].IsHeld) {

			//座標を固定
			go->enemy.LeftBullet[i].WorldPos.x = go->player.WorldPos.x;
			go->enemy.LeftBullet[i].WorldPos.y = go->player.WorldPos.y + 20.0f;

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

		//手に向かって移動
		for (int i = 0; i < 2; ++i) {
			FlickrAttract(&go->enemy.hand[i], go);
		}

		//移動処理
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

		//手に向かって移動
		for (int i = 0; i < 2; ++i) {
			FlickrAttract(&go->enemy.hand[i], go);
		}
		go->player.WorldPos.y += NormalizeY(go->player.Vector.x, go->player.Vector.y) * 10.0f;
	}
}

//フリッカーの処理をまとめた関数
void FlickrUpdate(GameObject* go, Key* key,Sounds* sounds) {

	//位置情報の更新
	SetFourVertexes(&go->player.flickr);

	//発射処理
	if (!go->player.flickr.IsShot && !go->player.IsHoldObject && go->player.CanShotFlickr) {
		FlickrShot(go, key,sounds);
	}

	//紐の当たり判定の移動処理
	if (go->player.flickr.IsShot && !go->player.flickr.IsHit && !go->player.IsHoldObject) {
		go->player.flickr.WorldPos.x += NormalizeX(go->player.flickr.Vector.x, go->player.flickr.Vector.y) * 15.0f;
		go->player.flickr.WorldPos.y += NormalizeY(go->player.flickr.Vector.x, go->player.flickr.Vector.y) * 15.0f;
	}
	

	//右弾
	for (int i = 0; i < EnemyBulletNum; ++i) {

		if (go->enemy.RightBullet[i].IsAttracted) {
			FlickrAttract(&go->enemy.RightBullet[i], go);
		}
	}

	//左弾
	for (int i = 0; i < EnemyBulletNum; ++i) {

		if (go->enemy.LeftBullet[i].IsAttracted) {
			FlickrAttract(&go->enemy.LeftBullet[i], go);
		}
	}

	//うんちぶりぶりブリタニア

	//保持しているオブジェクトの固定
	ObjectHold(go);

	//フラグがおれているとき、判定円をプレイヤーのポジションに移動
	if (!go->player.IsHoldObject && !go->player.flickr.IsShot) {
		go->player.flickr.WorldPos = go->player.WorldPos;
	}

	//紐の当たり判定
	if (go->player.flickr.IsShot) {
		FlickrCollision(go);
	}

	//射程限界になったらフラグを折る
	if (Distance(go->player.WorldPos,go->player.flickr.WorldPos) >= go->player.flickr.RangeLimit) {
		go->player.flickr.IsShot = false;

		//限界射程を初期化する
		go->player.flickr.RangeLimit = 300;
	}
}

//保持している弾の発射
void IsPlayerHoldObject(GameObject* go) {

	//プレイヤーがオブジェクトを持っているかの判別
	for (int i = 0; i < EnemyBulletNum; ++i) {

		//いずれかのバレットが「保持されている」状態であったら
		if (go->enemy.RightBullet[i].IsHeld || go->enemy.LeftBullet[i].IsHeld) {

			go->player.IsHoldObject = true;
		}
		else {
			go->player.IsHoldObject = false;
		}
	}
}

//保持しているオブジェクトの発射
void HoldObjectShot(GameObject* go, Key* key ,float speed) {

	for (int i = 0; i < EnemyBulletNum; ++i) {

		if (go->enemy.RightBullet[i].IsHeld) {

			if (key->keys[DIK_J] && !key->preKeys[DIK_J]) {

				//プレイヤーに発射らフラグを立てる
				go->enemy.RightBullet[i].IsShot_p = true;

				//「保持している」フラグを折る
				go->enemy.RightBullet[i].IsHeld = false;

				//ベクトルの取得
				MovableObjectShotDirection(&go->enemy.RightBullet[i], key);

				//フリッカー発射不可能
				go->player.CanShotFlickr = false;
			}
		}

		if (go->enemy.LeftBullet[i].IsHeld) {

			if (key->keys[DIK_J] && !key->preKeys[DIK_J]) {

				//プレイヤーに発射らフラグを立てる
				go->enemy.LeftBullet[i].IsShot_p = true;

				//「保持している」フラグを折る
				go->enemy.LeftBullet[i].IsHeld = false;

				//ベクトルの取得
				MovableObjectShotDirection(&go->enemy.LeftBullet[i], key);

				//フリッカー発射不可能
				go->player.CanShotFlickr = false;
			}
		}
	}

	for (int i = 0; i < EnemyBulletNum; ++i) {

		//弾の挙動
		if (go->enemy.RightBullet[i].IsShot_p) {

			//右弾
			if (go->enemy.RightBullet[i].IsShot_p) {
				go->enemy.RightBullet[i].WorldPos.x += go->enemy.RightBullet[i].Vector.x * speed;
				go->enemy.RightBullet[i].WorldPos.y += go->enemy.RightBullet[i].Vector.y * speed;
			}
		}

		if (go->enemy.LeftBullet[i].IsShot_p) {

			//左弾
			if (go->enemy.LeftBullet[i].IsShot_p) {
				go->enemy.LeftBullet[i].WorldPos.x += go->enemy.LeftBullet[i].Vector.x * speed;
				go->enemy.LeftBullet[i].WorldPos.y += go->enemy.LeftBullet[i].Vector.y * speed;
			}
		}
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

	//オブジェクトの投擲処理
	IsPlayerHoldObject(go);
	HoldObjectShot(go, key,8.0f);

	//攻撃判定の付与
	if (go->player.flickr.IsHit) {
		go->player.IsAggression = true;
	}
	else {
		go->player.IsAggression = false;
	}

	//無敵判定の付与
	if (go->player.GetDamage) {
		go->player.InvincibleTime = 120;
	}
	if (go->player.InvincibleTime > 0) {
		go->player.IsInvincible = true;
		go->player.InvincibleTime--;
	}
	if (go->player.InvincibleTime <= 0) {
		go->player.IsInvincible = false;
	}



	//フリッカー発射可能状態の制御
	if (!go->player.CanShotFlickr) {

		if (!key->keys[DIK_J] && !key->preKeys[DIK_J]) {

			go->player.CanShotFlickr = true;

		}
	}

	//色の更新
	//無敵時間は色をくすませる
	if (go->player.IsInvincible) {
		go->player.Color = 0xaaaaaaff;
	}
	else {
		go->player.Color = 0xf8f8f8ff;
	}


	//基本情報の更新
	SetFourVertexes(&go->player);
	RenderingPipeline(&go->player, cr);
}

//プレイヤーのHUD関連の更新処理
void PlayerHudUpdate(GameObject* go) {

	//描画範囲の変更
	go->player.HPGH.ImagePos.x = 300.0f * (go->player.HP - 1);

	//四つ角
	SetFourVertexes(&go->player.HPGH);
}


//描画関数
void PlayerDraw(GameObject* go) {

	go->player.RectObjDraw();
}

//プレイヤーのHUD描画関数
void PlayerHudDraw(GameObject* go) {

	Novice::DrawQuad(

		static_cast<int>(1050 - go->player.HPGH.Width / 2.0f),
		static_cast<int>(50 - go->player.HPGH.Height / 2.0f),

		static_cast<int>(1050 + go->player.HPGH.Width / 2.0f),
		static_cast<int>(50 - go->player.HPGH.Height / 2.0f),

		static_cast<int>(1050 - go->player.HPGH.Width / 2.0f),
		static_cast<int>(50 + go->player.HPGH.Height / 2.0f),

		static_cast<int>(1050 + go->player.HPGH.Width / 2.0f),
		static_cast<int>(50 + go->player.HPGH.Height / 2.0f),

		static_cast<int>(go->player.HPGH.ImagePos.x),
		static_cast<int>(go->player.HPGH.ImagePos.y),

		300, 300,

		go->player.HPGH.Image,

		WHITE
	);

	Novice::DrawQuad(
		static_cast<int>(1100 - go->player.RemainingLifeGH.Width / 2.0f),
		static_cast<int>(50 - go->player.RemainingLifeGH.Height / 2.0f),

		static_cast<int>(1100 + go->player.RemainingLifeGH.Width / 2.0f),
		static_cast<int>(50 - go->player.RemainingLifeGH.Height / 2.0f),

		static_cast<int>(1100 - go->player.RemainingLifeGH.Width / 2.0f),
		static_cast<int>(50 + go->player.RemainingLifeGH.Height / 2.0f),

		static_cast<int>(1100 + go->player.RemainingLifeGH.Width / 2.0f),
		static_cast<int>(50 + go->player.RemainingLifeGH.Height / 2.0f),

		static_cast<int>(go->player.RemainingLifeGH.ImagePos.x),
		static_cast<int>(go->player.RemainingLifeGH.ImagePos.y),

		500, 300,

		go->player.RemainingLifeGH.Image,

		WHITE

	);


}

void FlickrDraw(GameObject* go) {

	if (go->player.flickr.IsShot) {
		go->player.flickr.RectObjDraw();
	}
}