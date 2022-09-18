#include "Screen.h"
#include <string.h>

namespace Daklit
{
	Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL)
	{
	}

	bool Screen::init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			return false;
		}

		m_window = SDL_CreateWindow("Particle Fire Explosion",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth,
			screenHeight, SDL_WINDOW_SHOWN);

		if (m_window == NULL)
		{
			SDL_Quit();
			return false;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, screenWidth, screenHeight);

		if (m_renderer == NULL)
		{
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		if (m_texture == NULL)
		{
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		m_buffer1 = new Uint32[screenWidth * screenHeight];
		m_buffer2 = new Uint32[screenWidth * screenHeight];

		memset(m_buffer1, 0, screenWidth * screenHeight * sizeof(Uint32));
		memset(m_buffer2, 0, screenWidth * screenHeight * sizeof(Uint32));

		return true;
	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
	{
		if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
		{
			return;
		}

		//RGBA
		Uint32 color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xff;

		m_buffer1[(y * screenWidth) + x] = color;
	}

	void Screen::boxBlur()
	{
		Uint32* temp = m_buffer1;
		m_buffer1 = m_buffer2;
		m_buffer2 = temp;

		for (int y = 0; y < screenHeight; y++)
		{
			for (int x = 0; x < screenWidth; x++)
			{
				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;
					
				for (int row = -1; row <= 1; row++)
				{
					for (int col = -1; col <= 1; col++)
					{
						int currentX = x + col;
						int currentY = y + row;

						if (currentX >= 0 && currentX < screenWidth &&
							currentY >= 0 && currentY < screenHeight)
						{
							Uint32 color = m_buffer2[currentY * screenWidth + currentX];

							Uint8 red = (color & 0xff000000 )>> 24;
							Uint8 green = (color & 0xff0000) >> 16;
							Uint8 blue = (color & 0xff00) >> 8;

							redTotal += red;
							greenTotal += green;
							blueTotal += blue;
						}
					}
				}
				Uint8 red = redTotal/9;
				Uint8 green = greenTotal/9;
				Uint8 blue = blueTotal/9;

				setPixel(x, y, red, green, blue);
			}
		}
	}

	void Screen::update()
	{
		SDL_UpdateTexture(m_texture, NULL, m_buffer1, screenWidth * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	}

	bool Screen::processEvents()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				return false;
			}
		}
		return true;
	}

	void Screen::close()
	{
		delete[] m_buffer1;
		delete[] m_buffer2;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}
}