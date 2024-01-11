#include "soundmanager.h"

SoundManager::SoundManager(QObject* parent)
	: QObject(parent)
{
	sound = new QSoundEffect;
	currentVolume = 10.0;
	muted = false;
	sound->setSource(QUrl::fromLocalFile("./Sounds/MainMenu.wav"));
	sound->setVolume(qreal(currentVolume) / 100.0);
	sound->setLoopCount(QSoundEffect::Infinite);
	sound->play();
}

SoundManager::~SoundManager()
{
}

void SoundManager::setVolume(uint32_t volume) {
	currentVolume = qreal(volume) / 100.0;
	sound->setVolume(currentVolume);
}

void SoundManager::setMuted(bool muted) {
	if (muted) {
		sound->setMuted(true);
	}
	else {
		sound->setMuted(false);
		sound->setVolume(currentVolume);
	}
}

SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance; // Static instance
	return instance;
}
