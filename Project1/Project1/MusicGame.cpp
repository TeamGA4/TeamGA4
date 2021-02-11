#pragma warning(disable:4996)

#include <list>

#include "Header.h"

//���X�g(�m�[�c�p)
list<Notes*>notes;

//���X�g�̏�����(�m�[�c�p)
auto a = new Notes(0, 780, 0, 0);

//���X�g(�y�Ȃ̏o���m�[�c���p)
list<MusicNotes*>music;

//���X�g�̏�����(�y�Ȃ̏o���m�[�c���p)
auto b = new MusicNotes{ 0,0,0,0 };

//�R���X�g���N�^(�����@�Ȗ��A�m�[�c���x)
MusicGame::MusicGame(char name[], int level, float speed)
{
	img = LoadGraph("image\\backnotes.jpg");//�m�[�c���C���w�i�ǂݍ���

	backimg = LoadGraph("image\\backimage.jpg");//�S�ʔw�i�ǂݍ���

	//�Ȗ���ݒ�
	strcpy(music_name, name);

	//�����t�@�C���ǂݍ���
	char str[256] = "Music\\";
	strcat(str, music_name);
	strcat(str, ".mp3");
	sound = LoadSoundMem(str);

	//�m�[�c���x��ݒ�
	notes_speed = speed;

	//���ԏ�����
	elapsed_flame = 0;

	//�����m�[�c��������
	max_notes = 0;

	//���X�g������
	for (auto i = notes.begin(); i != notes.end();)
	{
		delete(*i); //�I�u�W�F�N�g���폜
		i = notes.erase(i); //���X�g����폜�����X�g�̌q���ς�
	}

	for (auto i = music.begin(); i != music.end();)
	{
		delete(*i); //�I�u�W�F�N�g���폜
		i = music.erase(i); //���X�g����폜�����X�g�̌q���ς�
	}

	//�y�ȏ���ǂݍ���
	LoadMusicNotes(music_name, level);

	//����̃e�L�X�g��񏉊���
	for (int i = 0; i < 4; i++)
	{
		strcpy(judg_txt[i], "\0");
		judg_txt_time[i] = 0;
	}
	
	//�L�[���������䏉����
	longpush_ctrl[0] = false;
	longpush_ctrl[1] = false;
	longpush_ctrl[2] = false;
	longpush_ctrl[3] = false;

	//�R���{��������
	combo = 0;

	//�X�R�A������
	score = 0;

	//READY������
	ready_x = -320;
}

