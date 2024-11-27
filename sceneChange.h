#pragma once
#include"structuer.h"

void intializeScene(sceneChange* scene);
void initializeSounds(Sounds* sounds);
void initializeShake(Shake* shake);
void initializeTitle(Title* title);
void MaskChange(sceneChange* scene,GameObject*go,Key* key);
void CameraTransition_Start(GameObject* go, CameraRelated* cr,Sounds* sounds);
void ShakeFanction(Shake* shake, CameraRelated* cr, Key* key);
void SoundPlaySE(int playHandle, int soundHandle, float volume);
void SoundPlayBGM(int playHandleBgm, int soundHandleBgm, float volume);
void MaskDraw(sceneChange* scene);
void TitleChange(sceneChange* scene, Key* key, Sounds* sounds, GameObject* go, CameraRelated* cr);
void TitleUpdate(Title* title);
void TitleDraw(Title* title, sceneChange* scene);
void SetColor(unsigned int* color, int R, int G, int B, int A);
//void ToGamePlay(sceneChange* scene);
 