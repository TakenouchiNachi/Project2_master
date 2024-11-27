#include"sceneChange.h"
#include"common.h"
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
	scene->option = 0;
	scene->state = TITLE;

	scene->titlePos = { 640.0f,450.0f };
	scene->titleEnd = { 640.0f,256.0f };
	scene->titleStart = { 640.0f,450.0f };
	scene->titleT = 0.0f;
	scene->titleNowFrame = 0.0f;
	scene->startFrame = 0;
	scene->isStart = false;
	scene->isTransition = false;
	
}

void initializeTitle(Title* title)
{
	title->allowPos = { 480.0f,592.0f };
	title->allowSpeed = 0.5f;
	title->Color = WHITE;
	title->allowHeight = 36.0f;
	title->allowWidth = 64.0f;
	title->allowImage = Novice::LoadTexture("./image/titleAllow.png");
	title->allowColor = WHITE;
	title->ScreenPos = { 0.0f,0.0f };
	title->Image= Novice::LoadTexture("./image/title.png");
	
	title->startOption = { 640.0f,592.0f };
	title->startOptionHeight = 144.0f;
	title->startOptionWidth = 256.0f;
	title->startOptionImage = Novice::LoadTexture("./image/start.png");
	
}

//音の変数の初期化
void initializeSounds(Sounds* sounds)
{
	sounds->cursorPlayHandle = false;
	sounds->cursorSoundHandle= Novice::LoadAudio("./Resources/Sounds/MoveCursol.mp3");

	sounds->decisionPlayHandle = false;
	sounds->decisionSoundHandle = Novice::LoadAudio("./Resources/Sounds/Decision.mp3");

	sounds->gamePlayPlayHandle = -1;
	sounds->gamePlaySoundHandle = Novice::LoadAudio("./Resources/Sounds/gamePlay.mp3");

	//タイトルbgm
	sounds->titlePlayHandle=- 1;
	sounds->titleSoundHandle= Novice::LoadAudio("./Resources/Sounds/title.mp3");

	sounds->flickrChargePlayHandle = false;
	sounds->flickrChargeSoundHandle = Novice::LoadAudio("./Resources/Sounds/flickrCharge.mp3");

	sounds->flickrShotPlayHandle = false;
	sounds->flickrShotSoundHandle = Novice::LoadAudio("./Resources/Sounds/flickrShot.mp3");

	sounds->bossShoutPlayHandle = false;
	sounds->bossShoutSoundHandle = Novice::LoadAudio("./Resources/Sounds/bossShout.mp3");

	sounds->handPressPlayHandle = false;
	sounds->handPressSoundHandle = Novice::LoadAudio("./Resources/Sounds/handPress.mp3");

	sounds->handAttackPlayHandle = false;
	sounds->handAttackSoundHandle = Novice::LoadAudio("./Resources/Sounds/handAttack.mp3");
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
void CameraTransition_Start(GameObject* go, CameraRelated* cr,Sounds* sounds)
{
	if (cr->easeCamera.isTransionCamera&&cr->easeCamera.state == NONE)
	{
		cr->easeCamera.state = TO_ENEMY;
		

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
			&cr->easeCamera.nowFrame, 60.0f,
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
				SoundPlaySE(sounds->bossShoutPlayHandle, sounds->bossShoutSoundHandle, 0.5f);
				cr->easeCamera.isTransionCamera = false;
			}
		}
	}
}

//シェイクの関数
void ShakeFanction(Shake*shake,CameraRelated*cr,Key*key)
{
	if (key->keys[DIK_E])
	{
		shake->isShake = true;
		
	}


	if (shake->elapsedTime > shake->duration)
	{
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
		cr->CameraPos.x += shake->outX;
		cr->CameraPos.y += shake->outY;

	}
}

void TitleUpdate(Title* title)
{
	if (title->allowPos.x >=488.0f || title->allowPos.x <= 472.0f)
	{
		title->allowSpeed *= -1.0f;
    }
	title->allowPos.x += title->allowSpeed;

	
}

void TitleDraw(Title* title, sceneChange* scene)
{
	Novice::DrawSprite(static_cast<int>(title->ScreenPos.x), static_cast<int>(title->ScreenPos.y), title->Image, 1.0f, 1.0f, 0.0f, title->Color);
	Novice::DrawSprite(static_cast<int>(title->allowPos.x - title->allowWidth / 2.0f), static_cast<int>(title->allowPos.y - title->allowHeight / 2.0f+ scene->option * 64), title->allowImage, 1.0f, 1.0f, 0.0f, title->allowColor);
	Novice::DrawSprite(static_cast<int>(title->startOption.x - title->startOptionWidth / 2.0f), static_cast<int>(title->startOption.y - title->startOptionHeight / 2.0f), title->startOptionImage, 1.0f, 1.0f, 0.0f, scene->color);
}

