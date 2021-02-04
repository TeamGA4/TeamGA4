#include <stdlib.h>
#include <iostream>

#include "DxLib.h"
#include "Header.h"

using namespace std;

enum Scene game_scene = Musicgame;

//メイン
int WINAPI WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//windowの設定

	//SetMainWindowText("ああああ"); //windowの名前
	ChangeWindowMode(TRUE); //windowモード
	SetGraphMode(WINDOW_SIDE, WINDOW_VERTICAL, 32); //windowサイズ
	SetAlwaysRunFlag(TRUE); //バックグラウンドでも動くように設定
	SetDoubleStartValidFlag(TRUE); //多重起動の許可

	//dxライブラリ初期化
	if (DxLib_Init() == -1) return -1; //エラーが起きたら終了

	//描画先の変更
	SetDrawScreen(DX_SCREEN_BACK);

	CharaSelect* charaselect = new CharaSelect();

	char music_name[] = "マ・メール・ロワ";
	MusicGame* music_game = new MusicGame(music_name, 10);

	//メインループ
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (ProcessMessage() == -1)
			break;

		switch (game_scene)
		{
		case Charaselect:
		{
			charaselect->Action();
			charaselect->Draw();
			break;
		}

		case Musicgame:
		{
			music_game->Action();
			music_game->Draw();
			break;
		}

		default:
			break;
		}

		//画面の更新
		ScreenFlip();
		ClearDrawScreen();

		wait_flame();
	}

	DxLib_End();

	return 0;//ソフトの終了
}