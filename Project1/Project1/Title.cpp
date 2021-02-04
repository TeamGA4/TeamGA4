#pragma warning(disable:4996)

#include "Header.h"

//�R���X�g���N�^
Title::Title()
{
	background = LoadGraph("image\\chara.jpg"); //�w�i�摜�ǂݍ���
}

//�A�N�V����
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

//�h���[
void Title::Draw()
{
	DrawGraph(0, 0, background, TRUE); //�w�i�`��

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