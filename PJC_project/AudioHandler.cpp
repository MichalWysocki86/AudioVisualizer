#include "AudioHandler.h"

/**
 * @brief Default constructor for the AudioHandler class.
 */
AudioHandler::AudioHandler() { }

/**
 * @brief Loads an audio file into the handler.
 * @param filename Path to the audio file.
 * @throws std::runtime_error If loading the file fails.
 */
void AudioHandler::loadFile(const std::string& filename) {
    if (!buffer.loadFromFile(filename)) {
        throw std::runtime_error("Failed to open file!");
    }
    sound.setBuffer(buffer);
}

void AudioHandler::play() {
    sound.play();
}

void AudioHandler::pause() {
    sound.pause();
}

void AudioHandler::stop() {
    sound.stop();
}

sf::Time AudioHandler::getDuration() const {
    return buffer.getDuration();
}

sf::Time AudioHandler::getPlayingOffset() const {
    return sound.getPlayingOffset();
}

sf::Uint64 AudioHandler::getSampleCount() const {
    return buffer.getSampleCount();
}

unsigned int AudioHandler::getSampleRate() const {
    return buffer.getSampleRate();
}

const sf::Int16* AudioHandler::getSamples() const {
    return buffer.getSamples();
}

unsigned int AudioHandler::getChannelCount() const {
    return buffer.getChannelCount();
}

sf::Sound::Status AudioHandler::getStatus() const {
    return sound.getStatus();
}