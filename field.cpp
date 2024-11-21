#include "field.h"

void Effect(Particle* particle, Field* field) {

	Vector2 leftUp = { field->pos.x - field->wid.x ,field->pos.y - field->wid.y };
	Vector2 rightDown = { field->pos.x + field->wid.x ,field->pos.y + field->wid.y };

	//場の範囲内なら
	if (particle->WorldPos.x >= leftUp.x && particle->WorldPos.x <= rightDown.x && particle->WorldPos.y >= leftUp.y && particle->WorldPos.y <= rightDown.y) {

		Vector2 power = {};
		power.x = field->F.x / particle->weight;
		power.y = field->F.y / particle->weight;

		particle->Acceleration.x += power.x;
		particle->Acceleration.y += power.y;

		particle->Velocity.x += particle->Acceleration.x;
		particle->Velocity.y += particle->Acceleration.y;

		particle->WorldPos.x += particle->Velocity.x;
		particle->WorldPos.y += particle->Velocity.y;

	}

	particle->life -= 1;
	if (particle->life <= 120)
		particle->Color -= 1;

}

void ParticleInitialize(PARTICLE* particle) {

	//初期化
	for (int i = 0; i < pF;i++) {
		particle->particleFlicker[i].BaseInfoInitialize(
			//初期座標(x,y)
			0.0f,
			0.0f,

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
			2.0f,

			//画像
			Novice::LoadTexture("./image./TD1-2_particle.png"),

			//色
			0xFF00FFDD,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
	}

	for (int i = 0;i < pC;i++) {
		particle->particleCharge[i].BaseInfoInitialize(
			//初期座標(x,y)
			0.0f,
			0.0f,

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
			2.0f,

			//画像
			Novice::LoadTexture("./image./TD1-2_particle.png"),

			//色
			WHITE,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
	}
	

}

void ParticleUpDate(PARTICLE* particle, CameraRelated* cr ,GameObject *go, Key *key) {


	//================= [ フリッカー ] ===================/
	for (int k = 0;k < pF;k++) {

		if (!go->player.flickr.IsShot) {
			if (key->keys[DIK_A] || key->keys[DIK_D] && key->keys[DIK_W] || key->keys[DIK_S]) {
				particleIsKey = 3;
			}
			else if (key->keys[DIK_W] || key->keys[DIK_S]) {
				particleIsKey = 1;
			}
			else if (key->keys[DIK_A] || key->keys[DIK_D]) {
				particleIsKey = 2;
			}
		}
		if (particleIsKey == 1) {
			particleRand.y = 0;
			particleRand.x = rand() % 61 - 30;
		}
		if (particleIsKey == 2) {
			particleRand.y = rand() % 61 - 30;
			particleRand.x = 0;
		}
		if (particleIsKey == 3) {
			particleRand.y = rand() % 51 - 25;
			particleRand.x = rand() % 101 - 50;
		}

		//弾を撃っている時はパーティクルを出す
		if (go->player.flickr.IsShot) {
			particle->particleFlicker[k].isParticle = 1;
		}

		//フラグが立っている間パーティクルの処理を施す
		if (particle->particleFlicker[k].isParticle == 1) {
			//=========================== [ ひもの作成 ] ================================/

			//== [ 制御点の生成 ] ==/
			Vector2 p1[control] = {};

			//== [ ひもの処理 ] ==/
			for (int i = 0;i < control;i++) {

				p1[i].x = go->player.WorldPos.x + (go->player.flickr.WorldPos.x - go->player.WorldPos.x) / 2.0f + particleRand.x;
				p1[i].y = go->player.flickr.WorldPos.y + particleRand.y;

				particle->particleFlicker[k].t = k / float(pF);//for文外でもいい説
				particle->particleFlicker[k].WorldPos = Bezier(&go->player.WorldPos, &p1[i], &go->player.flickr.WorldPos, particle->particleFlicker[k].t);

			}

			//================================== [ 弾が着弾した際の処理 ] ==============================/

	        //弾のフラグが０なら、寿命を決定する -> （透明度のため）　
			if (!go->player.flickr.IsShot) {
				particle->particleFlicker[k].life = 10;
			}

			if (particle->particleFlicker[k].life > 0) {
				if (particle->particleFlicker[k].Color > 0xFF00FF00) {
					particle->particleFlicker[k].Color -= 255 / particle->particleFlicker[k].life;
				}
				else if (particle->particleFlicker[k].Color <= 0xFF00FF00) {
					particle->particleFlicker[k].isParticle = 0;
					particle->particleFlicker[k].life = 0;
					particle->particleFlicker[k].Color = 0xFF00FFFF;
				}
			}

		}


		SetFourVertexes(&particle->particleFlicker[k]);
		RenderingPipeline(&particle->particleFlicker[k], cr);
	}
	//============== [ チャージ ] ================/
	for (int i = 0;i < pC;i++) {
		if (key->keys[DIK_J]) {

			if (particle->particleCharge[i].isParticle == 0) {
				particle->particleCharge[i].isParticle = 1;
				particle->particleCharge[i].WorldPos.x = go->player.flickr.WorldPos.x + rand() % 181 - 90.0f;
				particle->particleCharge[i].WorldPos.y = go->player.flickr.WorldPos.y + rand() % 181 - 90.0f;

				particle->particleCharge[i].start = particle->particleCharge[i].WorldPos;
				

				particle->particleCharge[i].life = 20;
				particle->particleCharge[i].nowFrame = 0;
				particle->particleCharge[i].endFrame = float(particle->particleCharge[i].life);
				particle->particleCharge[i].Color = 0xFF00FFFF;
			}
		}
		/*if (go->player.flickr.ChargeTime <= 20 && go->player.flickr.ChargeTime > 0) {*/
			if (particle->particleCharge[i].isParticle == 1) {
				if (particle->particleCharge[i].life <= 0) {
					particle->particleCharge[i].isParticle = 0;
				}
				else if (particle->particleCharge[i].life > 0) {
					particle->particleCharge[i].life -= 1;
					Easing(&particle->particleCharge[i].WorldPos, particle->particleCharge[i].start.x, particle->particleCharge[i].start.y,
						particle->particleCharge[i].end.x, particle->particleCharge[i].end.y, &particle->particleCharge[i].nowFrame, particle->particleCharge[i].endFrame,
						&particle->particleCharge[i].t, 1.0f, materialOutCubic);
				}
			}
		/*}*/
			particle->particleCharge[i].end = go->player.flickr.WorldPos;
		SetFourVertexes(&particle->particleCharge[i]);
		RenderingPipeline(&particle->particleCharge[i], cr);
	}

}

//描画関数
void ParticleDraw(PARTICLE* particle) {
	Novice::SetBlendMode(BlendMode::kBlendModeAdd);


	for (int i = 0;i < pF;i++) {
		//ひものフラグが立っているなら描画する
		if (particle->particleFlicker[i].isParticle) {
			particle->particleFlicker[i].RectObjDraw();
		}
	}
	for (int i = 0;i < pC;i++) {
		//ひものフラグが立っているなら描画する
		if (particle->particleCharge[i].isParticle) {
			particle->particleCharge[i].RectObjDraw();
		}
	}


	Novice::SetBlendMode(BlendMode::kBlendModeNormal);
}
