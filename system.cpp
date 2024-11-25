//ヘッダーファイルの読み込み
#include"structuer.h"
#include"define.h"
#include"camerasystem.h"
#include"enemy.h"
#include"easing.h"

//スクロール処理
void ScrollFunction(GameObject* go, CameraRelated* cr) {
	
	Vector2 pos;
	pos = MakeCenterOfGravity({ -go->player.WorldPos.x * 1.75f, -go->player.WorldPos.y },
			{ -go->enemy.hand[Right].WorldPos.x / 2 ,-go->enemy.hand[Right].WorldPos.y / 1 },
			{ -go->enemy.hand[Left].WorldPos.x / 2, -go->enemy.hand[Left].WorldPos.y / 1 });
	/*Easing(&cr->CameraPos, cr->CameraPos.x, cr->CameraPos.y, pos.x, pos.y, &cameraNowFrame, cameraEndFrame, &cameraT, 6.25f, materialOutBack);*/
	pos.x += (-go->player.WorldPos.x - pos.x) / 2.0f;
	pos.y += (-go->player.WorldPos.y - pos.y) / 2.0f;
	if (cameraNowFrame >= cameraEndFrame)
		cameraNowFrame = 0;

	cr->CameraPos = pos;
}
