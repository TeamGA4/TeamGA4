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
MusicGame::MusicGame(char name[], int speed)
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

	//楽曲情報を読み込み
	LoadMusicNotes(music_name);

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

	//体力初期化
	life = 1000;
}

//アクション
void MusicGame::Action()
{
	//経過時間加算
	elapsed_flame++;

	//120フレーム(2秒)経過、かつ楽曲が再生されていない場合、再生する
	if (CheckSoundMem(sound) == false && elapsed_flame > 120)
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);

	//ノーツの生成
	for (auto i = music.begin(); i != music.end(); i++)
	{
		if (elapsed_flame == (*i)->flame - 780 / notes_speed + 120)
		{
			a = new Notes((*i)->lane, notes_speed, (*i)->type, (*i)->length - (*i)->flame);
			notes.push_back(a);
		}
	}

	//ノーツの処理
	for (auto i = notes.begin(); i != notes.end(); i++)
	{
		//入力処理

		Pos notes_pos = (*i)->GetNotesPos(); //ノーツの座標取得

		//D(1列目)が入力された時
		if (CheckHitKey(KEY_INPUT_D) == true)
			if (PushNotesButton((*i)->GetNotesPos(), (*i)->GetNotesType(), 0) == true)
				(*i)->SetDeleteFlg(true);
		else
			if (ReleaseNotesButton((*i)->GetNotesPos(), (*i)->GetNotesLength(), (*i)->GetNotesType(), 0) == true)
				(*i)->SetDeleteFlg(true);

		//F(2列目)が入力された時
		if (CheckHitKey(KEY_INPUT_F) == true)
			if (PushNotesButton((*i)->GetNotesPos(), (*i)->GetNotesType(), 1) == true)
				(*i)->SetDeleteFlg(true);
		else
			if (ReleaseNotesButton((*i)->GetNotesPos(), (*i)->GetNotesLength(), (*i)->GetNotesType(), 1) == true)
				(*i)->SetDeleteFlg(true);

		//J(3列目)が入力された時
		if (CheckHitKey(KEY_INPUT_J) == true)
			if (PushNotesButton((*i)->GetNotesPos(), (*i)->GetNotesType(), 2) == true)
				(*i)->SetDeleteFlg(true);
		else
			if (ReleaseNotesButton((*i)->GetNotesPos(), (*i)->GetNotesLength(), (*i)->GetNotesType(), 2) == true)
				(*i)->SetDeleteFlg(true);

		//K(4列目)が入力された時
		if (CheckHitKey(KEY_INPUT_K) == true)
			if (PushNotesButton((*i)->GetNotesPos(), (*i)->GetNotesType(), 3) == true)
				(*i)->SetDeleteFlg(true);
		else
			if (ReleaseNotesButton((*i)->GetNotesPos(), (*i)->GetNotesLength(), (*i)->GetNotesType(), 3) == true)
				(*i)->SetDeleteFlg(true);

		(*i)->Action();
	}

	//キーが押されていない場合、長押し制御解除
	if (CheckHitKey(KEY_INPUT_D) == false)
		longpush_ctrl[0] = false;
	if (CheckHitKey(KEY_INPUT_F) == false)
		longpush_ctrl[1] = false;
	if (CheckHitKey(KEY_INPUT_J) == false)
		longpush_ctrl[2] = false;
	if (CheckHitKey(KEY_INPUT_K) == false)
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

	//if (life <=0)
	//{

	//}
}

//ドロー
void MusicGame::Draw()
{
	DrawExtendGraph(0, 0, 0 + 626*2, 0 + 417*2.1, backimg, TRUE);//ノーツライン背景

	DrawExtendGraph(380, 0,380+626/1.73,0+417*2.1, img, TRUE);//ノーツライン背景

		//ノーツの描画
	for (auto i = notes.begin(); i != notes.end(); i++)
	{
		(*i)->Draw();
	}


	//フレーム数表示
	char time[256];
	sprintf_s(time, 256, "%d", elapsed_flame);
	DrawString(0, 0, time, GetColor(255, 0, 0));

	//横線
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

	//縦線
	DrawLine(380, 0, 380, 840, GetColor(0, 0, 0));
	DrawLine(470, 0, 470, 840, GetColor(0, 0, 0));
	DrawLine(560, 0, 560, 840, GetColor(0, 0, 0));
	DrawLine(650, 0, 650, 840, GetColor(0, 0, 0));
	DrawLine(740, 0, 740, 840, GetColor(0, 0, 0));

	//判定表示
	for (int i = 0; i < 4; i++)
	{
		DrawString(390 + i * 90, 720, judg_txt[i], GetColor(255, 0, 0));
		judg_txt_time[i]++;
		if (judg_txt_time[i] > 15)
		{
			strcpy(judg_txt[i], "\0");
			judg_txt_time[i] = 0;
		}

		DrawFormatString(100, 100, GetColor(0, 0, 0), "コンボ\n%d", combo);

		DrawFormatString(200, 100, GetColor(0, 0, 0), "スコア\n%d", score);
	
		DrawFormatString(100, 200, GetColor(0, 0, 0), "ライフ\n%d", life);

	}

}

