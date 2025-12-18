#pragma once

#include <QString>

class QAudioOutput;
class QMediaPlayer;

// Creational Pattern: Singleton for audio playback.
class AudioManager {
public:
    static AudioManager& instance();

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    void playSuccess();
    void playError();
    void playAudio(const QString& filePath);

private:
    AudioManager();
    ~AudioManager();

    QMediaPlayer* m_player;
    QAudioOutput* m_audioOutput;
};
