
//ソースファイルの読み込み
#include<math.h>

//ヘッダーファイルの読み込み
#include"enemy.h"
#include"easing.h"
#include"structuer.h"
#include"enum.h"
#include"common.h"
#include"camera.h"
#include"sceneChange.h"


//初期化関数
void EnemyInitialize(GameObject* go) {

	//顔
	go->enemy.BaseInfoInitialize(

		//初期座標(x,y)
		WorldWidth / 2.0f,
		WorldHeight / 2.0f,

		//横幅、縦幅
		160.0f,
		160.0f,

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
		Novice::LoadTexture("./image./boss_ver2.png"),

		//画像の幅
		160.0f,
		160.0f,

		//色
		0xffff00ff,

		//オブジェクトタイプ（可動or不可動）
		ImMovable
	);

	go->enemy.Condition = BothHands;
	go->enemy.MoveType = None;
	go->enemy.DaiPanInfo.CurrentFrame = 0;
	go->enemy.RocketPunchInfo.CurrentFrame = 0;
	go->enemy.BulletShotCurrentFrame = 0;
	go->enemy.IsAlive = true;
	go->enemy.ShotCount = 0;
	go->enemy.ShotNumLimit = 2;

	go->enemy.LapNum = 0;

	//手
	go->enemy.hand[Right].BaseInfoInitialize(
		//初期座標(x,y)
		go->enemy.WorldPos.x -100.0f,
		go->enemy.WorldPos.y,

		//横幅、縦幅
		80.0f,
		80.0f,

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
		Novice::LoadTexture("./image./RightHand_ver3.png"),

		//画像の幅
		800.0f,
		800.0f,

		//色
		0xffff00ff,

		//オブジェクトタイプ（可動or不可動）
		ImMovable
	);

	//左手
	go->enemy.hand[Left].BaseInfoInitialize(
		//初期座標(x,y)
		go->enemy.WorldPos.x + 100.0f,
		go->enemy.WorldPos.y,

		//横幅、縦幅
		80.0f,
		80.0f,

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
		Novice::LoadTexture("./image./LeftHand_ver3.png"),

		//画像の幅
		800.0f,
		800.0f,

		//色
		0xffff00ff,

		//オブジェクトタイプ（可動or不可動）
		ImMovable
	);

	for (int i = 0; i < 2; ++i) {
		go->enemy.hand[i].EasingStartPos = {};
		go->enemy.hand[i].IsDown = false;

		go->enemy.hand[i].DownTime = HandDownTime;
	}

	go->enemy.hand[Right].IsAlive = true;
	go->enemy.hand[Left].IsAlive = true;
	

	//各攻撃の初期化
	
	go->enemy.DaiPanInfo.BaseInfoInitialize(

		//初期座標(x,y)
		1300.0f,
		360.0f,

		//横幅、縦幅
		80.0f,
		80.0f,

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
		0,

		//画像の幅
		0.0f,
		0.0f,

		//色
		WHITE,

		//オブジェクトタイプ（可動or不可動）
		ImMovable
	);


	//弾の初期化
	for (int i = 0; i < EnemyBulletNum; ++i) {
		go->enemy.RightBullet[i].BaseInfoInitialize(
			//初期座標(x,y)
			0.0f,
			0.0f,

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
			3.0f,

			//画像
			Novice::LoadTexture("./image./bullet_ver2.png"),

			//画像の幅
			320.0f,
			320.0f,

			//色
			0x9932ccff,

			//オブジェクトタイプ（可動or不可動）
			Movable
		);
		
		go->enemy.RightBullet[i].IsShot = false;
		go->enemy.RightBullet[i].IsShot_p = false;
		go->enemy.RightBullet[i].IsAggression = true;
		go->enemy.RightBullet[i].IsAttracted = false;
		go->enemy.RightBullet[i].IsHeld = false;
	}

	for (int i = 0; i < EnemyBulletNum; ++i) {
		go->enemy.LeftBullet[i].BaseInfoInitialize(
			//初期座標(x,y)
			0.0f,
			0.0f,

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
			3.0f,

			//画像
			Novice::LoadTexture("./image./bullet_ver2.png"),

			//画像の幅
			320.0f,
			320.0f,

			//色
			0x88ddffff,

			//オブジェクトタイプ（可動or不可動）
			Movable
		);

		go->enemy.LeftBullet[i].IsShot = false;
		go->enemy.LeftBullet[i].IsShot_p = false;
		go->enemy.LeftBullet[i].IsAggression = true;
		go->enemy.LeftBullet[i].IsAttracted = false;
		go->enemy.LeftBullet[i].IsHeld = false;
	}

	//発射間隔
	go->enemy.ShotIntervalTime = 30;
}



//行動パターンを決める関数
void DecisionMoveType_Ver1(GameObject* go) {

	go->enemy.MoveType = rand() % 3 + 1;

}

/*=================================
		　 攻撃パターン
 =================================*/
 //台パン
