#include <stdlib.h>
#include <iostream>

#include "DxLib.h"
#include "Header.h"

using namespace std;

//グローバル変数定義
bool push = false;
enum Scene game_scene = SceneTitle;
Result* result = new Result();

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

	//フォントの読み込み
	LPCSTR font_path = "font\\PixelMplus12-Regular.ttf";

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {}
	//フォント読込エラー処理
	else
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);

	//フォントの変更
	ChangeFont("PixelMplus12", DX_CHARSET_DEFAULT);

	//描画先の変更
	SetDrawScreen(DX_SCREEN_BACK);

	//BGMの読み込み
	int bgm_menu;
	bgm_menu = LoadSoundMem("Music\\menu.mp3");

	//クラスの作成
	Title* title = new Title();

	//CharaSelect* charaselect = new CharaSelect();

	MusicSelect* music_select = new MusicSelect();

	MusicGame* music_game = new MusicGame("マ・メール・ロワ", 5);

	result = new Result();

	//メインループ
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

		//画面の更新
		ScreenFlip();
		ClearDrawScreen();

		wait_flame();
	}

	DxLib_End();

	return 0;//ソフトの終了
}