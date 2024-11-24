#pragma once

#include<Novice.h>

#include"define.h"

/*============================================
				型の作成
============================================*/

struct Vector2 {
	float x;
	float y;
};

struct IntVector2 {
	int x;
	int y;
};

struct Matrix3x3 {
	float m[3][3];
};


/*============================================
				基本クラス
============================================*/

//オブジェクトの基本情報をまとめた構造体
struct ObjectBaseInfo {

	//矩形の「scale」「rotate」「transrate」を制御する行列
	Matrix3x3 WorldMatrix;
	Matrix3x3 ScreenMatrix;

	/*  座標系  */
	Vector2 ScreenPos;
	Vector2 WorldPos;
	Vector2 LocalPos;

	/*  サイズ関連  */
	Vector2 Scale;
	float Width;
	float Height;

	/*  動き関連  */
	Vector2 Acceleration;
	Vector2 Velocity;
	Vector2 Vector;
	float Speed;

	Vector2 ShakePos;

	/*  描画関連  */
	//画像の描画する座標
	Vector2 ImagePos;

	//アニメーションに用いる
	float DrawWidth;
	float DrawHeight;

	//回転に用いる
	float Degree;
	float Theta;

	//画像
	int Image;
	int Color;


};

//オブジェクトの四つ角を使用目的毎に宣言する構造体
struct FoursVertxes {

	//原点周りの四つ角
	Vector2 OriginLeftTop;
	Vector2 OriginLeftBottom;
	Vector2 OriginRightTop;
	Vector2 OriginRightBottom;

	//World座標で処理される四つ角
	Vector2 WorldLeftTop;
	Vector2 WorldLeftBottom;
	Vector2 WorldRightTop;
	Vector2 WorldRightBottom;

	//マップとの当たり判定
	IntVector2 MapCollisionLeftTop;
	IntVector2 MapCollisionLeftBottom;
	IntVector2 MapCollisionRightTop;
	IntVector2 MapCollisionRightBottom;

	//矩形の当たり判定用
	Vector2 CollisionLeftTop;
	Vector2 CollisionLeftBottom;
	Vector2 CollisionRightTop;
	Vector2 CollisionRightBottom;

	//描画用
	Vector2 DrawLeftTop;
	Vector2 DrawLeftBottom;
	Vector2 DrawRightTop;
	Vector2 DrawRightBottom;
};

/*============================================
			基本クラスをまとめる
============================================*/

//矩形のオブジェクトが持つ情報をまとめた構造体
struct RectangleObject : ObjectBaseInfo, FoursVertxes {


	//オブジェクトの種類を判別する変数
	int ObjectType;


	/*===========================
		   メンバー関数
	============================*/

	void BaseInfoInitialize(float Ini_PosX, float Ini_PosY, float Ini_width, float Ini_height, float Ini_acceX, float Ini_acceY, float Ini_veloX, float Ini_veloY, float Ini_vecX, float Ini_vecY, float Ini_speed, int Ini_image, int Ini_color,int ObjType) {

		//座標
		WorldPos.x = static_cast<float>(Ini_PosX);
		WorldPos.y = static_cast<float>(Ini_PosY);

		ScreenPos = {};


		//大きさ
		Scale = { 1.0f,1.0f };
		Width = static_cast<float>(Ini_width);
		Height = static_cast<float>(Ini_height);


		//速度
		Acceleration.x = static_cast<float>(Ini_acceX);
		Acceleration.y = static_cast<float>(Ini_acceY);

		Velocity.x = static_cast<float>(Ini_veloX);
		Velocity.y = static_cast<float>(Ini_veloY);

		Vector.x = static_cast<float>(Ini_vecX);
		Vector.y = static_cast<float>(Ini_vecY);

		Speed = static_cast<float>(Ini_speed);

		ShakePos = {};

		//描画関係
		ImagePos = {};

		DrawWidth = static_cast<float>(Ini_width);
		DrawHeight = static_cast<float>(Ini_height);

		Degree = 0.0f;
		Theta = 0.0f;

		Image = Ini_image;
		Color = Ini_color;

		ObjectType = ObjType;
	}

	//描画関数
	void RectObjDraw() {

		Novice::DrawQuad(
			//左上
			static_cast<int>(DrawLeftTop.x + ShakePos.x),
			static_cast<int>(DrawLeftTop.y + ShakePos.y),

			//右上
			static_cast<int>(DrawRightTop.x + ShakePos.x),
			static_cast<int>(DrawRightTop.y + ShakePos.y),

			//左下
			static_cast<int>(DrawLeftBottom.x + ShakePos.x),
			static_cast<int>(DrawLeftBottom.y + ShakePos.y),

			//右下
			static_cast<int>(DrawRightBottom.x + ShakePos.x),
			static_cast<int>(DrawRightBottom.y + ShakePos.y),

			//画像上の座標
			static_cast<int>(ImagePos.x),
			static_cast<int>(ImagePos.y),

			//横幅、縦幅
			static_cast<int>(Width),
			static_cast<int>(Height),

			//テクスチャハンドル
			Image,

			//色
			Color
		);
	}
};


/*============================================
			　　 発展クラス
============================================*/
struct Flickr :RectangleObject {

	//発射状態か判別用の変数
	int IsShot;

	//可動オブジェクトと当たったか判別用の変数
	int IsMovableObjHit;

