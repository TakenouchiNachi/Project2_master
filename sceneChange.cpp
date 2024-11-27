#include"sceneChange.h"
#include"easing.h"
#include<math.h>
#include<time.h>

//シーン遷移の変数の初期化
void intializeScene(sceneChange* scene)
{
	scene->pos = { 256.0f,512.0f };
	scene->endFrame = 0.01f;
	scene->width = 33600.0f;
	scene->height = 18900.0f;
	scene->t = 0.0f;
	scene->isEase = false;
	scene->image = Novice::LoadTexture("./image/sceneChange.png");
	scene->option = 1;
	scene->state = TITLE;
}

//音の変数の初期化
void initializeSounds(Sounds* sounds)
{
	sounds->cursorPlayHandle = false;
	sounds->cursorSoundHandle= Novice::LoadAudio("./Resources/Sounds/MoveCursol.mp3");

	sounds->decisionPlayHandle = false;
	sounds->decisionSoundHandle = Novice::LoadAudio("./Resources/Sounds/Decision.mp3");

}

//シェイクの初期化
void initializeShake(Shake* shake)
{
	shake->elapsedTime = 0.0f;
	shake->duration = 120.0f;
	shake->amplitude = 10.0f;
	shake->frequency = 20.0f;
	shake->outX=0.0f;
	shake->outY=0.0f;
	shake->progress = 0.0f;
	shake->easedProgress = 0.0f;
	shake->randomX=0.0f;
	shake->randomY=0.0f;
	shake->randMax=0.0f;
	shake->isShake = false;
}


//マスク処理の描画
void MaskDraw(sceneChange* scene)
{
	Novice::DrawQuad(static_cast<int>(scene->pos.x-scene->width / 2.0f), static_cast<int>(scene->pos.y - scene->height / 2.0f),
		static_cast<int>(scene->pos.x + scene->width / 2.0f), static_cast<int>(scene->pos.y - scene->height / 2.0f),
		static_cast<int>(scene->pos.x-scene->width / 2.0f), static_cast<int>(scene->pos.y + scene->height / 2.0f),
		static_cast<int>(scene->pos.x +scene->width / 2.0f), static_cast<int>(scene->pos.y + scene->height / 2.0f),
		0, 0, 1280, 720, scene->image, WHITE);
}

//マスク処理
void MaskChange(sceneChange* scene,GameObject* go,Key* key)
{
	if (key->keys[DIK_SPACE]) 
	{
		scene->isEase = true;

		scene->pos.x = go->player.ScreenPos.x + go->player.Width / 2.0f;
		scene->pos.y = go->player.ScreenPos.y + go->player.Height / 2.0f;

		scene->startWidth = scene->width;
		scene->startHeight = scene->height;

		scene->endWidth = 2560.0f;
		scene->endHeight = 1440.0f;
	}

	if (scene->isEase)
	{
		scene->t += scene->endFrame;

		if (scene->t >= 1.0f)
		{
			
			scene->endFrame *= -1.0f;
				 
			scene->startWidth = 33600.0f;
			scene->startHeight = 18900.0f;
				 
			scene->endWidth = scene->width;
			scene->endHeight= scene->height;
		}

		if (scene->t <= 0.0f)
		{		 
			scene->t = 0.0f;

			scene->endFrame *= -1.0f;

			scene->isEase = false;
		}

		scene->width = easeBounce(scene->startWidth, scene->endWidth, scene->t);
		scene->height= easeBounce(scene->startHeight,scene->endHeight,scene->t);
	}
}

