#pragma once
#include"structuer.h"

void intializeScene(sceneChange* scene);
void initializeSounds(Sounds* sounds);
void initializeShake(Shake* shake);
void MaskChange(sceneChange* scene,GameObject*go,Key* key);
void CameraTransition_Start(GameObject* go, CameraRelated* cr,Key* key);
void ShakeFanction(Shake* shake, CameraRelated* cr, Key* key);
void SoundPlaySE(int playHandle, int soundHandle, float volume);
void SoundPlayBGM(int playHandleBgm, int soundHandleBgm, float volume);
void MaskDraw(sceneChange* scene);
void TitleChange(sceneChange* sceneState, Key* key, Sounds* sounds);
