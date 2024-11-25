#pragma once
#include "structuer.h"
#include"enum.h"
#include"easing.h"
#include"common.h"
#include"camera.h"

void TitleInitialize(TitleScene *T);

void TitleSceneUpDate(TitleScene *T, Key *key, CameraRelated* cr);

void TitleDraw(TitleScene* T);