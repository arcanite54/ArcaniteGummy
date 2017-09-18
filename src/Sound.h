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
	bool exists(string name) { return soundMap.find(name) != soundMap.end(); }

public:
	//�C���X�^���X��getter
	static Sound* getInstance()
	{
		//static�ϐ��ɂ�菉��Ăяo�����̂ݐ���
		static Sound obj;
		return &obj;
	}

	void setSound(string path, string name);
	void deleteSound(string name);
	void playSound(string name, PlayType);
	void playSoundWithPath(string path, PlayType);
	void StopSound(string name);
	void stopAllSound();
	void setVolume(string name, float ratio);
	void setAllVolume(float ratio);
};

static Sound* sound;

}

using namespace MySound;
