#pragma once

#include <stdio.h>

#include "DxLib.h"

using namespace std;

//ウィンドウサイズ
#define WINDOW_SIDE 640
#define WINDOW_VERTICAL 640

//楽曲数
#define MUSIC_COUNT 5

//ゲームシーン
enum Scene
{
	//Charaselect,//キャラクター選択画面
	SceneTitle,//タイトル
	SceneMusicSelect,//楽曲選択画面
	SceneMusicGame,//音ゲー部分
	SceneResult,//リザルト画面
};

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

//マウスクリック関数(左上の座標x,左上の座標y,範囲x,範囲y,クリック音声ID)
bool MouseClick(float x, float y, float side, float vertical, int sound_id);

//タイトルクラス
class Title
{
private:
	int background; //背景画像
public:
	Title(); //コンストラクタ
	void Action();
	void Draw();
};

//楽曲選択クラス
class MusicSelect
{
private:
	int background; //背景画像
	int image_vec[8]; //矢印画像
	char music_name[MUSIC_COUNT][256]; //楽曲名
	int music_sound[MUSIC_COUNT]; //楽曲の音声データ

	char pre_str[7][256]; //楽曲表示用の文字列変数
	char level_str[3][256]; //難易度表示用の文字列変数
	float pre_str_y; //楽曲表示用の座標Y
	float level_str_x; //難易度文字列の座標X
	bool up_ani; //文字列上昇アニメーションフラグ
	bool down_ani; //文字列下降アニメーションフラグ
	bool right_ani;
	bool left_ani;

	unsigned char select_item; //選択中の項目情報
	unsigned char select_music; //選択中の楽曲情報
	unsigned char select_level; //選択中の難易度(0=easy 1=normal 2=hard)
public:
	MusicSelect(); //コンストラクタ
	void Action();
	void Draw();
};

//楽曲クラス
class MusicGame
{
private:
	char music_name[256]; //曲名
	int sound; //楽曲の音声データ
	int notes_speed; //ノーツ速度
	int elapsed_flame; //楽曲経過時間(フレーム単位)
	int max_notes; //楽曲の総合ノーツ数

	char judg_txt[4][9]; //判定のテキスト表示
	int judg_txt_time[4]; //判定のテキスト表示時間

	bool longpush_ctrl[4]; //キー長押し制御

	int img;     //ノーツライン背景用
	int backimg; //全面背景用

	int combo;//コンボ用

	int score;//スコア用

public:
	MusicGame(char name[], int speed); //コンストラクタ
	void Action(); //アクション
	void Draw(); //ドロー
	void LoadMusicNotes(char music_name[]); //楽曲情報読み込み関数(曲名,難易度(0=easy 1=normal 2=hard))
	bool PushNotesButton(Pos notes_pos, unsigned int notes_type, int line); //ノーツ入力処理
	//bool ReleaseNotesButton(Pos notes_pos, float notes_length, unsigned int notes_type, int line); //ノーツ入力処理(ロングノーツ、キー離した時用)
};

//ノーツクラス
class Notes
{
private:
	Pos pos; //座標
	unsigned int notes_type; //ノーツタイプ(1=通常ノーツ、2=ロングノーツ、3=エクストラノーツ)
	unsigned int notes_speed; //ノーツ速度
	float notes_length; //ロングノーツの長さ(フレーム数)
	bool delete_flg; //消去フラグ

	int imgnotesN;     //通常ノーツグラフィックハンドル
	int notesN;        //通常ノーツグラフィック

	int imgnotesL;     //ロングノーツグラフィックハンドル
	int notesL;        //ロングノーツグラフィック

	int imgnotesS;     //スペシャルノーツグラフィックハンドル
	int notesS;        //スペシャルノーツグラフィック



public:
	Notes(int lane, int speed, int type, float length); //コンストラクタ
	void Action(); //アクション
	void Draw(); //ドロー
	Pos GetNotesPos(); //ノーツ座標取得関数
	int GetNotesType(); //ノーツタイプ取得関数
	float GetNotesLength(); //ロングノーツの長さ取得関数
	void SetDeleteFlg(bool flg); //消去フラグ設定関数
	bool GetDeleteFlg(); //消去フラグ取得関数
};

//キャラクタークラス
//class CharaSelect
//{
//private:
//
//public:
//	int imgchara;//キャラクター用
//	void Action(); //アクション
//	void Draw(); //ドロー
//};

//リザルトクラス
class Result
{
private:
	int background; //背景画像
	int max_notes; //楽曲の総合ノーツ数
	int score; //スコア
public:
	Result();
	void Action();
	void Draw();
	void SetMaxNotes(int set_notes); //総合ノーツ数変更
	void SetScore(int set_score); //スコア変更
};

//グローバル変数宣言
extern bool push; //キー長押し制御
extern enum Scene game_scene;
extern Result* result;