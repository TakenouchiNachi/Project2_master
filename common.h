#pragma once

//ソースファイルの読み込み
#include<math.h>

//ヘッダーファイルの読み込み
#include"structuer.h"

//アフィン変換行列の生成
//（rotate:theta    translate: velocity）だと考えている
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);

//アフィン行列の計算をVector2型に変換
Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

Matrix3x3 Inverse(Matrix3x3 M);

Matrix3x3 MakeOrthoMatrix(Ortho O);

Matrix3x3 MakeViewportMatrix(Viewport V);

Matrix3x3 Multiply(Matrix3x3 a, Matrix3x3 b);


//オブジェクトの四つ角を計算する関数
void SetFourVertexes(RectangleObject* obj);

//ベクトルのX成分を求める関数(obj1←obj2のベクトル)
float FindVectorX(Vector2 obj1, Vector2 obj2);

//ベクトルのY成分を求める関数(obj1←obj2のベクトル)
float FindVectorY(Vector2 obj1, Vector2 obj2);

//ベクトル正規化関数
float NormalizeX(float vecx, float vecy);

float NormalizeY(float vecx, float vecy);

//矩形の当たり判定をとる関数(引数に対象の２つのオブジェクトを指定,trueなら1を返す falseなら0を返す)
int RectangleObjectCollision(RectangleObject* obj1, RectangleObject* obj2);

//2物体の距離を測る関数
float Distance(float obj1X, float obj1Y, float obj2X, float obj2Y);

//　Rキーリセット関数
void RkeyReset(GameObject* go, CameraRelated* cr, Key* key);