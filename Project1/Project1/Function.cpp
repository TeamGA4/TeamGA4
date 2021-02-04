#include "Header.h"

//60fps�œ��삷��悤�ɂ���֐�
void wait_flame()
{
	static int time = 0;
	int term = GetNowCount() - time;

	if (16 - term > 0)
		Sleep(16 - term);
	time = GetNowCount();

	return;
}

//�}�E�X�N���b�N�֐�(����̍��Wx,����̍��Wy,�͈�x,�͈�y,�N���b�N����ID)
bool MouseClick(float x, float y, float side, float vertical, int sound_id)
{
	//�t�F�[�h�A�E�g�E�t�F�[�h�C���A�j���[�V�������͓��삵�Ȃ�
	//if (fade->GetFadeFlg() == false)
	//{
		//�N���b�N�����������̍��W�ƁA���������̍��W�����ɑI��͈͓��ɂ����true��Ԃ�
		//����ȊO��false��Ԃ�

		static int click_x = -1; //�N���b�N�����������̍��W
		static int click_y = -1;

		//�N���b�N����Ă��鎞
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			//�N���b�N�����������̍��W���擾
			GetMousePoint(&click_x, &click_y);
		}
		//�N���b�N����Ă��Ȃ���
		else
		{
			//�N���b�N�𗣂������̍��W���擾
			int separate_x, separate_y;
			GetMousePoint(&separate_x, &separate_y);

			//�N���b�N�����������̍��W�ƁA���������̍��W�����ɑI��͈͓��ɂ����true��Ԃ�
			if (click_x >= x &&
				click_y >= y &&
				click_x <= x + side &&
				click_y <= y + vertical &&
				separate_x >= x &&
				separate_y >= y &&
				separate_x <= x + side &&
				separate_y <= y + vertical)
			{
				//�N���b�N�����Đ�
				//static int se_click_1 = LoadSoundMem("asset\\sound\\se_click_1.mp3");
				//static int se_click_2 = LoadSoundMem("asset\\sound\\se_click_2.mp3");
				//static int se_diceroll = LoadSoundMem("asset\\sound\\se_diceroll.mp3");

				//if (sound_id == 1)
				//	PlaySoundMem(se_click_1, DX_PLAYTYPE_BACK); //���艹���Đ�

				//else if (sound_id == 2)
				//	PlaySoundMem(se_click_2, DX_PLAYTYPE_BACK); //�L�����Z�������Đ�

				//else if (sound_id == 3)
				//	PlaySoundMem(se_diceroll, DX_PLAYTYPE_BACK); //�T�C�R����U�鉹���Đ�

				click_x = -1;
				click_y = -1;

				return true;
			}
		}
	//}

	return false;
}