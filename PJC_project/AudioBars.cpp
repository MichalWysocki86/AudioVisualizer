#include "AudioBars.h"

/**
 * @brief Constructs the AudioBars visualizer with an audio handler.
 * @param handler Reference to the audio handler.
 */
AudioBars:: AudioBars(AudioHandler& handler) : AudioVisualizer(handler) { }

/**
 * @brief Scales a value logarithmically.
 * @param value The value to be scaled.
 * @param maxVal Maximum value used for normalization.
 * @return The logarithmically scaled value.
 */
float AudioBars::logScale(float value, float maxVal) {
    if (value == 0) return 0;
    float logMax = std::log(maxVal + 1);
    return std::log(value + 1) / logMax;
}

/**
 * @brief The main thread function for visualizing audio with FFT.
 * @param vis Reference to the AudioBars instance.
 */
void AudioBars::visualizationThread(AudioBars& vis) {
    fftw_complex out[vis.FFT_SIZE / 2 + 1];
    double in[vis.FFT_SIZE];
    fftw_plan p = fftw_plan_dft_r2c_1d(vis.FFT_SIZE, in, out, FFTW_MEASURE);

    while (vis.barsWindow.isOpen()) { 
        if (vis.audioHandler.getStatus() != sf::Sound::Playing) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        sf::Time currentOffset = vis.audioHandler.getPlayingOffset();
        std::size_t sampleOffset = currentOffset.asSeconds() * vis.SAMPLE_RATE;

        if (sampleOffset < vis.audioHandler.getSampleCount() - vis.FFT_SIZE) {
            const sf::Int16* samples = vis.audioHandler.getSamples() + sampleOffset;

            for (int i = 0; i < vis.FFT_SIZE; i++) {
                in[i] = samples[i] / 32768.0;
            }

            fftw_execute(p);

            int binSize = (vis.FFT_SIZE / 2 + 1) / vis.BARS;
            std::vector<float> localMagnitudes(vis.BARS, 0);

            for (int i = 0; i < vis.BARS; i++) {
                for (int j = 0; j < binSize; j++) {
                    localMagnitudes[i] += std::sqrt(out[i * binSize + j][0] * out[i * binSize + j][0] + out[i * binSize + j][1] * out[i * binSize + j][1]);
                }
                localMagnitudes[i] /= binSize;
            }
            vis.mtx.lock();
            vis.magnitudes = localMagnitudes;
            vis.mtx.unlock();
        }
    }

    fftw_destroy_plan(p);
    fftw_cleanup();
}

/**
 * @brief Loads an audio file for visualization.
 * @param filename The path to the audio file.
 */
void AudioBars::loadFile(const std::string& filename) {
    audioHandler.loadFile(filename);
}

/**
 * @brief Initiates the audio visualization.
 */
void AudioBars::run() {
    barsWindow.create(sf::VideoMode(WINDOW_X, WINDOW_Y), "Audio Bars");
    barsWindow.setFramerateLimit(WINDOW_FPS);

    visThread = std::thread(AudioBars::visualizationThread, std::ref(*this));
    audioHandler.sound.play();

    while (barsWindow.isOpen()) {
        sf::Event event;
        while (barsWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                barsWindow.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (audioHandler.sound.getStatus() == sf::Sound::Playing) {
                    audioHandler.sound.pause();
                }
                else if (audioHandler.sound.getStatus() == sf::Sound::Paused) {
                    audioHandler.sound.play();
                }
            }
        }
        if (audioHandler.sound.getStatus() == sf::Sound::Stopped) {
            barsWindow.close();
        }

        mtx.lock();
        std::vector<float> localMagnitudes = magnitudes;
        mtx.unlock();

        barsWindow.clear();
        for (int i = 0; i < localMagnitudes.size(); i++) {
            float scaledMagnitude = logScale(localMagnitudes[i], 1.0f) * 100.0f;
            sf::RectangleShape line(sf::Vector2f(15, scaledMagnitude));
            line.setPosition(i * 16, barsWindow.getSize().y);
            line.rotate(180);
            if (scaledMagnitude >  100) {
                line.setFillColor(sf::Color::Red);
            }
            else
            {
                line.setFillColor(sf::Color::Green);
            }
            barsWindow.draw(line);
        }
        barsWindow.display();
    }
    audioHandler.sound.pause();
    visThread.join();
}