void Daipan(GameObject* go,float WholeFrame,float TransrateFrame,float OccurrenceFrame,float LastingFlame,Sounds* sounds) {


	//この関数が呼び出されたときに一度だけイージングに関する初期化を行う
	if (go->enemy.DaiPanInfo.CurrentFrame == 0) {
		for (int i = 0; i < 2; ++i) {
			EasingInitialize(&go->enemy.hand[i].t, &go->enemy.hand[i].NowFrame, &go->enemy.hand[i].EasingStartPos, &go->enemy.hand[i].WorldPos);
		}
		EasingInitialize(&go->enemy.t, &go->enemy.NowFrame, &go->enemy.EasingStartPos, &go->enemy.WorldPos);
	}

	//現在フレームを毎フレーム１ずつ増やす
	++go->enemy.DaiPanInfo.CurrentFrame;

	//移動処理
	if (go->enemy.DaiPanInfo.CurrentFrame > 0 && go->enemy.DaiPanInfo.CurrentFrame <= TransrateFrame) {

		if (go->enemy.Condition == BothHands) {

			for (int i = 0; i < 2; ++i) {

				Easing(
					&go->enemy.hand[i].WorldPos,

					//イージングスタート座標
					go->enemy.hand[i].EasingStartPos.x,
					go->enemy.hand[i].EasingStartPos.y,

					//イージング終了座標
					go->player.WorldPos.x - 40.0f + 80.0f * i,
					go->player.WorldPos.y + 80.0f, 

					//現在フレーム
					&go->enemy.hand[i].NowFrame,

					//移動の全体フレーム
					TransrateFrame,

					//ｔ
					&go->enemy.hand[i].t,

					//勢い
					1.0f,

					//イージングの種類
					materialInOutQuart
				);

			}
		}
		else if (go->enemy.Condition == OneHand) {

			for (int i = 0; i < 2; ++i) {
				if (go->enemy.hand[i].IsAlive && !go->enemy.hand[i].IsDown) {


					Easing(
						&go->enemy.hand[i].WorldPos,

						//イージングスタート座標
						go->enemy.hand[i].EasingStartPos.x,
						go->enemy.hand[i].EasingStartPos.y,

						//イージング終了座標
						go->player.WorldPos.x,
						go->player.WorldPos.y + 80.0f,

						//現在フレーム
						&go->enemy.hand[i].NowFrame,

						//移動の全体フレーム
						TransrateFrame,

						//ｔ
						&go->enemy.hand[i].t,

						//勢い
						1.0f,

						//イージングの種類
						materialInOutQuart
					);
				}
			}
		}

		//頭のイージング処理
		Easing(
			&go->enemy.WorldPos,

			//イージングスタート座標
			go->enemy.EasingStartPos.x,
			go->enemy.EasingStartPos.y,

			//イージング終了座標
			go->player.WorldPos.x,
			go->enemy.hand[Right].WorldPos.y + 60.0f,

			//現在フレーム
			&go->enemy.NowFrame,

			//移動の全体フレーム
			TransrateFrame,

			//ｔ
			&go->enemy.t,

			//勢い
			1.0f,

			//イージングの種類
			materialInOutQuart
		);

	}

	//攻撃予備動作
	if (go->enemy.DaiPanInfo.CurrentFrame > TransrateFrame && go->enemy.DaiPanInfo.CurrentFrame < OccurrenceFrame) {

		//シェイク用の数値を取得
		for (int i = 0; i < 2; ++i) {
			go->enemy.hand[i].ShakePos.x = static_cast<float>(rand() % 8 - 4);
			go->enemy.hand[i].ShakePos.y = static_cast<float>(rand() % 8 - 4);
		}
	}
	else {
		for (int i = 0; i < 2; ++i) {
			go->enemy.hand[i].ShakePos.x = 0.0f;
			go->enemy.hand[i].ShakePos.y = 0.0f;
		}
	}
	
	//攻撃動作
	if (go->enemy.DaiPanInfo.CurrentFrame == OccurrenceFrame) {
		for (int i = 0; i < 2; ++i) {
			EasingInitialize(&go->enemy.hand[i].t, &go->enemy.hand[i].NowFrame, &go->enemy.hand[i].EasingStartPos, &go->enemy.hand[i].WorldPos);
		}
	}


	if (go->enemy.DaiPanInfo.CurrentFrame >= OccurrenceFrame && go->enemy.DaiPanInfo.CurrentFrame < OccurrenceFrame + 30.0f) {

		if (go->enemy.Condition == BothHands) {

			for (int i = 0; i < 2; ++i) {

				//攻撃判定を付ける
				go->enemy.hand[i].IsAggression = true;


				if (!sounds->isPlayPressSE)
				{
					SoundPlaySE(sounds->handPressPlayHandle, sounds->handPressSoundHandle, sounds->volume);
					sounds->isPlayPressSE = true;
				}

				//モーション
				Easing(
					&go->enemy.hand[i].WorldPos,

					//イージングスタート座標
					go->enemy.hand[i].EasingStartPos.x,
					go->enemy.hand[i].EasingStartPos.y,

					//イージング終了座標
					go->enemy.hand[i].EasingStartPos.x,
					go->player.WorldPos.y,

					//現在フレーム
					&go->enemy.hand[i].NowFrame,

					//移動の全体フレーム
					30,

					//ｔ
					&go->enemy.hand[i].t,

					//勢い
					1.0f,

					//イージングの種類
					materialInBack
				);
			}
		}
		else if (go->enemy.Condition == OneHand) {

			for (int i = 0; i < 2; ++i) {

				if (go->enemy.hand[i].IsAlive && !go->enemy.hand[i].IsDown) {

					//攻撃判定を付ける
					go->enemy.hand[i].IsAggression = true;



					//モーション
					Easing(
						&go->enemy.hand[i].WorldPos,

						//イージングスタート座標
						go->enemy.hand[i].EasingStartPos.x,
						go->enemy.hand[i].EasingStartPos.y,

						//イージング終了座標
						go->enemy.hand[i].EasingStartPos.x,
						go->player.WorldPos.y,

						//現在フレーム
						&go->enemy.hand[i].NowFrame,

						//移動の全体フレーム
						30,

						//ｔ
						&go->enemy.hand[i].t,

						//勢い
						1.0f,

						//イージングの種類
						materialInOutQuart
					);
				}
			}
		}
	}
	else {
		//攻撃判定をとる
		for (int i = 0; i < 2; ++i) {
			go->enemy.hand[i].IsAggression = false;
			sounds->isPlayPressSE=false;
		}
	}

	//攻撃後の移動
	if (go->enemy.DaiPanInfo.CurrentFrame == OccurrenceFrame + 30.0f) {
		for (int i = 0; i < 2; ++i) {
			EasingInitialize(&go->enemy.hand[i].t, &go->enemy.hand[i].NowFrame, &go->enemy.hand[i].EasingStartPos, &go->enemy.hand[i].WorldPos);
		}
	}

	else if (go->enemy.DaiPanInfo.CurrentFrame >= OccurrenceFrame + 30.0f && go->enemy.DaiPanInfo.CurrentFrame < WholeFrame) {

		if (go->enemy.Condition == BothHands) {

			for (int i = 0; i < 2; ++i) {

				Easing(
					&go->enemy.hand[i].WorldPos,

					//イージングスタート座標
					go->enemy.hand[i].EasingStartPos.x,
					go->enemy.hand[i].EasingStartPos.y,

					//イージング終了座標
					go->enemy.hand[i].FixedPosition.x,
					go->enemy.hand[i].FixedPosition.y,

					//現在フレーム
					&go->enemy.hand[i].NowFrame,

					//移動の全体フレーム
					((WholeFrame)-(OccurrenceFrame + 30.0f)),

					//ｔ
					&go->enemy.hand[i].t,

					//勢い
					1.0f,

					//イージングの種類
					materialInOutQuart
				);

			}
		}
		else if (go->enemy.Condition == OneHand) {

			for (int i = 0; i < 2; ++i) {
				if (go->enemy.hand[i].IsAlive && !go->enemy.hand[i].IsDown) {


					Easing(
						&go->enemy.hand[i].WorldPos,

						//イージングスタート座標
						go->enemy.hand[i].EasingStartPos.x/* - 100.0f + 200.0f * i*/,
						go->enemy.hand[i].EasingStartPos.y,

						//イージング終了座標
						go->enemy.hand[i].FixedPosition.x,
						go->enemy.hand[i].FixedPosition.y,

						//現在フレーム
						&go->enemy.hand[i].NowFrame,

						//移動の全体フレーム
						((WholeFrame)-(OccurrenceFrame + 30.0f)),

						//ｔ
						&go->enemy.hand[i].t,

						//勢い
						1.0f,

						//イージングの種類
						materialInOutQuart
					);
				}
			}
			LastingFlame;
		}
	}

	//行動終了
	if (go->enemy.DaiPanInfo.CurrentFrame == WholeFrame) {
		go->enemy.MoveType = None;
		go->enemy.DaiPanInfo.CurrentFrame = 0;
	}

	//頭の動き
	//if(go->enemy.DaiPanInfo.CurrentFrame > 0 && go->enemy.DaiPanInfo.CurrentFrame < OccurrenceFrame)
	//go->enemy.WorldPos.x = (go->enemy.hand[Right].WorldPos.x + go->enemy.hand[Left].WorldPos.x) / 2.0f;
	//go->enemy.WorldPos.y = (go->enemy.hand[Right].WorldPos.y + go->enemy.hand[Left].WorldPos.y) / 2.0f + 80.0f;
}


