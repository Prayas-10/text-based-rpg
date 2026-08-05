#include "soundManager.h"

#include <windows.h>
#include <mmsystem.h>
#include <fstream>
#include <string>

#pragma comment(lib, "winmm.lib")

namespace
{
    const std::string musicAlias = "dharmadevas_music";
    const std::string effectAlias = "dharmadevas_effect";

    // Default playback volumes (0-1000, MCI scale).
    // These were previously unset, which meant everything played
    // back at whatever the system/device default happened to be.
    // Music is intentionally quieter than sound effects so combat
    // cues and dialogue stingers stay audible over the background
    // track.

    int musicVolume = 550;
    int effectVolume = 750;

    // Minimum time that must pass between two sound EFFECTS
    // (attack.mp3, enemy cries, victory/defeat stings, etc).
    // Without this, an enemy's cry fired immediately after the
    // player's attack sound would close/reopen the shared effect
    // alias mid-playback and cut the first sound off entirely.
    // A short gap lets one effect finish (or at least clearly
    // start) before the next one is allowed to interrupt it.

    const DWORD EFFECT_GAP_MS = 450;

    DWORD lastEffectTick = 0;
    std::string currentMusicPath;
    bool musicPlaying = false;

    bool exists(const std::string& path)
    {
        std::ifstream file(path);
        return file.good();
    }

    void sendMci(const std::string& command)
    {
        mciSendStringA(
            command.c_str(),
            nullptr,
            0,
            nullptr
        );
    }

    void applyVolume(const std::string& alias, int volume)
    {
        if (volume < 0)
            volume = 0;

        if (volume > 1000)
            volume = 1000;

        // Not every MCI driver supports "setaudio ... volume",
        // but the mpegvideo/mciqtz32 driver used for MP3 playback
        // does. If a given build's driver silently rejects it,
        // playback simply continues at full volume instead of
        // failing - so this call is safe to attempt unconditionally.

        sendMci(
            "setaudio " + alias +
            " volume to " +
            std::to_string(volume)
        );
    }

    void closeAlias(const std::string& alias)
    {
        sendMci("stop " + alias);
        sendMci("close " + alias);
    }

    void openMusic(const std::string& path, bool loop)
    {
        if (!exists(path))
            return;

        // If the exact same track is already looping (e.g. the
        // world screen redraw fires again for the same region),
        // don't tear it down and reopen it. Rapidly closing and
        // reopening the same MCI alias is what caused the music
        // to sometimes go silent when moving between regions -
        // the device did not always finish releasing the file
        // before the very next "open" command ran.

        if (musicPlaying && currentMusicPath == path)
            return;

        closeAlias(musicAlias);

        // Give the MCI device a brief moment to fully release the
        // previous file handle before opening the next one.

        Sleep(60);

        const std::string openCommand =
            "open \"" + path + "\" type mpegvideo alias " + musicAlias;

        sendMci(openCommand);

        applyVolume(musicAlias, musicVolume);

        const std::string playCommand =
            "play " + musicAlias + (loop ? " repeat" : "");

        sendMci(playCommand);

        currentMusicPath = path;
        musicPlaying = true;
    }

    void playEffect(const std::string& path)
    {
        if (!exists(path))
            return;

        // keep a minimum gap since the last effect so that two
        // effects fired back-to-back (player attack sound followed
        // immediately by the enemy's cry, for example) don't stomp
        // on each other. If not enough time has passed, wait out
        // the remainder before starting the next one.

        const DWORD now = GetTickCount();
        const DWORD elapsed = now - lastEffectTick;

        if (lastEffectTick != 0 && elapsed < EFFECT_GAP_MS)
        {
            Sleep(EFFECT_GAP_MS - elapsed);
        }

        closeAlias(effectAlias);

        const std::string openCommand =
            "open \"" + path + "\" type mpegvideo alias " + effectAlias;

        sendMci(openCommand);

        applyVolume(effectAlias, effectVolume);

        sendMci("play " + effectAlias);

        lastEffectTick = GetTickCount();
    }
}

void SoundManager::playOnce(const std::string& relativePath)
{
    openMusic(relativePath, false);
}

void SoundManager::playLoop(const std::string& relativePath)
{
    openMusic(relativePath, true);
}

void SoundManager::stopMusic()
{
    closeAlias(musicAlias);
    currentMusicPath.clear();
    musicPlaying = false;
}

void SoundManager::stopEffect()
{
    closeAlias(effectAlias);
}

void SoundManager::stop()
{
    stopMusic();
    stopEffect();
}

void SoundManager::event(const std::string& name)
{
    playEffect("data/sounds/" + name + ".mp3");
}

void SoundManager::setMusicVolume(int volume)
{
    musicVolume = volume;
    applyVolume(musicAlias, musicVolume);
}

void SoundManager::setEffectVolume(int volume)
{
    effectVolume = volume;
    applyVolume(effectAlias, effectVolume);
}
