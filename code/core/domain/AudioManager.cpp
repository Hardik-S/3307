#include "AudioManager.h"

#include <QAudioOutput>
#include <QCoreApplication>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QUrl>

AudioManager& AudioManager::instance() {
    static AudioManager instance;
    return instance;
}

AudioManager::AudioManager()
    : m_player(new QMediaPlayer()), m_audioOutput(new QAudioOutput()) {
    m_player->setAudioOutput(m_audioOutput);
}

AudioManager::~AudioManager() {
    delete m_player;
    delete m_audioOutput;
}

void AudioManager::playSuccess() {
    playAudio("assets/success.wav");
}

void AudioManager::playError() {
    playAudio("assets/error.wav");
}

void AudioManager::playAudio(const QString& filePath) {
    const QString basePath = QCoreApplication::applicationDirPath();
    const QString resolved = QFileInfo(filePath).isAbsolute() ? filePath : basePath + "/" + filePath;
    if (!QFileInfo::exists(resolved)) {
        return;
    }
    m_player->setSource(QUrl::fromLocalFile(resolved));
    m_player->play();
}
