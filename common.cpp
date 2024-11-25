//ソースファイルの読み込み
#include<math.h>

//ヘッダーファイルの読み込み
#include"camera.h"
#include"enemy.h"
#include"structuer.h"
#include"common.h"
#include"define.h"
#include"player.h"
#include"stage.h"



//アフィン変換行列の生成
//（rotate:theta    translate: WorldPos)
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {

	Matrix3x3 result = {};

	result.m[0][0] = scale.x * cosf(rotate);
	result.m[0][1] = scale.x * sinf(rotate);

	result.m[1][0] = scale.y * (-sinf(rotate));
	result.m[1][1] = scale.y * (cosf(rotate));

	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	result.m[2][2] = 1.0f;

	return result;
}

Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

	result.x /= w;
	result.y /= w;

	return result;
}


Matrix3x3 Inverse(Matrix3x3 M) {

	float a11 = M.m[0][0]; float a12 = M.m[0][1]; float a13 = M.m[0][2];
	float a21 = M.m[1][0]; float a22 = M.m[1][1]; float a23 = M.m[1][2];
	float a31 = M.m[2][0]; float a32 = M.m[2][1]; float a33 = M.m[2][2];
	float revival = a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a13 * a22 * a31 - a12 * a21 * a33 - a11 * a23 * a32;
	Matrix3x3 W = {};
	W.m[0][0] = a22 * a33 - a23 * a32; W.m[0][1] = -(a12 * a33 - a13 * a32); W.m[0][2] = a12 * a23 - a13 * a22;
	W.m[1][0] = -(a21 * a33 - a23 * a31); W.m[1][1] = a11 * a33 - a13 * a31; W.m[1][2] = -(a11 * a23 - a13 * a21);
	W.m[2][0] = a21 * a32 - a22 * a31; W.m[2][1] = -(a11 * a32 - a12 * a31); W.m[2][2] = a11 * a22 - a12 * a21;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			W.m[i][j] /= revival;
		}
	}

	return W;

}

Matrix3x3 MakeOrthoMatrix(Ortho O) {
	return{
		2.0f / (O.Right - O.Left),  0,  0,
		0,  2.0f / (O.Top - O.Bottom),  0,
		(O.Left + O.Right) / (O.Left - O.Right),  (O.Top + O.Bottom) / (O.Bottom - O.Top),  1
	};
}

Matrix3x3 MakeViewportMatrix(Viewport V) {
	return{
	   V.Width / 2,  0,  0,
	   0,  -(V.Height / 2),  0,
	   V.Left + (V.Width / 2),  V.Top + (V.Height / 2),  1
	};
}

Matrix3x3 Multiply(Matrix3x3 a, Matrix3x3 b) {
	return{
		a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0],  a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1], 0,
		a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0],  a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1], 0,
		a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0],  a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1], 1
	};
}




