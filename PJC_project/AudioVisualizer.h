#pragma once
#include "AudioHandler.h"

/**
 * @class AudioVisualizer
 * @brief Abstract base class for audio visualization.
 *
 * The AudioVisualizer class provides an interface for visualizing audio.
 * Derived classes are expected to provide their own implementations for
 * loading audio files and running the visualization.
 */
class AudioVisualizer {
public:
    /**
     * @brief Constructor that initializes the AudioVisualizer with an AudioHandler.
     * @param handler Reference to an AudioHandler instance.
     */
    AudioVisualizer(AudioHandler& handler) : audioHandler(handler) {}

    /**
     * @brief Loads an audio file for visualization.
     * @param filename Path to the audio file.
     * @note This is a pure virtual function and must be implemented by derived classes.
     */
    virtual void loadFile(const std::string& filename) = 0;

    /**
     * @brief Starts the audio visualization.
     * @note This is a pure virtual function and must be implemented by derived classes.
     */
    virtual void run() = 0;

protected:
    AudioHandler& audioHandler; ///< Reference to the associated AudioHandler instance. Derived classes can access this.
};