//ロケットパンチ
void LocketPunch(GameObject* go, float WholeFrame, float TransrateFrame, float OccurrenceFrame, float LastingFlame,Sounds* sounds) {

	//この関数が呼び出されたときに一度だけイージングに関する初期化を行う
	if (go->enemy.RocketPunchInfo.CurrentFrame == 0) {
		for (int i = 0; i < 2; ++i) {
			EasingInitialize(&go->enemy.hand[i].t, &go->enemy.hand[i].NowFrame, &go->enemy.hand[i].EasingStartPos, &go->enemy.hand[i].WorldPos);
		}
		EasingInitialize(&go->enemy.t, &go->enemy.NowFrame, &go->enemy.EasingStartPos, &go->enemy.WorldPos);
	}

	//現在フレームを毎フレーム１ずつ増やす
	++go->enemy.RocketPunchInfo.CurrentFrame;

	//移動処理
	if (go->enemy.RocketPunchInfo.CurrentFrame > 0 && go->enemy.RocketPunchInfo.CurrentFrame <= TransrateFrame) {

		if (go->enemy.Condition == BothHands) {

			for (int i = 0; i < 2; ++i) {

				Easing(
					&go->enemy.hand[i].WorldPos,

					//イージングスタート座標
					go->enemy.hand[i].EasingStartPos.x,
					go->enemy.hand[i].EasingStartPos.y,

					//イージング終了座標
					go->player.WorldPos.x - 200.0f + 400.0f * i,
					go->player.WorldPos.y + 300.0f,

					//現在フレーム
					&go->enemy.hand[i].NowFrame,

					//移動の全体フレーム
					TransrateFrame,

					//ｔ
					&go->enemy.hand[i].t,

					//勢い
					2.0f,

					//イージングの種類
					materialInOutCubic
				);
			}
		}
		else if (go->enemy.Condition == OneHand) {

			for (int i = 0; i < 2; ++i) {
				if (go->enemy.hand[i].IsAlive && !go->enemy.hand[i].IsDown) {


					Easing(
						&go->enemy.hand[i].WorldPos,

						//イージングスタート座標
						go->enemy.hand[i].EasingStartPos.x,
						go->enemy.hand[i].EasingStartPos.y,

						//イージング終了座標
						go->player.WorldPos.x,
						go->player.WorldPos.y + 200.0f,

						//現在フレーム
						&go->enemy.hand[i].NowFrame,

						//移動の全体フレーム
						TransrateFrame,

						//ｔ
						&go->enemy.hand[i].t,

						//勢い
						2.0f,

						//イージングの種類
						materialInOutQuart
					);
				}
			}
		}



		//頭のイージング処理
		Easing(
			&go->enemy.WorldPos,

			//イージングスタート座標
			go->enemy.EasingStartPos.x,
			go->enemy.EasingStartPos.y,

			//イージング終了座標
			go->player.WorldPos.x,
			go->enemy.hand[Right].WorldPos.y + 60.0f,

			//現在フレーム
			&go->enemy.NowFrame,

			//移動の全体フレーム
			TransrateFrame,

			//ｔ
			&go->enemy.t,

			//勢い
			1.0f,

			//イージングの種類
			materialInOutQuart
		);


	}

	//攻撃予備動作
	if (go->enemy.RocketPunchInfo.CurrentFrame > TransrateFrame && go->enemy.RocketPunchInfo.CurrentFrame < OccurrenceFrame) {

		//ベクトルの取得

		for (int i = 0; i < 2; ++i) {

			go->enemy.hand[i].Vector.x = (go->player.WorldPos.x - go->enemy.hand[i].WorldPos.x);
			go->enemy.hand[i].Vector.y = (go->player.WorldPos.y - go->enemy.hand[i].WorldPos.y);

			//go->enemy.hand[i].Vector.x=(go->player.WorldPos.x - )

		}

	}

	//攻撃動作
	if (go->enemy.RocketPunchInfo.CurrentFrame >= OccurrenceFrame && go->enemy.RocketPunchInfo.CurrentFrame < OccurrenceFrame + 30.0f) {

		if (go->enemy.Condition == BothHands) {
			for (int i = 0; i < 2; ++i) {

				//攻撃判定を付ける
				go->enemy.hand[i].IsAggression = true;

				//発射時に音をならす
				if (!sounds->isPlayHandSE)
				{
					SoundPlaySE(sounds->handAttackPlayHandle, sounds->handAttackSoundHandle, sounds->volume);
					sounds->isPlayHandSE = true;
				}


				

				//移動処理
				go->enemy.hand[i].WorldPos.x += NormalizeX(go->enemy.hand[i].Vector.x, go->enemy.hand[i].Vector.y) * 20;
				go->enemy.hand[i].WorldPos.y += NormalizeY(go->enemy.hand[i].Vector.y, go->enemy.hand[i].Vector.y) * 20;
			}
		}
		else if (go->enemy.Condition == OneHand) {

			for (int i = 0; i < 2; ++i) {
				if (go->enemy.hand[i].IsAlive && !go->enemy.hand[i].IsDown) {

					//攻撃判定を付ける
					go->enemy.hand[i].IsAggression = true;

					//移動処理
					go->enemy.hand[i].WorldPos.x += NormalizeX(go->enemy.hand[i].Vector.x, go->enemy.hand[i].Vector.y) * 20;
					go->enemy.hand[i].WorldPos.y += NormalizeY(go->enemy.hand[i].Vector.y, go->enemy.hand[i].Vector.y) * 20;

				}
			}
		}
	}
	else {
		for (int i = 0; i < 2; ++i) {

			//攻撃判定をとる
			go->enemy.hand[i].IsAggression = false;
			sounds->isPlayHandSE = false;
		}
	}

	//攻撃後の移動
	if (go->enemy.RocketPunchInfo.CurrentFrame == OccurrenceFrame + 30.0f) {
		for (int i = 0; i < 2; ++i) {
			EasingInitialize(&go->enemy.hand[i].t, &go->enemy.hand[i].NowFrame, &go->enemy.hand[i].EasingStartPos, &go->enemy.hand[i].WorldPos);
		}
	}
	else if (go->enemy.RocketPunchInfo.CurrentFrame >= OccurrenceFrame + 30.0f && go->enemy.RocketPunchInfo.CurrentFrame < WholeFrame) {

		if (go->enemy.Condition == BothHands) {

			for (int i = 0; i < 2; ++i) {

				Easing(
					&go->enemy.hand[i].WorldPos,

					//イージングスタート座標
					go->enemy.hand[i].EasingStartPos.x,
					go->enemy.hand[i].EasingStartPos.y,

					//イージング終了座標
					go->enemy.hand[i].FixedPosition.x,
					go->enemy.hand[i].FixedPosition.y,

					//現在フレーム
					& go->enemy.hand[i].NowFrame,

					//移動の全体フレーム
					((WholeFrame)-(OccurrenceFrame + 30.0f)),

					//ｔ
					&go->enemy.hand[i].t,

					//勢い
					1.0f,

					//イージングの種類
					materialInOutQuart
				);

			}
		}
		else if (go->enemy.Condition == OneHand) {

			for (int i = 0; i < 2; ++i) {
				if (go->enemy.hand[i].IsAlive && !go->enemy.hand[i].IsDown) {


					Easing(
						&go->enemy.hand[i].WorldPos,

						//イージングスタート座標
						go->enemy.hand[i].EasingStartPos.x/* - 100.0f + 200.0f * i*/,
						go->enemy.hand[i].EasingStartPos.y,

						//イージング終了座標
						go->enemy.hand[i].FixedPosition.x,
						go->enemy.hand[i].FixedPosition.y,

						//現在フレーム
						&go->enemy.hand[i].NowFrame,

						//移動の全体フレーム
					((WholeFrame)-(OccurrenceFrame + 30.0f)),

						//ｔ
						&go->enemy.hand[i].t,

						//勢い
						1.0f,

						//イージングの種類
						materialInOutQuart
					);
				}
			}
		}
	}
	//行動終了
	if (go->enemy.RocketPunchInfo.CurrentFrame == WholeFrame) {
		go->enemy.MoveType = None;
		go->enemy.RocketPunchInfo.CurrentFrame = 0;
	}
	LastingFlame;

	//go->enemy.WorldPos.x = (go->enemy.hand[Right].WorldPos.x + go->enemy.hand[Left].WorldPos.x) / 2.0f;
	//go->enemy.WorldPos.y = (go->enemy.hand[Right].WorldPos.y + go->enemy.hand[Left].WorldPos.y) / 2.0f + 200.0f;

}


