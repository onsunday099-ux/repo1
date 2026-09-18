#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "audio.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace audio
{
    static ma_engine engine;
    static ma_sound bgm_sound;
    static ma_sound voice_sound;
    static ma_sound_group group_bgm;
    static ma_sound_group group_voice;
    static ma_sound_group group_sfx;

    static bool is_initialized = false;
    static bool is_bgm_loaded = false;
    static bool is_voice_loaded = false;

    float bgm_volume = 1.0f;
    float voice_volume = 1.0f;
    float sfx_volume = 1.0f;

    bool Init()
    {
        if (is_initialized) return true;

        ma_result result = ma_engine_init(NULL, &engine);
        if (result != MA_SUCCESS)
        {
            spdlog::error("Failed to init audio engine: {}", ma_result_description(result));
            return false;
        }

        ma_sound_group_init(&engine, 0, NULL, &group_bgm);
        ma_sound_group_init(&engine, 0, NULL, &group_voice);
        ma_sound_group_init(&engine, 0, NULL, &group_sfx);

        is_initialized = true;
        return true;
    }

    void PlayBGM(const std::string& filepath, bool loop, float fadeDurationSeconds)
    {
        if (!is_initialized) return;

        StopBGM(0.0f);

        ma_result result = ma_sound_init_from_file(
            &engine,
            filepath.c_str(),
            MA_SOUND_FLAG_STREAM,
            &group_bgm,
            NULL,
            &bgm_sound
        );

        if (result != MA_SUCCESS)
        {
            spdlog::error("Error PlayBGM [{}]: {}", filepath, ma_result_description(result));
            return;
        }

        ma_sound_set_looping(&bgm_sound, loop ? MA_TRUE : MA_FALSE);

        if (fadeDurationSeconds > 0.0f)
        {
            ma_sound_set_fade_in_milliseconds(&bgm_sound, 0.0f, 1.0f, (ma_uint64)(fadeDurationSeconds * 1000));
        }

        ma_sound_start(&bgm_sound);
        is_bgm_loaded = true;
    }

    void StopBGM(float fadeDurationSeconds)
    {
        if (is_bgm_loaded)
        {
            if (fadeDurationSeconds > 0.0f)
            {
                ma_sound_stop_with_fade_in_milliseconds(&bgm_sound, (ma_uint64)(fadeDurationSeconds * 1000));
            }
            else
            {
                ma_sound_stop(&bgm_sound);
            }
            ma_sound_uninit(&bgm_sound);
            is_bgm_loaded = false;
        }
    }

    void PlayVoice(const std::string& filepath)
    {
        if (!is_initialized) return;

        StopVoice();

        ma_result result = ma_sound_init_from_file(
            &engine,
            filepath.c_str(),
            0,
            &group_voice,
            NULL,
            &voice_sound
        );

        if (result != MA_SUCCESS)
        {     
            spdlog::error("Error PlayVoice [{}]: {}", filepath, ma_result_description(result));
            return;
        }

        ma_sound_set_looping(&voice_sound, MA_FALSE);
        ma_sound_start(&voice_sound);
        is_voice_loaded = true;
    }

    void StopVoice()
    {
        if (is_voice_loaded)
        {
            ma_sound_stop(&voice_sound);
            ma_sound_uninit(&voice_sound);
            is_voice_loaded = false;
        }
    }

    void PlaySFX(const std::string& filepath)
    {
        if (!is_initialized) return;

        ma_result result = ma_engine_play_sound(&engine, filepath.c_str(), &group_sfx);
        if (result != MA_SUCCESS)
        {
            spdlog::error("Error PlaySFX [{}]: {}", filepath, ma_result_description(result));
        }
    }

    void SetVolume(Channel channel, float volume)
    {
        if (!is_initialized) return;

        switch (channel)
        {
        case Channel::BGM:
            ma_sound_group_set_volume(&group_bgm, volume);
            break;
        case Channel::VOICE:
            ma_sound_group_set_volume(&group_voice, volume);
            break;
        case Channel::SFX:
            ma_sound_group_set_volume(&group_sfx, volume);
            break;
        }
    }

    void DestroyAudio()
    {
        StopBGM(0.0f);
        StopVoice();

        if (is_initialized)
        {
            ma_sound_group_uninit(&group_bgm);
            ma_sound_group_uninit(&group_voice);
            ma_sound_group_uninit(&group_sfx);
            ma_engine_uninit(&engine);
            is_initialized = false;
        }
    }
}