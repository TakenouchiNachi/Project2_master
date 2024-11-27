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

			//画像の幅
			16.0f,
			16.0f,


			//色
			0xFF00FFDD,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
		particle->particleFlickerT[i].BaseInfoInitialize(
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

			//画像の幅
			16.0f,
			16.0f,

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

			//画像の幅
			16.0f,
			16.0f,

			//色
			WHITE,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
	}
	
	for (int i = 0;i < pCC;i++) {
		particle->particleMoya[i].BaseInfoInitialize(
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
			Novice::LoadTexture("./image./particle.jpg"),

			//画像の幅
			80.0f,
			80.0f,

			//色
			0x770077FF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
		particle->particleMoya[i].weight = 1.0f;
	}
	particle->particleHit.BaseInfoInitialize(
		//初期座標(x,y)
		640.0f,
		360.0f,

		//横幅、縦幅
		1280.0f,
		720.0f,

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
		Novice::LoadTexture("./image./Hit.png"),

		//画像の幅
		1280.0f,
		720.0f,

		//色
		0x770077FF,

		//オブジェクトタイプ（可動or不可動）
		ImMovable
	);
	for (int i = 0;i < 2;i++) {
		particle->bar[i].BaseInfoInitialize(
			//初期座標(x,y)
			0.0f,
			0.0f,

			//横幅、縦幅
			320.0f,
			192.0f,

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
			Novice::LoadTexture("./image./bar.png"),

			//画像の幅
			640.0f,
			192.0f,

			//色
			0xFFFFFFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
		particle->bar[i].ImagePos = { i * 320.0f,0 };
		particle->bar[0].WorldPos = { 192 + 160, 464 + 96 };
		particle->bar[1].WorldPos = { 767 + 160, 464 + 96 };
	}
}

void ParticleUpDate(PARTICLE* particle, CameraRelated* cr ,GameObject *go, Key *key) {


	//================= [ フリッカー ] ===================/
	for (int k = 0;k < pF;k++) {

		if (!go->player.flickr.IsShot) {
			if ((key->keys[DIK_A] || key->keys[DIK_D]) && (key->keys[DIK_W] || key->keys[DIK_S])) {
				particleIsKey = 3;
			}
			else if (key->keys[DIK_W] || key->keys[DIK_S]) {
				particleIsKey = 1;
			}
			else if (key->keys[DIK_A] || key->keys[DIK_D]) {
				particleIsKey = 2;
			}
		}
		

		//弾を撃っている時はパーティクルを出す
		if (go->player.flickr.IsShot) {
			particle->particleFlicker[k].isParticle = 1;
		}

		if (!go->player.flickr.IsShot) {
			particle->particleFlicker[k].life = 10;
			particle->particleFlickerT[k].life = 10;
			
		}

		//フラグが立っている間パーティクルの処理を施す
		if (particle->particleFlicker[k].isParticle == 1) {
			//=========================== [ ひもの作成 ] ================================/

			//== [ 制御点の生成 ] ==/
			Vector2 p1[control] = {};

			//== [ ひもの処理 ] ==/
			for (int i = 0;i < control;i++) {

				if (particleIsKey == 1) {
					particle->particleFlicker[k].Scale = { 0.75f, 4.0f };
					particle->particleFlickerT[k].Scale = { 0.75f, 4.0f };
					if(i == 0)
						particleRand = {20,0};
					if (i == 1)
						particleRand = { -50,0 };
				}
				if (particleIsKey == 2) {
					particle->particleFlicker[k].Scale = { 4.0f,0.75f };
					particle->particleFlickerT[k].Scale = { 4.0f,0.75f };
					if (i == 0)
						particleRand = {0,20};
					if (i == 1)
						particleRand = { 0,-50 };
				}
				if (particleIsKey == 3) {
					particle->particleFlicker[k].Scale = { 2.2f,2.2f };
					particle->particleFlickerT[k].Scale = { 2.2f,2.2f };
					if (i == 0)
						particleRand = {14,14};
					if (i == 1)
						particleRand = { -35,-35 };
				}

				p1[i].x = go->player.WorldPos.x + (go->player.flickr.WorldPos.x - go->player.WorldPos.x) / 2.0f + particleRand.x;
				p1[i].y = go->player.flickr.WorldPos.y + particleRand.y;
				SelectColor(&particle->particleFlicker[k].Color, rand() % 12);
				SelectColor(&particle->particleFlickerT[k].Color, rand() % 12);
				particle->particleFlicker[k].t = k / float(pF);//for文外でもいい説
				particle->particleFlicker[k].WorldPos = Bezier(&go->player.WorldPos, &p1[0], &go->player.flickr.WorldPos, particle->particleFlicker[k].t);
				particle->particleFlickerT[k].t = k / float(pF);//for文外でもいい説
				particle->particleFlickerT[k].WorldPos = Bezier(&go->player.WorldPos, &p1[1], &go->player.flickr.WorldPos, particle->particleFlickerT[k].t);

			}

			//================================== [ 弾が着弾した際の処理 ] ==============================/

	        //弾のフラグが０なら、寿命を決定する -> （透明度のため）　
			

			if (particle->particleFlicker[k].life > 0) {
				
				if (particle->particleFlicker[k].Color <= 0xFF00FF00) {
					particle->particleFlicker[k].isParticle = 0;
					particle->particleFlicker[k].life = 0;
					

					particle->particleFlickerT[k].isParticle = 0;
					particle->particleFlickerT[k].life = 0;
					
				}
			}

		}


		SetFourVertexes(&particle->particleFlicker[k]);
		RenderingPipeline(&particle->particleFlicker[k], cr);

		SetFourVertexes(&particle->particleFlickerT[k]);
		RenderingPipeline(&particle->particleFlickerT[k], cr);

	}

	//============== [ チャージ ] ================/
	for (int i = 0;i < pC;i++) {
		if (key->keys[DIK_J]) {

			if (particle->particleCharge[i].isParticle == 0) {

				particle->particleCharge[i].isParticle = 1;
				particle->particleCharge[i].WorldPos.x = go->player.flickr.WorldPos.x + rand() % 361 - 180.0f;
				particle->particleCharge[i].WorldPos.y = go->player.flickr.WorldPos.y + rand() % 361 - 180.0f;

				particle->particleCharge[i].start = particle->particleCharge[i].WorldPos;

				particle->particleCharge[i].life = 20;
				particle->particleCharge[i].Scale = { 1,1 };
				particle->particleCharge[i].nowFrame = 0;
				particle->particleCharge[i].endFrame = float(particle->particleCharge[i].life);
				particle->particleCharge[i].Color = 0xFF00FFFF;
			}
			
		}
		if (particle->particleCharge[i].isParticle == 1) {
			if (particle->particleCharge[i].life <= 0) {
				particle->particleCharge[i].isParticle = 0;
			}
			else if (particle->particleCharge[i].life > 0) {
				particle->particleCharge[i].life -= 1;
				Easing(&particle->particleCharge[i].WorldPos, particle->particleCharge[i].start.x, particle->particleCharge[i].start.y,
					particle->particleCharge[i].end.x, particle->particleCharge[i].end.y, &particle->particleCharge[i].nowFrame, particle->particleCharge[i].endFrame,
					&particle->particleCharge[i].t, 1.0f, materialOutCubic);
				particle->particleCharge[i].nowFrame -= 1;
				Easing(&particle->particleCharge[i].Scale, 0.25f, 0.25f,
					2.0f, 2.0f, &particle->particleCharge[i].nowFrame, particle->particleCharge[i].endFrame,
					&particle->particleCharge[i].t, 1.0f, materialOutBack);
			}
		}
		
		particle->particleCharge[i].end = go->player.flickr.WorldPos;
		SetFourVertexes(&particle->particleCharge[i]);
		RenderingPipeline(&particle->particleCharge[i], cr);
	}

	Field field = {};

	//もやもやのパーティクル
	for (int i = 0;i < pCC;i++) {

		field.pos = go->player.WorldPos;
		field.wid = { 1280,720 };

		//エミッターが自機の位置
		if (particle->particleMoya[i].life < 0) {
			particle->particleMoya[i].WorldPos.x = go->player.WorldPos.x + ((go->player.Width + 50 + rand()%41-25) * cosf((i * (360.0f / pCC)) / 180.0f * 3.14f));
			particle->particleMoya[i].WorldPos.y = go->player.WorldPos.y + ((go->player.Height + 50 + rand()%41-25) * sinf((i * (360.0f / pCC)) / 180.0f * 3.14f));
			particle->particleMoya[i].life = 15 + i % 30;
			particle->particleMoya[i].Acceleration = {};
			particle->particleMoya[i].Velocity = {};
			particle->particleMoya[i].Color = 0x020012FF;
			particle->particleMoya[i].Scale = { 1.5f,1.5f };
		}
		else if (particle->particleMoya[i].life >= 0) {
			if (key->preKeys[DIK_W] || key->preKeys[DIK_A] || key->preKeys[DIK_S] || key->preKeys[DIK_D]) {
				particle->particleMoya[i].life -= 1;
			}
			particle->particleMoya[i].Scale.x += 0.025f;
			particle->particleMoya[i].Scale.y += 0.025f;
			field.F.x = -NormalizeX(go->player.WorldPos.x - particle->particleMoya[i].WorldPos.x, go->player.WorldPos.y - particle->particleMoya[i].WorldPos.y) * 0.00375f;
			field.F.y = -NormalizeY(go->player.WorldPos.x - particle->particleMoya[i].WorldPos.x, go->player.WorldPos.y - particle->particleMoya[i].WorldPos.y) * 0.00375f;
			Effect(&particle->particleMoya[i], &field);
		}

		SetFourVertexes(&particle->particleMoya[i]);
		RenderingPipeline(&particle->particleMoya[i], cr);
	}

	//ヒットの見た目
	if (go->player.GetDamage) {
		particle->particleHit.life = 51;
		particle->particleHit.Color = 0xFF0000FF;
	}

	if (particle->particleHit.life > 0) {
		particle->particleHit.life -= 1;
		particle->particleHit.Color -= 0x05000005;
	}
	else if (particle->particleHit.life <= 0) {
		particle->particleHit.Color = 0xFF000000;
		go->player.GetDamage = false;
	}
	/*SetFourVertexes(&particle->particleHit);
	RenderingPipeline(&particle->particleHit, cr);*/
}

//描画関数
void ParticleDraw(PARTICLE* particle) {
	Novice::SetBlendMode(BlendMode::kBlendModeAdd);
	int randDraw = 0;
	
	for (int i = 0;i < pF;i++) {
		//ひものフラグが立っているなら描画する
		randDraw = rand() % 2;
		if (particle->particleFlicker[i].isParticle) {
			if (randDraw) {
				particle->particleFlicker[i].RectObjDraw();
				particle->particleFlickerT[i].RectObjDraw();
			}
		}
	}
	for (int i = 0;i < pC;i++) {
		//ひものフラグが立っているなら描画する
		if (particle->particleCharge[i].isParticle) {
			particle->particleCharge[i].RectObjDraw();
		}
	}

	for (int i = 0;i < pCC;i++) {
		
			particle->particleMoya[i].RectObjDraw();
		
	}

	

	Novice::SetBlendMode(BlendMode::kBlendModeNormal);
}
