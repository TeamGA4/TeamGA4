#include "Header.h"

//60fpsで動作するようにする関数
void wait_flame()
{
	static int time = 0;
	int term = GetNowCount() - time;

	if (16 - term > 0)
		Sleep(16 - term);
	time = GetNowCount();

	return;
}

//マウスクリック関数(左上の座標x,左上の座標y,範囲x,範囲y,クリック音声ID)
bool MouseClick(float x, float y, float side, float vertical, int sound_id)
{
	//フェードアウト・フェードインアニメーション中は動作しない
	//if (fade->GetFadeFlg() == false)
	//{
		//クリックを押した時の座標と、離した時の座標が共に選択範囲内にあればtrueを返す
		//それ以外はfalseを返す

		static int click_x = -1; //クリックを押した時の座標
		static int click_y = -1;

		//クリックされている時
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			//クリックを押した時の座標を取得
			GetMousePoint(&click_x, &click_y);
		}
		//クリックされていない時
		else
		{
			//クリックを離した時の座標を取得
			int separate_x, separate_y;
			GetMousePoint(&separate_x, &separate_y);

			//クリックを押した時の座標と、離した時の座標が共に選択範囲内にあればtrueを返す
			if (click_x >= x &&
				click_y >= y &&
				click_x <= x + side &&
				click_y <= y + vertical &&
				separate_x >= x &&
				separate_y >= y &&
				separate_x <= x + side &&
				separate_y <= y + vertical)
			{
				//クリック音を再生
				//static int se_click_1 = LoadSoundMem("asset\\sound\\se_click_1.mp3");
				//static int se_click_2 = LoadSoundMem("asset\\sound\\se_click_2.mp3");
				//static int se_diceroll = LoadSoundMem("asset\\sound\\se_diceroll.mp3");

				//if (sound_id == 1)
				//	PlaySoundMem(se_click_1, DX_PLAYTYPE_BACK); //決定音を再生

				//else if (sound_id == 2)
				//	PlaySoundMem(se_click_2, DX_PLAYTYPE_BACK); //キャンセル音を再生

				//else if (sound_id == 3)
				//	PlaySoundMem(se_diceroll, DX_PLAYTYPE_BACK); //サイコロを振る音を再生

				click_x = -1;
				click_y = -1;

				return true;
			}
		}
	//}

	return false;
}