//! \file main.cpp
//! \brief Entry point for the Audio Visualizer application.
//! 
#include "MainWindow.h"

/*!
 * \brief Main function that initiates and runs the Audio Visualizer.
 *
 * This function creates the main window of the application and runs it.
 *
 * \return Returns 0 upon successful execution.
 */
int main()
{
    MainWindow mainWindow(1000, 800, "Audio Vizualiser");
    mainWindow.run();
    return 0;
}

