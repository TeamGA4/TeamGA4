#include "Header.h"

//�R���X�g���N�^(�����@�m�[�c�o�����[���A�m�[�c���x�A�m�[�c�^�C�v�A�����O�m�[�c�̏ꍇ�̒���(�t���[����))
Notes::Notes(int lane, int speed, int type, float length)
{
	//�m�[�c�o�����[���ݒ�
	pos.x = --lane * 90 + 140;
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
	
	//�ʏ�m�[�c�摜�̓ǂݍ���
	imgnotesN =LoadGraph("image\\notesN.png");

	imgnotesL= LoadGraph("image\\notesL.png");

	imgnotesS = LoadGraph("image\\notesS.png");


}

//�A�N�V����
void Notes::Action()
{
	pos.y += notes_speed;

	if (pos.y > WINDOW_VERTICAL&&notes_type == 1 ||
		pos.y - notes_speed * notes_length > WINDOW_VERTICAL&&notes_type == 2)
		delete_flg = true;
}

//�h���[
void Notes::Draw()
{		

	switch (notes_type)
	{

	case 1:
		//�ʏ�m�[�c�摜�Ăяo��
		DrawGraph(pos.x, pos.y, imgnotesN, TRUE);

		break;
	case 2:
		DrawBox(pos.x, pos.y - notes_speed * notes_length, pos.x + 90, pos.y, GetColor(75, 75, 255), TRUE);

		DrawGraph(pos.x, pos.y - notes_speed * notes_length, imgnotesL, TRUE);

		DrawGraph(pos.x , pos.y, imgnotesL, TRUE);

		break;
	case 3:
		//�X�y�V�����m�[�c�摜�Ăяo��
		DrawGraph(pos.x, pos.y, imgnotesS, TRUE);

		break;
	default:
		break;
	}
}

//�m�[�c���W�擾�֐�
Pos Notes::GetNotesPos()
{
	return pos;
}

//�m�[�c�^�C�v�擾�֐�
int Notes::GetNotesType()
{
	return notes_type;
}

//�����O�m�[�c�̒����擾�֐�
float Notes::GetNotesLength()
{
	return notes_length;
}

//�����t���O�ݒ�֐�
void Notes::SetDeleteFlg(bool flg)
{
	delete_flg = flg;
}

//�����t���O�擾�֐�
bool Notes::GetDeleteFlg()
{
	return delete_flg;
}