#pragma once
#include <string>
namespace SoundManager {
void playOnce(const std::string& relativePath);
void playLoop(const std::string& relativePath);
void stopMusic();
void stopEffect();
void stop();
void event(const std::string& name);

// Volume is on the MCI 0-1000 scale. Applies immediately to
// whatever is currently open on that channel, and to everything
// opened afterwards.
void setMusicVolume(int volume);
void setEffectVolume(int volume);
}
