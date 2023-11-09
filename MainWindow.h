#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include "WaveFormAudio.h"
#include "AudioHandler.h"
#include "AudioBars.h"
#include "AudioVisualizer.h"

/**
 * @class MainWindow
 * @brief The primary GUI window for audio file selection and visualization.
 *
 * The MainWindow class provides an interface for choosing audio files,
 * playing/pausing audio, and switching between different audio visualizations.
 */
class MainWindow {
public:
    /**
    * @brief Constructor that initializes the MainWindow with specific dimensions and a title.
    * @param width Width of the window.
    * @param height Height of the window.
    * @param title The title displayed in the window's title bar.
    */
    MainWindow(int width, int height, const char* title);

    /**
     * @brief Main loop for rendering the window and handling events.
     */
    void run();

private:
    /**
      * @brief Process and handle SFML window events.
      */
    void handleEvents();

    /**
     * @brief Lets the user choose an audio file for playback and visualization.
     */
    void chooseFile();

    /**
     * @brief Begins playing the chosen audio file.
     */
    void play();

    /**
     * @brief Pauses the audio playback.
     */
    void pause();

    sf::RenderWindow window; ///< The primary SFML window.
    sf::RectangleShape chooseFileButton, playButton, pauseButton, barsModeButton, waveFormButton; ///< UI buttons.
    sf::Text chooseFileText, playText, pauseText, barsText, waveFormText; ///< Text displayed on UI buttons.
    sf::Font font; ///< Font used for button text.

    std::string selectedFile; ///< Path to the currently selected audio file.
    AudioHandler audioHandler; ///< Handler for loading and controlling audio.
    WaveFormAudio waveFormAudio; ///< Audio visualization mode showing waveform.
    AudioBars audioBars; ///< Audio visualization mode showing bars.
    AudioVisualizer* visualizer; ///< Current audio visualization mode in use.

    /**
     * @brief Sets the active audio visualization mode.
     * @param mode Pointer to the AudioVisualizer to use.
     */
    void setVisualizerMode(AudioVisualizer* mode) {
        visualizer = mode;
    }

    /**
     * @brief Loads the selected audio file into the current visualizer and begins visualization.
     */
    void visualize() {
        if (visualizer) {
            window.setVisible(false);
            visualizer->loadFile(selectedFile);
            visualizer->run();
            window.setVisible(true);
        }
    }
};

#endif // MAINWINDOW_H