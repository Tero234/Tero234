#include <SDL.h>
#include <cmath>
#include <ctime>
#include <iostream>

#define S_WIDTH 1024
#define S_HEIGHT 768




void drawCircle(SDL_Renderer* renderer,float radius, float center_x = S_WIDTH / 2, float center_y = S_HEIGHT / 2) {
	int x, y;
	for (int i = 0; i <= 360; i = i + 1) {
		x = center_x + radius * cos(i * M_PI / 180);
		y = center_y + radius * sin(i * M_PI / 180);
		//SDL_SetRenderDrawColor(renderer,1.0,1.0,1.0,0.4);
		SDL_RenderDrawPoint(renderer, x, y); //Renders on middle of screen.
	}
	for (int i = 0; i <= 360; i = i + 1) {
		x = center_x + (radius - 1) * cos(i * M_PI / 180);
		y = center_y + (radius - 1) * sin(i * M_PI / 180);
		//SDL_SetRenderDrawColor(renderer,1.0,1.0,1.0,0.4);
		SDL_RenderDrawPoint(renderer, x, y); //Renders on middle of screen.
	}
	for (int i = 0; i <= 360; i = i + 1) {
		x = center_x + (radius - 2) * cos(i * M_PI / 180);
		y = center_y + (radius - 2) * sin(i * M_PI / 180);
		//SDL_SetRenderDrawColor(renderer,1.0,1.0,1.0,0.4);
		SDL_RenderDrawPoint(renderer, x, y); //Renders on middle of screen.
	}

}

void drawLine(SDL_Renderer* renderer,float distance, float angle_in_degree, float center_x = S_WIDTH / 2, float center_y = S_HEIGHT / 2) {
	int x, y;
	y = center_y + distance * sin(angle_in_degree * M_PI / 180);
	x = center_x + distance * cos(angle_in_degree * M_PI / 180);
	SDL_RenderDrawLine(renderer, S_WIDTH / 2, S_HEIGHT / 2, x, y);
}
int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	SDL_CreateWindowAndRenderer(S_WIDTH, S_HEIGHT, 0, &window, &renderer);
	//SDL_Surface *s = SDL_GetWindowSurface(window); //Declaring the surface.
	//s = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0, 0, 0, 0); //Creating the surface.
	//SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 0, 0)); //Filling the surface with red colour.
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 55);

	SDL_RenderFillRect(renderer, NULL);
	SDL_RenderPresent(renderer);

	//Probably on a loop
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	drawCircle(renderer, 160);
	//drawLine(renderer,150,62);
	SDL_RenderPresent(renderer); //back buffer to front buffer? :D 
	SDL_Delay(2000);

	while (true)
	{



		//Get system Time
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		int hr = timeinfo->tm_hour;
		int min = timeinfo->tm_min;
		int sec = timeinfo->tm_sec;
		//int ap = (hr>=12) 1 : 0 ; //1=> pm, 0 =>am 
		hr = (hr >= 12) ? (hr - 12) : hr;
		std::cout << min;
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		drawCircle(renderer, 160);
		SDL_RenderPresent(renderer);
		drawLine(renderer, 150, (-9090 + sec * 6));
		drawLine(renderer, 100, (-9090 + min * 6));
		drawLine(renderer, 50, (-9090 + hr * 360 / 12));
		SDL_RenderPresent(renderer);
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) break;
		if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) break;

	}
	SDL_Quit();
	return 0;
}