//弾打ち攻撃
void BulletShot(GameObject* go, float WholeFrame, float TransrateFrame, float OccurrenceFrame, Vector2 FixedPos,Sounds* sounds) {

	//この関数が呼び出されたときに一度だけイージングに関する初期化を行う
	if (go->enemy.BulletShotCurrentFrame == 0) {
		//頭
		EasingInitialize(&go->enemy.t, &go->enemy.NowFrame, &go->enemy.EasingStartPos, &go->enemy.WorldPos);

		//手
		for (int i = 0; i < 2; ++i) {
			EasingInitialize(&go->enemy.hand[i].t, &go->enemy.hand[i].NowFrame, &go->enemy.hand[i].EasingStartPos, &go->enemy.hand[i].WorldPos);
		}
	}

	//現在フレームを毎フレーム１ずつ増やす
	++go->enemy.BulletShotCurrentFrame;

	//移動処理
	if (go->enemy.BulletShotCurrentFrame > 0 && go->enemy.BulletShotCurrentFrame <= TransrateFrame) {

		//固定位置に移動(引数で指定可能)
		Easing(
			&go->enemy.WorldPos,

			//イージングスタート座標
			go->enemy.EasingStartPos.x,
			go->enemy.EasingStartPos.y,

			//イージング終了座標
			FixedPos.x,
			FixedPos.y,

			//現在フレーム
			&go->enemy.NowFrame,

			//移動の全体フレーム
			TransrateFrame,

			//ｔ
			&go->enemy.t,

			//勢い
			1.0f,

			//イージングの種類
			materialInOutQuart
		);


		for (int i = 0; i < 2; ++i) {
			Easing(
				&go->enemy.hand[i].WorldPos,

				//イージングスタート座標
				go->enemy.hand[i].EasingStartPos.x,
				go->enemy.hand[i].EasingStartPos.y,

				//イージング終了座標
				go->enemy.hand[i].FixedPosition.x,
				go->enemy.hand[i].FixedPosition.y,

				//現在フレーム
				&go->enemy.hand[i].NowFrame,

				//移動の全体フレーム
				TransrateFrame,

				//ｔ
				&go->enemy.hand[i].t,

				//勢い
				1.0f,

				//イージングの種類
				materialInOutCubic
			);
		}
	}



	//予備動作
	if (go->enemy.BulletShotCurrentFrame > TransrateFrame && go->enemy.BulletShotCurrentFrame < OccurrenceFrame) {
	}

	//攻撃動作
	if (go->enemy.BulletShotCurrentFrame == OccurrenceFrame) {
		for (int i = 0; i < 2; ++i) {
			EasingInitialize(&go->enemy.hand[i].t, &go->enemy.hand[i].NowFrame, &go->enemy.hand[i].EasingStartPos, &go->enemy.hand[i].WorldPos);
		}

		if (!sounds->isPlayShotSE)
		{
			SoundPlaySE(sounds->flickrChargePlayHandle, sounds->flickrChargeSoundHandle, sounds->volume);
			sounds->isPlayShotSE = true;
		}

	}

	if (go->enemy.BulletShotCurrentFrame > TransrateFrame && go->enemy.BulletShotCurrentFrame < WholeFrame) {

		go->enemy.ShotIntervalTime--;

		if (go->enemy.ShotCount < go->enemy.ShotNumLimit) {

			if (go->enemy.ShotIntervalTime <= 0) {

				for (int i = 0; i < EnemyBulletNum; ++i) {

					//右手
					if (go->enemy.hand[Right].IsAlive && !go->enemy.hand[Right].IsDown) {
						if (!go->enemy.RightBullet[i].IsShot && !go->enemy.RightBullet[i].IsHeld && !go->enemy.RightBullet[i].IsShot_p) {

							//座標を設定
							go->enemy.RightBullet[i].WorldPos = go->enemy.hand[Right].WorldPos;

							//プレイヤーが発射した状態をリセットする
							go->enemy.RightBullet[i].IsShot_p = false;

							//ベクトルを求める
							FindVectorX(go->player.WorldPos, go->enemy.RightBullet[i].WorldPos);
							FindVectorY(go->player.WorldPos, go->enemy.RightBullet[i].WorldPos);

							//フラグを立てる
							go->enemy.RightBullet[i].IsShot = true;

							break;
						}
					}
				}


				//左手

				if (go->enemy.hand[Left].IsAlive && !go->enemy.hand[Left].IsDown) {

					for (int i = 0; i < EnemyBulletNum; ++i) {

						if (!go->enemy.LeftBullet[i].IsShot && !go->enemy.RightBullet[i].IsHeld && !go->enemy.LeftBullet[i].IsShot_p) {

							//座標を設定
							go->enemy.LeftBullet[i].WorldPos = go->enemy.hand[Left].WorldPos;

							//プレイヤーが発射した状態をリセットする
							go->enemy.LeftBullet[i].IsShot_p = false;

							//ベクトルを求める
							go->enemy.LeftBullet[i].Vector.x = FindVectorX(go->player.WorldPos, go->enemy.LeftBullet[i].WorldPos);
							go->enemy.LeftBullet[i].Vector.y = FindVectorY(go->player.WorldPos, go->enemy.LeftBullet[i].WorldPos);

							//フラグを立てる
							go->enemy.LeftBullet[i].IsShot = true;

							break;
						}
					}
				}

				
				go->enemy.ShotIntervalTime = 45;
				go->enemy.ShotCount++;
			}
		}
	}

	//行動終了
	if (go->enemy.BulletShotCurrentFrame == WholeFrame) {
		go->enemy.MoveType = None;
		go->enemy.BulletShotCurrentFrame = 0;
		go->enemy.ShotCount = 0;

		for (int i = 0; i < EnemyBulletNum; ++i) {
			go->enemy.RightBullet[i].IsShot = false;
			go->enemy.LeftBullet[i].IsShot = false;
		}

		sounds->isPlayShotSE = false;
	}

}

