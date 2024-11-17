//ソースファイルの読み込み
#include<math.h>
#include<Novice.h>

//ヘッダーファイルの読み込み
#include"common.h"
#include"structuer.h"
#include"define.h"
#include"enum.h"
#include"player.h"

//初期化関数
void StageInitialize(GameObject* go) {


	//マップチップの初期化
	for (int i = 0; i < VerBlockNum; ++i) {
		for (int j = 0; j < HolBlockNum; ++j) {

			go->mapchip[i][j].BaseInfoInitialize(
				//初期座標(x,y)
				static_cast<float>((j * BlockSize) + BlockSize / 2),
				static_cast<float>((i * BlockSize) + BlockSize / 2),

				//横幅、縦幅
				static_cast<float>(BlockSize),
				static_cast<float>(BlockSize),

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
				0.0f,

				//画像
				Novice::LoadTexture("./image./map.png"),

				//色
				WHITE,

				//オブジェクトタイプ（可動or不可動）
				ImMovable
			);

			go->mapchip[i][j].ScreenPos.x = static_cast<float>((j * BlockSize) + BlockSize / 2);
			go->mapchip[i][j].ScreenPos.y = static_cast<float>((i * BlockSize) + BlockSize / 2);
			go->mapchip[i][j].IsHit = false;

		}
	}

	//MovableObjectの初期化
	go->movableobject.BaseInfoInitialize(

		//初期座標(x,y)
		800.0f,
		700.0f,

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
		10.0f,

		//画像
		Novice::LoadTexture("./image./MovableObject.png"),

		//色
		WHITE,

		//オブジェクトタイプ（可動or不可動）
		Movable
	);

	go->movableobject.IsShot = false;
}

//ステージ情報の更新
void StageGenerate(GameObject* go) {

	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};

	for (int i = 0; i < VerBlockNum; ++i) {
		for (int j = 0; j < HolBlockNum; ++j) {
			
			go->mapchip[VerBlockNum - 1 - i][j].Map = map[i][j];
		}
	}

	//行列の作成・四つ角の更新
	for (int i = 0; i < VerBlockNum; ++i) {
		for (int j = 0; j < HolBlockNum; ++j) {

			SetFourVertexes(&go->mapchip[i][j]);


			//画像上の座標の始点の更新
			go->mapchip[i][j].ImagePos.x = static_cast<float>(BlockSize * go->mapchip[i][j].Map);
		}
	}
}


void  MovableObjectHold(GameObject* go) {
	if (go->player.IsHoldObject) {
		go->movableobject.WorldPos.x = go->player.WorldPos.x + BlockSize; 
		go->movableobject.WorldPos.y = go->player.WorldPos.y + BlockSize;
	}
}


//可動オブジェクトの更新処理関数
void MovableObjectUpdate(GameObject* go,Key* key) {

	//四つ角の更新
	SetFourVertexes(&go->movableobject);


	//保持している時の処理
	MovableObjectHold(go);

	MovableObjectShot(go, key);
}

//描画関数
void StageDraw(GameObject* go) {
	for (int i = 0; i < VerBlockNum; ++i) {
		for (int j = 0; j < HolBlockNum; ++j) {

			go->mapchip[i][j].RectObjDraw();
		}
	}
}

//可動オブジェクトの描画関数
void MovableObjectDraw(GameObject* go) {

	go->movableobject.RectObjDraw();

}