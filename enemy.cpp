
//ソースファイルの読み込み
#include<math.h>

//ヘッダーファイルの読み込み
#include"enemy.h"
#include"easing.h"
#include"structuer.h"
#include"enum.h"
#include"common.h"
#include"camera.h"


//初期化関数
void EnemyInitialize(GameObject* go) {

	//顔
	go->enemy.BaseInfoInitialize(

		//初期座標(x,y)
		1200.0f,
		360.0f,

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
		Novice::LoadTexture("./image./boss.png"),

		//色
		WHITE,

		//オブジェクトタイプ（可動or不可動）
		ImMovable
	);

	go->enemy.Condition = BothHands;

	go->enemy.DaiPanInfo.CurrentFrame = 0;


	//手
	go->enemy.hand[0].BaseInfoInitialize(
		//初期座標(x,y)
		1100.0f,
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
		Novice::LoadTexture("./image./Righthand.png"),

		//色
		WHITE,

		//オブジェクトタイプ（可動or不可動）
		ImMovable
	);

	//左手
	go->enemy.hand[1].BaseInfoInitialize(
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
		Novice::LoadTexture("./image./Lefthand.png"),

		//色
		WHITE,

		//オブジェクトタイプ（可動or不可動）
		ImMovable
	);

	for (int i = 0; i < 2; ++i) {
		go->enemy.hand[i].EasingStartPos = {};
	}

	go->enemy.hand[Right].IsAlive = false;
	go->enemy.hand[Left].IsAlive = true;

}



//行動パターンを決める関数
//void DecisionMoveType_Ver1(GameObject* go) {
//
//}

/*=================================
		　 攻撃パターン
 =================================*/
 //台パン
void Daipan(GameObject* go,float WholeFrame,float TransrateFrame,float OccurrenceFrame,float LastingFlame) {


	//この関数が呼び出されたときに一度だけイージングに関する初期化を行う
	if (go->enemy.DaiPanInfo.CurrentFrame == 0) {
		for (int i = 0; i < 2; ++i) {
			EasingInitialize(&go->enemy.hand[i].t, &go->enemy.hand[i].NowFrame, &go->enemy.hand[i].EasingStartPos, &go->enemy.hand[i].WorldPos);
		}
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
				if (go->enemy.hand[i].IsAlive) {


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
	}

	//攻撃処理
	if (go->enemy.DaiPanInfo.CurrentFrame > TransrateFrame && go->enemy.DaiPanInfo.CurrentFrame <= OccurrenceFrame + LastingFlame) {

		if (go->enemy.Condition == BothHands) {



		}
		else if (go->enemy.Condition == OneHand) {



		}
	}

	//攻撃後の移動処理
	if (go->enemy.DaiPanInfo.CurrentFrame > OccurrenceFrame + LastingFlame && go->enemy.DaiPanInfo.CurrentFrame <= WholeFrame) {

	}
}


//ロケットパンチ
//void LocketPunch(GameObject* go, int WholeFrame, int TransrateFrame, int LastingFlame) {
//
//	//移動処理
//	if (go->enemy.Condition = BothHands) {
//
//	}
//	else if (go->enemy.Condition = OneHand) {
//
//	}
//
//	//攻撃処理
//	if (go->enemy.Condition = BothHands) {
//
//	}
//	else if (go->enemy.Condition = OneHand) {
//
//	}
//}


//更新処理
void EnemyUpdate(GameObject* go,CameraRelated* cr) {
	  
	//状態判別
	if (go->enemy.hand[Right].IsAlive && go->enemy.hand[Left].IsAlive) {

		go->enemy.Condition = BothHands;
	}
	else if (go->enemy.hand[Right].IsAlive || go->enemy.hand[Left].IsAlive) {
		
		go->enemy.Condition = OneHand;
	}
	else {

		go->enemy.Condition = HeadOnly;
	}

	//行動パターンの決定関数
	Daipan(go,DaiPanWholeFrame,150.0f,300.0f,5.0f);

	//基本情報の更新
	//頭
	SetFourVertexes(&go->enemy);
	RenderingPipeline(&go->enemy, cr);

	//手
	for (int i = 0; i < 2; ++i) {
		SetFourVertexes(&go->enemy.hand[i]);
		RenderingPipeline(&go->enemy.hand[i], cr);
	}
}


//描画関数
void EnemyDraw(GameObject* go) {
	go->enemy.RectObjDraw();
	for (int i = 0; i < 2; ++i) {
		go->enemy.hand[i].RectObjDraw();
	}
}

//デバッグ表示関数
void EnemyDebugPrintf(GameObject* go) {
	Novice::ScreenPrintf(850, 0, "posX : %f", go->enemy.hand[0].EasingStartPos.x);
}