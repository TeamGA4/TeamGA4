#pragma once

#include <stdio.h>

#include "DxLib.h"

using namespace std;

//�E�B���h�E�T�C�Y
#define WINDOW_SIDE 1120
#define WINDOW_VERTICAL 840

//���W�f�[�^
struct Pos
{
	float x, y;
};

//�y�Ȃ̏o���m�[�c���
struct MusicNotes
{
	int flame; //�^�b�v�^�C�~���O(�t���[��)
	int lane; //�o�����[��
	int type; //���
	float length; //����(�����O�m�[�c�̏ꍇ�̂�)
};

//60fps�œ��삷��悤�ɂ���֐�
void wait_flame();

//�y�ȃN���X
class MusicGame
{
private:
	char music_name[256]; //�Ȗ�
	int sound; //�y�Ȃ̉����f�[�^
	int notes_speed; //�m�[�c���x
	int elapsed_flame; //�y�Ȍo�ߎ���(�t���[���P��)
public:
	MusicGame(char name[], int speed); //�R���X�g���N�^
	void Action(); //�A�N�V����
	void Draw(); //�h���[
	void LoadMusic(char music_name[]); //�y�ȏ��ǂݍ��݊֐�
};

//�m�[�c�N���X
class Notes
{
private:
	Pos pos; //���W
	unsigned int notes_type; //�m�[�c�^�C�v(1=���ʃm�[�c�A2=�����O�m�[�c�A3=�G�N�X�g���m�[�c)
	unsigned int notes_speed; //�m�[�c���x
	float notes_length; //�����O�m�[�c�̒���(�t���[����)
	bool delete_flg; //�����t���O
public:
	Notes(int lane, int speed, int type, float length); //�R���X�g���N�^
	void Action(); //�A�N�V����
	void Draw(); //�h���[
	bool GetDeleteFlg(); //�����t���O�擾�֐�
};