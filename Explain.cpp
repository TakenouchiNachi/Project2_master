
#include<Novice.h>

#include"structuer.h"
#include"common.h"
#include"enum.h"
#include"enemy.h"


void ExplainIitialize(AllExplain* ex) {

	ex->J.BaseInfoInitialize(
		//初期座標(x,y)
		20.0f,
		680.0f,

		//横幅、縦幅
		40.0f,
		40.0f,

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
		Novice::LoadTexture("./image./J.png"),

		//画像の幅
		100.0f,
		50.0f,

		//色
		0xffffffff,

		//オブジェクトタイプ（可動or不可動）
		ImMovable
	);



	ex->explain.BaseInfoInitialize(

		//初期座標(x,y)
		20.0f,
		680.0f,

		//横幅、縦幅
		100.0f,
		50.0f,

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
		Novice::LoadTexture("./image./Explain.png"),

		//画像の幅
		100.0f,
		50.0f,

		//色
		0xffffffff,

		//オブジェクトタイプ（可動or不可動）
		ImMovable
	);
}

void ExplainUpdate(GameObject* go, AllExplain* ex) {
	//画像描画範囲の変更
	if (go->enemy.Condition == BothHands) {
		ex->explain.ImagePos.x = 0.0f;
	}
	else {
		ex->explain.ImagePos.x = 100.0f;
	}

}

void ExplainDraw( AllExplain* ex) {

	Novice::DrawQuad(
		static_cast<int>(120.0f - ex->J.Width / 2.0f),
		static_cast<int>(680.0f - ex->J.Height / 2.0f),

		static_cast<int>(120.0f + ex->J.Width / 2.0f),
		static_cast<int>(680.0f - ex->J.Height / 2.0f),

		static_cast<int>(120.0f - ex->J.Width / 2.0f),
		static_cast<int>(680.0f + ex->J.Height / 2.0f),

		static_cast<int>(120.0f + ex->J.Width / 2.0f),
		static_cast<int>(680.0f + ex->J.Height / 2.0f),

		static_cast<int>(ex->J.ImagePos.x),
		static_cast<int>(ex->J.ImagePos.y),

		100, 50,

		ex->J.Image,

		WHITE
	);


	Novice::DrawQuad(
		static_cast<int>(200.0f - ex->explain.Width/2.0f),
		static_cast<int>(680.0f - ex->explain.Height / 2.0f),

		static_cast<int>(200.0f + ex->explain.Width / 2.0f),
		static_cast<int>(680.0f - ex->explain.Height / 2.0f),

		static_cast<int>(200.0f - ex->explain.Width / 2.0f),
		static_cast<int>(680.0f + ex->explain.Height / 2.0f),

		static_cast<int>(200.0f + ex->explain.Width / 2.0f),
		static_cast<int>(680.0f + ex->explain.Height / 2.0f),

		static_cast<int>(ex->explain.ImagePos.x),
		static_cast<int>(ex->explain.ImagePos.y),

		100,50,

		ex->explain.Image,

		WHITE
	);
}