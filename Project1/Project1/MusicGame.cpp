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
MusicGame::MusicGame(char name[], int speed)
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

	//�y�ȏ���ǂݍ���
	LoadMusicNotes(music_name);

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

	//�̗͏�����
	life = 1000;
}

//�A�N�V����
void MusicGame::Action()
{
	//�o�ߎ��ԉ��Z
	elapsed_flame++;

	//120�t���[��(2�b)�o�߁A���y�Ȃ��Đ�����Ă��Ȃ��ꍇ�A�Đ�����
	if (CheckSoundMem(sound) == false && elapsed_flame > 120)
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);

	//�m�[�c�̐���
	for (auto i = music.begin(); i != music.end(); i++)
	{
		if (elapsed_flame == (*i)->flame - 780 / notes_speed + 120)
		{
			a = new Notes((*i)->lane, notes_speed, (*i)->type, (*i)->length - (*i)->flame);
			notes.push_back(a);
		}
	}

	//�m�[�c�̏���
	for (auto i = notes.begin(); i != notes.end(); i++)
	{
		//���͏���

		Pos notes_pos = (*i)->GetNotesPos(); //�m�[�c�̍��W�擾

		//D(1���)�����͂��ꂽ��
		if (CheckHitKey(KEY_INPUT_D) == true)
			if (PushNotesButton((*i)->GetNotesPos(), (*i)->GetNotesType(), 0) == true)
				(*i)->SetDeleteFlg(true);
		else
			if (ReleaseNotesButton((*i)->GetNotesPos(), (*i)->GetNotesLength(), (*i)->GetNotesType(), 0) == true)
				(*i)->SetDeleteFlg(true);

		//F(2���)�����͂��ꂽ��
		if (CheckHitKey(KEY_INPUT_F) == true)
			if (PushNotesButton((*i)->GetNotesPos(), (*i)->GetNotesType(), 1) == true)
				(*i)->SetDeleteFlg(true);
		else
			if (ReleaseNotesButton((*i)->GetNotesPos(), (*i)->GetNotesLength(), (*i)->GetNotesType(), 1) == true)
				(*i)->SetDeleteFlg(true);

		//J(3���)�����͂��ꂽ��
		if (CheckHitKey(KEY_INPUT_J) == true)
			if (PushNotesButton((*i)->GetNotesPos(), (*i)->GetNotesType(), 2) == true)
				(*i)->SetDeleteFlg(true);
		else
			if (ReleaseNotesButton((*i)->GetNotesPos(), (*i)->GetNotesLength(), (*i)->GetNotesType(), 2) == true)
				(*i)->SetDeleteFlg(true);

		//K(4���)�����͂��ꂽ��
		if (CheckHitKey(KEY_INPUT_K) == true)
			if (PushNotesButton((*i)->GetNotesPos(), (*i)->GetNotesType(), 3) == true)
				(*i)->SetDeleteFlg(true);
		else
			if (ReleaseNotesButton((*i)->GetNotesPos(), (*i)->GetNotesLength(), (*i)->GetNotesType(), 3) == true)
				(*i)->SetDeleteFlg(true);

		(*i)->Action();
	}

	//�L�[��������Ă��Ȃ��ꍇ�A�������������
	if (CheckHitKey(KEY_INPUT_D) == false)
		longpush_ctrl[0] = false;
	if (CheckHitKey(KEY_INPUT_F) == false)
		longpush_ctrl[1] = false;
	if (CheckHitKey(KEY_INPUT_J) == false)
		longpush_ctrl[2] = false;
	if (CheckHitKey(KEY_INPUT_K) == false)
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

	//if (life <=0)
	//{

	//}
}

//�h���[
void MusicGame::Draw()
{
	DrawExtendGraph(0, 0, 0 + 626*2, 0 + 417*2.1, backimg, TRUE);//�m�[�c���C���w�i

	DrawExtendGraph(380, 0,380+626/1.73,0+417*2.1, img, TRUE);//�m�[�c���C���w�i

		//�m�[�c�̕`��
	for (auto i = notes.begin(); i != notes.end(); i++)
	{
		(*i)->Draw();
	}


	//�t���[�����\��
	char time[256];
	sprintf_s(time, 256, "%d", elapsed_flame);
	DrawString(0, 0, time, GetColor(255, 0, 0));

	//����
	DrawLine(380, 60, 740, 60, GetColor(0, 0, 0));
	DrawLine(380, 240, 740, 240, GetColor(0, 0, 0));
	DrawLine(380, 420, 740, 420, GetColor(0, 0, 0));
	DrawLine(380, 600, 740, 600, GetColor(0, 0, 0));
	if (CheckHitKey(KEY_INPUT_D))
		DrawLine(380, 780, 470, 780, GetColor(0, 255, 255));
	else
		DrawLine(380, 780, 470, 780, GetColor(0, 0, 0));
	if (CheckHitKey(KEY_INPUT_F))
		DrawLine(470, 780, 560, 780, GetColor(0, 255, 255));
	else
		DrawLine(470, 780, 560, 780, GetColor(0, 0, 0));
	if (CheckHitKey(KEY_INPUT_J))
		DrawLine(560, 780, 650, 780, GetColor(0, 255, 255));
	else
		DrawLine(560, 780, 650, 780, GetColor(0, 0, 0));
	if (CheckHitKey(KEY_INPUT_K))
		DrawLine(650, 780, 740, 780, GetColor(0, 255, 255));
	else
		DrawLine(650, 780, 740, 780, GetColor(0, 0, 0));

	//�c��
	DrawLine(380, 0, 380, 840, GetColor(0, 0, 0));
	DrawLine(470, 0, 470, 840, GetColor(0, 0, 0));
	DrawLine(560, 0, 560, 840, GetColor(0, 0, 0));
	DrawLine(650, 0, 650, 840, GetColor(0, 0, 0));
	DrawLine(740, 0, 740, 840, GetColor(0, 0, 0));

	//����\��
	for (int i = 0; i < 4; i++)
	{
		DrawString(390 + i * 90, 720, judg_txt[i], GetColor(255, 0, 0));
		judg_txt_time[i]++;
		if (judg_txt_time[i] > 15)
		{
			strcpy(judg_txt[i], "\0");
			judg_txt_time[i] = 0;
		}

		DrawFormatString(100, 100, GetColor(0, 0, 0), "�R���{\n%d", combo);

		DrawFormatString(200, 100, GetColor(0, 0, 0), "�X�R�A\n%d", score);
	
		DrawFormatString(100, 200, GetColor(0, 0, 0), "���C�t\n%d", life);

	}

}

