#pragma once

#include <stdio.h>

#include "DxLib.h"

using namespace std;

//�E�B���h�E�T�C�Y
#define WINDOW_SIDE 640
#define WINDOW_VERTICAL 640

//�y�Ȑ�
#define MUSIC_COUNT 5

//�Q�[���V�[��
enum Scene
{
	//Charaselect,//�L�����N�^�[�I�����
	SceneTitle,//�^�C�g��
	SceneMusicSelect,//�y�ȑI�����
	SceneMusicGame,//���Q�[����
	SceneResult,//���U���g���
};

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

//�}�E�X�N���b�N�֐�(����̍��Wx,����̍��Wy,�͈�x,�͈�y,�N���b�N����ID)
bool MouseClick(float x, float y, float side, float vertical, int sound_id);

//�^�C�g���N���X
class Title
{
private:
	int background; //�w�i�摜
public:
	Title(); //�R���X�g���N�^
	void Action();
	void Draw();
};

//�y�ȑI���N���X
class MusicSelect
{
private:
	int background; //�w�i�摜
	int image_vec[8]; //���摜
	char music_name[MUSIC_COUNT][256]; //�y�Ȗ�
	int music_sound[MUSIC_COUNT]; //�y�Ȃ̉����f�[�^

	char pre_str[7][256]; //�y�ȕ\���p�̕�����ϐ�
	char level_str[3][256]; //��Փx�\���p�̕�����ϐ�
	float pre_str_y; //�y�ȕ\���p�̍��WY
	float level_str_x; //��Փx������̍��WX
	bool up_ani; //������㏸�A�j���[�V�����t���O
	bool down_ani; //�����񉺍~�A�j���[�V�����t���O
	bool right_ani;
	bool left_ani;

	unsigned char select_item; //�I�𒆂̍��ڏ��
	unsigned char select_music; //�I�𒆂̊y�ȏ��
	unsigned char select_level; //�I�𒆂̓�Փx(0=easy 1=normal 2=hard)
public:
	MusicSelect(); //�R���X�g���N�^
	void Action();
	void Draw();
};

//�y�ȃN���X
class MusicGame
{
private:
	char music_name[256]; //�Ȗ�
	int sound; //�y�Ȃ̉����f�[�^
	int notes_speed; //�m�[�c���x
	int elapsed_flame; //�y�Ȍo�ߎ���(�t���[���P��)
	int max_notes; //�y�Ȃ̑����m�[�c��

	char judg_txt[4][9]; //����̃e�L�X�g�\��
	int judg_txt_time[4]; //����̃e�L�X�g�\������

	bool longpush_ctrl[4]; //�L�[����������

	int img;     //�m�[�c���C���w�i�p
	int backimg; //�S�ʔw�i�p

	int combo;//�R���{�p

	int score;//�X�R�A�p

public:
	MusicGame(char name[], int speed); //�R���X�g���N�^
	void Action(); //�A�N�V����
	void Draw(); //�h���[
	void LoadMusicNotes(char music_name[]); //�y�ȏ��ǂݍ��݊֐�(�Ȗ�,��Փx(0=easy 1=normal 2=hard))
	bool PushNotesButton(Pos notes_pos, unsigned int notes_type, int line); //�m�[�c���͏���
	//bool ReleaseNotesButton(Pos notes_pos, float notes_length, unsigned int notes_type, int line); //�m�[�c���͏���(�����O�m�[�c�A�L�[���������p)
};

//�m�[�c�N���X
class Notes
{
private:
	Pos pos; //���W
	unsigned int notes_type; //�m�[�c�^�C�v(1=�ʏ�m�[�c�A2=�����O�m�[�c�A3=�G�N�X�g���m�[�c)
	unsigned int notes_speed; //�m�[�c���x
	float notes_length; //�����O�m�[�c�̒���(�t���[����)
	bool delete_flg; //�����t���O

	int imgnotesN;     //�ʏ�m�[�c�O���t�B�b�N�n���h��
	int notesN;        //�ʏ�m�[�c�O���t�B�b�N

	int imgnotesL;     //�����O�m�[�c�O���t�B�b�N�n���h��
	int notesL;        //�����O�m�[�c�O���t�B�b�N

	int imgnotesS;     //�X�y�V�����m�[�c�O���t�B�b�N�n���h��
	int notesS;        //�X�y�V�����m�[�c�O���t�B�b�N



public:
	Notes(int lane, int speed, int type, float length); //�R���X�g���N�^
	void Action(); //�A�N�V����
	void Draw(); //�h���[
	Pos GetNotesPos(); //�m�[�c���W�擾�֐�
	int GetNotesType(); //�m�[�c�^�C�v�擾�֐�
	float GetNotesLength(); //�����O�m�[�c�̒����擾�֐�
	void SetDeleteFlg(bool flg); //�����t���O�ݒ�֐�
	bool GetDeleteFlg(); //�����t���O�擾�֐�
};

//�L�����N�^�[�N���X
//class CharaSelect
//{
//private:
//
//public:
//	int imgchara;//�L�����N�^�[�p
//	void Action(); //�A�N�V����
//	void Draw(); //�h���[
//};

//���U���g�N���X
class Result
{
private:
	int background; //�w�i�摜
	int max_notes; //�y�Ȃ̑����m�[�c��
	int score; //�X�R�A
public:
	Result();
	void Action();
	void Draw();
	void SetMaxNotes(int set_notes); //�����m�[�c���ύX
	void SetScore(int set_score); //�X�R�A�ύX
};

//�O���[�o���ϐ��錾
extern bool push; //�L�[����������
extern enum Scene game_scene;
extern Result* result;