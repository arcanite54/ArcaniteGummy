#pragma once



namespace MySave
{


/*
Memento
�����o�ϐ�
�E�@��
�E�N���A�󋵁ibool?int? �܂������j
�E�i�R�C�������j
*/

struct Data
{
	int hp;//�̗�
	int clearStage;//�N���A�ς݂̃X�e�[�W
	bool isValid();
};

//Singleton�Ŏ���
class SaveData
{
public:
	SaveData();
	~SaveData();
	Data loadData();
	void saveData();
	void setSaveData(Data);

private:
	int hp;
	int left;
	int clearStage;

};


}

using namespace MySave;