//タイトルから変更する関数
void TitleChange(sceneChange* scene, Key* key,Sounds* sounds, GameObject* go, CameraRelated* cr)
{
	//オブジェクトの基本情報更新
	SetFourVertexes(&go->player);
	SetFourVertexes(&go->enemy);
	for (int i = 0; i < 2; ++i) {
		SetFourVertexes(&go->enemy.hand[i]);
	}


	if (key->keys[DIK_SPACE] && !key->preKeys[DIK_SPACE])
	{
		scene->isStart = true;
		//Novice::StopAudio(sounds->titlePlayHandle);
		SoundPlaySE(sounds->decisionPlayHandle, sounds->decisionSoundHandle, sounds->volume);
	}

	if (scene->isStart)
	{
		//シーンの状態がタイトルで選択肢がスタートなら
		if  (scene->option == 0)
		{
			if (scene->startFrame >= 740.0f)
			{
				intializeScene(scene);
				scene->isTransition = true;
				cr->easeCamera.isTransionCamera = true;
				scene->state = GAMEPLAY;

			}
			else if (scene->startFrame >= 600.0f)
			{
				CameraTransition_Start(go,cr,sounds);
				scene->startFrame++;
			}
			else if (scene->startFrame >= 480.0f)
			{
				scene->state = GAMEPLAY;
				static float const startFade[4] = { 255,255,255,0 };
				static float const endFade[4] = { 255,255,255,255 };
				static float const kInv_ChangeingFadeTime = 1.0f / 120.0f;

				scene->changeFade_t -= kInv_ChangeingFadeTime;

				for (int i = 0; i < 4; ++i)
				{
					scene->currentFadeColor[i] = endFade[i] * scene->changeFade_t + (1.0f - scene->changeFade_t) * startFade[i];
				}

				SetColor(&scene->fadeColor, (int)scene->currentFadeColor[0], (int)scene->currentFadeColor[1],
					(int)scene->currentFadeColor[2], (int)scene->currentFadeColor[3]);

				scene->startFrame++;
			}
			else if (scene->startFrame >= 360.0f)
			{
				
				static float const startFade[4] = {255,255,255,0};
				static float const endFade[4] = { 255,255,255,255 };
				static float const kInv_ChangeingFadeTime = 1.0f / 120.0f;

				scene->changeFade_t += kInv_ChangeingFadeTime;

				for (int i = 0; i < 4; ++i)
				{
					scene->currentFadeColor[i] = endFade[i] * scene->changeFade_t + (1.0f - scene->changeFade_t) * startFade[i];
				}

				SetColor(&scene->fadeColor, (int)scene->currentFadeColor[0], (int)scene->currentFadeColor[1],
					(int)scene->currentFadeColor[2], (int)scene->currentFadeColor[3]);

				scene->startFrame++;
			}
			else if (scene->startFrame >= 120.0f)
			{
				Easing(&scene->titlePos,
					scene->titleStart.x, scene->titleStart.y,
					scene->titleEnd.x, scene->titleEnd.y,
					&scene->titleNowFrame, 240.0f, &scene->titleT, 1.0f, materialInQuad);

				scene->startFrame++;

			}
			else
			{
				static float const kInv_ChangeingColorTime = 1.0f / 120.0f;
				static float const startColor[4] = { 255,255,255,255 };
				static float const endColor[4] = { 255,0,255,255 };

				scene->changeColor_t += kInv_ChangeingColorTime;

				for (int i = 0; i < 4; ++i)
				{
					scene->buff_currentColor[i] = endColor[i] * scene->changeColor_t + (1.0f - scene->changeColor_t) * startColor[i];
				}

				SetColor(&scene->color,(int) scene->buff_currentColor[0], (int)scene->buff_currentColor[1],
					(int)scene->buff_currentColor[2], (int)scene->buff_currentColor[3]);

				//Easing(&scene->titleAlpha,
				//	scene->startTitleAlpha, 0.0f,
				//	255.0f,0.0f,
				//	&scene->titleNowAlpha, 120.0f, &scene->alphaT, 1.0f, materialInQuad);
				scene->startFrame++;
			}

		}
	}


	//if (!scene->isStart)
	//{
	//	if (key->keys[DIK_W] && !key->preKeys[DIK_W])
	//	{
	//		//選択肢を変える
	//		if (scene->option > 0)
	//		{
	//			scene->option -= 1;

	//			SoundPlaySE(sounds->cursorPlayHandle, sounds->cursorSoundHandle, sounds->volume);
	//		}

	//	}

	//	if (key->keys[DIK_S] && !key->preKeys[DIK_S])
	//	{
	//		//選択肢を変える
	//		if (scene->option < 1)
	//		{
	//			scene->option += 1;

	//			SoundPlaySE(sounds->cursorPlayHandle, sounds->cursorSoundHandle, sounds->volume);
	//		}
	//	}
	//}
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

void SetColor(unsigned int* color, int R, int G, int B, int A)
{
	*color = 0x01000000 * R + 0x00010000 * G + 0x00000100 * B + 0x00000001 * A;
}