#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <stdexcept>

/**
 * @class AudioHandler
 * @brief A utility class to handle audio operations using SFML.
 *
 * The AudioHandler class provides basic functionalities for audio operations like
 * playing, pausing, and stopping an audio, as well as retrieving information about
 * the audio file, such as its duration, playing offset, sample count, etc.
 */
class AudioHandler {
private:

public:
    /**
     * @brief Default constructor for the AudioHandler class.
     */
    AudioHandler();

    sf::Sound sound;            ///< SFML Sound object to handle audio playback.
    sf::SoundBuffer buffer;    ///< Buffer storing audio data.

    /**
     * @brief Loads an audio file into the handler.
     * @param filename Path to the audio file.
     * @throws std::runtime_error If loading the file fails.
     */
    void loadFile(const std::string& filename);

    /**
     * @brief Starts or resumes the playback of the audio.
     */
    void play();

    /**
     * @brief Pauses the playback of the audio.
     */
    void pause();

    /**
     * @brief Stops the playback of the audio.
     */
    void stop();

    /**
     * @brief Retrieves the total duration of the audio.
     * @return The duration of the audio.
     */
    sf::Time getDuration() const;

    /**
     * @brief Retrieves the current playback position of the audio.
     * @return The current playback offset.
     */
    sf::Time getPlayingOffset() const;

    /**
     * @brief Retrieves the number of audio samples.
     * @return The sample count.
     */
    sf::Uint64 getSampleCount() const;

    /**
     * @brief Retrieves the sample rate of the audio.
     * @return The sample rate in hertz.
     */
    unsigned int getSampleRate() const;

    /**
     * @brief Retrieves a pointer to the audio samples.
     * @return Pointer to the audio samples.
     */
    const sf::Int16* getSamples() const;

    /**
     * @brief Retrieves the number of channels in the audio.
     * @return The channel count.
     */
    unsigned int getChannelCount() const;

    /**
     * @brief Retrieves the current status of the audio (Playing, Paused, Stopped).
     * @return The audio's current status.
     */
    sf::Sound::Status getStatus() const;
};



