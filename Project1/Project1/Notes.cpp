#include "Header.h"

//コンストラクタ(引数　ノーツ出現レーン、ノーツ速度、ノーツタイプ、ロングノーツの場合の長さ(フレーム数))
Notes::Notes(int lane, int speed, int type, float length)
{
	//ノーツ出現レーン設定
	pos.x = --lane * 90 + 140;
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
	
	//通常ノーツ画像の読み込み
	imgnotesN =LoadGraph("image\\notesN.png");

	imgnotesL= LoadGraph("image\\notesL.png");

	imgnotesS = LoadGraph("image\\notesS.png");


}

//アクション
void Notes::Action()
{
	pos.y += notes_speed;

	if (pos.y > WINDOW_VERTICAL&&notes_type == 1 ||
		pos.y - notes_speed * notes_length > WINDOW_VERTICAL&&notes_type == 2)
		delete_flg = true;
}

//ドロー
void Notes::Draw()
{		

	switch (notes_type)
	{

	case 1:
		//通常ノーツ画像呼び出し
		DrawGraph(pos.x, pos.y, imgnotesN, TRUE);

		break;
	case 2:
		DrawBox(pos.x, pos.y - notes_speed * notes_length, pos.x + 90, pos.y, GetColor(75, 75, 255), TRUE);

		DrawGraph(pos.x, pos.y - notes_speed * notes_length, imgnotesL, TRUE);

		DrawGraph(pos.x , pos.y, imgnotesL, TRUE);

		break;
	case 3:
		//スペシャルノーツ画像呼び出し
		DrawGraph(pos.x, pos.y, imgnotesS, TRUE);

		break;
	default:
		break;
	}
}

//ノーツ座標取得関数
Pos Notes::GetNotesPos()
{
	return pos;
}

//ノーツタイプ取得関数
int Notes::GetNotesType()
{
	return notes_type;
}

//ロングノーツの長さ取得関数
float Notes::GetNotesLength()
{
	return notes_length;
}

//消去フラグ設定関数
void Notes::SetDeleteFlg(bool flg)
{
	delete_flg = flg;
}

//消去フラグ取得関数
bool Notes::GetDeleteFlg()
{
	return delete_flg;
}