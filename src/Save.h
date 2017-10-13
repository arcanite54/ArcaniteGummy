#pragma once
#include <vector>

using namespace std;

namespace MySave
{




//Singleton�Ŏ���
class SaveData
{
public:
	SaveData();
	~SaveData();
	void saveData();
	void loadData();

private:
	int hp;
	int left;
	int clearStage;
	vector<int> allDatas;
};


}

using namespace MySave;
