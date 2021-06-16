#define SDL_MAIN_HANDLED 
#include "SDL.h"
#include "SDL_image.h"
#include "stdio.h"

//cl main.cpp /Iinclude SDL2main.lib SDL2.lib SDL2_image.lib

void HandleInput();
void Update();
void Draw();

bool quit = false;
SDL_Renderer *renderer; 
SDL_Surface *screen_surface;
int x, y;
float velocity = 1.0f;

int main(int argc, char* argv[])
{
	SDL_Window *window; 

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
		fprintf(stderr, "could not initialize sdl2_image: %s\n", IMG_GetError());
		return false;
	}

    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_RESIZABLE               // flags - see below
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    while(!quit)
    {
    	HandleInput();
    	Update();
    	Draw();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();

    return 0;
}

void HandleInput()
{
	SDL_Event event;

	SDL_GetMouseState(&x, &y);

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				SDL_Log("Quit");
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_DOWN:
						y += velocity;
						break;
					case SDLK_UP:
						y -= velocity;
						break;
					case SDLK_LEFT:
						x -= velocity;
						break;
					case SDLK_RIGHT:
						x += velocity;
						break;
					case SDLK_KP_PLUS:
						velocity += 1;
						break;
					case SDLK_KP_MINUS:
						velocity -= 1;
						break;
					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_DOWN:
						
						break;
					case SDLK_UP:
						
						break;
					case SDLK_LEFT:
						
						break;
					case SDLK_RIGHT:
						
						break;
					default:
						break;
				}
				break;
			default:
				break;
	    }
    }
}

void Update()
{

}

void Draw()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_Rect rect;
	rect.w = 100;
	rect.h = 100;
	rect.x = x - rect.w/2;
	rect.y = y - rect.h/2;
	SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}


// static SDL_Surface* LoadImage(std::string path)
// {
// 	SDL_Surface* img = IMG_Load(path.c_str());

// 	if (img == NULL)
// 	{
// 		fprintf(stderr, "could not load image: %s\n", IMG_GetError());
// 		return NULL;
// 	}

// 	SDL_Surface* optimizedImg = SDL_ConvertSurface(img, screen_surface->format, 0);

// 	if (optimizedImg == NULL) 
// 		fprintf(stderr, "could not optimize image: %s\n", SDL_GetError());
// 	SDL_FreeSurface(img);
	
// 	return optimizedImg;
// }