//�A�N�V����
void MusicGame::Action()
{
	static bool play_flg = false;

	//�t�F�[�h�A�E�g�E�t�F�[�h�C���A�j���[�V�������͓��삵�Ȃ�
	if (fade->GetFadeFlg() == false)
	{
		//�o�ߎ��ԉ��Z
		elapsed_flame++;

		//READY�e�L�X�g����
		if (elapsed_flame <= 60 || elapsed_flame >= 120 && play_flg == false)
		{
			ready_x += 8;
		}

		//120�t���[��(2�b)�o�߁A���y�Ȃ��Đ�����Ă��Ȃ��ꍇ�A�Đ�����
		if (CheckSoundMem(sound) == false && elapsed_flame > 300 && play_flg == false)
		{
			PlaySoundMem(sound, DX_PLAYTYPE_BACK);
			play_flg = true;
		}

		//�y�ȏI������
		if (CheckSoundMem(sound) == false && play_flg == true)
		{
			static int end_flame = 0;
			end_flame++;

			if (end_flame > 120)
			{
				result->SetMaxNotes(max_notes);
				result->SetScore(score);
				play_flg = false;
				end_flame = 0;
				fade->SetFadeoutFlg(SceneResult);
			}
		}
	}

	//�m�[�c�̐���
	for (auto i = music.begin(); i != music.end(); i++)
	{
		if (elapsed_flame == (*i)->flame - 600 / notes_speed + 300)
		{
			a = new Notes((*i)->lane, notes_speed, (*i)->type, (*i)->length - (*i)->flame);
			notes.push_back(a);
		}
	}

	//�m�[�c�̏���
	for (auto i = notes.begin(); i != notes.end(); i++)
	{
		//���͏���

		Pos pos = (*i)->GetNotesPos(); //�m�[�c�̍��W�擾
		int type = (*i)->GetNotesType();
		int length = (*i)->GetNotesLength();

		//D(1���)�����͂��ꂽ��
		if (CheckHitKey(KEY_INPUT_D) == true)
		{
			if (longpush_ctrl[0] == false)
				if (PushNotesButton(pos, type, 0) == true)
					(*i)->SetDeleteFlg(true);
		}
		else
		{
			if (type == 2 && longpush_ctrl[0] == true)
			{
				pos.y -= length*notes_speed;

				if (PushNotesButton(pos, type, 0) == true)
					(*i)->SetDeleteFlg(true);
			}
		}

		//F(2���)�����͂��ꂽ��
		if (CheckHitKey(KEY_INPUT_F) == true)
		{
			if (longpush_ctrl[1] == false)
				if (PushNotesButton(pos, type, 1) == true)
					(*i)->SetDeleteFlg(true);
		}	
		else
		{
			if (type == 2 && longpush_ctrl[1] == true)
			{
				pos.y -= length*notes_speed;

				if (PushNotesButton(pos, type, 1) == true)
					(*i)->SetDeleteFlg(true);
			}
		}

		//J(3���)�����͂��ꂽ��
		if (CheckHitKey(KEY_INPUT_J) == true)
		{
			if (longpush_ctrl[2] == false)
				if (PushNotesButton(pos, type, 2) == true)
					(*i)->SetDeleteFlg(true);
		}
		else
		{
			if (type == 2 && longpush_ctrl[2] == true)
			{
				pos.y -= length*notes_speed;

				if (PushNotesButton(pos, type, 2) == true)
					(*i)->SetDeleteFlg(true);
			}
		}

		//K(4���)�����͂��ꂽ��
		if (CheckHitKey(KEY_INPUT_K) == true)
		{
			if (longpush_ctrl[3] == false)
				if (PushNotesButton(pos, type, 3) == true)
					(*i)->SetDeleteFlg(true);
		}
		else
		{
			if (type == 2 && longpush_ctrl[3] == true)
			{
				pos.y -= length*notes_speed;

				if (PushNotesButton(pos, type, 3) == true)
					(*i)->SetDeleteFlg(true);
			}
		}

		//��ʊO�ɏo�����̏���
		if (pos.y > WINDOW_VERTICAL&&type != 2 ||
			pos.y - notes_speed * length > WINDOW_VERTICAL&&type == 2)
		{
			int line = (pos.x - 140) / 90;
			strcpy(judg_txt[line], "�l�h�r�r");
			combo = 0;
			judg_txt_time[line] = 0;
			(*i)->SetDeleteFlg(true);
		}

		(*i)->Action();
	}

	//����������
	if (CheckHitKey(KEY_INPUT_D) == true)
		longpush_ctrl[0] = true;
	else
		longpush_ctrl[0] = false;
	if (CheckHitKey(KEY_INPUT_F) == true)
		longpush_ctrl[1] = true;
	else
		longpush_ctrl[1] = false;
	if (CheckHitKey(KEY_INPUT_J) == true)
		longpush_ctrl[2] = true;
	else
		longpush_ctrl[2] = false;
	if (CheckHitKey(KEY_INPUT_K) == true)
		longpush_ctrl[3] = true;
	else
		longpush_ctrl[3] = false;

	//�m�[�c�̃��X�g�̐���
	for (auto i = notes.begin(); i != notes.end(); i++)
	{
		if ((*i)->GetDeleteFlg() == true)
		{
			delete(*i); //�I�u�W�F�N�g���폜
			i = notes.erase(i); //���X�g����폜�����X�g�̌q���ς�
			break;
		}
	}

	//�ȑI����ʂɖ߂鏈��
	if (MouseClick(16, 568, 64, 64, 0) == true)
	{
		play_flg = false;
		StopSoundMem(sound);
		fade->SetFadeoutFlg(SceneMusicSelect);
	}
}

