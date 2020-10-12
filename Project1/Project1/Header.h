#pragma once

#include <stdio.h>

#include "DxLib.h"

using namespace std;

//ウィンドウサイズ
#define WINDOW_SIDE 1120
#define WINDOW_VERTICAL 840

//座標データ
struct Pos
{
	float x, y;
};

//楽曲の出現ノーツ情報
struct MusicNotes
{
	int flame; //タップタイミング(フレーム)
	int lane; //出現レーン
	int type; //種類
	float length; //長さ(ロングノーツの場合のみ)
};

//60fpsで動作するようにする関数
void wait_flame();

//楽曲クラス
class MusicGame
{
private:
	char music_name[256]; //曲名
	int sound; //楽曲の音声データ
	int notes_speed; //ノーツ速度
	int elapsed_flame; //楽曲経過時間(フレーム単位)
public:
	MusicGame(char name[], int speed); //コンストラクタ
	void Action(); //アクション
	void Draw(); //ドロー
	void LoadMusic(char music_name[]); //楽曲情報読み込み関数
};

//ノーツクラス
class Notes
{
private:
	Pos pos; //座標
	unsigned int notes_type; //ノーツタイプ(1=普通ノーツ、2=ロングノーツ、3=エクストラノーツ)
	unsigned int notes_speed; //ノーツ速度
	float notes_length; //ロングノーツの長さ(フレーム数)
	bool delete_flg; //消去フラグ
public:
	Notes(int lane, int speed, int type, float length); //コンストラクタ
	void Action(); //アクション
	void Draw(); //ドロー
	bool GetDeleteFlg(); //消去フラグ取得関数
};