//楽曲情報読み込み関数(引数　読み込むノーツデータの曲名)
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

	//ファイルを開く
	fp = fopen(fname, "r");

	//指定したファイルが見つからない場合
	if (fp == NULL)
	{
		fclose(fp); //ファイルを閉じる
		return;
	}

	//ファイルから楽曲のノーツデータを読み込む
	while ((ret = fscanf(fp, "%d,%d,%d,%f", &flame, &lane, &type, &length) != EOF))
	{
		//読み込んだデータを楽曲の出現ノーツ情報リストに登録
		b = new MusicNotes{ flame,lane,type,length };
		music.push_back(b);
	}

	//ファイルを閉じる
	fclose(fp);
}

//ノーツ入力処理
bool MusicGame::PushNotesButton(Pos notes_pos, unsigned int notes_type, int line)
{
	if ((int)notes_pos.x - 380 == line * 90 && longpush_ctrl[line] == false)
	{
		//GOOD判定
		if (notes_pos.y >= 780 - notes_speed * 2 &&
			notes_pos.y <= 780 + notes_speed * 2 ||
			notes_type == 3 &&
			notes_pos.y >= 780 - notes_speed * 4 &&
			notes_pos.y <= 780 + notes_speed * 4)
		{
			strcpy(judg_txt[line], "ＧＯＯＤ");
			combo++;
			score += 100;
			judg_txt_time[line] = 0;
			if (notes_type != 2)
				return true;
		}
		//NEAR判定
		else if (notes_pos.y >= 780 - notes_speed * 4 &&
			notes_pos.y <= 780 + notes_speed * 4)
		{
			strcpy(judg_txt[line], "ＮＥＡＲ");
			combo++;
			score += 50;
			judg_txt_time[line] = 0;
			if (notes_type != 2)
				return true;
		}
		//MISS判定
		else if (notes_pos.y >= 780 - notes_speed * 6 &&
			notes_pos.y <= 780 + notes_speed * 6)
		{
			strcpy(judg_txt[line], "ＭＩＳＳ");
			combo = 0;
			life -= 100;
			judg_txt_time[line] = 0;
			if (notes_type != 2)
				return true;
		}
	}

	longpush_ctrl[line] = true; //キー長押し制御

	return false;
}

//ノーツ入力処理(ロングノーツ、キー離した時用)
bool MusicGame::ReleaseNotesButton(Pos notes_pos, float notes_length, unsigned int notes_type, int line)
{
	if ((int)notes_pos.x-380 == line*90 && longpush_ctrl[line] == true && notes_type == 2)
	{
		//GOOD判定
		if (notes_pos.y - notes_speed * notes_length >= 780 - notes_speed * 2 &&
			notes_pos.y - notes_speed * notes_length <= 780 + notes_speed * 2)
		{
			strcpy(judg_txt[line], "ＧＯＯＤ");			
			combo++;
			score += 100;
			judg_txt_time[line] = 0;
			return true;
		}
		//NEAR判定
		else if (notes_pos.y - notes_speed * notes_length >= 780 - notes_speed * 4 &&
			notes_pos.y - notes_speed * notes_length <= 780 + notes_speed * 4)
		{
			strcpy(judg_txt[line], "ＮＥＡＲ");
			combo++;
			score += 50;
			judg_txt_time[line] = 0;
			return true;
		}
		//MISS判定
		else if (notes_pos.y - notes_speed * notes_length >= 780 - notes_speed * 6 &&
			notes_pos.y - notes_speed * notes_length <= 780 + notes_speed * 6)
		{
			strcpy(judg_txt[line], "ＭＩＳＳ");
			combo=0;
			life -= 100;
			judg_txt_time[line] = 0;
			return true;
		}
	}

	longpush_ctrl[line] = false; //キー長押し制御

	return false;
}
