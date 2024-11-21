//ヘッダーファイルの読み込み
#include"structuer.h"
#include"define.h"

//スクロール処理
void ScrollFunction(GameObject* go, CameraRelated* cr) {

	//if (cr->CameraPos.x < WindowWidth / 2.0f && cr->CameraPos.x > WorldWidth - WindowWidth / 2.0f) {
		cr->CameraPos.x = -(go->player.WorldPos.x);
	//}

	//if (cr->CameraPos.y > WindowHeight / 2.0f && cr->CameraPos.y < WorldHeight - WindowHeight / 2.0f) {
		cr->CameraPos.y = -(go->player.WorldPos.y);
	//}
}
