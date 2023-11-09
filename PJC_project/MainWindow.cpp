#include "MainWindow.h"
#include <iostream>


MainWindow::MainWindow(int width, int height, const char* title) : waveFormAudio(audioHandler), audioBars(audioHandler) {
    window.create(sf::VideoMode(width, height), title);
    window.setFramerateLimit(60);


    font.loadFromFile("arial.ttf");
    //Button for choosing file
    chooseFileButton.setPosition(20, height - 70);
    chooseFileButton.setSize(sf::Vector2f(176, 50));
    chooseFileButton.setFillColor(sf::Color::Black);
    chooseFileButton.setOutlineThickness(2);
    chooseFileButton.setOutlineColor(sf::Color::Green);
    
    chooseFileText.setFont(font);
    chooseFileText.setString("Choose File");
    chooseFileText.setCharacterSize(24);
    chooseFileText.setFillColor(sf::Color::Green);
    chooseFileText.setPosition(40, height - 60);

    //Button for start playing music file
    playButton.setPosition(216, height - 70);
    playButton.setSize(sf::Vector2f(176, 50));
    playButton.setFillColor(sf::Color::Black);
    playButton.setOutlineThickness(2);
    playButton.setOutlineColor(sf::Color::Green);

    playText.setFont(font);
    playText.setString("Play File");
    playText.setCharacterSize(24);
    playText.setFillColor(sf::Color::Green);
    playText.setPosition(256, height - 60);

    //Button for pause playing music file
    pauseButton.setPosition(412, height - 70);
    pauseButton.setSize(sf::Vector2f(176, 50));
    pauseButton.setFillColor(sf::Color::Black);
    pauseButton.setOutlineThickness(2);
    pauseButton.setOutlineColor(sf::Color::Green);

    pauseText.setFont(font);
    pauseText.setString("Pause");
    pauseText.setCharacterSize(24);
    pauseText.setFillColor(sf::Color::Green);
    pauseText.setPosition(465, height - 60);
    
    //Button for choosing Bars Mode
    barsModeButton.setPosition(608, height - 70);
    barsModeButton.setSize(sf::Vector2f(176, 50));
    barsModeButton.setFillColor(sf::Color::Black);
    barsModeButton.setOutlineThickness(2);
    barsModeButton.setOutlineColor(sf::Color::Green);

    barsText.setFont(font);
    barsText.setString("Bars Mode");
    barsText.setCharacterSize(24);
    barsText.setFillColor(sf::Color::Green);
    barsText.setPosition(640, height - 60);

    //Button for choosing WaveForm Spectrum
    waveFormButton.setPosition(804, height - 70);
    waveFormButton.setSize(sf::Vector2f(176, 50));
    waveFormButton.setFillColor(sf::Color::Black);
    waveFormButton.setOutlineThickness(2);
    waveFormButton.setOutlineColor(sf::Color::Green);

    waveFormText.setFont(font);
    waveFormText.setString("Wave Mode");
    waveFormText.setCharacterSize(24);
    waveFormText.setFillColor(sf::Color::Green);
    waveFormText.setPosition(830, height - 60);
}

void MainWindow::run() {
    while (window.isOpen()) {
        handleEvents();
        window.clear(sf::Color::Black);

        window.draw(chooseFileButton);
        window.draw(chooseFileText);

        window.draw(playButton);
        window.draw(playText);

        window.draw(pauseButton);
        window.draw(pauseText);

        window.draw(barsModeButton);
        window.draw(barsText);

        window.draw(waveFormButton);
        window.draw(waveFormText);

        window.display();       
    }
}

void MainWindow::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (chooseFileButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    chooseFile();
                }
                if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    play();
                }
                if (pauseButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    pause();
                }
                if (waveFormButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    setVisualizerMode(&waveFormAudio);
                    visualize();
                }
                if (barsModeButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    setVisualizerMode(&audioBars);
                    visualize();
                }
            }
        
        }
    }
}
void MainWindow::chooseFile() {
    std::cout << "Pass the file name (.wav):" << std::endl;
    while (true) {
        std::cin >> selectedFile;

        // Check if file has .wav extension
        if (selectedFile.size() >= 4 && selectedFile.substr(selectedFile.size() - 4) == ".wav") {

            // Check if file exists using fstream
            std::ifstream file(selectedFile);
            if (file.good()) {
                file.close();
                break;  // exit the loop if the file exists and is a .wav file
            }
            else {
                std::cout << "The file does not exist. Please enter a valid .wav file:" << std::endl;
            }
        }
        else {
            std::cout << "Please enter a valid .wav file:" << std::endl;
        }
    }
    std::cout << "File is okay, enjoy!" << std::endl;
}

void MainWindow::play() {
    if (!selectedFile.empty()) {
        audioHandler.loadFile(selectedFile);
        audioHandler.play();
    }
}

void MainWindow::pause() {
    audioHandler.pause();
}