void BulletMove(GameObject *go,int VectorUpdateFlame){

	//弾の挙動
	for (int i = 0; i < EnemyBulletNum; ++i) {


		//右

		//引き付けられていないとき
		if (!go->enemy.RightBullet[i].IsAttracted) {

			if (go->enemy.RightBullet[i].IsShot) {

				//まいたけまいたけ
				go->enemy.hand[i].Degree++;

				DegreeToTheta(&go->enemy.hand[i]);


				//ベクトルの更新
				if (go->enemy.FlameCount % (VectorUpdateFlame) == 0) {
					go->enemy.RightBullet[i].Vector.x = FindVectorX(go->player.WorldPos, go->enemy.RightBullet[i].WorldPos);
				}

				if (go->enemy.FlameCount % (VectorUpdateFlame) == 0) {
					go->enemy.RightBullet[i].Vector.y = FindVectorY(go->player.WorldPos, go->enemy.RightBullet[i].WorldPos);

				}


				//弾を動かす
				go->enemy.RightBullet[i].WorldPos.x += NormalizeX(go->enemy.RightBullet[i].Vector.x, go->enemy.RightBullet[i].Vector.y) * go->enemy.RightBullet[i].Speed;
				go->enemy.RightBullet[i].WorldPos.y += NormalizeY(go->enemy.RightBullet[i].Vector.x, go->enemy.RightBullet[i].Vector.y) * go->enemy.RightBullet[i].Speed;

			}
		}


		//左

		//引き付けられていないとき
		if (!go->enemy.LeftBullet[i].IsAttracted) {

			if (go->enemy.LeftBullet[i].IsShot) {

				//ベクトルの更新
				if (go->enemy.FlameCount % (VectorUpdateFlame) == 0) {
					go->enemy.LeftBullet[i].Vector.x = FindVectorX(go->player.WorldPos, go->enemy.LeftBullet[i].WorldPos);
				}

				if (go->enemy.FlameCount % (VectorUpdateFlame) == 0) {
					go->enemy.LeftBullet[i].Vector.y = FindVectorY(go->player.WorldPos, go->enemy.LeftBullet[i].WorldPos);

				}


				//弾を動かす
				go->enemy.LeftBullet[i].WorldPos.x += NormalizeX(go->enemy.LeftBullet[i].Vector.x, go->enemy.LeftBullet[i].Vector.y) * go->enemy.LeftBullet[i].Speed;
				go->enemy.LeftBullet[i].WorldPos.y += NormalizeY(go->enemy.LeftBullet[i].Vector.x, go->enemy.LeftBullet[i].Vector.y) * go->enemy.LeftBullet[i].Speed;
			}
		}
	}


	//頭の動き
	//if(go->enemy.DaiPanInfo.CurrentFrame > 0 && go->enemy.DaiPanInfo.CurrentFrame < OccurrenceFrame)
	//go->enemy.WorldPos.x = (go->enemy.hand[Right].WorldPos.x + go->enemy.hand[Left].WorldPos.x) / 2.0f;
	//go->enemy.WorldPos.y = (go->enemy.hand[Right].WorldPos.y + go->enemy.hand[Left].WorldPos.y) / 2.0f + 80.0f;
}