//オブジェクトの四つ角を計算する関数
void SetFourVertexes(RectangleObject* obj) {

	//行列の作成
	obj->WorldMatrix = MakeAffineMatrix(obj->Scale,obj->Theta,obj->WorldPos);


	//原点周りの四つ角
	obj->OriginLeftTop.x = -obj->Width / 2.0f;
	obj->OriginLeftTop.y = +obj->Height / 2.0f;

	obj->OriginLeftBottom.x = -obj->Width / 2.0f;
	obj->OriginLeftBottom.y = -obj->Height / 2.0f;

	obj->OriginRightTop.x = +obj->Width / 2.0f;
	obj->OriginRightTop.y = +obj->Height / 2.0f;

	obj->OriginRightBottom.x = +obj->Width / 2.0f;
	obj->OriginRightBottom.y = -obj->Height / 2.0f;


	//拡縮・回転・移動処理を行う四つ角
	obj->WorldLeftTop = Transform(obj->OriginLeftTop, obj->WorldMatrix);
	obj->WorldLeftBottom = Transform(obj->OriginLeftBottom, obj->WorldMatrix);
	obj->WorldRightTop = Transform(obj->OriginRightTop, obj->WorldMatrix);
	obj->WorldRightBottom = Transform(obj->OriginRightBottom, obj->WorldMatrix);


	//マップとの衝突判定処理を行う四つ角
	obj->MapCollisionLeftTop.x = int(obj->WorldPos.x - obj->Width / 2.0f) / BlockSize;
	obj->MapCollisionLeftTop.y = int(obj->WorldPos.y - obj->Height / 2.0f) / BlockSize;

	obj->MapCollisionLeftBottom.x = int(obj->WorldPos.x - obj->Width / 2.0f) / BlockSize;
	obj->MapCollisionLeftBottom.y = int(obj->WorldPos.y + obj->Height / 2.0f - 1) / BlockSize;

	obj->MapCollisionRightTop.x = int(obj->WorldPos.x + obj->Width / 2.0f - 1) / BlockSize;
	obj->MapCollisionRightTop.y = int(obj->WorldPos.y - obj->Height / 2.0f) / BlockSize;

	obj->MapCollisionRightBottom.x = int(obj->WorldPos.x + obj->Width / 2.0f - 1) / BlockSize;
	obj->MapCollisionRightBottom.y = int(obj->WorldPos.y + obj->Height / 2.0f - 1) / BlockSize;


	//矩形の衝突判定処理を行う四つ角
	obj->CollisionLeftTop.x = obj->WorldPos.x - obj->Width / 2.0f;
	obj->CollisionLeftTop.y = obj->WorldPos.y - obj->Height / 2.0f;

	obj->CollisionLeftBottom.x = obj->WorldPos.x - obj->Width / 2.0f;
	obj->CollisionLeftBottom.y = obj->WorldPos.y + obj->Height / 2.0f;

	obj->CollisionRightTop.x = obj->WorldPos.x + obj->Width / 2.0f;
	obj->CollisionRightTop.y = obj->WorldPos.y - obj->Height / 2.0f;

	obj->CollisionRightBottom.x = obj->WorldPos.x + obj->Width / 2.0f;
	obj->CollisionRightBottom.y = obj->WorldPos.y + obj->Height / 2.0f;


	//描画用の四つ角
	//obj->DrawLeftTop.x = obj->ScreenPos.x - obj->Width / 2.0f;
	//obj->DrawLeftTop.y = obj->ScreenPos.y - obj->Height / 2.0f;

	//obj->DrawLeftBottom.x = obj->ScreenPos.x - obj->Width / 2.0f;
	//obj->DrawLeftBottom.y = obj->ScreenPos.y + obj->Height / 2.0f;

	//obj->DrawRightTop.x = obj->ScreenPos.x + obj->Width / 2.0f;
	//obj->DrawRightTop.y = obj->ScreenPos.y - obj->Height / 2.0f;

	//obj->DrawRightBottom.x = obj->ScreenPos.x + obj->Width / 2.0f;
	//obj->DrawRightBottom.y = obj->ScreenPos.y + obj->Height / 2.0f;
}


/*====================================
		  ベクトル関数
 ====================================*/
 //ベクトルのX成分を求める関数(obj1←obj2のベクトル)
float FindVectorX(Vector2 obj1, Vector2 obj2) {
	float vecX;

	vecX = obj1.x - obj2.x;

	return vecX;
}

//ベクトルのY成分を求める関数(obj1←obj2のベクトル)
float FindVectorY(Vector2 obj1, Vector2 obj2) {
	float vecY;

	vecY = obj1.y - obj2.y;

	return vecY;

}


/*====================================
		  ベクトル正規化関数
 ====================================*/
float NormalizeX(float vecx, float vecy) {
	float length = sqrtf((vecx * vecx) + (vecy * vecy));

	if (!length == 0) {
		return  vecx / length;
	}
	else {
		return vecx;
	}
}

float NormalizeY(float vecx, float vecy) {
	float length = sqrtf((vecx * vecx) + (vecy * vecy));

	if (!length == 0) {
		return  vecy / length;
	}
	else {
		return vecy;
	}
}

//矩形の当たり判定をとる関数(引数に対象の２つのオブジェクトを指定,trueなら1を返す falseなら0を返す)
int RectangleObjectCollision(RectangleObject* obj1, RectangleObject* obj2) {

	int result;
	
	if (obj1->CollisionLeftTop.x < obj2->CollisionRightBottom.x && obj2->CollisionLeftTop.x < obj1->CollisionRightBottom.x &&
		obj1->CollisionLeftTop.y < obj2->CollisionRightBottom.y && obj2->CollisionLeftTop.y < obj1->CollisionRightBottom.y) {

		result = true;

	}
	else {
		result = false;
	}

	return result;
}


/*=======================================
          2物体の距離を測る関数
 =======================================*/
float Distance(Vector2 obj1, Vector2 obj2) {
	float distance;

	float DifferX = obj1.x - obj2.x;
	float DifferY = obj1.y - obj2.y;


	distance = sqrtf((DifferX * DifferX) + (DifferY * DifferY));

	return distance;
}


//　Rキーリセット関数
void RkeyReset(GameObject* go,CameraRelated* cr, Key* key) {
	if (key->keys[DIK_R] && !key->preKeys[DIK_R]) {
		PlayerInitialize(go);
		
		StageInitialize(go);
		EnemyInitialize(go);
		CameraInitialize(cr);

	}
}