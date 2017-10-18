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
class ClearFlag;
class CheckPoint;
class GameMain;
class EnemyController;



//Stage�̊��N���X
class StageChild
{
public:
	StageChild(int stage_max_x, int stage_max_y);
	virtual ~StageChild();
	virtual void update(GameMain*, PlayerChild*) = 0;
	virtual void draw(const Vector2* camera) const = 0;
	virtual bool isClear() const = 0;

	void standardUpdate(PlayerChild* _player);
	void updateStoppingDynamics(PlayerChild* _player);

	void standardDraw(const Vector2* camera) const;
	virtual void draw_front(const Vector2* camera) const;

	enum ChipType
	{
		TYPE_BACK				= 0b0000000001, //���蔲������
		TYPE_RIGID				= 0b0000000010, //���蔲�����Ȃ�
		TYPE_RIDE				= 0b0000000100, //������͂��蔲���A�ォ��͂��蔲�����Ȃ�
		TYPE_DOWN_SLANT_RIGHT	= 0b0000001000, //�E��֌������΂߃u���b�N, �オ�u���b�N�Ȃ�
		TYPE_DOWN_SLANT_LEFT	= 0b0000010000, //����֌������΂߃u���b�N, �オ�u���b�N�Ȃ�
		TYPE_UP_SLANT_RIGHT		= 0b0000100000, //�E��֌������΂߃u���b�N, �����u���b�N�Ȃ�
		TYPE_UP_SLANT_LEFT		= 0b0001000000, //����֌������΂߃u���b�N, �����u���b�N�Ȃ�
		TYPE_LADDER				= 0b0010000000, //�͂���
		TYPE_LADDER_TOP			= 0b0100000000, //�͂����̏�
		TYPE_LESAL				= 0b1000000000, //���������炵�ʁB
	};

	enum ChangeableCharacter
	{
		CHARA_NONE		= 0b000,
		CHARA_MOKOU		= 0b001,
		CHARA_SAKUYA	= 0b010,
		CHARA_NUE		= 0b100,
	};

	//���ɂ��蔲�����Ȃ��u���b�N�C���ɂȂ�
	virtual bool isRigid_down(ChipType _ct) const { return (_ct & 0b0101100110) != 0; }

	//��ɂ��蔲�����Ȃ��u���b�N�C�V��ɂȂ�
	virtual bool isRigid_up(ChipType _ct)   const { return (_ct & 0b0000011010) != 0; }

	//�΂߃u���b�N
	virtual bool isSlant(ChipType _ct)		const { return (_ct & 0b0001111000) != 0; }

	ChipType getChipType(const Vector2&, bool isPlayer) const;
	ChipType getChipType(const Vector2&) const;
	ChipType getChipType(const RawVector2&, bool isPlayer) const;

	int getTopPosition(const Vector2*, const int& dy) const;//�����͍�����n�_�̍��W��vectorRrate������������
	int getBottomPosition(const Vector2*, const int& dy) const;//�����͍�����n�_�̍��W��vectorRrate������������

	const bool canChangeCharacter(const ChangeableCharacter& cc, bool inverse) const 
	{
		if(inverse)	return (changeableCharacter & (~cc)); 
		return (changeableCharacter & (cc));
	}
	int getChangeableCharacter() const { return changeableCharacter; }

	vector< DynamicGimmickChild* > getDynamicGimmicks();
	vector< SwitchWithBlock* > getSwitchWithBlocks();
	EnemyController* getEController();

	enum HowStageMove
	{
		MOVE_NONE,

		MOVE_UP,
		MOVE_RIGHT,
		MOVE_LEFT,
		MOVE_DOWN,
	};

	void moveStage(HowStageMove);
	void processDynamcCollision(PlayerChild*);
	void addDynamicGimmickToAllMaps(DynamicGimmickChild*);

	int startX, startY;

protected:
	int mBackImg;

	unsigned now_stage_num;
	int stage_max_x;
	int stage_max_y;

	int changeableCharacter;

	vector<Map*> maps;
	vector<CheckPoint*> checkPoints;
	ClearFlag* flag;
	
	//�����ł���`�F�b�N�|�C���g��T���āC����Ε���
	void findRestartPoint();

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