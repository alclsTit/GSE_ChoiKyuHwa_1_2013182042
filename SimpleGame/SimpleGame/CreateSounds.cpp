#include "stdafx.h"
#include "CreateSounds.h"


CreateSounds::CreateSounds(char *path, int vol, bool Isloop)
{
	//"./Sounds/BackgroundBGM/MapleStoryTitle.mp3"
	Sound *m_sound = new Sound();
	
	auto soundBG = m_sound->CreateSound(path);

	m_sound->PlaySoundW(soundBG, true, 0.2f);
}


CreateSounds::~CreateSounds()
{

}
