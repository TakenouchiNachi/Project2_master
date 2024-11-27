#pragma once
#include"structuer.h"

enum ColorCode {
	Amethyst = 0x9E76B4FF,//アメジスト色

	Crocus = 0xA5A0CFFF, // クロックス色

	Lavender = 0xB7A8CCFF, // ラベンダー色

	Raspberry = 0x8D1A4AFF, // ラズベリー色

	Purple = 0xFF00FFFF,// ?

	Ayame = 0xC77EB5FF,// あやめ色

	Hujimurasaki = 0x9B95C9FF,// 藤紫色

	Hutaai = 0x6B4978FF,// 二藍色

	Hasita = 0xA69ABDFF,// 端色

	Kodaimurasaki = 0x7D5484FF,// 古代紫色

	Kousi = 0x954C93FF,// 紅紫

	Pansy = 0x583F99FF,// パンジー
};

void SelectColor(int* objColor, int whatColor);