//タイトルからスタートの処理
void CameraTransition_Start(GameObject* go, CameraRelated* cr, Key* key)
{
	if (key->keys[DIK_Q] && cr->easeCamera.state == NONE)
	{
		cr->easeCamera.state = TO_ENEMY;
		cr->easeCamera.isEase = true;

		cr->easeCamera.start.x = cr->CameraPos.x;
		cr->easeCamera.start.y = cr->CameraPos.y;
		cr->easeCamera.end.x = -go->enemy.WorldPos.x;
		cr->easeCamera.end.y = -go->enemy.WorldPos.y;

		// 初期化
		cr->easeCamera.t = 0.0f;
		cr->easeCamera.nowFrame = 0;
	}

	if (cr->easeCamera.state == TO_ENEMY || cr->easeCamera.state == TO_PLAYER)
	{
		Easing(&cr->CameraPos,
			cr->easeCamera.start.x, cr->easeCamera.start.y,
			cr->easeCamera.end.x, cr->easeCamera.end.y,
			&cr->easeCamera.nowFrame, 60,
			&cr->easeCamera.t, 1.0f, materialOutQuart);

		if (cr->easeCamera.t >= 1.0f)
		{
			cr->easeCamera.t = 0.0f;

			if (cr->easeCamera.state == TO_ENEMY)
			{
				// 帰りの準備
				cr->easeCamera.state = TO_PLAYER;

				cr->easeCamera.start.x = cr->CameraPos.x;
				cr->easeCamera.start.y = cr->CameraPos.y;

				cr->easeCamera.end.x = -go->player.WorldPos.x;
				cr->easeCamera.end.y = -go->player.WorldPos.y;

				cr->easeCamera.nowFrame = 0; // フレームカウントをリセット
			}
			else if (cr->easeCamera.state == TO_PLAYER)
			{
				// イージング終了
				cr->easeCamera.state = NONE;
			}
		}
	}
}

//シェイクの関数
void ShakeFanction(Shake* shake, CameraRelated* cr, float ShakeTime, float Amplitude)
{
	shake->duration = ShakeTime;
	shake->amplitude = Amplitude;



	if (shake->elapsedTime <= shake->duration) {
		shake->isShake = true;
	}
	else {
		shake->isShake = false;
		initializeShake(shake);
	}


	if (shake->isShake)
	{
		shake->elapsedTime += 1.0f;

		// 時間に基づいてイージング値を計算
		shake->progress = shake->elapsedTime / shake->duration; // 0.0～1.0
		shake->easedProgress = OutSine(shake->progress);

		// ランダムなシェイク値（-1.0～1.0）
		shake->randomX = (rand() / float(RAND_MAX)) * 2.0f - 1.0f;
		shake->randomY = (rand() / float(RAND_MAX)) * 2.0f - 1.0f;

		// 振幅と周波数に基づいて位置を計算
		shake->outX = shake->randomX * shake->amplitude * shake->easedProgress * sinf(shake->elapsedTime * shake->frequency);
		shake->outY = shake->randomY * shake->amplitude * shake->easedProgress * cosf(shake->elapsedTime * shake->frequency);

		//カメラにシェイクの量を追加
		cr->CameraShakePos.x = shake->outX;
		cr->CameraShakePos.y = shake->outY;

	}
	else {
		cr->CameraShakePos.x = 0;
		cr->CameraShakePos.y = 0;


	}
}

//タイトルから変更する関数
void TitleChange(sceneChange* scene, Key* key,Sounds* sounds)
{
	if (key->keys[DIK_SPACE]&&!key->preKeys[DIK_SPACE])
	{
		//シーンの状態がタイトルで選択肢がスタートなら
		if (scene->state == TITLE && scene->option == 1)
		{
			scene->state =GAMEPLAY;
		}
	}

	if (key->keys[DIK_W] && !key->preKeys[DIK_W])
	{
		//選択肢を変える
		if (scene->option > 1)
		{
			scene->option -= 1;

			SoundPlaySE(sounds->cursorPlayHandle, sounds->cursorSoundHandle, sounds->volume);
		}

	}

	if (key->keys[DIK_S] && !key->preKeys[DIK_S])
	{
		//選択肢を変える
		if (scene->option < 2)
		{
			scene->option += 1;

			SoundPlaySE(sounds->cursorPlayHandle, sounds->cursorSoundHandle, sounds->volume);
		}
	}
}



//seの関数
void SoundPlaySE(int playHandle, int soundHandle, float volume)
{
	//SEを止める
	playHandle = false;

	//SEを鳴らす
	if (!playHandle)
	{
		playHandle =
			Novice::PlayAudio(soundHandle, false, volume);
	}
}

//bgmの関数
void SoundPlayBGM(int playHandleBgm, int soundHandleBgm, float volume)
{
	// 音楽を鳴らす
	if (!Novice::IsPlayingAudio(playHandleBgm) ||
		playHandleBgm == -1) {
		playHandleBgm =
			Novice::PlayAudio(soundHandleBgm, true, volume);
	}
}
