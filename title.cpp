#include "title.h"

void TitleInitialize(TitleScene *T) {

	T->titleScene.BaseInfoInitialize(
		//初期座標(x,y)
		640.0f,
		180.0f,

		//横幅、縦幅
		640.0f,
		180.0f,

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
		2.0f,

		//画像
		Novice::LoadTexture("./image./RightHand_ver3.png"),

		//画像の幅
		800.0f,
		800.0f,

		//色
		0xFFFFFFFF,

		//オブジェクトタイプ（可動or不可動）
		ImMovable
	);

	for (int i = 0;i < 5;i++) {
		T->titleSpace[i].BaseInfoInitialize(
			//初期座標(x,y)
			0.0f,
			0.0f,

			//横幅、縦幅
			40.0f,
			40.0f,

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
			2.0f,

			//画像
			Novice::LoadTexture("./image./RightHand_ver3.png"),

			//画像の幅
			800.0f,
			800.0f,

			//色
			0xFFFFFFFF,

			//オブジェクトタイプ（可動or不可動）
			ImMovable
		);
	}
	T->titleSpace[0].WorldPos = { 240,400 };
	T->titleSpace[1].WorldPos = { 320,480 };
	T->titleSpace[2].WorldPos = { 640,600 };
	T->titleSpace[3].WorldPos = { 960,480 };
	T->titleSpace[4].WorldPos = { 1040,400 };
}

void TitleDraw(TitleScene* T) {
	T->titleScene.RectObjDraw();
	for (int i = 0;i < 5;i++) {
		T->titleSpace[i].RectObjDraw();
	}
}

void TitleSceneUpDate(TitleScene *T,Key *key, CameraRelated* cr) {

	

		if (&key->keys[DIK_SPACE] && doreTitle == 0) {
			doreTitle = 1;
		}
		if (&key->keys[DIK_SPACE] && doreTitle == 2) {
			doreTitle = 3;
		}

		if (doreTitle == 1) {
			Easing(&T->titleSpace[0].WorldPos, 240, 400, 480, 600, &T->nowFrame, T->endFrame, &T->t, 1.0f, materialInBack);
			T->nowFrame -= 1;
			Easing(&T->titleSpace[1].WorldPos, 320, 480, 560, 600, &T->nowFrame, T->endFrame, &T->t, 1.0f, materialInBack);
			T->nowFrame -= 1;
			Easing(&T->titleSpace[3].WorldPos, 960, 480, 720, 600, &T->nowFrame, T->endFrame, &T->t, 1.0f, materialInBack);
			T->nowFrame -= 1;
			Easing(&T->titleSpace[4].WorldPos, 1040, 400, 800, 600, &T->nowFrame, T->endFrame, &T->t, 1.0f, materialInBack);

			if (T->nowFrame >= T->endFrame) {
				doreTitle = 2;
				T->nowFrame = 0;
			}
		}
		if (doreTitle == 3) {
			Easing(&T->titleSpace[0].WorldPos, 480, 600, 480, 400, &T->nowFrame, T->endFrame, &T->t, 1.0f, materialInBack);
			T->nowFrame -= 1;
			Easing(&T->titleSpace[1].WorldPos, 560, 600, 560, 400, &T->nowFrame, T->endFrame, &T->t, 1.0f, materialInBack);
			T->nowFrame -= 1;
			Easing(&T->titleSpace[2].WorldPos, 640, 600, 560, 400, &T->nowFrame, T->endFrame, &T->t, 1.0f, materialInBack);
			T->nowFrame -= 1;
			Easing(&T->titleSpace[3].WorldPos,720, 600, 720, 400, &T->nowFrame, T->endFrame, &T->t, 1.0f, materialInBack);
			T->nowFrame -= 1;
			Easing(&T->titleSpace[4].WorldPos, 800, 600, 800, 400, &T->nowFrame, T->endFrame, &T->t, 1.0f, materialInBack);

			if (T->nowFrame >= T->endFrame) {
				isTitle = 0;
			}
		}

		SetFourVertexes(&T->titleScene);
		RenderingPipeline(&T->titleScene, cr);

		for (int i = 0;i < 5;i++) {
			SetFourVertexes(&T->titleSpace[i]);
			RenderingPipeline(&T->titleSpace[i], cr);
		}


		
	
	
}

