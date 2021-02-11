#pragma warning(disable:4996)

#include <list>

#include "Header.h"

//リスト(ノーツ用)
list<Notes*>notes;

//リストの初期化(ノーツ用)
auto a = new Notes(0, 780, 0, 0);

//リスト(楽曲の出現ノーツ情報用)
list<MusicNotes*>music;

//リストの初期化(楽曲の出現ノーツ情報用)
auto b = new MusicNotes{ 0,0,0,0 };

//コンストラクタ(引数　曲名、ノーツ速度)
MusicGame::MusicGame(char name[], int level, float speed)
{
	img = LoadGraph("image\\backnotes.jpg");//ノーツライン背景読み込み

	backimg = LoadGraph("image\\backimage.jpg");//全面背景読み込み

	//曲名を設定
	strcpy(music_name, name);

	//音声ファイル読み込み
	char str[256] = "Music\\";
	strcat(str, music_name);
	strcat(str, ".mp3");
	sound = LoadSoundMem(str);

	//ノーツ速度を設定
	notes_speed = speed;

	//時間初期化
	elapsed_flame = 0;

	//総合ノーツ数初期化
	max_notes = 0;

	//リスト初期化
	for (auto i = notes.begin(); i != notes.end();)
	{
		delete(*i); //オブジェクトを削除
		i = notes.erase(i); //リストから削除＆リストの繋ぎ変え
	}

	for (auto i = music.begin(); i != music.end();)
	{
		delete(*i); //オブジェクトを削除
		i = music.erase(i); //リストから削除＆リストの繋ぎ変え
	}

	//楽曲情報を読み込み
	LoadMusicNotes(music_name, level);

	//判定のテキスト情報初期化
	for (int i = 0; i < 4; i++)
	{
		strcpy(judg_txt[i], "\0");
		judg_txt_time[i] = 0;
	}
	
	//キー長押し制御初期化
	longpush_ctrl[0] = false;
	longpush_ctrl[1] = false;
	longpush_ctrl[2] = false;
	longpush_ctrl[3] = false;

	//コンボ数初期化
	combo = 0;

	//スコア初期化
	score = 0;

	//READY初期化
	ready_x = -320;
}

//アクション
void MusicGame::Action()
{
	static bool play_flg = false;

	//フェードアウト・フェードインアニメーション中は動作しない
	if (fade->GetFadeFlg() == false)
	{
		//経過時間加算
		elapsed_flame++;

		//READYテキスト処理
		if (elapsed_flame <= 60 || elapsed_flame >= 120 && play_flg == false)
		{
			ready_x += 8;
		}

		//120フレーム(2秒)経過、かつ楽曲が再生されていない場合、再生する
		if (CheckSoundMem(sound) == false && elapsed_flame > 300 && play_flg == false)
		{
			PlaySoundMem(sound, DX_PLAYTYPE_BACK);
			play_flg = true;
		}

		//楽曲終了処理
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

	//ノーツの生成
	for (auto i = music.begin(); i != music.end(); i++)
	{
		if (elapsed_flame == (*i)->flame - 600 / notes_speed + 300)
		{
			a = new Notes((*i)->lane, notes_speed, (*i)->type, (*i)->length - (*i)->flame);
			notes.push_back(a);
		}
	}

	//ノーツの処理
	for (auto i = notes.begin(); i != notes.end(); i++)
	{
		//入力処理

		Pos pos = (*i)->GetNotesPos(); //ノーツの座標取得
		int type = (*i)->GetNotesType();
		int length = (*i)->GetNotesLength();

		//D(1列目)が入力された時
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

		//F(2列目)が入力された時
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

		//J(3列目)が入力された時
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

		//K(4列目)が入力された時
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

		//画面外に出た時の処理
		if (pos.y > WINDOW_VERTICAL&&type != 2 ||
			pos.y - notes_speed * length > WINDOW_VERTICAL&&type == 2)
		{
			int line = (pos.x - 140) / 90;
			strcpy(judg_txt[line], "ＭＩＳＳ");
			combo = 0;
			judg_txt_time[line] = 0;
			(*i)->SetDeleteFlg(true);
		}

		(*i)->Action();
	}

	//長押し制御
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

	//ノーツのリストの整理
	for (auto i = notes.begin(); i != notes.end(); i++)
	{
		if ((*i)->GetDeleteFlg() == true)
		{
			delete(*i); //オブジェクトを削除
			i = notes.erase(i); //リストから削除＆リストの繋ぎ変え
			break;
		}
	}

	//曲選択画面に戻る処理
	if (MouseClick(16, 568, 64, 64, 0) == true)
	{
		play_flg = false;
		StopSoundMem(sound);
		fade->SetFadeoutFlg(SceneMusicSelect);
	}
}

//ドロー
void MusicGame::Draw()
{
	DrawGraph(0, 0, backimg, TRUE); //ノーツライン背景

	DrawExtendGraph(140, 0, 500, 640, img, TRUE); //ノーツライン背景

	//戻るボタン描画
	SetFontSize(64);
	DrawString(16, 568, "←", GetColor(0, 255, 0));

	//コンボ数描画
	if (ready_x >= 640)
	{
		if (combo < 10)
			DrawFormatString(306, 256, GetColor(255, 255, 255), "%d", combo);
		else
			DrawFormatString(290, 256, GetColor(255, 255, 255), "%d", combo);
		SetFontSize(32);
		DrawFormatString(278, 320, GetColor(255, 255, 255), "COMBO", combo);
	}

	//ノーツの描画
	for (auto i = notes.begin(); i != notes.end(); i++)
	{
		(*i)->Draw();
	}

	//フレーム数表示
	/*char time[256];
	sprintf_s(time, 256, "%d", elapsed_flame);
	DrawString(0, 0, time, GetColor(255, 0, 0));*/

	//横線
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

	//縦線
	DrawLine(140, 0, 140, 840, GetColor(0, 0, 0));
	DrawLine(230, 0, 230, 840, GetColor(0, 0, 0));
	DrawLine(320, 0, 320, 840, GetColor(0, 0, 0));
	DrawLine(410, 0, 410, 840, GetColor(0, 0, 0));
	DrawLine(500, 0, 500, 840, GetColor(0, 0, 0));

	//判定表示
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

	//スコア表示
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

	//READYテキスト描画
	if (CheckSoundMem(sound) == false)
	{
		SetFontSize(64);
		DrawString(ready_x, 288, "ＲＥＡＤＹ", GetColor(255, 0, 0));
	}
}

//楽曲情報読み込み関数(引数　読み込むノーツデータの曲名)
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

	//ファイルを開く
	fp = fopen(fname, "r");

	//指定したファイルが見つからない場合
	if (fp == NULL)
	{
		return;
	}

	//ファイルから楽曲のノーツデータを読み込む
	while ((ret = fscanf(fp, "%d,%d,%d,%f", &flame, &lane, &type, &length) != EOF))
	{
		//読み込んだデータを楽曲の出現ノーツ情報リストに登録
		b = new MusicNotes{ flame,lane,type,length };
		music.push_back(b);

		//総合ノーツ数加算
		max_notes++;
	}

	//ファイルを閉じる
	fclose(fp);
}

