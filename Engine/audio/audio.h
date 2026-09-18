#pragma once
#include <string>

namespace audio
{
    enum class Channel
    {
        BGM,
        VOICE,
        SFX
    };

    bool Init();
    void PlayBGM(const std::string& filepath, bool loop = true, float fadeDurationSeconds = 0.0f);
    void StopBGM(float fadeDurationSeconds = 0.0f);
    void PlayVoice(const std::string& filepath);
    void StopVoice();
    void PlaySFX(const std::string& filepath);
    void SetVolume(Channel channel, float volume);
    void DestroyAudio();
}