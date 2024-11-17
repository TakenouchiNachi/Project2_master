#pragma once

//ソースファイルの読み込み
#include <Novice.h>

//ヘッダーファイルの読み込み（アルファベット順）
#include"common.h"
#include"define.h"
#include"structuer.h"

//カメラ関連の初期化関数
void CameraInitialize(CameraRelated* cr);

//カメラの拡縮
void CameraUpdate(CameraRelated* cr, Key* key);


void RenderingPipeline(RectangleObject* obj, CameraRelated* cr);