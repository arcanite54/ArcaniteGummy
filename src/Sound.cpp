#include "Sound.h"
#include <cassert>

namespace MySound{

void Sound::setSound(string _path, string _name)
{
	if (exists(_name))assert(!"Sound: ���łɓo�^����Ă��閼�O�ł�.");
	
	int tmp_handle = LoadSoundMem(_path.c_str());
	assert(tmp_handle != -1 && "�T�E���h�ǂݍ��݃G���[");

	soundMap.insert(make_pair(_name, tmp_handle));
}

void Sound::deleteSound(string _name)
{
	if (!exists(_name))return;

	DeleteSoundMem(soundMap.at(_name));
	soundMap.erase(_name);
}

void Sound::playSound(string _name, PlayType _pType)
{
	if (!exists(_name))assert(!"�w��̃T�E���h�͑��݂��܂���");

	//���d�Đ���h��
	if (CheckSoundMem(soundMap.at(_name)) == 1)return;

	int pType = 0;
	switch (_pType)
	{
	case BACK: pType = DX_PLAYTYPE_BACK; break;
	case LOOP: pType = DX_PLAYTYPE_LOOP; break;
	case NORMAL: pType = DX_PLAYTYPE_NORMAL; break;
	}

	PlaySoundMem(soundMap.at(_name), pType);
}

void Sound::playSoundWithPath(string _path, PlayType _pType)
{
	int pType = 0;
	switch (_pType)
	{
	case BACK: pType = DX_PLAYTYPE_BACK; break;
	case LOOP: pType = DX_PLAYTYPE_LOOP; break;
	case NORMAL: pType = DX_PLAYTYPE_NORMAL; break;
	}
	int tmp = PlaySoundFile(_path.c_str(), pType);
	assert(tmp != -1 && "�w��̃T�E���h�͑��݂��܂���.");
}

void Sound::StopSound(string _name)
{
	if (soundMap.count(_name) == 0)
	{
		StopSoundFile();
		return;
	}
	StopSoundMem(soundMap.at(_name));
}

void Sound::stopAllSound()
{
	for (auto& s : soundMap)
	{
		StopSoundMem(s.second);
	}
}

void Sound::setVolume(string _name, float _ratio)
{
	if (!exists(_name))assert(!"�w��̃T�E���h�͑��݂��܂���");

	ChangeVolumeSoundMem((int)(255 * _ratio), soundMap.at(_name));
}

void Sound::setAllVolume(float _ratio)
{
	int param = (int)(255 * _ratio);

	for (auto& s : soundMap)
	{
		ChangeVolumeSoundMem(param, s.second);
	}
}


}