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
			Novice::LoadTexture("./image./RightHand_ver2.png"),

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
			Novice::LoadTexture("./image./LeftHand_ver2.png"),

			//色
			0xFFFFFFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);

	}

}

void AfterimageUpDate(AFTERIMAGE* Af,PARTICLE* p, CameraRelated* cr, GameObject *go) {

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
		
	}
	
}


void AfterimageDraw(AFTERIMAGE* Af, PARTICLE* p, GameObject *go) {

	p->particleFlicker;
	Novice::SetBlendMode(BlendMode::kBlendModeAdd);
	for (int k = 0;k < AFINum;k++) {

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