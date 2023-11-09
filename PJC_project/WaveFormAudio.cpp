#include "WaveFormAudio.h"

WaveFormAudio::WaveFormAudio(AudioHandler& handler) : AudioVisualizer(handler) { }

void WaveFormAudio::loadFile(const std::string& filename) {
    // Delegate to AudioHandler.
    audioHandler.loadFile(filename);

    origChannelCount = audioHandler.getChannelCount();
    duration = audioHandler.getDuration();
    origSampleCount = audioHandler.getSampleCount();
    origSampleRate = audioHandler.getSampleRate();
    origSamples = audioHandler.getSamples();

    mergeChannel();
}

void WaveFormAudio::mergeChannel() {
    if (origChannelCount == 1) {
        return;
    }

    for (int i = 0; i < origSampleCount; i += 2) {
        monoSamples.push_back((origSamples[i] + origSamples[i + 1]) / 2);
    }

    monoBuffer.loadFromSamples(&monoSamples[0], origSampleCount / 2, 1, origSampleRate);

    audioHandler.sound.setBuffer(monoBuffer);
}

void WaveFormAudio::mapBuffer(int high, int low) {
    mappedSamples.clear();

    int newRange = high - low;

    for (int i = 0; i < origSampleCount / 2; i++) {
        mappedSamples.push_back(low + ((monoSamples[i] + 32768) * newRange / 65535));
    }
}

int WaveFormAudio::getHeight() {
    int val = mappedSamples[audioHandler.sound.getPlayingOffset().asSeconds() * origSampleRate];
    return val;
}

void WaveFormAudio::initializeWindow() {
    waveFormWindow.create(sf::VideoMode(WINDOW_X, WINDOW_Y), "Wave Form");
    waveFormWindow.setFramerateLimit(WINDOW_FPS);
}

void WaveFormAudio::mainLoop() {
    int dur = duration.asSeconds();
    sf::Event ev;

    sf::RectangleShape timeline(sf::Vector2f(TEXTURE_X, 1));
    timeline.setFillColor(sf::Color::Green);
    timeline.setPosition((WINDOW_X - TEXTURE_X) / 2, 0.9 * WINDOW_Y);

    sf::CircleShape seek(3);
    seek.setPointCount(64);
    seek.setOrigin(3, 3);
    seek.setFillColor(sf::Color::Green);

    for (int i = 0; i < TEXTURE_X; i++) {
        vertices[i].position.y = TEXTURE_Y / 2;
        vertices[i].color = sf::Color(0, 255, 0, i * 255 / TEXTURE_X);
    }

    sf::VertexBuffer vertexBuffer(sf::LineStrip);
    vertexBuffer.create(TEXTURE_X);

    renderGraph.create(TEXTURE_X, TEXTURE_Y);
    graph.setTexture(renderGraph.getTexture());
    graph.setPosition((WINDOW_X - TEXTURE_X) / 2, (WINDOW_Y - TEXTURE_Y) * 0.2);

    audioHandler.play();

    while (waveFormWindow.isOpen()) {
        while (waveFormWindow.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed || (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)) {
                waveFormWindow.close();
            }
            else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space) {
                if (audioHandler.getStatus() == sf::Sound::Paused) {
                    audioHandler.play();
                }
                else {
                    audioHandler.pause();
                }
            }
        }
        for (int i = 0; i < TEXTURE_X; i++) {
            vertices[i].position = sf::Vector2f(i, vertices[i + 1].position.y);
        }

        vertices[TEXTURE_X - 1].position = sf::Vector2f(TEXTURE_X - 1, TEXTURE_Y / 2 + getHeight());

        vertexBuffer.update(vertices);

        int nowSec = audioHandler.sound.getPlayingOffset().asSeconds();
        int pos = (WINDOW_X - TEXTURE_X) / 2 + nowSec * TEXTURE_X / dur;
        seek.setPosition(pos, WINDOW_Y * 0.9);

        renderGraph.clear(sf::Color::Black);
        renderGraph.draw(vertexBuffer);

        waveFormWindow.clear(sf::Color::Black);
        waveFormWindow.draw(graph);
        waveFormWindow.draw(timeline);
        waveFormWindow.draw(seek);
        waveFormWindow.display();

        if (dur == nowSec) {
            audioHandler.pause();
            waveFormWindow.close();
        }
    }
    audioHandler.pause();
}

void WaveFormAudio::run() {
    mapBuffer(TEXTURE_Y / 2, -TEXTURE_Y / 2);
    initializeWindow();
    mainLoop();
}
