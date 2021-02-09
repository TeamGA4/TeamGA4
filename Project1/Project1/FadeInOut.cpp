#include "Header.h"

//コンストラクタ
FadeInOut::FadeInOut()
{
	img_panel = LoadGraph("image\\backimage.jpg");//全面背景読み込み

	fadein_flg = false; //フェードアウト制御初期化
	fadeout_flg = false; //フェードイン制御初期化
	change_scene = SceneTitle; //変更シーン初期化

	//パネル初期化
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
			panel[i][j] = false;
}

//アクション
void FadeInOut::Action()
{
	static int time = 0;

	//フェードアウトアニメーションの処理
	if (fadeout_flg == true)
	{
		time++;

		if (time % 2 == 0)
		{
			//／に画面を覆っていく
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

		//画面全てがパネルで覆われた時、ゲームシーンを変更し、フェードインアニメーションを開始する
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

	//フェードインアニメーションの処理
	else if (fadein_flg == true)
	{
		time++;

		if (time % 2 == 0)
		{
			//／に画面を開いていく
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

		//画面全てのパネルが無くなった時、アニメーションを終了する
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

//ドロー
void FadeInOut::Draw()
{
	//パネルの描画
	if (fadeout_flg == true || fadein_flg == true)
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				if (panel[i][j] == true)
					DrawBox(j * 64, i * 64, j * 64 + 64, i * 64 + 64, GetColor(0, 0, 0), TRUE);
					//DrawRectGraph(j * 64, i * 64, j * 64, i * 64, j * 64 + 64, i * 64 + 64, img_panel, TRUE, FALSE);
}

//パネルが全て埋まったか、全て無くなったかチェックする関数(true=フェードイン、false=フェードアウト)
bool FadeInOut::CheckAnimation(bool flg)
{
	//パネルが埋まりきっていない、もしくは無くなりきっていなければfalseを返す
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (panel[i][j] == flg)
				return false;

	//パネルが全て埋まっている、もしくは全て無くなったらtrueを返す
	return true;
}

//アニメーション再生制御関数
void FadeInOut::SetFadeoutFlg(enum Scene scene)
{
	fadeout_flg = true; //フェードアウトアニメーションを実行する
	change_scene = scene; //変更するシーンを格納する
}

//現在アニメーションが再生されているかを返す関数
bool FadeInOut::GetFadeFlg()
{
	//アニメーションが再生されていればtrueを返す
	if (fadein_flg == true || fadeout_flg == true)
		return true;
	//アニメーションが再生されていなければfalseを返す
	else
		return false;
}