#pragma warning(disable:4996)

#include "Header.h"

//�R���X�g���N�^
MusicSelect::MusicSelect()
{
	background = LoadGraph("image\\chara.jpg"); //�w�i�摜�ǂݍ���
	LoadDivGraph("image\\vector.png", 8, 4, 2, 48, 48, image_vec); //���摜�ǂݍ���

	strcpy(music_name[0], "Absolute Area");
	strcpy(music_name[1], "Battle");
	strcpy(music_name[2], "Heavenly Depression");
	strcpy(music_name[3], "MEGAMARESPERO");
	strcpy(music_name[4], "�}�E���[���E����");

	music_sound[0] = LoadSoundMem("Music\\Absolute Area.mp3");
	music_sound[1] = LoadSoundMem("Music\\Battle.mp3");
	music_sound[2] = LoadSoundMem("Music\\Heavenly Depression.mp3");
	music_sound[3] = LoadSoundMem("Music\\MEGAMARESPERO.mp3");
	music_sound[4] = LoadSoundMem("Music\\�}�E���[���E����.mp3");

	select_music = 0;
	select_level = 1;
	select_speed = 1.0;

	strcpy(pre_str[0], music_name[MUSIC_COUNT - 3]);
	strcpy(pre_str[1], music_name[MUSIC_COUNT - 2]);
	strcpy(pre_str[2], music_name[MUSIC_COUNT - 1]);
	strcpy(pre_str[3], music_name[select_music]);
	strcpy(pre_str[4], music_name[select_music + 1]);
	strcpy(pre_str[5], music_name[select_music + 2]);
	strcpy(pre_str[6], music_name[select_music + 3]);

	strcpy(level_str[0], " EASY");
	strcpy(level_str[1], "NORMAL");
	strcpy(level_str[2], " HARD");

	pre_str_y = (WINDOW_VERTICAL - 32) / 2 + 64;
	level_str_x = 368;

	up_ani = false;
	down_ani = false;
	right_ani = false;
	left_ani = false;
}

