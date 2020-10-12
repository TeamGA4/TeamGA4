#include "Header.h"

//�R���X�g���N�^(�����@�m�[�c�o�����[���A�m�[�c���x�A�m�[�c�^�C�v�A�����O�m�[�c�̏ꍇ�̒���(�t���[����))
Notes::Notes(int lane, int speed, int type, float length)
{
	//�m�[�c�o�����[���ݒ�
	pos.x = --lane * 90;
	pos.y = 780;
	do { pos.y -= speed; } while (pos.y > 0);

	//�m�[�c���x�ݒ�
	notes_speed = speed;

	//�m�[�c�^�C�v�ݒ�
	notes_type = type;

	//�����O�m�[�c�̏ꍇ�̒����ݒ�(�t���[����)
	notes_length = length;

	//�m�[�c�폜�t���O�̐ݒ�
	delete_flg = false;
}

//�A�N�V����
void Notes::Action()
{
	pos.y += notes_speed;

	if (pos.y > WINDOW_VERTICAL)
		delete_flg = true;
}

//�h���[
void Notes::Draw()
{
	DrawLine(pos.x + 60, pos.y, pos.x + 150, pos.y, GetColor(0, 255, 0));
}

//�����t���O�擾�֐�
bool Notes::GetDeleteFlg()
{
	return delete_flg;
}