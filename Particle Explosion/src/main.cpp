#include <iostream>
#include <cmath>
#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include "Screen.h" 
#include "Swarm.h" 
#include <windows.h>

int main(int argc, char* argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE); 

	srand(time(NULL));

	Daklit::Screen screen;

	if (screen.init() == false)
	{
		std::cout << "Error Initializing" << std::endl;
	}

	Daklit::Swarm swarm; 

	while (true)
	{	
		const Daklit::Particle * const pParticles = swarm.getParticles(); 
		
		Uint32 elapsed = SDL_GetTicks();

		//screen.clear();
		swarm.update(elapsed);

		
		unsigned char red = (1 + sin(elapsed * 0.0001)) * 128;
		unsigned char green = (1 + sin(elapsed * 0.0002)) * 128;
		unsigned char blue = (1 + sin(elapsed * 0.0003)) * 128;

		for (int i = 0; i < swarm.nParticles; i++)
		{
			Daklit::Particle particle = pParticles[i]; 

			int x = (particle.m_x + 1) * screen.screenWidth / 2;
			int y = particle.m_y * screen.screenWidth / 2 + screen.screenHeight  / 2;

			screen.setPixel(x, y, red, green, blue);
		}


		screen.boxBlur();
		 
		screen.update();

		if (screen.processEvents() == false)
		{
			break; 
		}
	}

	//ShowWindow(GetConsoleWindow(), SW_RESTORE);
	screen.close();

	return 0;
}