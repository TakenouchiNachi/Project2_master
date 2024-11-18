
//ソースファイルの読み込み
#include<math.h>

//ヘッダーファイルの読み込み
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

	//右手
	go->enemy.righthand.BaseInfoInitialize(
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
	go->enemy.lefthand.BaseInfoInitialize(
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
}



//行動パターンを決める関数
void DecisionMoveType_Ver1(GameObject* go) {

}





//更新処理
void EnemyUpdate(GameObject* go,CameraRelated* cr) {
	  
	//行動パターンの決定関数

	//四つ角の更新

	//頭
	SetFourVertexes(&go->enemy);
	RenderingPipeline(&go->enemy, cr);

	//右手
	SetFourVertexes(&go->enemy.righthand);
	RenderingPipeline(&go->enemy.righthand, cr);

	//左手
	SetFourVertexes(&go->enemy.lefthand);
	RenderingPipeline(&go->enemy.lefthand, cr);
}


//描画関数
void EnemyDraw(GameObject* go) {
	go->enemy.RectObjDraw();
	go->enemy.righthand.RectObjDraw();
	go->enemy.lefthand.RectObjDraw();
}