#include "Save.h"
#include <cassert>
#include <fstream>

namespace MySave{

SaveData::SaveData()
{
	loadData();
}

SaveData::~SaveData()
{
	//�t�@�C���o��
	ofstream fout("Data/Text/save.txt", ios_base::binary | ios_base::out);
	for (const auto& data : allDatas)
	{
		fout << data << endl;
	}
}

void SaveData::loadData()
{
	ifstream fin("Data/Text/save.txt", ios_base::binary | ios_base::in);

	allDatas.clear();

	//�Z�[�u�f�[�^��ǂݍ����vector��push
	int stage = 0;
	while (fin >> stage, stage)
	{
		allDatas.push_back(stage);
	}
	
	allDatas.shrink_to_fit();
}

void SaveData::save(int _stageNum)
{
	allDatas.push_back(_stageNum);
}




}
