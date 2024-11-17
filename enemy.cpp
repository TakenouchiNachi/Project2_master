
//ソースファイルの読み込み
#include<math.h>

//ヘッダーファイルの読み込み
#include"structuer.h"
#include"enum.h"
#include"common.h"


//初期化関数
void EnemyInitialize(GameObject* go) {
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
}

//更新処理
void EnemyUpdate(GameObject* go) {
	  
	//四つ角の更新
	SetFourVertexes(&go->enemy);

}


//描画関数
void EnemyDraw(GameObject* go) {
	go->enemy.RectObjDraw();
}