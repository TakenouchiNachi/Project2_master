#include "afterimage.h"


void MakeAfterImage(RectangleObject* obj,Vector2 go, Afterimage *af, int afterImageNum, int* afterNum, int *inter) {
	*inter -= 1;
	for (int k = 0;k < afterImageNum;k++) {
			if (go.x != af[k].WorldPos.x || go.y != af[k].WorldPos.y) {
				if (*afterNum == k && *inter <= 0) {
					af[k].WorldPos = go;
					af[k].Color = obj->Color;
					*afterNum += 1;
					*inter = maxInterval;
					if (*afterNum >= afterImageNum) {
						*afterNum = 0;
					}
					break;
				}
			}
	}
	
}

void AfterimageInitialize(AFTERIMAGE* Af) {

	for (int k = 0;k < AFINum;k++) {

		//プレイヤー
		Af->playerPA[k].BaseInfoInitialize(
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
			2.0f,

			//画像
			Novice::LoadTexture("./image./player_ver5.png"),

			//画像の幅
			32.0f,
			32.0f,

			//色
			0xFFFFFFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
		//ボス
		Af->bossBA[k].BaseInfoInitialize(
			//初期座標(x,y)
			0.0f,
			0.0f,

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
			0xFFFFFFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);

		//ボス R
		Af->bossBAR[k].BaseInfoInitialize(
			//初期座標(x,y)
			0.0f,
			0.0f,

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
			0xFFFFFFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);

		//ボス L
		Af->bossBAL[k].BaseInfoInitialize(
			//初期座標(x,y)
			0.0f,
			0.0f,

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
			0xFFFFFFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
		Af->bul1[k].BaseInfoInitialize(
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
			2.0f,

			//画像
			Novice::LoadTexture("./image./bullet.png"),

			//画像の幅
			32.0f,
			32.0f,

			//色
			0xFF00FFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
		Af->bul2[k].BaseInfoInitialize(
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
			2.0f,

			//画像
			Novice::LoadTexture("./image./bullet.png"),

			//画像の幅
			32.0f,
			32.0f,

			//色
			0xFF00FFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
		Af->bul3[k].BaseInfoInitialize(
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
			2.0f,

			//画像
			Novice::LoadTexture("./image./bullet.png"),

			//画像の幅
			32.0f,
			32.0f,

			//色
			0xFF00FFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
		Af->bul4[k].BaseInfoInitialize(
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
			2.0f,

			//画像
			Novice::LoadTexture("./image./bullet.png"),

			//画像の幅
			32.0f,
			32.0f,

			//色
			0xFF00FFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
		Af->bul1L[k].BaseInfoInitialize(
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
			2.0f,

			//画像
			Novice::LoadTexture("./image./bullet.png"),

			//画像の幅
			32.0f,
			32.0f,

			//色
			0xFF00FFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
		Af->bul2L[k].BaseInfoInitialize(
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
			2.0f,

			//画像
			Novice::LoadTexture("./image./bullet.png"),

			//画像の幅
			32.0f,
			32.0f,

			//色
			0xFF00FFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
		Af->bul3L[k].BaseInfoInitialize(
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
			2.0f,

			//画像
			Novice::LoadTexture("./image./bullet.png"),

			//画像の幅
			32.0f,
			32.0f,

			//色
			0xFF00FFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
		Af->bul4L[k].BaseInfoInitialize(
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
			2.0f,

			//画像
			Novice::LoadTexture("./image./bullet.png"),

			//画像の幅
			32.0f,
			32.0f,

			//色
			0xFF00FFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
	}

}

void AfterimageUpDate(AFTERIMAGE* Af,PARTICLE* p, CameraRelated* cr, GameObject *go) {

	//パーティクル
	MakeAfterImage(&go->enemy.RightBullet[0], go->enemy.RightBullet[0].WorldPos, Af->bul1, AFINum, &afterNumPcA1, &intervalBul1);
	for (int k = 0;k < AFINum;k++) {
		Af->bul1[k].Color -= (255 / (AFINum * maxInterval));
	}
	MakeAfterImage(&go->enemy.RightBullet[1], go->enemy.RightBullet[1].WorldPos, Af->bul2, AFINum, &afterNumPcA2, &intervalBul2);
	for (int k = 0;k < AFINum;k++) {
		Af->bul2[k].Color -= (255 / (AFINum * maxInterval));
	}
	MakeAfterImage(&go->enemy.RightBullet[2], go->enemy.RightBullet[2].WorldPos, Af->bul3, AFINum, &afterNumPcA3, &intervalBul3);
	for (int k = 0;k < AFINum;k++) {
		Af->bul3[k].Color -= (255 / (AFINum * maxInterval));
	}
	MakeAfterImage(&go->enemy.RightBullet[3], go->enemy.RightBullet[3].WorldPos, Af->bul4, AFINum, &afterNumPcA4, &intervalBul4);
	for (int k = 0;k < AFINum;k++) {
		Af->bul4[k].Color -= (255 / (AFINum * maxInterval));
	}

	MakeAfterImage(&go->enemy.LeftBullet[0], go->enemy.LeftBullet[0].WorldPos, Af->bul1L, AFINum, &afterNumPcA1L, &intervalBul1L);
	for (int k = 0;k < AFINum;k++) {
		Af->bul1L[k].Color -= (255 / (AFINum * maxInterval));
	}
	MakeAfterImage(&go->enemy.LeftBullet[1], go->enemy.LeftBullet[1].WorldPos, Af->bul2L, AFINum, &afterNumPcA2L, &intervalBul2L);
	for (int k = 0;k < AFINum;k++) {
		Af->bul2L[k].Color -= (255 / (AFINum * maxInterval));
	}
	MakeAfterImage(&go->enemy.LeftBullet[2], go->enemy.LeftBullet[2].WorldPos, Af->bul3L, AFINum, &afterNumPcA3L, &intervalBul3L);
	for (int k = 0;k < AFINum;k++) {
		Af->bul3L[k].Color -= (255 / (AFINum * maxInterval));
	}
	MakeAfterImage(&go->enemy.LeftBullet[3], go->enemy.LeftBullet[3].WorldPos, Af->bul4L, AFINum, &afterNumPcA4L, &intervalBul4L);
	for (int k = 0;k < AFINum;k++) {
		Af->bul4L[k].Color -= (255 / (AFINum * maxInterval));
	}

	//プレイヤー
	MakeAfterImage(&go->player,go->player.WorldPos, Af->playerPA, AFINum, &afterNumPA, &intervalPlayer);
	for (int k = 0;k < AFINum;k++) {
		Af->playerPA[k].Color -= (255 / (AFINum * maxInterval));
	}

	//ボス
	MakeAfterImage(&go->enemy,go->enemy.WorldPos, Af->bossBA, AFINum, &afterNumBA, &intervalBoss);
	for (int k = 0;k < AFINum;k++) {
		Af->bossBA[k].Color -= (255 / (AFINum * maxInterval));
	}

	//ボス R
	MakeAfterImage(&go->enemy.hand[Right], go->enemy.hand[Right].WorldPos, Af->bossBAR, AFINum, &afterNumBAR, &intervalBossR);
	for (int k = 0;k < AFINum;k++) {
		Af->bossBAR[k].Color -= (255 / (AFINum * maxInterval));
	}

	//ボス L
	MakeAfterImage(&go->enemy.hand[Left], go->enemy.hand[Left].WorldPos, Af->bossBAL, AFINum, &afterNumBAL, &intervalBossL);
	for (int k = 0;k < AFINum;k++) {
		Af->bossBAL[k].Color -= (255 / (AFINum * maxInterval));
	}
	p->particleFlicker;
	
	//================= [ マップに映しているところ ] ========================/



	for (int k = 0;k < AFINum;k++) {

		SetFourVertexes(&Af->bul1[k]);
		RenderingPipeline(&Af->bul1[k], cr);
		SetFourVertexes(&Af->bul2[k]);
		RenderingPipeline(&Af->bul2[k], cr);
		SetFourVertexes(&Af->bul3[k]);
		RenderingPipeline(&Af->bul3[k], cr);
		SetFourVertexes(&Af->bul4[k]);
		RenderingPipeline(&Af->bul4[k], cr);


		SetFourVertexes(&Af->bul1L[k]);
		RenderingPipeline(&Af->bul1L[k], cr);
		SetFourVertexes(&Af->bul2L[k]);
		RenderingPipeline(&Af->bul2L[k], cr);
		SetFourVertexes(&Af->bul3L[k]);
		RenderingPipeline(&Af->bul3L[k], cr);
		SetFourVertexes(&Af->bul4L[k]);
		RenderingPipeline(&Af->bul4L[k], cr);


		//プレイヤー
		SetFourVertexes(&Af->playerPA[k]);
		RenderingPipeline(&Af->playerPA[k], cr);
		//ボス
		SetFourVertexes(&Af->bossBA[k]);
		RenderingPipeline(&Af->bossBA[k], cr);
		//ボス R
		SetFourVertexes(&Af->bossBAR[k]);
		RenderingPipeline(&Af->bossBAR[k], cr);
		//ボス L
		SetFourVertexes(&Af->bossBAL[k]);
		RenderingPipeline(&Af->bossBAL[k], cr);
		
		//画像の描画範囲を合わせる
		Af->bossBAR[k].ImagePos = go->enemy.hand[Right].ImagePos;
		Af->bossBAL[k].ImagePos = go->enemy.hand[Left].ImagePos;
	}
	
}


void AfterimageDraw(AFTERIMAGE* Af, PARTICLE* p, GameObject *go) {

	p->particleFlicker;
	Novice::SetBlendMode(BlendMode::kBlendModeAdd);
	for (int k = 0;k < AFINum;k++) {
		if(go->enemy.RightBullet[0].IsShot)
		Af->bul1[k].RectObjDraw();
		if (go->enemy.RightBullet[1].IsShot)
		Af->bul2[k].RectObjDraw();
		if (go->enemy.RightBullet[2].IsShot)
		Af->bul3[k].RectObjDraw();
		if (go->enemy.RightBullet[3].IsShot)
		Af->bul4[k].RectObjDraw();

		if(go->enemy.LeftBullet[0].IsShot)
		Af->bul1L[k].RectObjDraw();
		if (go->enemy.LeftBullet[1].IsShot)
		Af->bul2L[k].RectObjDraw();
		if (go->enemy.LeftBullet[2].IsShot)
		Af->bul3L[k].RectObjDraw();
		if (go->enemy.LeftBullet[3].IsShot)
		Af->bul4L[k].RectObjDraw();

		//プレイヤー
		if(go->player.flickr.IsShot)
		Af->playerPA[k].RectObjDraw();

		//ボス
		Af->bossBA[k].RectObjDraw();

		//ボス R
		if (go->enemy.hand[Right].IsAlive) {
			Af->bossBAR[k].RectObjDraw();
		}

		//ボス L
		if (go->enemy.hand[Left].IsAlive) {
			Af->bossBAL[k].RectObjDraw();
		}
	}
	Novice::SetBlendMode(BlendMode::kBlendModeNormal);
}