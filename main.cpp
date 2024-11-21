//ソースファイルの読み込み
#include <Novice.h>
#include<math.h>
#include<time.h>

//ヘッダーファイルの読み込み（アルファベット順）
#include"camera.h"
#include"common.h"
#include"define.h"
#include"enemy.h"
#include"player.h"
#include"stage.h"
#include"structuer.h"
#include"system.h"

const char kWindowTitle[] = "LC1A_21_タケノウチ_ナチ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WindowWidth, WindowHeight);

	//乱数値の取得
	srand((unsigned)time(NULL));

	//構造体の実体化
	GameObject gameobject;
	CameraRelated camera;
	Key key;

	//構造体のアドレスを格納する変数の宣言
	GameObject* p_gameobject = &gameobject;
	CameraRelated* p_camera = &camera;
	Key* p_key = &key;


	//初期化関数
	PlayerInitialize(p_gameobject);
	StageInitialize(p_gameobject);
	EnemyInitialize(p_gameobject);
	CameraInitialize(p_camera);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(key.preKeys, key.keys, 256);
		Novice::GetHitKeyStateAll(key.keys);

		///
		/// ↓更新処理ここから
		///
		
		//プレイヤーの更新処理

		PlayerUpdate(p_gameobject, p_camera, p_key);

		FlickrUpdate(p_gameobject, p_key);
		RenderingPipeline(&gameobject.player.flickr, p_camera);



		//ステージの更新処理

		StageGenerate(p_gameobject);

		for (int i = 0; i < VerBlockNum; ++i) {
			for (int j = 0; j < HolBlockNum; ++j) {

				RenderingPipeline(&gameobject.mapchip[i][j],p_camera);
			}
		}





		//エネミーの更新処理
		EnemyUpdate(p_gameobject, p_camera);

		ScrollFunction(p_gameobject,p_camera);

		CameraUpdate(p_camera, p_key);

		//リセット関数
		RkeyReset(p_gameobject, p_key);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
	 
		EnemyDraw(p_gameobject);

		PlayerDraw(p_gameobject);

		FlickrDraw(p_gameobject);

		StageDraw(p_gameobject);

		MovableObjectDraw(p_gameobject);

		Novice::DrawLine(
			static_cast<int>(gameobject.player.ScreenPos.x),
			static_cast<int>(gameobject.player.ScreenPos.y),
			static_cast<int>(gameobject.player.flickr.ScreenPos.x),
			static_cast<int>(gameobject.player.flickr.ScreenPos.y),
			RED
		);

		//デバッグ
		Novice::ScreenPrintf(20, 0, "player pos x : %f", gameobject.player.ScreenPos.x);
		Novice::ScreenPrintf(20, 20, "player pos y : %f", gameobject.player.ScreenPos.y);

		Novice::ScreenPrintf(20, 50, "player Wpos x : %f", gameobject.player.WorldPos.x);
		Novice::ScreenPrintf(20, 70, "player Wpos y : %f", gameobject.player.WorldPos.y);

		Novice::ScreenPrintf(20, 100, "IsHit : %d", gameobject.player.flickr.IsHit);
		Novice::ScreenPrintf(20, 120, "IsMovableObjHit : %d", gameobject.player.flickr.IsMovableObjHit);
		Novice::ScreenPrintf(20, 140, "IsShot : %d", gameobject.player.flickr.IsShot);
		Novice::ScreenPrintf(20, 160, "IsHold : %d", gameobject.player.IsHoldObject);

		Novice::ScreenPrintf(20, 200, "Flickr VecX : %f", gameobject.player.flickr.Vector.x);
		Novice::ScreenPrintf(20, 220, "Flickr VecY : %f", gameobject.player.flickr.Vector.y);

		Novice::ScreenPrintf(20, 250, "RangeLimit : %d", gameobject.player.flickr.RangeLimit);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (key.preKeys[DIK_ESCAPE] == 0 && key.keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
