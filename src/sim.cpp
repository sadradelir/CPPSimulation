#include <sim.h>
#include <iostream>

Sim::Sim() {};
Sim::~Sim() {};

void Sim::run()
{
    std::cout << "Sim running" << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    _window = SDL_CreateWindow("Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_SHOWN);
}