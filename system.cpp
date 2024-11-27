//ヘッダーファイルの読み込み
#include"structuer.h"
#include"define.h"
#include"camerasystem.h"
#include"enemy.h"
#include"easing.h"
#include "rope.h"


//スクロール処理
void ScrollFunction(GameObject* go, CameraRelated* cr) {
	
	Vector2 pos = {};
	
	if (go->enemy.hand[Right].IsAlive == 1 && go->enemy.hand[Left].IsAlive == 1) {
		pos = MakeCenterOfGravity({ -go->player.WorldPos.x * 1.75f, -go->player.WorldPos.y },
			{ -go->enemy.hand[Right].WorldPos.x / 2 ,-go->enemy.hand[Right].WorldPos.y / 1 },
			{ -go->enemy.hand[Left].WorldPos.x / 2, -go->enemy.hand[Left].WorldPos.y / 1 });
	}
	else if (go->enemy.hand[Right].IsAlive == 0 && go->enemy.hand[Left].IsAlive == 1) {
		pos = MakeCenterOfGravity({ -go->player.WorldPos.x * 1.75f, -go->player.WorldPos.y },
			{ -go->enemy.WorldPos.x / 2 ,-go->enemy.WorldPos.y / 1 },
			{ -go->enemy.hand[Left].WorldPos.x / 2, -go->enemy.hand[Left].WorldPos.y / 1 });
	}
	else if (go->enemy.hand[Right].IsAlive == 1 && go->enemy.hand[Left].IsAlive == 0) {
		pos = MakeCenterOfGravity({ -go->player.WorldPos.x * 1.75f, -go->player.WorldPos.y },
			{ -go->enemy.hand[Right].WorldPos.x / 2 ,-go->enemy.hand[Right].WorldPos.y / 1 },
			{ -go->enemy.WorldPos.x / 2, -go->enemy.WorldPos.y / 1 });
	}
	else if (go->enemy.hand[Right].IsAlive == 0 && go->enemy.hand[Left].IsAlive == 0) {
		pos.x = ( -go->player.WorldPos.x + -go->enemy.WorldPos.x) / 2.0f;
		pos.y = ( -go->player.WorldPos.y + -go->enemy.WorldPos.y) / 2.0f;
	}

	pos.x += (-go->player.WorldPos.x - pos.x) / 2.0f;
	pos.y += (-go->player.WorldPos.y - pos.y) / 2.0f;
	/*Easing(&cr->CameraPos, cr->CameraPos.x, cr->CameraPos.y, pos.x, pos.y, &cameraNowFrame, cameraEndFrame, &cameraT, 6.25f, materialOutBack);*/

	if (cameraNowFrame >= cameraEndFrame)
		cameraNowFrame = 0;

	cr->CameraPos = Lerp(&cr->CameraPos,&pos, 1.0f / 60.0f * 2.0f);

	/*cr->CameraPos.x = -go->player.WorldPos.x;
	cr->CameraPos.y = -go->player.WorldPos.y;*/
	
}