//�y�ȏ��ǂݍ��݊֐�(�����@�ǂݍ��ރm�[�c�f�[�^�̋Ȗ�)
void MusicGame::LoadMusicNotes(char music_name[])
{
	FILE *fp;
	char fname[256] = "NotesData\\";
	strcat(fname, music_name);
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
		fclose(fp); //�t�@�C�������
		return;
	}

	//�t�@�C������y�Ȃ̃m�[�c�f�[�^��ǂݍ���
	while ((ret = fscanf(fp, "%d,%d,%d,%f", &flame, &lane, &type, &length) != EOF))
	{
		//�ǂݍ��񂾃f�[�^���y�Ȃ̏o���m�[�c��񃊃X�g�ɓo�^
		b = new MusicNotes{ flame,lane,type,length };
		music.push_back(b);
	}

	//�t�@�C�������
	fclose(fp);
}

//�m�[�c���͏���
bool MusicGame::PushNotesButton(Pos notes_pos, unsigned int notes_type, int line)
{
	if ((int)notes_pos.x - 380 == line * 90 && longpush_ctrl[line] == false)
	{
		//GOOD����
		if (notes_pos.y >= 780 - notes_speed * 2 &&
			notes_pos.y <= 780 + notes_speed * 2 ||
			notes_type == 3 &&
			notes_pos.y >= 780 - notes_speed * 4 &&
			notes_pos.y <= 780 + notes_speed * 4)
		{
			strcpy(judg_txt[line], "�f�n�n�c");
			combo++;
			score += 100;
			judg_txt_time[line] = 0;
			if (notes_type != 2)
				return true;
		}
		//NEAR����
		else if (notes_pos.y >= 780 - notes_speed * 4 &&
			notes_pos.y <= 780 + notes_speed * 4)
		{
			strcpy(judg_txt[line], "�m�d�`�q");
			combo++;
			score += 50;
			judg_txt_time[line] = 0;
			if (notes_type != 2)
				return true;
		}
		//MISS����
		else if (notes_pos.y >= 780 - notes_speed * 6 &&
			notes_pos.y <= 780 + notes_speed * 6)
		{
			strcpy(judg_txt[line], "�l�h�r�r");
			combo = 0;
			life -= 100;
			judg_txt_time[line] = 0;
			if (notes_type != 2)
				return true;
		}
	}

	longpush_ctrl[line] = true; //�L�[����������

	return false;
}

//�m�[�c���͏���(�����O�m�[�c�A�L�[���������p)
bool MusicGame::ReleaseNotesButton(Pos notes_pos, float notes_length, unsigned int notes_type, int line)
{
	if ((int)notes_pos.x-380 == line*90 && longpush_ctrl[line] == true && notes_type == 2)
	{
		//GOOD����
		if (notes_pos.y - notes_speed * notes_length >= 780 - notes_speed * 2 &&
			notes_pos.y - notes_speed * notes_length <= 780 + notes_speed * 2)
		{
			strcpy(judg_txt[line], "�f�n�n�c");			
			combo++;
			score += 100;
			judg_txt_time[line] = 0;
			return true;
		}
		//NEAR����
		else if (notes_pos.y - notes_speed * notes_length >= 780 - notes_speed * 4 &&
			notes_pos.y - notes_speed * notes_length <= 780 + notes_speed * 4)
		{
			strcpy(judg_txt[line], "�m�d�`�q");
			combo++;
			score += 50;
			judg_txt_time[line] = 0;
			return true;
		}
		//MISS����
		else if (notes_pos.y - notes_speed * notes_length >= 780 - notes_speed * 6 &&
			notes_pos.y - notes_speed * notes_length <= 780 + notes_speed * 6)
		{
			strcpy(judg_txt[line], "�l�h�r�r");
			combo=0;
			life -= 100;
			judg_txt_time[line] = 0;
			return true;
		}
	}

	longpush_ctrl[line] = false; //�L�[����������

	return false;
}
