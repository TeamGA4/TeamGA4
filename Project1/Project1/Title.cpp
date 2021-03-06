#pragma warning(disable:4996)

#include "Header.h"

//コンストラクタ
Title::Title()
{
	background = LoadGraph("image\\chara.jpg"); //背景画像読み込み
}

//アクション
void Title::Action()
{
	if (MouseClick(0, 0, 640, 640, 0) == true ||
		CheckHitKey(KEY_INPUT_RETURN) == true)
	{
		if (push == false)
			game_scene = SceneMusicSelect;

		push = true;
	}
	else
	{
		push = false;
	}
}

//ドロー
void Title::Draw()
{
	DrawGraph(0, 0, background, TRUE); //背景描画

	SetFontSize(80);
	DrawString(WINDOW_SIDE / 2 - 220, 192, "- b e a t -", GetColor(255, 255, 255));

	static int time = 0;
	time++;
	if (time > 120)
		time = 0;

	SetFontSize(48);
	if (time <= 60)
	{
		DrawString(WINDOW_SIDE / 2 - 60, 416, "click", GetColor(255, 0, 0));
		DrawString(WINDOW_SIDE / 2 - 60, 520, "Enter", GetColor(255, 0, 0));
	}
	DrawString(WINDOW_SIDE / 2 - 24, 468, "or", GetColor(255, 255, 255));
}