#pragma once

#include <QObject>
#include <qsoundeffect.h>

class SoundManager  : public QObject
{
	Q_OBJECT

public:
	explicit SoundManager(QObject *parent);
	~SoundManager();

public slots:
	void setVolume(uint32_t volume);
	void setMuted(bool muted);
	
private:
	QSoundEffect* sound;
	float currentVolume;
	bool muted;
};
