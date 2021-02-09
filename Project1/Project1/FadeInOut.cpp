#include "Header.h"

//�R���X�g���N�^
FadeInOut::FadeInOut()
{
	img_panel = LoadGraph("image\\backimage.jpg");//�S�ʔw�i�ǂݍ���

	fadein_flg = false; //�t�F�[�h�A�E�g���䏉����
	fadeout_flg = false; //�t�F�[�h�C�����䏉����
	change_scene = SceneTitle; //�ύX�V�[��������

	//�p�l��������
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
			panel[i][j] = false;
}

//�A�N�V����
void FadeInOut::Action()
{
	static int time = 0;

	//�t�F�[�h�A�E�g�A�j���[�V�����̏���
	if (fadeout_flg == true)
	{
		time++;

		if (time % 2 == 0)
		{
			//�^�ɉ�ʂ𕢂��Ă���
			for (int i = 0; i < 19; i++)
			{
				if (panel[0][i] == false)
				{
					for (int j = 0, k = i; j < i + 1; j++, k--)
						panel[j][k] = true;
					break;
				}
			}

			time = 0;
		}

		//��ʑS�Ă��p�l���ŕ���ꂽ���A�Q�[���V�[����ύX���A�t�F�[�h�C���A�j���[�V�������J�n����
		if (CheckAnimation(false) == true)
		{
			for (int i = 0; i < 19; i++)
				for (int j = 0; j < 19; j++)
					panel[i][j] = true;

			time = 0;
			fadeout_flg = false;
			game_scene = change_scene;
			fadein_flg = true;
		}
	}

	//�t�F�[�h�C���A�j���[�V�����̏���
	else if (fadein_flg == true)
	{
		time++;

		if (time % 2 == 0)
		{
			//�^�ɉ�ʂ��J���Ă���
			for (int i = 0; i < 19; i++)
			{
				if (panel[0][i] == true)
				{
					for (int j = 0, k = i; j < i + 1; j++, k--)
						panel[j][k] = false;
					break;
				}
			}

			time = 0;
		}

		//��ʑS�Ẵp�l���������Ȃ������A�A�j���[�V�������I������
		if (CheckAnimation(true) == true)
		{
			for (int i = 0; i < 19; i++)
				for (int j = 0; j < 19; j++)
					panel[i][j] = false;

			time = 0;
			fadein_flg = false;
		}
	}
}

//�h���[
void FadeInOut::Draw()
{
	//�p�l���̕`��
	if (fadeout_flg == true || fadein_flg == true)
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				if (panel[i][j] == true)
					DrawBox(j * 64, i * 64, j * 64 + 64, i * 64 + 64, GetColor(0, 0, 0), TRUE);
					//DrawRectGraph(j * 64, i * 64, j * 64, i * 64, j * 64 + 64, i * 64 + 64, img_panel, TRUE, FALSE);
}

//�p�l�����S�Ė��܂������A�S�Ė����Ȃ������`�F�b�N����֐�(true=�t�F�[�h�C���Afalse=�t�F�[�h�A�E�g)
bool FadeInOut::CheckAnimation(bool flg)
{
	//�p�l�������܂肫���Ă��Ȃ��A�������͖����Ȃ肫���Ă��Ȃ����false��Ԃ�
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (panel[i][j] == flg)
				return false;

	//�p�l�����S�Ė��܂��Ă���A�������͑S�Ė����Ȃ�����true��Ԃ�
	return true;
}

//�A�j���[�V�����Đ�����֐�
void FadeInOut::SetFadeoutFlg(enum Scene scene)
{
	fadeout_flg = true; //�t�F�[�h�A�E�g�A�j���[�V���������s����
	change_scene = scene; //�ύX����V�[�����i�[����
}

//���݃A�j���[�V�������Đ�����Ă��邩��Ԃ��֐�
bool FadeInOut::GetFadeFlg()
{
	//�A�j���[�V�������Đ�����Ă����true��Ԃ�
	if (fadein_flg == true || fadeout_flg == true)
		return true;
	//�A�j���[�V�������Đ�����Ă��Ȃ����false��Ԃ�
	else
		return false;
}