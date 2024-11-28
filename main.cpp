//ソースファイルの読み込み
#include <Novice.h>
#include<math.h>
#include<time.h>

//ヘッダーファイルの読み込み（アルファベット順）
#include"camera.h"
#include"common.h"
#include"Explain.h"
#include"collision.h"
#include"define.h"
#include"enemy.h"
#include"player.h"
#include"stage.h"
#include"structuer.h"
#include"system.h"
#include "field.h"

#include"sceneChange.h"
#include "afterimage.h"
#include"title.h"


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
	sceneChange scene;
	Sounds sounds;
	Shake shake;
	AllExplain allexplain;
	PARTICLE particle;//@@@
	AFTERIMAGE afterimage;

	TitleScene title;
	Title titleU;

	int HandleClear = Novice::LoadTexture("./image/clear.png");
	Vector2 wid = {};

	//構造体のアドレスを格納する変数の宣言
	GameObject* p_gameobject = &gameobject;
	CameraRelated* p_camera = &camera;
	Key* p_key = &key;
	AllExplain* p_allexplain = &allexplain;
	sceneChange* p_scene=&scene;
	Sounds* p_sounds = &sounds;
	Shake * p_shake= &shake;

	PARTICLE* p_particle = &particle;//@@@
	AFTERIMAGE *p_afterimage = &afterimage;

	TitleScene* p_title = &title;
	Title* p_titleU = &titleU;

	//初期化関数
	PlayerInitialize(p_gameobject);
	StageInitialize(p_gameobject);
	EnemyInitialize(p_gameobject);
	CameraInitialize(p_camera);
	intializeScene(p_scene);
	initializeSounds(p_sounds);
	initializeShake(p_shake);
	initializeTitle(p_titleU);
	
	ExplainIitialize(p_allexplain);

	ParticleInitialize(p_particle);
	AfterimageInitialize(p_afterimage);//@@@

	TitleInitialize(p_title);


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

		switch (scene.state)
		{
		case TITLE:
			Novice::StopAudio(p_sounds->gamePlayPlayHandle);
			TitleUpdate(p_titleU);
			TitleChange(p_scene, p_key, p_sounds,p_gameobject,p_camera);


			//描画処理
			Novice::DrawBox(static_cast<int>(640.0f-32.0f), static_cast<int>(450.0f ), 64, 64, 0.0f, p_scene->color, kFillModeSolid);

			TitleDraw(p_titleU,p_scene);

			//Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);

			//Novice::ScreenPrintf(10, 500, "posP : %f / isP : %f / ", p_scene->titleT, p_scene->startFrame);

				/*Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x222222ff, kFillModeSolid);
				
				


				Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);


				EnemyDraw(p_gameobject);


				PlayerDraw(p_gameobject);*/

			

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, p_scene->fadeColor, kFillModeSolid);

			if (!Novice::IsPlayingAudio(p_sounds->titlePlayHandle) ||
				p_sounds->titlePlayHandle == -1) {
				p_sounds->titlePlayHandle =
					Novice::PlayAudio(p_sounds->titleSoundHandle, true, 0.3f);
			}


			//Novice::DrawBox(128, 128 + p_scene->option * 64, 64, 64, 0.0f, WHITE, kFillModeSolid);
			TitleDraw(p_title);

			break;


		case GAMEPLAY:

			//Novice::StopAudio(p_sounds->gamePlayPlayHandle);
			Novice::StopAudio(p_sounds->titlePlayHandle);
			if (!p_scene->isTransition)
			{
				TitleChange(p_scene, p_key, p_sounds, p_gameobject, p_camera);
				
				
			}
			else
			{
				PlayerUpdate(p_gameobject, p_camera, p_key);

			clearColor = 0x00000000;
			isSelectBar = 0;
			//プレイヤーの更新処理






				AfterimageUpDate(p_afterimage, p_particle, p_camera, p_gameobject);//@@@
				MovableObjectUpdate(p_gameobject, p_camera, p_key);





				ParticleUpDate(p_particle, p_camera, p_gameobject, p_key);//@@@

				FlickrUpdate(p_gameobject, p_key,p_sounds);
				RenderingPipeline(&gameobject.player.flickr, p_camera);




				CameraTransition_Start(p_gameobject, p_camera,p_sounds);
				ScrollFunction(p_gameobject, p_camera);


				MaskChange(p_scene, p_gameobject, p_key);

				//ステージの更新処理

				StageGenerate(p_gameobject);

				for (int i = 0; i < VerBlockNum; ++i) {
					for (int j = 0; j < HolBlockNum; ++j) {

						RenderingPipeline(&gameobject.mapchip[i][j], p_camera);
					}
				}



				//エネミーの更新処理
				EnemyUpdate(p_gameobject, p_camera,p_sounds);

				ScrollFunction(p_gameobject, p_camera);

				ShakeFanction(p_shake, p_camera, p_key);

				PlayerHudUpdate(p_gameobject);

				CameraUpdate(p_camera, p_key);

				ExplainUpdate(p_gameobject, p_allexplain);

				//当たり判定関数
				Col_Update(p_gameobject);



				//リセット関数
				RkeyReset(p_gameobject, p_camera, p_key);
				

			}

			if (gameobject.enemy.LapNum == 1) {
				if (!gameobject.enemy.IsAlive) {
					scene.state = 2;
				}
			}

			if (gameobject.player.HP <= 0) {
				scene.state = 3;
			}



			///
			/// ↓描画処理ここから
			///

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x222222ff, kFillModeSolid);

			

			///
			/// ↓描画処理ここから
			///


			Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);


			///
			/// ↑更新処理ここまで
			///


			///
			/// ↓描画処理ここから
			///


		  //AfterimageDraw(p_afterimage, p_particle, p_gameobject);//@@@


			StageDraw(p_gameobject);

	        ParticleDraw(p_particle);
	  
	        EnemyDraw(p_gameobject);


			PlayerDraw(p_gameobject);

			ExplainDraw(p_allexplain);

			PlayerHudDraw(p_gameobject);

			FlickrDraw(p_gameobject);

			if (p_particle->particleHit.life > 0) {
				Novice::DrawQuad(0, 0, 1280, 0, 0, 720, 1280, 720, 0, 0, 1280, 720, p_particle->particleHit.Image, p_particle->particleHit.Color);
			}


			MaskDraw(p_scene);


			Novice::DrawBox(0, 0, 1280, 720, 0.0f, p_scene->fadeColor, kFillModeSolid);


			//Novice::DrawLine(
			//	static_cast<int>(gameobject.player.ScreenPos.x),
			//	static_cast<int>(gameobject.player.ScreenPos.y),
			//	static_cast<int>(gameobject.player.flickr.ScreenPos.x),
			//	static_cast<int>(gameobject.player.flickr.ScreenPos.y),
			//	RED
			//);



			//Novice::ScreenPrintf(900, 0, "ShotCount :%d", gameobject.enemy.ShotCount);


			////デバッグ
			///*Novice::ScreenPrintf(20, 0, "player pos x : %f", gameobject.player.ScreenPos.x);
			//Novice::ScreenPrintf(20, 20, "player pos y : %f", gameobject.player.ScreenPos.y);*/


			//デバッグ
			/*Novice::ScreenPrintf(20, 0, "player pos x : %f", gameobject.player.ScreenPos.x);
			Novice::ScreenPrintf(20, 20, "player pos y : %f", gameobject.player.ScreenPos.y);*/

			//Novice::ScreenPrintf(20, 50, "player Wpos x : %f", gameobject.player.WorldPos.x);
			//Novice::ScreenPrintf(20, 70, "player Wpos y : %f", gameobject.player.WorldPos.y);

			////Novice::ScreenPrintf(20, 100, "IsHit : %d", gameobject.player.flickr.IsHit);
			////Novice::ScreenPrintf(20, 120, "IsMovableObjHit : %d", gameobject.player.flickr.IsMovableObjHit);
			//Novice::ScreenPrintf(20, 140, "IsShot : %d", gameobject.player.flickr.IsShot);
			////Novice::ScreenPrintf(20, 160, "IsHold : %d", gameobject.player.IsHoldObject);
			////
			////Novice::ScreenPrintf(20, 200, "Flickr VecX : %f", gameobject.player.flickr.Vector.x);
			////Novice::ScreenPrintf(20, 220, "Flickr VecY : %f", gameobject.player.flickr.Vector.y);
		
			////Novice::ScreenPrintf(20, 250, "RangeLimit : %d", gameobject.player.flickr.RangeLimit);

			//Novice::ScreenPrintf(10, 10, "posP : %f / isP : %d / ", p_particle->particleCharge[0].DrawLeftTop.y, p_particle->particleCharge[0].isParticle);
			//Novice::ScreenPrintf(10, 40, "posP : %f / isP : %d / ", p_particle->particleFlicker[5].DrawLeftBottom.y, p_particle->particleFlicker[6].isParticle);
			//Novice::ScreenPrintf(10, 400, "posP : %f / isP : %f / ", p_camera->CameraPos.x, p_camera->CameraPos.y);

			//Novice::ScreenPrintf(10, 500, "posP : %f / isP : %f / ", p_camera->easeCamera.t, p_scene->startFrame);
			//プレイヤーの更新処理

			//Novice::ScreenPrintf(10, 500, "posP : %f / isP : %f / ", p_camera->easeCamera.t, p_scene->pos.y);
			
			//Novice::ScreenPrintf(20, 20, "Life :%d", gameobject.player.HP);
			

			//Novice::ScreenPrintf(0, 300, "life : %d", particle.particleHit.life);

			//EnemyDebugPrintf(p_gameobject);


			////シーンを切り替える
			//if (p_key->keys[DIK_G] && !p_key->preKeys[DIK_G])
			//{
			//	if (p_scene->state == GAMEPLAY)
			//	{


			//		p_scene->state = TITLE;

			//		// BGMを止める
			//		Novice::StopAudio(p_sounds->gamePlayPlayHandle);
			//		break;
			//	}

			//}
			//SoundPlayBGM(p_sounds->gamePlayPlayHandle, p_sounds->gamePlaySoundHandle, p_sounds->volume);
			// 音楽を鳴らす
			if (!Novice::IsPlayingAudio(p_sounds->gamePlayPlayHandle) ||
				p_sounds->gamePlayPlayHandle == -1) {
				p_sounds->gamePlayPlayHandle =
					Novice::PlayAudio(p_sounds->gamePlaySoundHandle, true, 0.3f);
			}
			break;

		case CLEAR:
			
			if (clearColor <= 0x000000EE) {
				clearColor += 5;
			}
			for (int i = 0;i < 2;i++) {

				if (isSelectBar == 1) {
					wid = { p_particle->bar[1].Width, p_particle->bar[1].Height };
					Easing(&wid, 320.0f, 192.0f, 384.0f, 230.4f, &p_particle->bar[1].nowFrame, p_particle->bar[1].endFrame, &p_particle->bar[1].t, 1.0f, materialOutCirc);
					p_particle->bar[1].Width = wid.x;p_particle->bar[1].Height = wid.y;
					if (p_particle->bar[1].nowFrame >= p_particle->bar[1].endFrame) {
						p_particle->bar[1].nowFrame = p_particle->bar[1].endFrame;
					}
					if (p_key->keys[DIK_A]) {
						isSelectBar = 0;
						p_particle->bar[0].endFrame = 30;
					}
					
					p_particle->bar[0].Width = 320;
					p_particle->bar[0].Height = 192;
					p_particle->bar[0].nowFrame = 0;
					if (p_key->keys[DIK_J]) {
						p_scene->state = 0;
						PlayerInitialize(p_gameobject);

						StageInitialize(p_gameobject);
						EnemyInitialize(p_gameobject);
						CameraInitialize(p_camera);
					}
				}
				if (isSelectBar == 0) {
					wid = { p_particle->bar[0].Width, p_particle->bar[0].Height };
					Easing(&wid, 320.0f, 192.0f, 384.0f, 230.4f, &p_particle->bar[0].nowFrame, p_particle->bar[0].endFrame, &p_particle->bar[0].t, 1.0f, materialOutCirc);
					p_particle->bar[0].Width = wid.x;p_particle->bar[0].Height = wid.y;
					if (p_particle->bar[0].nowFrame >= p_particle->bar[0].endFrame) {
						p_particle->bar[0].nowFrame = p_particle->bar[0].endFrame;
					}
					if (p_key->keys[DIK_D]) {
						isSelectBar = 1;
						p_particle->bar[1].endFrame = 30;
					}

					p_particle->bar[1].Width = 320;
					p_particle->bar[1].Height = 192;
					p_particle->bar[1].nowFrame = 0;
					if (p_key->keys[DIK_J]) {
						p_scene->state = 1;
						PlayerInitialize(p_gameobject);

						StageInitialize(p_gameobject);
						EnemyInitialize(p_gameobject);
						CameraInitialize(p_camera);
					}
				}
			}
			

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);
			AfterimageDraw(p_afterimage, p_particle, p_gameobject);//@@@


			StageDraw(p_gameobject);

			ParticleDraw(p_particle);

			EnemyDraw(p_gameobject);


			PlayerDraw(p_gameobject);

			FlickrDraw(p_gameobject);



			if (p_particle->particleHit.life > 0) {
				Novice::DrawQuad(0, 0, 1280, 0, 0, 720, 1280, 720, 0, 0, 1280, 720, p_particle->particleHit.Image, p_particle->particleHit.Color);
			}

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, clearColor, kFillModeSolid);
			if (clearColor > 0x000000EE) {
				Novice::DrawQuad(0, 0 - 100, 1280, 0 - 100, 0, 720 - 100, 1280, 720 - 100, 0, 0, 1280, 720, HandleClear, 0xFFFFFFFF);
				for (int i = 0;i < 2;i++) {
					Novice::DrawQuad(int(p_particle->bar[i].WorldPos.x - p_particle->bar[i].Width / 2), int(p_particle->bar[i].WorldPos.y - p_particle->bar[i].Height / 2),
						int(p_particle->bar[i].WorldPos.x + p_particle->bar[i].Width / 2), int(p_particle->bar[i].WorldPos.y - p_particle->bar[i].Height / 2),
						int(p_particle->bar[i].WorldPos.x - p_particle->bar[i].Width / 2), int(p_particle->bar[i].WorldPos.y + p_particle->bar[i].Height / 2),
						int(p_particle->bar[i].WorldPos.x + p_particle->bar[i].Width / 2), int(p_particle->bar[i].WorldPos.y + p_particle->bar[i].Height / 2),
						int(p_particle->bar[i].ImagePos.x), int(p_particle->bar[i].ImagePos.y), int(320), int(192), p_particle->bar[i].Image,
						p_particle->bar[i].Color);
				}
				
			}

			break;

		case GAMEOVER:

			if (clearColor <= 0x000000EE) {
				clearColor += 5;
			}

			for (int i = 0;i < 2;i++) {

				if (isSelectBar == 1) {
					wid = { p_particle->bar[1].Width, p_particle->bar[1].Height };
					Easing(&wid, 320.0f, 192.0f, 384.0f, 230.4f, &p_particle->bar[1].nowFrame, p_particle->bar[1].endFrame, &p_particle->bar[1].t, 1.0f, materialOutCirc);
					p_particle->bar[1].Width = wid.x;p_particle->bar[1].Height = wid.y;
					if (p_particle->bar[1].nowFrame >= p_particle->bar[1].endFrame) {
						p_particle->bar[1].nowFrame = p_particle->bar[1].endFrame;
					}
					if (p_key->keys[DIK_A]) {
						isSelectBar = 0;
						p_particle->bar[0].endFrame = 30;
					}

					p_particle->bar[0].Width = 320;
					p_particle->bar[0].Height = 192;
					p_particle->bar[0].nowFrame = 0;
					if (p_key->keys[DIK_J]) {
						p_scene->state = 0;
						PlayerInitialize(p_gameobject);

						StageInitialize(p_gameobject);
						EnemyInitialize(p_gameobject);
						CameraInitialize(p_camera);
					}
				}
				if (isSelectBar == 0) {
					wid = { p_particle->bar[0].Width, p_particle->bar[0].Height };
					Easing(&wid, 320.0f, 192.0f, 384.0f, 230.4f, &p_particle->bar[0].nowFrame, p_particle->bar[0].endFrame, &p_particle->bar[0].t, 1.0f, materialOutCirc);
					p_particle->bar[0].Width = wid.x;p_particle->bar[0].Height = wid.y;
					if (p_particle->bar[0].nowFrame >= p_particle->bar[0].endFrame) {
						p_particle->bar[0].nowFrame = p_particle->bar[0].endFrame;
					}
					if (p_key->keys[DIK_D]) {
						isSelectBar = 1;
						p_particle->bar[1].endFrame = 30;
					}

					p_particle->bar[1].Width = 320;
					p_particle->bar[1].Height = 192;
					p_particle->bar[1].nowFrame = 0;
					if (p_key->keys[DIK_J]) {
						p_scene->state = 1;
						PlayerInitialize(p_gameobject);

						StageInitialize(p_gameobject);
						EnemyInitialize(p_gameobject);
						CameraInitialize(p_camera);
					}
				}
			}

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);
			AfterimageDraw(p_afterimage, p_particle, p_gameobject);//@@@


			StageDraw(p_gameobject);

			ParticleDraw(p_particle);

			EnemyDraw(p_gameobject);


			PlayerDraw(p_gameobject);

			FlickrDraw(p_gameobject);


			if (p_particle->particleHit.life > 0) {
				Novice::DrawQuad(0, 0, 1280, 0, 0, 720, 1280, 720, 0, 0, 1280, 720, p_particle->particleHit.Image, p_particle->particleHit.Color);
			}

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, clearColor, kFillModeSolid);
			if (clearColor > 0x000000EE) {
				Novice::DrawQuad(0, 0 - 100, 1280, 0 - 100, 0, 720 - 100, 1280, 720 - 100, 1280, 0, 1280, 720, HandleClear, 0xFFFFFFFF);
				for (int i = 0;i < 2;i++) {
					Novice::DrawQuad(int(p_particle->bar[i].WorldPos.x - p_particle->bar[i].Width / 2), int(p_particle->bar[i].WorldPos.y - p_particle->bar[i].Height / 2),
						int(p_particle->bar[i].WorldPos.x + p_particle->bar[i].Width / 2), int(p_particle->bar[i].WorldPos.y - p_particle->bar[i].Height / 2),
						int(p_particle->bar[i].WorldPos.x - p_particle->bar[i].Width / 2), int(p_particle->bar[i].WorldPos.y + p_particle->bar[i].Height / 2),
						int(p_particle->bar[i].WorldPos.x + p_particle->bar[i].Width / 2), int(p_particle->bar[i].WorldPos.y + p_particle->bar[i].Height / 2),
						int(p_particle->bar[i].ImagePos.x), int(p_particle->bar[i].ImagePos.y), int(320), int(192), p_particle->bar[i].Image,
						p_particle->bar[i].Color);
				}
			}
			
			break;
		}


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
