#pragma once

#include "structuer.h"
#include"enum.h"
#include"enemy.h"
#include"common.h"
#include"camera.h"
#include "player.h"
#include "rope.h"
#include "easing.h"

void MakeAfterImage(RectangleObject* obj, Vector2 go, Afterimage* af, int afterImageNum, int* afterNum, int* inter);

void AfterimageInitialize(AFTERIMAGE* Af);

void AfterimageUpDate(AFTERIMAGE* Af, PARTICLE* p, CameraRelated* cr, GameObject* go);


void AfterimageDraw(AFTERIMAGE* Af, PARTICLE* p, GameObject* go);