//�h���[
void MusicGame::Draw()
{
	DrawGraph(0, 0, backimg, TRUE); //�m�[�c���C���w�i

	DrawExtendGraph(140, 0, 500, 640, img, TRUE); //�m�[�c���C���w�i

	//�߂�{�^���`��
	SetFontSize(64);
	DrawString(16, 568, "��", GetColor(0, 255, 0));

	//�R���{���`��
	if (ready_x >= 640)
	{
		if (combo < 10)
			DrawFormatString(306, 256, GetColor(255, 255, 255), "%d", combo);
		else
			DrawFormatString(290, 256, GetColor(255, 255, 255), "%d", combo);
		SetFontSize(32);
		DrawFormatString(278, 320, GetColor(255, 255, 255), "COMBO", combo);
	}

	//�m�[�c�̕`��
	for (auto i = notes.begin(); i != notes.end(); i++)
	{
		(*i)->Draw();
	}

	//�t���[�����\��
	/*char time[256];
	sprintf_s(time, 256, "%d", elapsed_flame);
	DrawString(0, 0, time, GetColor(255, 0, 0));*/

	//����
	DrawLine(140, 60, 500, 60, GetColor(0, 0, 0));
	DrawLine(140, 240, 500, 240, GetColor(0, 0, 0));
	DrawLine(140, 420, 500, 420, GetColor(0, 0, 0));
	if (CheckHitKey(KEY_INPUT_D))
		DrawLine(140, 600, 230, 600, GetColor(0, 255, 0));
	else
		DrawLine(140, 600, 230, 600, GetColor(0, 0, 0));
	if (CheckHitKey(KEY_INPUT_F))
		DrawLine(230, 600, 320, 600, GetColor(0, 255, 0));
	else
		DrawLine(230, 600, 320, 600, GetColor(0, 0, 0));
	if (CheckHitKey(KEY_INPUT_J))
		DrawLine(320, 600, 410, 600, GetColor(0, 255, 0));
	else
		DrawLine(320, 600, 410, 600, GetColor(0, 0, 0));
	if (CheckHitKey(KEY_INPUT_K))
		DrawLine(410, 600, 500, 600, GetColor(0, 255, 0));
	else
		DrawLine(410, 600, 500, 600, GetColor(0, 0, 0));

	//�c��
	DrawLine(140, 0, 140, 840, GetColor(0, 0, 0));
	DrawLine(230, 0, 230, 840, GetColor(0, 0, 0));
	DrawLine(320, 0, 320, 840, GetColor(0, 0, 0));
	DrawLine(410, 0, 410, 840, GetColor(0, 0, 0));
	DrawLine(500, 0, 500, 840, GetColor(0, 0, 0));

	//����\��
	SetFontSize(16);
	for (int i = 0; i < 4; i++)
	{
		DrawString(152 + i * 90, 540, judg_txt[i], GetColor(0, 255, 0));
		judg_txt_time[i]++;
		if (judg_txt_time[i] > 15)
		{
			strcpy(judg_txt[i], "\0");
			judg_txt_time[i] = 0;
		}
	}

	//�X�R�A�\��
	SetFontSize(32);
	DrawFormatString(28, 64, GetColor(0, 0, 0), "SCORE");
	if (score == 0)
		DrawFormatString(60, 112, GetColor(0, 0, 0), "%d", score);
	else if (score < 100)
		DrawFormatString(52, 112, GetColor(0, 0, 0), "%d", score);
	else if (score < 1000)
		DrawFormatString(44, 112, GetColor(0, 0, 0), "%d", score);
	else if (score < 10000)
		DrawFormatString(36, 112, GetColor(0, 0, 0), "%d", score);
	else if (score < 100000)
		DrawFormatString(28, 112, GetColor(0, 0, 0), "%d", score);

	DrawFormatString(28, 192, GetColor(0, 0, 0), "CLEAR");
	if (max_notes * 100 * 8 / 10 < 10000)
		DrawFormatString(36, 240, GetColor(0, 0, 0), "%d", max_notes * 100 * 8 / 10);
	else if (max_notes * 100 * 8 / 10 < 100000)
		DrawFormatString(28, 240, GetColor(0, 0, 0), "%d", max_notes * 100 * 8 / 10);

	//READY�e�L�X�g�`��
	if (CheckSoundMem(sound) == false)
	{
		SetFontSize(64);
		DrawString(ready_x, 288, "�q�d�`�c�x", GetColor(255, 0, 0));
	}
}

