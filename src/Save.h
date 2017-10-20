#pragma once
#include <vector>

using namespace std;

namespace MySave
{

class SaveData
{
public:
	//�C���X�^���X��getter
	static SaveData* getInstance()
	{
		//static�ϐ��ɂ�菉��Ăяo�����̂ݐ���
		static SaveData obj;
		return &obj;
	}

	int slotNum = 0;

	void save(int);
	void saveNewData(int stageNum, int slot);
	const vector<int>& getSaveData() const { return allDatas; }

	//�`�F�b�N�|�C���g�̏������Z�b�g
	void resetCheckPoint();

	//�`�F�b�N�|�C���g�̏����Z�[�u
	void saveCheckPoint(int checkIndex, int switch_flags);

	//�Q�Ƃ��g���ă`�F�b�N�|�C���g�̏����Q�b�g
	void updateCheckPoint(int& _checkIndex, int& _switch_flags);


private:

	//Singleton
	SaveData();
	~SaveData();


	//�R�s�[�R���X�g���N�^�Ƒ�����Z�q�𖾎��I��private�ɂ���
	SaveData(const SaveData &x);
	SaveData& operator=(const SaveData &) {};

	int checkIndex;
	int switch_flags;

	vector<int> allDatas;

	void loadData();
	void outputSaveData();
};


}

using namespace MySave;
