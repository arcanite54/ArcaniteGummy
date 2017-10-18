#pragma once

#include "DXLib.h"
#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

namespace MySound
{

enum PlayType
{
	BACK,
	LOOP,
	NORMAL,
};


//Singleton�Ŏ���
class Sound
{
private:
	Sound() {};
	~Sound() {};

	//�R�s�[�R���X�g���N�^�Ƒ�����Z�q�𖾎��I��private�ɂ���
	Sound(const Sound &x);
	Sound& operator=(const Sound &);

	unordered_map<string, int> soundMap;

public:
	float allVolume = 1.0f;

	//�C���X�^���X��getter
	static Sound* getInstance()
	{
		//static�ϐ��ɂ�菉��Ăяo�����̂ݐ���
		static Sound obj;
		return &obj;
	}

	void setSound(string path, string name);
	void deleteSound(string name);

	//BACK�A���d�s�ōĐ�
	void playSound(string name);

	//���d�ōĐ������Ȃ�
	void playSound(string name, PlayType);

	//key, �Đ��X�^�C��, ���d�ōĐ��ł��邩�ǂ���
	void playSound(string name, PlayType, bool coverable);
	void playSoundWithPath(string path, PlayType);
	void stopSound(string name);
	void stopSoundOfFile();
	void stopAllSound();
	void setVolume(string name, float ratio);
	void setAllVolume(float ratio);
	bool exists(string name) { return soundMap.find(name) != soundMap.end(); }
};

}

using namespace MySound;
