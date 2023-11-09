#ifndef AUDIOBARS_H
#define AUDIOBARS_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fftw3.h>
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include <stdexcept>

#include "AudioHandler.h"
#include "AudioVisualizer.h"

/**
 * @class AudioBars
 * @brief Visualizes audio in the form of bars.
 *
 * This class uses the FFT algorithm to process audio samples and visualize them as bars.
 * The height of each bar represents the magnitude of the frequency at that index.
 */
class AudioBars : public AudioVisualizer {
private:
    static constexpr int SAMPLE_RATE = 44100;  ///< Sampling rate of the audio.
    static constexpr int FFT_SIZE = 512;       ///< Size for FFT calculations.
    static constexpr int BARS = 128;           ///< Number of bars for visualization.

    const int WINDOW_X = 1000;                 ///< Window width.
    const int WINDOW_Y = 600;                  ///< Window height.
    const int WINDOW_FPS = 60;                 ///< Window frame rate.

    sf::RenderWindow barsWindow;               ///< SFML window for rendering bars.
    std::thread visThread;                     ///< Thread for audio visualization.

    std::vector<float> magnitudes;             ///< Magnitudes for each bar.
    std::mutex mtx;                            ///< Mutex for synchronizing access to magnitudes.

    static float logScale(float value, float maxVal);
    static void visualizationThread(AudioBars& vis);

    sf::RectangleShape timeline;               ///< Shape representing the audio timeline.
    sf::CircleShape seek;                      ///< Shape for the seek circle.
    sf::Time duration;                         ///< Duration of the loaded audio.

public:
    /**
     * @brief Constructs the AudioBars visualizer with an audio handler.
     * @param handler Reference to the audio handler.
     */
    AudioBars(AudioHandler& handler);

    /**
     * @brief Loads an audio file for visualization.
     * @param filename The path to the audio file.
     */
    void loadFile(const std::string& filename);

    /**
     * @brief Initiates the audio visualization.
     */
    void run();
};

#endif // AUDIOBARS_H