//�A�N�V����
void MusicSelect::Action()
{
	//���͏���(�L�[�{�[�h)
	if (CheckHitKey(KEY_INPUT_UP) == true ||
		CheckHitKey(KEY_INPUT_DOWN) == true ||
		CheckHitKey(KEY_INPUT_RIGHT) == true ||
		CheckHitKey(KEY_INPUT_LEFT) == true ||
		CheckHitKey(KEY_INPUT_RETURN) == true)
	{
		if (push == false &&
			up_ani == false && down_ani == false &&
			right_ani == false && left_ani == false)
		{
			//��
			if (CheckHitKey(KEY_INPUT_UP) == true)
			{
				up_ani = true;
			}
			//��
			if (CheckHitKey(KEY_INPUT_DOWN) == true)
			{
				down_ani = true;
			}
			//��
			if (CheckHitKey(KEY_INPUT_LEFT) == true)
			{
				left_ani = true;
			}
			//��
			if (CheckHitKey(KEY_INPUT_RIGHT) == true)
			{
				right_ani = true;
			}
			//Enter
			if (CheckHitKey(KEY_INPUT_RETURN) == true)
			{
				game_scene = SceneMusicGame;
			}
		}

		push = true; //����������
	}
	else
	{
		push = false; //����������
	}
	//���͏���(�}�E�X)
	if (push == false &&
		up_ani == false && down_ani == false &&
		right_ani == false && left_ani == false)
	{
		if (MouseClick(144, 184, 48, 48, 0) == true)
		{
			up_ani = true;
		}
		else if (MouseClick(144, 544, 48, 48, 0) == true)
		{
			down_ani = true;
		}
		else if (MouseClick(528, 256, 48, 48, 0) == true)
		{
			right_ani = true;
		}
		else if (MouseClick(304, 256, 48, 48, 0) == true)
		{
			left_ani = true;
		}
		else if (MouseClick(528, 400, 48, 48, 0) == true)
		{
			if (select_speed >= 2.0)
				select_speed = 1.0;
			else
				select_speed += 0.1;
		}
		else if (MouseClick(304, 400, 48, 48, 0) == true)
		{
			if (select_speed <= 1.0)
				select_speed = 2.0;
			else
				select_speed -= 0.1;
		}
		else if (MouseClick(356, 520, 160, 64, 0) == true)
		{
			strcpy(m_name, music_name[select_music]);
			m_level = select_level;
			m_speed = select_speed * 5;
			game_scene = MusicDataSet;
		}
		else if (MouseClick(16, 568, 64, 64, 0) == true)
		{
			game_scene = SceneTitle;
		}
	}
	

	//�Ȗ��㏸�A�j���[�V����
	if (up_ani == true)
	{
		pre_str_y -= 4;
	}
	//�Ȗ����~�A�j���[�V����
	else if (down_ani == true)
	{
		pre_str_y += 4;
	}
	//��Փx�ړ��A�j���[�V����(�E)
	else if (right_ani == true)
	{
		level_str_x += 8;
	}
	//��Փx�ړ��A�j���[�V����(��)
	else if (left_ani == true)
	{
		level_str_x -= 8;
	}
	
	//�A�j���[�V�����I������
	//�Ȗ�������
	if (pre_str_y <= (WINDOW_VERTICAL - 32) / 2 + 64 - 54 ||
		pre_str_y >= (WINDOW_VERTICAL - 32) / 2 + 64 + 54)
	{
		//�I�𒆂̊y�ȏ��ύX
		if (up_ani == true)
		{
			if (select_music == MUSIC_COUNT - 1) select_music = 0;
			else select_music++;
		}
		else if (down_ani == true)
		{
			if (select_music == 0) select_music = MUSIC_COUNT - 1;
			else select_music--;
		}

		//�y�ȕ\���p�̕�����ύX
		if (select_music - 1 < 0)
			strcpy(pre_str[0], music_name[MUSIC_COUNT - 3]);
		else if (select_music - 2 < 0)
			strcpy(pre_str[0], music_name[MUSIC_COUNT - 2]);
		else if (select_music - 3 < 0)
			strcpy(pre_str[0], music_name[MUSIC_COUNT - 1]);
		else
			strcpy(pre_str[0], music_name[select_music - 3]);

		if (select_music - 1 < 0)
			strcpy(pre_str[1], music_name[MUSIC_COUNT - 2]);
		else if (select_music - 2 < 0)
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

		if (select_music + 1 == MUSIC_COUNT)
			strcpy(pre_str[5], music_name[1]);
		else if (select_music + 2 == MUSIC_COUNT)
			strcpy(pre_str[5], music_name[0]);
		else
			strcpy(pre_str[5], music_name[select_music + 2]);

		if (select_music + 1 == MUSIC_COUNT)
			strcpy(pre_str[6], music_name[2]);
		else if (select_music + 2 == MUSIC_COUNT)
			strcpy(pre_str[6], music_name[1]);
		else if (select_music + 3 == MUSIC_COUNT)
			strcpy(pre_str[6], music_name[0]);
		else
			strcpy(pre_str[6], music_name[select_music + 3]);

		//���W�ƃt���O��������
		pre_str_y = (WINDOW_VERTICAL - 32) / 2 + 64;
		up_ani = false;
		down_ani = false;
	}
	//��Փx������
	if (level_str_x >= 368 + 192 ||
		level_str_x <= 368 - 192)
	{
		//�I�𒆂̓�Փx���ύX
		if (right_ani == true)
		{
			if (select_level == 0) select_level = 2;
			else select_level--;
		}
		else if (left_ani == true)
		{
			if (select_level == 2) select_level = 0;
			else select_level++;
		}

		if (select_level == 0)
		{
			strcpy(level_str[0], " HARD");
			strcpy(level_str[1], " EASY");
			strcpy(level_str[2], "NORMAL");
		}
		else if (select_level == 1)
		{
			strcpy(level_str[0], " EASY");
			strcpy(level_str[1], "NORMAL");
			strcpy(level_str[2], " HARD");
		}
		else
		{
			strcpy(level_str[0], "NORMAL");
			strcpy(level_str[1], " HARD");
			strcpy(level_str[2], " EASY");
		}

		//���W�ƃt���O��������
		level_str_x = 368;
		right_ani = false;
		left_ani = false;
	}
}

