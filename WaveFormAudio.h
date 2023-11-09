#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "AudioHandler.h"
#include "AudioVisualizer.h"

/**
 * \class WaveFormAudio
 * \brief A class derived from AudioVisualizer to visualize the waveform of a given audio.
 *
 * This class visualizes audio waveforms by mapping audio samples onto the visual space of the window.
 */
class WaveFormAudio : public AudioVisualizer
{
public:

    /**
     * \brief Constructor that initializes the WaveFormAudio with a reference to an AudioHandler.
     * \param audioHandler Reference to the AudioHandler object.
     */
    WaveFormAudio(AudioHandler& audioHandler);

    /**
     * \brief Loads the given audio file and retrieves necessary data from it.
     * \param filename Path to the audio file.
     */
    void loadFile(const std::string& filename) override;

    /**
     * \brief Maps the amplitude of audio samples onto the visual space of the window.
     * \param high The maximum value for mapping.
     * \param low The minimum value for mapping.
     */
    void mapBuffer(int high, int low);

    /**
     * \brief Retrieves the height of a given sample for visualization.
     * \return An integer representing the height value.
     */
    int getHeight();

    /**
     * \brief Begins the waveform visualization process.
     */
    void run() override;

private:

    /**
     * \brief Converts stereo audio samples to mono.
     * If the audio is stereo (2 channels), it merges both channels into a mono channel.
     */
    void mergeChannel();

    /**
     * \brief Sets up the SFML window for waveform rendering.
     */
    void initializeWindow();

    /**
     * \brief Core loop for rendering the waveform and handling events.
     */
    void mainLoop();

    sf::Time duration; ///< Duration of the loaded audio file.
    sf::SoundBuffer origBuffer; ///< Buffer to store the original audio samples.
    const sf::Int16* origSamples; ///< Pointer to the original audio samples.
    unsigned int origChannelCount; ///< Number of channels in the original audio (e.g., 2 for stereo).
    unsigned int origSampleRate; ///< Sample rate of the original audio.
    sf::Uint64 origSampleCount; ///< Number of samples in the original audio.
    sf::SoundBuffer monoBuffer; ///< Buffer to store mono audio samples.
    std::vector<sf::Int16> monoSamples; ///< Vector storing the mono audio samples.
    unsigned int monoSampleRate; ///< Sample rate of the mono audio.
    std::vector<sf::Int16> mappedSamples; ///< Vector storing mapped audio samples for visualization.

    const int WINDOW_X = 600; ///< Width of the window.
    const int WINDOW_Y = 600; ///< Height of the window.
    const int WINDOW_FPS = 60; ///< Frames per second for the window.
    const int TEXTURE_X = 0.8 * WINDOW_X; ///< Width of the texture for rendering the waveform.
    const int TEXTURE_Y = 0.35 * WINDOW_Y; ///< Height of the texture for rendering the waveform.

    sf::RenderWindow waveFormWindow; ///< Window for rendering the waveform.
    sf::Vertex vertices[480]; ///< Vertices for rendering the waveform.
    sf::RenderTexture renderGraph; ///< Render texture for the waveform.
    sf::Sprite graph; ///< Sprite for displaying the waveform.
};

