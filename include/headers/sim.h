#pragma once

#include <iostream>
#include <SDL.h>

class Sim
{
public:
    // constructor
    Sim();
    ~Sim(); // destructor 
    
    // run function
    void run();

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;    

    int _screenWidth = 800;
    int _screenHeight = 600;

    bool isRunning;
    int count;
};

