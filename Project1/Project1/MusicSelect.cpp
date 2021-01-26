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

	select = 0;
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
		if (CheckHitKey(KEY_INPUT_UP) == true && push == false)
		{
			if (select == 0) select = MUSIC_COUNT - 1;
			else select--;
		}
		//��
		if (CheckHitKey(KEY_INPUT_DOWN) == true && push == false)
		{
			if (select == MUSIC_COUNT - 1) select = 0;
			else select++;
		}

		push = true; //����������
	}
	else
	{
		push = false; //����������
	}
}

//�h���[
void MusicSelect::Draw()
{
	DrawExtendGraph(0, 0, 640, 640, background, TRUE); //�w�i�摜�ǂݍ���

	DrawString(0, 32, music_name[select], GetColor(255, 255, 255));

	/*for (int i = 0; i < MUSIC_COUNT; i++)
	{
		DrawString(0, 32 * i, music_name[i], GetColor(255, 255, 255));
	}*/
}
