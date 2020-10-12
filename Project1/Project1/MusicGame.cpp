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
	LoadMusic(music_name);
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
		(*i)->Action();
		(*i)->Draw();
	}

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
}

//ドロー
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

//楽曲情報読み込み関数(引数　読み込むノーツデータの曲名)
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