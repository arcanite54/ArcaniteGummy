#pragma once

#include "..\DynamicGimmickChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Child;
class Block;

class SwitchWithBlock : public DynamicGimmickChild
{
public:
	//��3�������Ȃ��Ȃ畁�ʂ̃X�C�b�`
	//��3������1�Ȃ牟�����ςȂ��̃X�C�b�`
	//��3������2���傫���Ȃ玞�����X�C�b�`(��������������(�t���[���� / ����60��1�b))
	
	SwitchWithBlock(int x, int y);
	SwitchWithBlock(int x, int y, int notChangeable);
	SwitchWithBlock(int x, int y, int limitTime, bool notChangeable);
	~SwitchWithBlock();
	void initialize();
	void update(const StageChild*);
	void draw(const Vector2*) const;
	virtual void draw_front(const Vector2*) const {}
	void apply(Character*);

	void hittedAction() override;
	void burnedAction() override;
	bool isOverlap(const Vector2*) const override;

	bool onActiveArea(const Vector2*) const;
	void checkOnActiveArea(const Vector2* player) { this->onActiveArea(player); }
	StageChild::ChipType getChipType() const;

	//�X�C�b�`��on�̎��Ɍ����Block
	vector<Block*> blocks_on;

	//�X�C�b�`��off�̎��Ɍ����Block
	vector<Block*> blocks_off;

	vector<Block*> getBlocks() { return ((isPushed) ? blocks_on : blocks_off); }

	//��2������true�ŁC �X�C�b�`on�̎��Ɍ����
	//��2������false�ŁC�X�C�b�`off�̎��Ɍ����
	void push_block(Block* b, bool switch_on) { switch_on ? blocks_on.push_back(b) : blocks_off.push_back(b); }

private:
	bool isPushed;
	bool preOnActiveArea;
	mutable bool tmpOnActiveArea;
	int mTime;
	const int limitTime;
	const bool notChangeable;

	void loadImage();
};




}
}
}