//�h���[
void MusicSelect::Draw()
{
	DrawGraph(0, 0, background, TRUE); //�w�i�`��

	//��Փx�e�L�X�g�`��(1)
	SetFontSize(48);
	DrawString(level_str_x - 192, 256, level_str[0], GetColor(255, 0, 0));
	DrawString(level_str_x, 256, level_str[1], GetColor(255, 0, 0));
	DrawString(level_str_x + 192, 256, level_str[2], GetColor(255, 0, 0));

	//�m�[�c���x�`��
	DrawFormatString(404, 400, GetColor(255, 0, 0), "%.1f", select_speed);

	//�w�i(2����)�`��
	DrawRectGraph(0, 0, 0, 0, 360, 640, background, TRUE, FALSE);
	DrawRectGraph(520, 0, 520, 0, 640, 640, background, TRUE, FALSE);

	//�Ȗ��`��
	if (up_ani == true || down_ani == true)
	{
		SetFontSize(24);
		DrawString(48, pre_str_y, pre_str[3], GetColor(255, 255, 255));
	}
	else
	{
		SetFontSize(32);
		DrawString(32, pre_str_y - 8, pre_str[3], GetColor(255, 0, 0));
	}
	if (GetFontSize() != 24)
		SetFontSize(24);
	DrawString(48, pre_str_y - 54 * 3, pre_str[0], GetColor(255, 255, 255));
	DrawString(48, pre_str_y - 54 * 2, pre_str[1], GetColor(255, 255, 255));
	DrawString(48, pre_str_y - 54 * 1, pre_str[2], GetColor(255, 255, 255));
	DrawString(48, pre_str_y + 54 * 1, pre_str[4], GetColor(255, 255, 255));
	DrawString(48, pre_str_y + 54 * 2, pre_str[5], GetColor(255, 255, 255));
	DrawString(48, pre_str_y + 54 * 3, pre_str[6], GetColor(255, 255, 255));

	//�w�i(2����)�`��
	DrawRectGraph(0, 0, 0, 0, 640, (WINDOW_VERTICAL - 32) / 2 - 54 * 3 + 40 + 64, background, TRUE, FALSE);
	DrawRectGraph(0, (WINDOW_VERTICAL - 32) / 2 + 54 * 3 + 64, 0, (WINDOW_VERTICAL - 32) / 2 + 54 * 3 + 64, 640, 640, background, TRUE, FALSE);

	//��Փx�e�L�X�g�`��(2)
	DrawString(404, 208, "LEVEL", GetColor(255, 255, 255));
	DrawString(404, 352, "SPEED", GetColor(255, 255, 255));

	//���̑��e�L�X�g�`��
	SetFontSize(64);
	DrawString(128, 64, "MUSIC SELECT", GetColor(255, 255, 0));
	DrawString(356, 520, "START", GetColor(0, 255, 0));
	DrawString(16, 568, "��", GetColor(0, 255, 0));

	//���`��
	if (up_ani == true)
		DrawGraph(144, 184, image_vec[4], TRUE);
	else
		DrawGraph(144, 184, image_vec[0], TRUE);
	if (down_ani == true)
		DrawGraph(144, 544, image_vec[5], TRUE);
	else
		DrawGraph(144, 544, image_vec[1], TRUE);
	if (right_ani == true)
		DrawGraph(528, 256, image_vec[6], TRUE);
	else
		DrawGraph(528, 256, image_vec[2], TRUE);
	if (left_ani == true)
		DrawGraph(304, 256, image_vec[7], TRUE);
	else
		DrawGraph(304, 256, image_vec[3], TRUE);
	DrawGraph(528, 400, image_vec[2], TRUE);
	DrawGraph(304, 400, image_vec[3], TRUE);
}
