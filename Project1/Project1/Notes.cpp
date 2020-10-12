#include "Header.h"

//コンストラクタ(引数　ノーツ出現レーン、ノーツ速度、ノーツタイプ、ロングノーツの場合の長さ(フレーム数))
Notes::Notes(int lane, int speed, int type, float length)
{
	//ノーツ出現レーン設定
	pos.x = --lane * 90;
	pos.y = 780;
	do { pos.y -= speed; } while (pos.y > 0);

	//ノーツ速度設定
	notes_speed = speed;

	//ノーツタイプ設定
	notes_type = type;

	//ロングノーツの場合の長さ設定(フレーム数)
	notes_length = length;

	//ノーツ削除フラグの設定
	delete_flg = false;
}

//アクション
void Notes::Action()
{
	pos.y += notes_speed;

	if (pos.y > WINDOW_VERTICAL)
		delete_flg = true;
}

//ドロー
void Notes::Draw()
{
	DrawLine(pos.x + 60, pos.y, pos.x + 150, pos.y, GetColor(0, 255, 0));
}

//消去フラグ取得関数
bool Notes::GetDeleteFlg()
{
	return delete_flg;
}