	//不可動オブジェクトと当たったか判別用の変数
	int IsHit;

	//チャージ時間
	int ChargeTime;

	//射程限界距離(チャージで伸びる)
	int RangeLimit;
};


//プレイヤーのライフや残機の宣言
const int HPNum = 3;
const int RemainingLifeNum = 3;

struct Player :RectangleObject {

	//可動オブジェクトを保持しているかのフラグ
	int IsHoldObject;

	//プレイ中のライフ
	RectangleObject HP[HPNum];
	int HPGH;

	//残機
	RectangleObject RemainingLife[RemainingLifeNum];
	int RemainingLifeGH; 

	Flickr flickr;
};

//ボスの手の構造体
struct Hand :RectangleObject {

	//顔の横の固定位置
	Vector2 FixedPosition;

	//生存フラグ
	int IsAlive;

	//攻撃判定を持っているか
	int IsAggression;

	//イージング用の変数
	float t;
	Vector2 EasingStartPos;
	float NowFrame;
};

struct Bullet :RectangleObject{

	//フラグ
	int IsShot;

	//攻撃判定を持つか
	int IsAggression;
};


/*==============================
		  攻撃の構造体
 ==============================*/
//台パン攻撃の構造体
struct DaiPanStruct :RectangleObject {

	//現在のフレームを格納する変数
	int CurrentFrame;
};

struct RocketPunchstruct : RectangleObject {

	//現在のフレームを格納する変数
	int CurrentFrame;
};

struct Enemy : RectangleObject {
	//一週目か二週目か判断する変数
	int LapNum;

	//手の構造体（enumで管理）
	Hand hand[2];

	//弾の構造体
	Bullet RightBullet[4];
	Bullet LeftBullet[4];

	//発射間隔
	int ShotIntervalTime;
	
	//発射数カウント
	int ShotCount;

	//発射上限数
	int ShotNumLimit;

	//攻撃中か否かを判別する変数
	int IsAttack;

	//動きの番号を格納する変数
	int MoveType;

	//両手・片手・手なし　の状態を格納する変数
	int Condition;

	//攻撃の構造体
	DaiPanStruct DaiPanInfo;
	RocketPunchstruct RocketPunchInfo;

	//各攻撃の現在フレ―ムを取得する用の変数9
	int BulletShotCurrentFrame;

	//イージング用の変数
	float t;
	float NowFrame;
	Vector2 EasingStartPos;

	//フレームカウント
	int FlameCount;

};

struct MapChip : RectangleObject {
	int Map;
	int IsHit;
};

struct MovableObject :RectangleObject{
	int IsShot;

};

/*============================================
			発展クラスをまとめる
============================================*/
struct GameObject {
	Player player;
	Enemy enemy;
	MapChip mapchip[VerBlockNum][HolBlockNum];
	MovableObject movableobject;
};


/*============================================
			　 その他の構造体
============================================*/


struct Key {
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
};



//カメラ関連
struct Ortho {

	//初期の描画範囲
	float InitialRight;
	float InitialLeft;
	float InitialTop;
	float InitialBottom;

	//拡縮後の描画範囲
	float Right;
	float Left;
	float Top;
	float Bottom;

	Matrix3x3 orthoMatrix;

	//ズームイン・ズームアウト用の拡大率を格納する変数
	float Scale;
};

struct Viewport {
	float Width;
	float Height;
	float Left;
	float Top;

	Matrix3x3 viewportMatrix;
};

//カメラ関連の構造体をまとめる
struct CameraRelated {

	Ortho O;

	Viewport view;

	Matrix3x3 camera;
  
	Vector2 CameraPos;
};

//==================================
//　　　追加（パーティクル）
//==================================

//================== [ 残像の構造体 ] ================/
const int AFINum = 7;
struct Afterimage{
	int afterNum = 0;
	Vector2 afterImagePos[AFINum] = {};
	int aIColor[AFINum] = {};

	void MakeAfterImage(Vector2 *go, Afterimage *ai, int num) {
		for (int i = 0;i < ai->afterNum;i++) {

			if (go->x != ai->afterImagePos[i].x || go->y != ai->afterImagePos[i].y) {
				if (ai->afterNum == i) {
					ai->afterImagePos[i] = *go;
					ai->aIColor[i] = 0xFFFFFFFF;
					ai->afterNum += 1;
					if (ai->afterNum >= num - 1) {
						ai->afterNum = 0;
					}
					break;
				}
			}
		}
	}

};

//================= { パーティクルの構造体 ] ===================/
struct Particle : RectangleObject , Afterimage{

	Vector2 start = {};
	Vector2 end;
	float weight;
	float nowFrame = 0;
	float endFrame;
	float t;
	int life;
	int isParticle = 0;
};

//パーティクルの種類

//エドみたいなパーティクル
  const int pF = 100;
//| 紐を作成する際の制御点の数(あくまで紐の数を増やすためのもの)
  const int control = 1;
//|振れ幅
  inline IntVector2 particleRand = { 0,0 };
  inline int particleIsKey = 0;

//プレイヤー周りのパーティクル
const int pC = 10;

//パーティクルの処理をまとめるために合併したかった
struct PARTICLE {
	Particle particleFlicker[pF];
	Particle particleCharge[pC];
};

//==================================
//　　　　　　重力場
//==================================

struct Field {
	Vector2 pos;
	Vector2 wid;
	Vector2 F;//重力
};