#include <stdlib.h>
#include <iostream>

#include "DxLib.h"
#include "Header.h"

using namespace std;

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

	//dx���C�u����������NN
	if (DxLib_Init() == -1) return -1; //�G���[���N������I��

	//�`���̕ύX
	SetDrawScreen(DX_SCREEN_BACK);

	char music_name[] = "Battle";
	MusicGame* music_game = new MusicGame(music_name, 8);

	//���C�����[�v
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (ProcessMessage() == -1)
			break;

		music_game->Action();
		music_game->Draw();

		//��ʂ̍X�V
		ScreenFlip();
		ClearDrawScreen();

		wait_flame();
	}

	DxLib_End();

	return 0;//�\�t�g�̏I��
}