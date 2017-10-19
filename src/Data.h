#pragma once

#include "DXLib.h"
#include "Sound.h"
#include "Save.h"

#include <cassert>
#include <array>
#include <vector>
#include <algorithm>

using std::array;
using std::vector;

//�~����
constexpr float Pi = 3.14159265358979f;


//delete��0�|�C���^
#define SAFE_DELETE(p){\
	delete (p);\
	(p) = 0;\
}

//delete[]��0�|�C���^
#define SAFE_DELETE_ARRAY(p){\
	delete[] (p);\
	(p) = 0;\
}

//========================================
//�~�����̌v�Z(�R���p�C�����v�Z)
//========================================
constexpr float pi(float num)
{
	return Pi * num;
}


//========================================
//Data.cpp/h�Ŏg�p���閼�O���
//========================================
namespace MyData{

//�}�b�v�`�b�v
//�S�̂œ������̂��g��
extern int MapChip[256];

//�T�E���h
extern Sound* sound;

//�Z�[�u�f�[�^
extern SaveData* saveData;

//�v���C���[�̃`�b�v�T�C�Y
constexpr int PLAYER_CHIP_HEIGHT = 64;
constexpr int PLAYER_CHIP_WIDTH = 32;

//��ʂ̒��S���W
constexpr int CX = 320;
constexpr int CY = 240;

//�}�b�v1���̃T�C�Y(�s�N�Z����)
constexpr int MAP_WIDTH = 3200;
constexpr int MAP_HEIGHT = 1600;

//�}�b�v1���̃T�C�Y(�`�b�v��)
constexpr int MAP_WIDTH_NUM = 100;
constexpr int MAP_HEIGHT_NUM = 50;

//�}�b�v�`�b�v�̃T�C�Y(�s�N�Z����)
constexpr int CHIP_WIDTH = 32;
constexpr int CHIP_HEIGHT = 32;

//1�s�N�Z�����ǂꂾ���g�����邩
constexpr int vectorRate = 1000;

//�U�R�G�̃L�����`�b�v�̐�
constexpr int ENEMY_CHIP_NUM = 8;

//vectorRate���l�����v���C���[�`�b�v�̃T�C�Y
constexpr int PLAYER_CHIP_WIDTH_RATE() { return PLAYER_CHIP_WIDTH * vectorRate; }
constexpr int PLAYER_CHIP_HEIGHT_RATE() { return PLAYER_CHIP_HEIGHT * vectorRate; }

//vectorRate���l�������}�b�v�`�b�v�̃T�C�Y
constexpr int CHIP_WIDTH_RATE() { return CHIP_WIDTH * vectorRate; }
constexpr int CHIP_HEIGHT_RATE() { return CHIP_HEIGHT * vectorRate; }

//vectorRate���l�������}�b�v�̃T�C�Y
constexpr int MAP_WIDTH_RATE() { return MAP_WIDTH * vectorRate; }
constexpr int MAP_HEIGHT_RATE() { return MAP_HEIGHT * vectorRate; }

//�}�b�v�̃}�X�ɍ��킹�Ē���
int fixToStageWidth(int _a);
int fixToStageHeight(int _a);

//�}�b�v�̃}�X�ɍ��킹�Ē���
int fixToVectorWidth(int _a);
int fixToVectorHeight(int _a);

//�p���ۂ�����\��
void DrawFilledCircledBox(int x1, int y1, int x2, int y2, int r, unsigned color);

//�̗�
constexpr int PLAYER_MAX_HP = 200;


//�F
const unsigned BLACK = GetColor(0, 0, 0);
const unsigned DARKGLAY = GetColor(30, 30, 30);
const unsigned GLAY = GetColor(128, 128, 128);
const unsigned WHITE = GetColor(255, 255, 255);
const unsigned RED = GetColor(255, 0, 0);
const unsigned GREEN = GetColor(0, 255, 0);
const unsigned BLUE = GetColor(0, 0, 255);
const unsigned PURPLE = GetColor(255, 0, 255);
const unsigned YELLOW = GetColor(255, 255, 0);
const unsigned CYAN = GetColor(0, 255, 255);

//���ׂĂ̓G
enum AllEnemies
{
	//�n��
	ENE_USA		= 0,
	ENE_YACH	= 1,
	ENE_PIKA	= 2,
	ENE_BROTH	= 3,
	ENE_MARI	= 4,