//�y�ȏ��ǂݍ��݊֐�(�����@�ǂݍ��ރm�[�c�f�[�^�̋Ȗ�)
void MusicGame::LoadMusicNotes(char music_name[], int level)
{
	FILE *fp;

	char fname[256];
	sprintf(fname, "NotesData\\\%s", music_name);
	if (level == 0)
		strcat(fname, "_EASY");
	else if (level == 1)
		strcat(fname, "_NORMAL");
	else
		strcat(fname, "_HARD");
	strcat(fname, ".csv");
	int ret;
	int flame = 0;
	int lane = 0;
	int type = 0;
	float length = 0;

	//�t�@�C�����J��
	fp = fopen(fname, "r");

	//�w�肵���t�@�C����������Ȃ��ꍇ
	if (fp == NULL)
	{
		return;
	}

	//�t�@�C������y�Ȃ̃m�[�c�f�[�^��ǂݍ���
	while ((ret = fscanf(fp, "%d,%d,%d,%f", &flame, &lane, &type, &length) != EOF))
	{
		//�ǂݍ��񂾃f�[�^���y�Ȃ̏o���m�[�c��񃊃X�g�ɓo�^
		b = new MusicNotes{ flame,lane,type,length };
		music.push_back(b);

		//�����m�[�c�����Z
		max_notes++;
	}

	//�t�@�C�������
	fclose(fp);
}

//�m�[�c���͏���
bool MusicGame::PushNotesButton(Pos notes_pos, unsigned int notes_type, int line)
{
	if ((int)notes_pos.x - 140 == line * 90)
	{
		//GOOD����
		if (notes_pos.y >= 600 - notes_speed * 2 &&
			notes_pos.y <= 600 + notes_speed * 2 ||
			notes_type == 3 &&
			notes_pos.y >= 600 - notes_speed * 4 &&
			notes_pos.y <= 600 + notes_speed * 4)
		{
			strcpy(judg_txt[line], "�f�n�n�c");
			combo++;
			score += 100;
			judg_txt_time[line] = 0;
			if (notes_type != 2 ||
				notes_type == 2 && longpush_ctrl[line] == true)
			{
				return true;
			}
		}
		//NEAR����
		else if (notes_pos.y >= 600 - notes_speed * 4 &&
			notes_pos.y <= 600 + notes_speed * 4)
		{
			strcpy(judg_txt[line], "�m�d�`�q");
			combo++;
			score += 50;
			judg_txt_time[line] = 0;
			if (notes_type != 2 ||
				notes_type == 2 && longpush_ctrl[line] == true)
			{
				return true;
			}
		}
		//MISS����
		else if (notes_pos.y >= 600 - notes_speed * 6 &&
			notes_pos.y <= 600 + notes_speed * 6)
		{
			strcpy(judg_txt[line], "�l�h�r�r");
			combo = 0;
			judg_txt_time[line] = 0;
			if (notes_type != 2 ||
				notes_type == 2 && longpush_ctrl[line] == true)
			{
				return true;
			}
		}
	}

	return false;
}

//�m�[�c���͏���(�����O�m�[�c�A�L�[���������p)
//bool MusicGame::ReleaseNotesButton(Pos notes_pos, float notes_length, unsigned int notes_type, int line)
//{
//	if ((int)notes_pos.x - 380 == line * 90 && longpush_ctrl[line] == true && notes_type == 2)
//	{
//		//GOOD����
//		if (notes_pos.y - notes_speed * notes_length >= 600 - notes_speed * 2 &&
//			notes_pos.y - notes_speed * notes_length <= 600 + notes_speed * 2)
//		{
//			strcpy(judg_txt[line], "�f�n�n�c");			
//			combo++;
//			score += 100;
//			judg_txt_time[line] = 0;
//			return true;
//		}
//		//NEAR����
//		else if (notes_pos.y - notes_speed * notes_length >= 600 - notes_speed * 4 &&
//			notes_pos.y - notes_speed * notes_length <= 600 + notes_speed * 4)
//		{
//			strcpy(judg_txt[line], "�m�d�`�q");
//			combo++;
//			score += 50;
//			judg_txt_time[line] = 0;
//			return true;
//		}
//		//MISS����
//		else if (notes_pos.y - notes_speed * notes_length >= 600 - notes_speed * 6 &&
//			notes_pos.y - notes_speed * notes_length <= 600 + notes_speed * 6)
//		{
//			strcpy(judg_txt[line], "�l�h�r�r");
//			combo = 0;
//			judg_txt_time[line] = 0;
//			return true;
//		}
//	}
//
//	return false;
//}