//画像の角度を変更する関数
void DegreeUpdate(GameObject* go) {

	//ダウンしていないとき

	//ロケットパンチと弾打ちの時、プレイヤーの方をむけよこのやろう
	if (go->enemy.MoveType == locketpunch || go->enemy.MoveType == bulletshot) {

		//ベクトルの取得
		for (int i = 0; i < 2; ++i) {

			if (!go->enemy.hand[i].IsDown) {

				go->enemy.hand[i].Vector.x = FindVectorX(go->player.WorldPos, go->enemy.hand[i].WorldPos);
				go->enemy.hand[i].Vector.y = FindVectorY(go->player.WorldPos, go->enemy.hand[i].WorldPos);
			}
		}

		for (int i = 0; i < 2; ++i) {

			if (!go->enemy.hand[i].IsDown) {


				//角度を取得
				go->enemy.hand[i].Theta = static_cast<float> (-atan2(
					static_cast<double>(go->enemy.hand[i].Vector.x),
					static_cast<double>(go->enemy.hand[i].Vector.y)
				));

			}

		}
	}
	else {
		for (int i = 0; i < 2; ++i) {
			go->enemy.hand[i].Theta = 0.0f;
		}
	}
}


//更新処理
void EnemyUpdate(GameObject* go,CameraRelated* cr,Sounds* sounds) {
	
	//フレームカウント
	go->enemy.FlameCount++;

	//手の固定位置の更新
	for (int i = 0; i < 2; ++i) {
		go->enemy.hand[i].FixedPosition.x = go->enemy.WorldPos.x - 100.0f + 200.0f * i;
		go->enemy.hand[i].FixedPosition.y = go->enemy.WorldPos.y;
	}

	//周回数の更新
	if (go->enemy.LapNum == 0) {


		if (!go->enemy.IsAlive) {

			go->enemy.IsAlive = true;
			for (int i = 0; i < 2; i++) {
				go->enemy.hand[i].IsAlive = true;
				go->enemy.hand[i].IsDown = false;
			}
			go->enemy.LapNum = 1;

		}
	}

	//弾の上限数の更新
	if (go->enemy.LapNum == 0) {
		go->enemy.ShotNumLimit = 2;
	}
	else if (go->enemy.LapNum == 1) {
		go->enemy.ShotNumLimit = 4;
	}

	//状態判別（IsAlive）
	if (go->enemy.hand[Right].IsAlive && go->enemy.hand[Left].IsAlive) {

			go->enemy.Condition = BothHands;
	}
	else if (go->enemy.hand[Right].IsAlive || go->enemy.hand[Left].IsAlive) {
		
			go->enemy.Condition = OneHand;
	}
	else {

		go->enemy.Condition = HeadOnly;
	}

	//状態判別(IsDown)
	if (go->enemy.Condition == BothHands) {

		//どちらかがダウン状態なら状態を「OneHand」にする
		if (go->enemy.hand[Right].IsDown || go->enemy.hand[Left].IsDown) {
			go->enemy.Condition = OneHand;
		}
	}


	//ダウン状態からの回復
	for (int i = 0; i < 2; ++i) {

		if (go->enemy.hand[i].IsDown) {

			//ダウン時間を減らす
			go->enemy.hand[i].DownTime--;

			//時間が０以下になったらダウン状態から回復
			if (go->enemy.hand[i].DownTime <= 0) {
				
				//ダウンタイムの初期化
				go->enemy.hand[i].DownTime = HandDownTime;

				//ダウン状態から復帰
				go->enemy.hand[i].IsDown = false;
			}
		}
	}


	//行動パターンの決定関数
	if (go->enemy.MoveType == None) {
		DecisionMoveType_Ver1(go);
	}
	else if (go->enemy.MoveType == daipan) {
		Daipan(go, DaiPanWholeFrame, 150.0f, 200.0f, 5.0f,sounds);
	}
	else if (go->enemy.MoveType == locketpunch) {

		LocketPunch(go, LocketPunchWholeFrame, 90.0f, 200.0f, 5.0f, sounds);

		
	}
	else if (go->enemy.MoveType == bulletshot) {
		BulletShot(go, BulletShotWholeFrame, 90.0f, 100.0f, { WorldWidth / 2.0f ,WorldHeight / 2.0 },sounds);
	}

	//基本情報の更新
	//頭
	SetFourVertexes(&go->enemy);
	RenderingPipeline(&go->enemy, cr);

	//手
	for (int i = 0; i < 2; ++i) {
		SetFourVertexes(&go->enemy.hand[i]);
		RenderingPipeline(&go->enemy.hand[i], cr);
	}

	//弾
	BulletMove(go, 15);

	for (int i = 0; i < EnemyBulletNum; ++i) {
		SetFourVertexes(&go->enemy.RightBullet[i]);
		RenderingPipeline(&go->enemy.RightBullet[i], cr);

		SetFourVertexes(&go->enemy.LeftBullet[i] );
		RenderingPipeline(&go->enemy.LeftBullet[i], cr);
	}

	//画像の描画範囲の変更
	for (int i = 0; i < 2; ++i) {
		if (!go->enemy.hand[i].IsDown) {
			go->enemy.hand[i].ImagePos.x = 800.0f * go->enemy.MoveType;

			go->enemy.hand[i].Color = 0xffff00ff;
		}
		else {
			go->enemy.hand[i].ImagePos.x = 0.0f;

			go->enemy.hand[i].Color = 0x882222ff;

		}
	}

	//回転処理
	DegreeUpdate(go);
}


