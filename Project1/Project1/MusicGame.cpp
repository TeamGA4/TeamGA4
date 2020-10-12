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
	LoadMusic(music_name);
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
		(*i)->Action();
		(*i)->Draw();
	}

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
}

//�h���[
void MusicGame::Draw()
{
	char time[256];
	sprintf_s(time, 256, "%d", elapsed_flame);
	DrawString(0, 0, time, GetColor(255, 0, 0));

	DrawLine(60, 60, 420, 60, GetColor(255, 0, 0));
	DrawLine(60, 240, 420, 240, GetColor(255, 0, 0));
	DrawLine(60, 420, 420, 420, GetColor(255, 0, 0));
	DrawLine(60, 600, 420, 600, GetColor(255, 0, 0));
	DrawLine(60, 780, 420, 780, GetColor(255, 0, 0));

	DrawLine(60, 0, 60, 840, GetColor(255, 0, 0));
	DrawLine(150, 0, 150, 840, GetColor(255, 0, 0));
	DrawLine(240, 0, 240, 840, GetColor(255, 0, 0));
	DrawLine(330, 0, 330, 840, GetColor(255, 0, 0));
	DrawLine(420, 0, 420, 840, GetColor(255, 0, 0));
}

//�y�ȏ��ǂݍ��݊֐�(�����@�ǂݍ��ރm�[�c�f�[�^�̋Ȗ�)
void MusicGame::LoadMusic(char music_name[])
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