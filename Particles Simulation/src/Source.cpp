#include <iostream>
#include <SDL.h>

int main(int argc, char* args[])
{
    std::cout << "Hello World!" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL Failed" << std::endl;
        return 1;
    }

    std::cout << "SDL Succeeded" << std::endl;

    SDL_QUIT;

    return 0;
}