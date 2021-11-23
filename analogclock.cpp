#include <SDL.h>
#include <SDL_ttf.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <cstring>

#define S_WIDTH 1024
#define S_HEIGHT 768


/*class Exception{
private:
 int exCode;
 char* exDesc;
public:
 Exception(char* ex, int cd){
 exCode = cd;
 exDesc = new char[strlen(ex)+1];
 strcpy(exDesc, ex);
	}
	~Exception(){
		delete[] exDesc;
	}
};*/

class rgba {
private:
	int r, g, b, a;
public:
	rgba(int rr = 0, int gg = 0, int bb = 0, int aa = 0) :r(rr), g(gg), b(bb), a(aa) {}
	int getR() { return r; }
	int getG() { return g; }
	int getB() { return b; }
	int getA() { return a; }
};

class graphics {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	rgba forecolor;
public:
	SDL_Event event;
	graphics() {
		SDL_CreateWindowAndRenderer(S_WIDTH, S_HEIGHT, 0, &window, &renderer);
		forecolor = rgba(255, 255, 255, 255);
	}
	~graphics() {
		SDL_Quit();
	}


	void clearWithColor(rgba color) {
		SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, forecolor.getR(), forecolor.getG(), forecolor.getB(), forecolor.getA());
	}
	void plotGraph(float x, float y) {
		SDL_RenderDrawPoint(renderer, x, y);
	}
	void drawLine(float orX, float orY, float distX, float distY) {
		SDL_RenderDrawLine(renderer, orX, orY, distX, distY);
	}
	void setBlendMode(SDL_BlendMode mode) {
		SDL_SetRenderDrawBlendMode(renderer, mode);
	}
	void render() {
		SDL_RenderPresent(renderer);
	}
	bool poll(bool (*pollfunc)(SDL_Event&)) {
		SDL_PollEvent(&event);
		return pollfunc(event); //Passing by reference
	}
	void setDrawColor(rgba r) {
		SDL_SetRenderDrawColor(renderer, r.getR(), r.getG(), r.getB(), r.getA());
	}
	void bilt() {
		TTF_Font* font;
		font = TTF_OpenFont("font.ttf", 16);
		SDL_Surface* txtSurface;
		SDL_Color color = { 0,0,255,0 };
		txtSurface = TTF_RenderText_Solid(font, "Hello World!", color);
		SDL_Delay(2000);
		SDL_BlitSurface(txtSurface, NULL, SDL_GetWindowSurface(window), NULL);
		SDL_Delay(2000);
	}
	/*void mainLoop(void (*logic)(graphics& g), bool(*poll)(SDL_Event&)){
		while(1) {
			logic(this);
			if(pollFunction(poll)) break;
		}
	}*/
};


class shape {
protected:
	char* shapeName;
public:
	shape(char* name) {
		shapeName = new char[strlen(name) + 1];
		strcpy(shapeName, name);
	}
	virtual void draw() {
	};
};

class circle :public shape {
public:
	circle() :shape ("Circle") {}
	using shape::draw; //Just for overriding 

