#pragma once

#include "..\..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Map;
class PlayerChild;
class GimmickChild;
class DynamicGimmickChild;
class SwitchWithBlock;
class GameMain;


//Stage�̊��N���X
class StageChild
{
public:
	StageChild(int stage_max_x, int stage_max_y);
	virtual ~StageChild();
	virtual void update(GameMain*, PlayerChild*) = 0;
	virtual void draw(const Vector2* camera) const = 0;
	virtual bool isClear() const = 0;

	void standardUpdate(PlayerChild*);
	void standardDraw(const Vector2* camera) const;

	enum ChipType
	{
		TYPE_BACK				= 0b000000001, //���蔲������
		TYPE_RIGID				= 0b000000010, //���蔲�����Ȃ�
		TYPE_RIDE				= 0b000000100, //������͂��蔲���A�ォ��͂��蔲�����Ȃ�
		TYPE_DOWN_SLANT_RIGHT	= 0b000001000, //�E��֌������΂߃u���b�N, �オ�u���b�N�Ȃ�
		TYPE_DOWN_SLANT_LEFT	= 0b000010000, //����֌������΂߃u���b�N, �オ�u���b�N�Ȃ�
		TYPE_UP_SLANT_RIGHT		= 0b000100000, //�E��֌������΂߃u���b�N, �����u���b�N�Ȃ�
		TYPE_UP_SLANT_LEFT		= 0b001000000, //����֌������΂߃u���b�N, �����u���b�N�Ȃ�
		TYPE_LADDER				= 0b010000000, //�͂���
		TYPE_LADDER_TOP			= 0b100000000, //�͂����̏�
	};

	virtual bool isRigid_down(ChipType _ct) const { return (_ct & 0b101100110) != 0; }//���ɂ��蔲�����Ȃ��u���b�N�C���ɂȂ�
	virtual bool isRigid_up(ChipType _ct)   const { return (_ct & 0b000011010) != 0; }//��ɂ��蔲�����Ȃ��u���b�N�C�V��ɂȂ�
	virtual bool isSlant(ChipType _ct)		const { return (_ct & 0b001111000) != 0; }//�΂߃u���b�N

	ChipType getChipType(const Vector2&, bool isPlayer) const;
	ChipType getChipType(const Vector2&) const;
	ChipType getChipType(const RawVector2&, bool isPlayer) const;

	int getTopPosition(const Vector2*, const int& dy) const;//�����͍�����n�_�̍��W��vectorRrate������������
	int getBottomPosition(const Vector2*, const int& dy) const;//�����͍�����n�_�̍��W��vectorRrate������������

	vector< DynamicGimmickChild* > getDynamicGimmicks();
	vector< SwitchWithBlock* > getSwitchWithBlocks();

	enum HowStageMove
	{
		MOVE_NONE,

		MOVE_UP,
		MOVE_RIGHT,
		MOVE_LEFT,
		MOVE_DOWN,
	};

	void moveStage(HowStageMove);

protected:
	int mBackImg;

	int now_stage_num;
	int stage_max_x;
	int stage_max_y;
	vector<Map*> maps;

	class Chip
	{
	public:
		Chip(ChipType _chipType) : mChipType(_chipType) {};
		~Chip() {};
		ChipType getChipType() const { return mChipType; }
		void setChipType(ChipType _chipType) { mChipType = _chipType; }
	private:
		ChipType mChipType;
	};

private:
	void initialize();


};


}
}
}