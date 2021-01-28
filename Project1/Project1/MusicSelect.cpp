#pragma warning(disable:4996)

#include "Header.h"

//�R���X�g���N�^
MusicSelect::MusicSelect()
{
	background = LoadGraph("image\\chara.jpg"); //�w�i�摜�ǂݍ���

	strcpy(music_name[0], "Battle");
	strcpy(music_name[1], "SampleA");
	strcpy(music_name[2], "SampleB");
	strcpy(music_name[3], "SampleC");
	strcpy(music_name[4], "SampleD");

	select_music = 0;

	strcpy(pre_str[0], music_name[MUSIC_COUNT - 3]);
	strcpy(pre_str[1], music_name[MUSIC_COUNT - 2]);
	strcpy(pre_str[2], music_name[MUSIC_COUNT - 1]);
	strcpy(pre_str[3], music_name[select_music]);
	strcpy(pre_str[4], music_name[select_music + 1]);
	strcpy(pre_str[5], music_name[select_music + 2]);
	strcpy(pre_str[6], music_name[select_music + 3]);

	pre_str_y = (WINDOW_VERTICAL - 32) / 2;

	up_ani = false;
	down_ani = false;
}

//�A�N�V����
void MusicSelect::Action()
{
	static bool push = false;

	//���͏���
	if (CheckHitKey(KEY_INPUT_UP) == true ||
		CheckHitKey(KEY_INPUT_DOWN) == true ||
		CheckHitKey(KEY_INPUT_RIGHT) == true ||
		CheckHitKey(KEY_INPUT_LEFT) == true)
	{
		//��
		if (CheckHitKey(KEY_INPUT_UP) == true && push == false &&
			up_ani == false && down_ani == false)
		{
			up_ani = true;
		}
		//��
		if (CheckHitKey(KEY_INPUT_DOWN) == true && push == false &&
			up_ani == false && down_ani == false)
		{
			down_ani = true;
		}

		push = true; //����������
	}
	else
	{
		push = false; //����������
	}

	//������㏸�A�j���[�V����
	if (up_ani == true)
	{
		pre_str_y -= 2;
	}
	//�����񉺍~�A�j���[�V����
	else if (down_ani == true)
	{
		pre_str_y += 2;
	}
	//�A�j���[�V�����I������
	if (pre_str_y == (WINDOW_VERTICAL - 32) / 2 - 54||
		pre_str_y == (WINDOW_VERTICAL - 32) / 2 + 54)
	{
		//�I�𒆂̊y�ȏ��ύX
		if (up_ani == true && down_ani == false)
		{
			if (select_music == MUSIC_COUNT - 1) select_music = 0;
			else select_music++;
		}
		else if (up_ani == false && down_ani == true)
		{
			if (select_music == 0) select_music = MUSIC_COUNT - 1;
			else select_music--;
		}

		//�y�ȕ\���p�̕�����ύX
		if (select_music - 3 < 0)
			strcpy(pre_str[0], music_name[MUSIC_COUNT - 1]);
		else
			strcpy(pre_str[0], music_name[select_music - 3]);
		if (select_music - 2 < 0)
			strcpy(pre_str[1], music_name[MUSIC_COUNT - 1]);
		else
			strcpy(pre_str[1], music_name[select_music - 2]);
		if (select_music - 1 < 0)
			strcpy(pre_str[2], music_name[MUSIC_COUNT - 1]);
		else
			strcpy(pre_str[2], music_name[select_music - 1]);

		strcpy(pre_str[3], music_name[select_music]);

		if (select_music + 1 >= MUSIC_COUNT)
			strcpy(pre_str[4], music_name[0]);
		else
			strcpy(pre_str[4], music_name[select_music + 1]);
		if (select_music + 1 >= MUSIC_COUNT)
			strcpy(pre_str[5], music_name[1]);
		else
			strcpy(pre_str[5], music_name[select_music + 2]);
		if (select_music + 1 >= MUSIC_COUNT)
			strcpy(pre_str[6], music_name[2]);
		else
			strcpy(pre_str[6], music_name[select_music + 3]);

		//���W�ƃt���O��������
		pre_str_y = (WINDOW_VERTICAL - 32) / 2;
		up_ani = false;
		down_ani = false;
	}
}

//�h���[
void MusicSelect::Draw()
{
	SetFontSize(32);

	//DrawGraph(0, 0, background, TRUE); //�w�i�摜�ǂݍ���

	DrawString(96, pre_str_y - 54 * 3, pre_str[0], GetColor(255, 255, 255));
	DrawString(96, pre_str_y - 54 * 2, pre_str[1], GetColor(255, 255, 255));
	DrawString(96, pre_str_y - 54 * 1, pre_str[2], GetColor(255, 255, 255));
	DrawString(96, pre_str_y, pre_str[3], GetColor(255, 255, 255));
	DrawString(96, pre_str_y + 54 * 1, pre_str[4], GetColor(255, 255, 255));
	DrawString(96, pre_str_y + 54 * 2, pre_str[5], GetColor(255, 255, 255));
	DrawString(96, pre_str_y + 54 * 3, pre_str[6], GetColor(255, 255, 255));

	//DrawRectGraph(0, 0, 0, 0, 640, (WINDOW_VERTICAL - 32) / 2 - 54 * 3 + 40, background, TRUE, FALSE);
	//DrawRectGraph(0, (WINDOW_VERTICAL - 32) / 2 + 54 * 3, 0, (WINDOW_VERTICAL - 32) / 2 + 54 * 3, 640, 640, background, TRUE, FALSE);

	/*for (int i = 0; i < MUSIC_COUNT; i++)
	{
		DrawString(0, 32 * i, music_name[i], GetColor(255, 255, 255));
	}*/
}