//ノーツ入力処理
bool MusicGame::PushNotesButton(Pos notes_pos, unsigned int notes_type, int line)
{
	if ((int)notes_pos.x - 140 == line * 90)
	{
		//GOOD判定
		if (notes_pos.y >= 600 - notes_speed * 2 &&
			notes_pos.y <= 600 + notes_speed * 2 ||
			notes_type == 3 &&
			notes_pos.y >= 600 - notes_speed * 4 &&
			notes_pos.y <= 600 + notes_speed * 4)
		{
			strcpy(judg_txt[line], "ＧＯＯＤ");
			combo++;
			score += 100;
			judg_txt_time[line] = 0;
			if (notes_type != 2 ||
				notes_type == 2 && longpush_ctrl[line] == true)
			{
				return true;
			}
		}
		//NEAR判定
		else if (notes_pos.y >= 600 - notes_speed * 4 &&
			notes_pos.y <= 600 + notes_speed * 4)
		{
			strcpy(judg_txt[line], "ＮＥＡＲ");
			combo++;
			score += 50;
			judg_txt_time[line] = 0;
			if (notes_type != 2 ||
				notes_type == 2 && longpush_ctrl[line] == true)
			{
				return true;
			}
		}
		//MISS判定
		else if (notes_pos.y >= 600 - notes_speed * 6 &&
			notes_pos.y <= 600 + notes_speed * 6)
		{
			strcpy(judg_txt[line], "ＭＩＳＳ");
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

//ノーツ入力処理(ロングノーツ、キー離した時用)
//bool MusicGame::ReleaseNotesButton(Pos notes_pos, float notes_length, unsigned int notes_type, int line)
//{
//	if ((int)notes_pos.x - 380 == line * 90 && longpush_ctrl[line] == true && notes_type == 2)
//	{
//		//GOOD判定
//		if (notes_pos.y - notes_speed * notes_length >= 600 - notes_speed * 2 &&
//			notes_pos.y - notes_speed * notes_length <= 600 + notes_speed * 2)
//		{
//			strcpy(judg_txt[line], "ＧＯＯＤ");			
//			combo++;
//			score += 100;
//			judg_txt_time[line] = 0;
//			return true;
//		}
//		//NEAR判定
//		else if (notes_pos.y - notes_speed * notes_length >= 600 - notes_speed * 4 &&
//			notes_pos.y - notes_speed * notes_length <= 600 + notes_speed * 4)
//		{
//			strcpy(judg_txt[line], "ＮＥＡＲ");
//			combo++;
//			score += 50;
//			judg_txt_time[line] = 0;
//			return true;
//		}
//		//MISS判定
//		else if (notes_pos.y - notes_speed * notes_length >= 600 - notes_speed * 6 &&
//			notes_pos.y - notes_speed * notes_length <= 600 + notes_speed * 6)
//		{
//			strcpy(judg_txt[line], "ＭＩＳＳ");
//			combo = 0;
//			judg_txt_time[line] = 0;
//			return true;
//		}
//	}
//
//	return false;
//}