//描画関数
void EnemyDraw(GameObject* go) {
	go->enemy.RectObjDraw();
	for (int i = 0; i < 2; i++) {

		if (go->enemy.hand[i].IsAlive) {

			go->enemy.hand[i].RectObjDraw();
		}
	}

	for (int i = 0; i < EnemyBulletNum; ++i) {

		if (go->enemy.RightBullet[i].IsShot || go->enemy.RightBullet[i].IsAttracted || go->enemy.RightBullet[i].IsHeld || go->enemy.RightBullet[i].IsShot_p) {
			go->enemy.RightBullet[i].RectObjDraw();
		}

		if (go->enemy.LeftBullet[i].IsShot || go->enemy.LeftBullet[i].IsAttracted || go->enemy.LeftBullet[i].IsHeld || go->enemy.LeftBullet[i].IsShot_p) {
			go->enemy.LeftBullet[i].RectObjDraw();
		}
	}

}

//デバッグ表示関数
void EnemyDebugPrintf(GameObject* go) {

	Novice::ScreenPrintf(0, 0, "IsShot : %d", go->enemy.LeftBullet[0].IsShot);
	Novice::ScreenPrintf(0, 20, "IsAttracted : %d", go->enemy.LeftBullet[0].IsAttracted);
	Novice::ScreenPrintf(0, 40, "IsHeld : %d", go->enemy.LeftBullet[0].IsHeld);
	Novice::ScreenPrintf(0, 60, "IsShot_p : %d", go->enemy.LeftBullet[0].IsShot_p);

	Novice::ScreenPrintf(0, 100, "RIsAlive : %d", go->enemy.hand[Right].IsAlive);
	Novice::ScreenPrintf(0, 120, "RIsDown : %d", go->enemy.hand[Right].IsDown);

	Novice::ScreenPrintf(0, 150, "LIsAlive : %d", go->enemy.hand[1].IsAlive);
	Novice::ScreenPrintf(0, 170, "LIsDown : %d", go->enemy.hand[1].IsDown);

	Novice::ScreenPrintf(0, 200, "IsAggression : %d", go->player.IsAggression);

	Novice::ScreenPrintf(0, 220, "Condition : %d", go->enemy.Condition);

	Novice::ScreenPrintf(0, 240, "MoveType : %d", go->enemy.MoveType);
}