	void draw(graphics& graph, float radius, float center_x = S_WIDTH / 2, float center_y = S_HEIGHT / 2) {
		float x, y;
		for (int i = 0; i <= 360; i = i + 1) {
			x = center_x + radius * cos(i * M_PI / 180);
			y = center_y + radius * sin(i * M_PI / 180);
			//SDL_SetRenderDrawColor(renderer,1.0,1.0,1.0,0.4);
			graph.plotGraph(x, y);
			//SDL_RenderDrawPoint(renderer, x, y); //Renders on middle of screen.
		}
		for (int i = 0; i <= 360; i = i + 1) {
			x = center_x + (radius - 1) * cos(i * M_PI / 180);
			y = center_y + (radius - 1) * sin(i * M_PI / 180);
			//SDL_SetRenderDrawColor(renderer,1.0,1.0,1.0,0.4);
			graph.plotGraph(x, y);
			//SDL_RenderDrawPoint(renderer, x, y); //Renders on middle of screen.
		}
		for (int i = 0; i <= 360; i = i + 1) {
			x = center_x + (radius - 2) * cos(i * M_PI / 180);
			y = center_y + (radius - 2) * sin(i * M_PI / 180);
			//SDL_SetRenderDrawColor(renderer,1.0,1.0,1.0,0.4);
			graph.plotGraph(x, y);
			//SDL_RenderDrawPoint(renderer, x, y); //Renders on middle of screen.
		}
	}
	void drawAnim(graphics& graph, float radius, float center_x = S_WIDTH / 2, float center_y = S_HEIGHT / 2) {
		float x, y;
		for (int i = 0; i <= 360; i = i + 1) {
			x = center_x + radius * cos(i * M_PI / 180);
			y = center_y + radius * sin(i * M_PI / 180);
			//SDL_SetRenderDrawColor(renderer,1.0,1.0,1.0,0.4);
			graph.plotGraph(x, y);
			SDL_Delay(2);
			graph.render();
			//SDL_RenderDrawPoint(renderer, x, y); //Renders on middle of screen.
		}
		for (int i = 0; i <= 360; i = i + 1) {
			x = center_x + (radius + 1) * cos(i * M_PI / 180);
			y = center_y + (radius + 1) * sin(i * M_PI / 180);
			//SDL_SetRenderDrawColor(renderer,1.0,1.0,1.0,0.4);
			graph.plotGraph(x, y);
			//SDL_RenderDrawPoint(renderer, x, y); //Renders on middle of screen.
		}
		for (int i = 0; i <= 360; i = i + 1) {
			x = center_x + (radius + 2) * cos(i * M_PI / 180);
			y = center_y + (radius + 2) * sin(i * M_PI / 180);
			//SDL_SetRenderDrawColor(renderer,1.0,1.0,1.0,0.4);
			graph.plotGraph(x, y);
			//SDL_RenderDrawPoint(renderer, x, y); //Renders on middle of screen.
		}
	}
	void drawAnimSemi(graphics& graph, float radius, float center_x = S_WIDTH / 2, float center_y = S_HEIGHT / 2) {
		float x, y;
		for (int i = 90; i <= 270; i = i + 1) {
			x = center_x + radius * cos(i * M_PI / 180);
			y = center_y + radius * sin(i * M_PI / 180);
			//SDL_SetRenderDrawColor(renderer,1.0,1.0,1.0,0.4);
			graph.plotGraph(x, y);
			SDL_Delay(2);
			graph.render();
			//SDL_RenderDrawPoint(renderer, x, y); //Renders on middle of screen.
		}
		for (int i = 90; i <= 270; i = i + 1) {
			x = center_x + (radius - 1) * cos(i * M_PI / 180);
			y = center_y + (radius - 1) * sin(i * M_PI / 180);
			//SDL_SetRenderDrawColor(renderer,1.0,1.0,1.0,0.4);
			graph.plotGraph(x, y);
			//SDL_RenderDrawPoint(renderer, x, y); //Renders on middle of screen.
		}
		for (int i = 90; i <= 270; i = i + 1) {
			x = center_x + (radius - 2) * cos(i * M_PI / 180);
			y = center_y + (radius - 2) * sin(i * M_PI / 180);
			//SDL_SetRenderDrawColor(renderer,1.0,1.0,1.0,0.4);
			graph.plotGraph(x, y);
			//SDL_RenderDrawPoint(renderer, x, y); //Renders on middle of screen.
		}
	}

};

class line :public shape {
public:
	line() :shape ("Line") {}
	using shape::draw;
	void draw(graphics& g, float distance, float angle_in_degree, float center_x = S_WIDTH / 2, float center_y = S_HEIGHT / 2) {
		float x, y;
		y = center_y + distance * sin(angle_in_degree * 3.14 / 180);
		x = center_x + distance * cos(angle_in_degree * 3.14 / 180);
		g.drawLine(center_x, center_y, x, y);
		g.drawLine(center_x, center_y, x + 1, y + 1);
		g.drawLine(center_x, center_y, x + 2, y + 2);
	}
};

/* The Poll Function -- Checks for event and indicates whether to end or not!*/
bool poll(SDL_Event& event) {
	if (event.type == SDL_QUIT) return false;
	if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) return false;
	return true;
}

int main(int argc, char* argv[]) {
	graphics g;
	circle c1;
	circle dot;
	line hour, minute, second;
	//TTF_Init();
	// load font.ttf at size 16 into font
	//g.clearWithColor(rgba(255,150,0,255));
	//g.bilt();
	//g.render();  
	//SDL_Delay(4000);
	g.clearWithColor(rgba(255, 150, 0, 255));
	c1.drawAnimSemi(g, 20, 300, 400);
	hour.draw(g, 50, -90, 350, 420);
	hour.draw(g, 50, -90, 351, 420);
	hour.draw(g, 50, -90, 352, 420);
	c1.drawAnim(g, 20, 400, 400);
	c1.drawAnimSemi(g, 20, 450, 400);
	g.render();
	SDL_Delay(1500);
	while (1) {

		/* Get Time from System */
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		int hr = timeinfo->tm_hour;
		int min = timeinfo->tm_min;
		int sec = timeinfo->tm_sec;
		//int ap = (hr>=12) 1 : 0 ; //1=> pm, 0 =>am 
		hr = (hr >= 12) ? (hr - 12) : hr;
		std::cout << hr;

		/* BackBuffer: Clear Screen, and Plot on (unseen) screen */
		g.clearWithColor(rgba(255, 150, 0, 255));
		g.setBlendMode(SDL_BLENDMODE_BLEND);
		dot.draw(g, 5);
		c1.draw(g, 160);
		second.draw(g, 150, (-90 + sec * 6));
		minute.draw(g, 100, (-90 + min * 6));
		hour.draw(g, 50, (-90 + hr * 360 / 12));

		/* The magic: Put the changes on screen */
		g.render();

		/* Check for Event!*/
		if (!g.poll(poll)) break;
	}
	//TTF_Quit();
	return 0;
}
