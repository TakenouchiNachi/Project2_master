
//ソースファイルの読み込み
#include <Novice.h>

//ヘッダーファイルの読み込み（アルファベット順）
#include"common.h"
#include"define.h"
#include"structuer.h"

//カメラ関連の初期化関数
void CameraInitialize(CameraRelated* cr) {

	cr->camera = {
		1,0,0,
		0,1,0,
		-640,-360,1
	};

	cr->O.InitialLeft = -640.0f;
	cr->O.InitialTop = 360.0f;
	cr->O.InitialRight = 640.0f;
	cr->O.InitialBottom = -360.0f;

	cr->O.Scale = 1.0f;



	cr->view.Left = 0.0f;
	cr->view.Top = 0.0f;
	cr->view.Width = 1280.0f;
	cr->view.Height = 720.0f;
}


//カメラの拡縮
void CameraUpdate(CameraRelated* cr, Key* key) {

	cr->O.Left = cr->O.InitialLeft * cr->O.Scale;
	cr->O.Top = cr->O.InitialTop * cr->O.Scale;
	cr->O.Right = cr->O.InitialRight * cr->O.Scale;
	cr->O.Bottom = cr->O.InitialBottom * cr->O.Scale;


	if (key->keys[DIK_UP]) {
		cr->O.Scale += 0.01f;
	}
	if (key->keys[DIK_DOWN]) {
		cr->O.Scale -= 0.01f;
	}
}


void RenderingPipeline(RectangleObject* obj, CameraRelated* cr) {

	Matrix3x3 viewMatrix = Inverse(cr->camera);

	cr->O.orthoMatrix = MakeOrthoMatrix(cr->O);

	cr->view.viewportMatrix = MakeViewportMatrix(cr->view);


	Matrix3x3 wvpVpMatrix = Multiply(obj->WorldMatrix, cr->camera);

	wvpVpMatrix = Multiply(wvpVpMatrix, cr->O.orthoMatrix);

	wvpVpMatrix = Multiply(wvpVpMatrix, cr->view.viewportMatrix);


	//描画用の四つ角
	obj->DrawLeftTop = Transform(obj->OriginLeftTop, wvpVpMatrix);
	obj->DrawLeftBottom = Transform(obj->OriginLeftBottom, wvpVpMatrix);
	obj->DrawRightTop = Transform(obj->OriginRightTop, wvpVpMatrix);
	obj->DrawRightBottom = Transform(obj->OriginRightBottom, wvpVpMatrix);

}