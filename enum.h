#pragma once


//オブジェクトの種類
enum {
	//引き寄せられる
	Movable,

	//引き寄せられない（プレイヤーが引き寄せられる）
	ImMovable,

	//フリッカーが関与しないオブジェクト
	Else
};