	//��
	ENE_BALL	= 5,
	ENE_POPPY	= 6,
	ENE_AIRMZ	= 7,
	ENE_TERESA	= 8,

	//���ȂȂ�
	ENE_KARON,
	ENE_RARA,
	ENE_ICE,
	ENE_KAWARI,

	//�{�X
	BOSS_REISEN,
	BOSS_NUE,
	BOSS_JUNKO,
	BOSS_FRAN,
	BOSS_KAGUYA,

	ENE_NONE,
};

//�Q�[�����ɑ��݂���S�I�u�W�F�N�g
//���x�͋�̃N���X�P��
enum ObjectID
{
	ID_NONE,

	//Player
	P_MOKOU,
	P_SAKUYA,
	P_NUE,

	//Attack
	A_FIRE,
	A_KNIFE,
	A_SPEAR,

	//Enemy
	E_USAGI,
	E_BALOON,

	//MapChip
	M_BLOCK,

	//Gimmick
	G_BELT,
	G_SPRING,

	//DynamicGimmick
	DG_BLOCK
};


//�����l2�����x�N�g��
//�����ł͍��W��vectorRate�{���Ď����Ă���
class Vector2
{

public:
	int raw_x, raw_y;

	Vector2() : Vector2(0, 0, false)
	{

	}
	Vector2(int _x, int _y) : Vector2(_x, _y, false)
	{

	}
	Vector2(int _x, int _y, bool useRawValue)
	{
		this->raw_x = _x;
		this->raw_y = _y;
		
		if (!useRawValue)
		{
			this->raw_x *= vectorRate;
			this->raw_y *= vectorRate;
		}
	}


	const int x() const { return (this->raw_x / vectorRate) % MAP_WIDTH; }
	const int y() const { return (this->raw_y / vectorRate) % MAP_HEIGHT; }
	const int pos_x() const { return this->raw_x % MAP_WIDTH_RATE(); }
	const int pos_y() const { return this->raw_y % MAP_HEIGHT_RATE(); }


	bool isZero() const
	{
		return *this == Vector2::ZERO;
	}

	Vector2& operator += (const Vector2& other)
	{
		return *this = *this + other;
	}
	Vector2& operator -= (const Vector2& other)
	{
		return *this = *this - other;
	}
	const Vector2 operator + (const Vector2& other)
	{
		return Vector2(raw_x + other.raw_x, raw_y + other.raw_y, true);
	}
	const Vector2 operator - (const Vector2& other)
	{
		return Vector2(raw_x - other.raw_x, raw_y - other.raw_y, true);
	}
	const Vector2 operator * (int other) const
	{
		return Vector2(raw_x * other, raw_y * other, true);
	}
	const Vector2 operator / (int other) const
	{
		return Vector2(this->raw_x / other, this->raw_y / other, true);
	}
	bool operator == (const Vector2& other) const
	{
		return (raw_x == other.raw_x) && (raw_y == other.raw_y);
	}
	bool operator != (const Vector2& other) const
	{
		return !(*this == other);
	}

	
	static const Vector2 ZERO;
	static const Vector2 LEFT;
	static const Vector2 RIGHT;
	static const Vector2 UP;
	static const Vector2 DOWN;
};

class RawVector2
{
public:
	int pos_x, pos_y;
	RawVector2()
	{
		pos_x = pos_y = 0;
	}
	RawVector2(int _x, int _y)
	{
		pos_x = _x;
		pos_y = _y;
	}
	const RawVector2 operator + (const RawVector2& other)
	{
		return RawVector2(pos_x + other.pos_x, pos_y + other.pos_y);
	}
	const RawVector2 operator - (const RawVector2& other)
	{
		return RawVector2(pos_x - other.pos_x, pos_y - other.pos_y);
	}
	const RawVector2 operator * (int other) const
	{
		return RawVector2(pos_x * other, pos_y * other);
	}
	const RawVector2 operator / (int other) const
	{
		return RawVector2(this->pos_x / other, this->pos_y / other);
	}
	bool operator == (const RawVector2& other) const
	{
		return (pos_x == other.pos_x) && (pos_y == other.pos_y);
	}
	bool operator != (const RawVector2& other) const
	{
		return !(*this == other);
	}

};

//2�_�Ԃ̋����𓾂�, �d������񐄏�
float distance(int x1, int y1, int x2, int y2);
float distance(int x, int y, const Vector2*);
float distance(const Vector2*, const Vector2*);

}

using namespace MyData;
