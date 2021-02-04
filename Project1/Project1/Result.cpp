#pragma warning(disable:4996)

#include "Header.h"

//コンストラクタ
Result::Result()
{
	background = LoadGraph("image\\chara.jpg"); //背景画像読み込み
	max_notes = 0;
	score = 0;
}

//アクション
void Result::Action()
{
	if (MouseClick(0, 0, 640, 640, 0) == true ||
		CheckHitKey(KEY_INPUT_RETURN) == true)
	{
		if (push == false)
			game_scene = SceneTitle;

		push = true;
	}
	else
	{
		push = false;
	}
}

//ドロー
void Result::Draw()
{
	DrawGraph(0, 0, background, TRUE); //背景描画

	//スコア表示
	SetFontSize(80);

	if (score >= max_notes * 100 * 8 / 10)
		DrawFormatString(220, 128, GetColor(255, 0, 0), "CLEAR");
	else
		DrawFormatString(200, 128, GetColor(0, 0, 255), "FAILED");

	SetFontSize(48);
	
	if (score < 10000)
		DrawFormatString(160, 384, GetColor(255, 0, 0), "%d", score);
	else
		DrawFormatString(136, 384, GetColor(255, 0, 0), "%d", score);

	SetFontSize(32);

	DrawFormatString(280, 320, GetColor(255, 255, 255), "SCORE");

	DrawFormatString(312, 392, GetColor(255, 255, 255), "/   %d", max_notes * 100 * 8 / 10);

	static int time = 0;
	time++;
	if (time > 120)
		time = 0;

	if (time <= 60)
	{
		DrawString(WINDOW_SIDE / 2 - 40, 520, "click", GetColor(255, 255, 255));
		DrawString(WINDOW_SIDE / 2 - 40, 592, "Enter", GetColor(255, 255, 255));
	}
	DrawString(WINDOW_SIDE / 2 - 16, 556, "or", GetColor(255, 255, 255));
}

void Result::SetMaxNotes(int set_notes)
{
	max_notes = set_notes;
}

void Result::SetScore(int set_score)
{
	score = set_score;
}