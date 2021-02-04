#include <stdlib.h>
#include <iostream>

#include "DxLib.h"
#include "Header.h"

using namespace std;

//�O���[�o���ϐ���`
bool push = false;
enum Scene game_scene = SceneTitle;
Result* result = new Result();

//���C��
int WINAPI WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//window�̐ݒ�

	//SetMainWindowText("��������"); //window�̖��O
	ChangeWindowMode(TRUE); //window���[�h
	SetGraphMode(WINDOW_SIDE, WINDOW_VERTICAL, 32); //window�T�C�Y
	SetAlwaysRunFlag(TRUE); //�o�b�N�O���E���h�ł������悤�ɐݒ�
	SetDoubleStartValidFlag(TRUE); //���d�N���̋���

	//dx���C�u����������
	if (DxLib_Init() == -1) return -1; //�G���[���N������I��

	//�t�H���g�̓ǂݍ���
	LPCSTR font_path = "font\\PixelMplus12-Regular.ttf";

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {}
	//�t�H���g�Ǎ��G���[����
	else
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);

	//�t�H���g�̕ύX
	ChangeFont("PixelMplus12", DX_CHARSET_DEFAULT);

	//�`���̕ύX
	SetDrawScreen(DX_SCREEN_BACK);

	//BGM�̓ǂݍ���
	int bgm_menu;
	bgm_menu = LoadSoundMem("Music\\menu.mp3");

	//�N���X�̍쐬
	Title* title = new Title();

	//CharaSelect* charaselect = new CharaSelect();

	MusicSelect* music_select = new MusicSelect();

	MusicGame* music_game = new MusicGame("�}�E���[���E����", 5);

	result = new Result();

	//���C�����[�v
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (ProcessMessage() == -1)
			break;

		switch (game_scene)
		{
		case SceneTitle:
		{
			if (CheckSoundMem(bgm_menu) == false)
				PlaySoundMem(bgm_menu, DX_PLAYTYPE_BACK);

			title->Action();
			title->Draw();
			break;
		}
		/*case Charaselect:
		{
			charaselect->Action();
			charaselect->Draw();
			break;
		}*/

		case SceneMusicSelect:
		{
			if (CheckSoundMem(bgm_menu) == false)
				PlaySoundMem(bgm_menu, DX_PLAYTYPE_BACK);

			music_select->Action();
			music_select->Draw();
			break;
		}

		case SceneMusicGame:
		{
			if (CheckSoundMem(bgm_menu) == true)
				StopSoundMem(bgm_menu);

			music_game->Action();
			music_game->Draw();
			break;
		}

		case SceneResult:
		{
			if (CheckSoundMem(bgm_menu) == false)
				PlaySoundMem(bgm_menu, DX_PLAYTYPE_BACK);

			result->Action();
			result->Draw();
			break;
		}

		default:
			break;
		}

		//��ʂ̍X�V
		ScreenFlip();
		ClearDrawScreen();

		wait_flame();
	}

	DxLib_End();

	return 0;//�\�t�g�̏I��
}