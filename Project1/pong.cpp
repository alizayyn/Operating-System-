//L226551
//ALI ZAIN
//q3 assignment 2
//operating system
//this game is made using sdl library and threads
//threads are implemented to control the paddle and pong  
// play pong game  and enjoy :)
#include<iostream>

#include<SDL2/SDL.h>

#include<SDL2/SDL_ttf.h>

#include<string>

#include<sys/wait.h>

#include<pthread.h>

#include<unistd.h>
//#include<SDL2/SDL_mixer>

using namespace std;



//global variables


int rightPlayerScore = 0;

int LeftPlayerScore = 0;



int Roof = 155;



struct pingpong

{

	int x;

	int y;

	int radius = 20;

};
int winheight;

int  winwidth;



pingpong ball;



//function to draw the rectangle x y width length

SDL_Rect RigthPaddle = { 0,0,30,250 };

SDL_Rect LeftPaddle = { 0,0,30,250 };



//check to Quit the game



bool Quit = false;



void printcircle(SDL_Renderer* rend, int x, int y, int r)

{

	int X = -r;

	int Y = 0;

	int e1 = 2 - 2 * r;

	int e2;

	while (X <= 0) {

		SDL_RenderDrawLine(rend, x + X, y - Y, x - X, y - Y);

		SDL_RenderDrawLine(rend, x + X, y + Y, x - X, y + Y);

		e2 = e1;

		if (e2 <= Y)

		{

			e1 += ++Y * 2 + 1;

			if (-X == Y && e2 <= X)

				e2 = 0;

		}

		if (e2 > X)

			e1 += ++X * 2 + 1;

	}

}

void printScore(SDL_Renderer* rend, TTF_Font* font, int score, int x, int y)

{

	SDL_Color color = { 255,255,0,255 };

	SDL_Surface* surface = TTF_RenderText_Solid(font, to_string(score).c_str(), color);

	if (!surface)
	{
		exit(0);

	}
	SDL_Texture* text = SDL_CreateTextureFromSurface(rend, surface);

	if (!text)
	{
		exit(0);
	}
	SDL_Rect txtRect = { x,y,80,130 };

	SDL_RenderCopy(rend, text, nullptr, &txtRect);

	SDL_DestroyTexture(text);

	SDL_FreeSurface(surface);

}

void DrawIt(SDL_Renderer* rend, TTF_Font* font)

{

	SDL_Rect Full = { 0,0,winwidth,winheight };

	//back ground

	SDL_SetRenderDrawColor(rend, 146, 149, 152, 255);

	SDL_RenderFillRect(rend, &Full);

	// the lines

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

	printScore(rend, font, LeftPlayerScore, 800, 20);

	printScore(rend, font, rightPlayerScore, 1050, 20);



	//upper line

	SDL_Rect b;

	b.h = 30;

	b.w = winwidth;

	b.x = 0;

	b.y = 0;

	SDL_RenderFillRect(rend, &b);



	//upperlower

	b.y = Roof - 17;

	SDL_RenderFillRect(rend, &b);



	//lower lower

	b.y = winheight - 23;

	SDL_RenderFillRect(rend, &b);







	//right

	b.w = 15;

	b.h = winheight;

	b.x = 1905;
	b.y = 0;

	SDL_RenderFillRect(rend, &b);



	b.w = 30;

	b.h = 150;

	b.x = 1180;
	b.y = 0;

	SDL_RenderFillRect(rend, &b);





	b.w = 30;

	b.h = 150;

	b.x = 670;
	b.y = 0;

	SDL_RenderFillRect(rend, &b);





	//left

	b.w = 15;

	b.h = winheight;

	b.y = 0;

	b.x = 0;

	SDL_RenderFillRect(rend, &b);



	//middle

	SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

	b.w = 20;

	b.h = 890;

	b.x = 950;
	b.y = 165;

	SDL_RenderFillRect(rend, &b);







	//bat colours

	SDL_SetRenderDrawColor(rend, 255, 218, 185, 255);

	SDL_RenderFillRect(rend, &RigthPaddle);

	SDL_SetRenderDrawColor(rend, 139, 69, 19, 255);

	SDL_RenderFillRect(rend, &LeftPaddle);

	SDL_SetRenderDrawColor(rend, 0, 0, 80, 255);

	printcircle(rend, ball.x, ball.y, ball.radius);



	SDL_RenderPresent(rend);

	SDL_RenderClear(rend);

}

void press(SDL_Event& e, bool flag[])

{



	if (e.type == SDL_KEYDOWN) {

		if (e.key.keysym.sym == SDLK_ESCAPE) {

			Quit = true;

		}

		else if (e.key.keysym.sym == SDLK_w) {

			flag[0] = true;

		}

		else if (e.key.keysym.sym == SDLK_s) {

			flag[1] = true;

		}

		else if (e.key.keysym.sym == SDLK_UP) {

			flag[2] = true;

		}

		else if (e.key.keysym.sym == SDLK_DOWN) {

			flag[3] = true;

		}

	}







}



void release(SDL_Event& e, bool flag[])
{



	if (e.type == SDL_KEYUP) {

		if (e.key.keysym.sym == SDLK_w) {

			flag[0] = false;

		}

		else if (e.key.keysym.sym == SDLK_s) {

			flag[1] = false;

		}

		else if (e.key.keysym.sym == SDLK_UP) {

			flag[2] = false;

		}

		else if (e.key.keysym.sym == SDLK_DOWN) {

			flag[3] = false;

		}

	}





}



void PaddleMove(bool flag[])

{

	int count = 0;

	if (flag[0])

		while (LeftPaddle.y > Roof & count < 20)

		{

			LeftPaddle.y--;

			count++;

		}

	count = 0;

	if (flag[1])

		while (LeftPaddle.y + LeftPaddle.h < winheight - 5 && count < 20)

		{

			LeftPaddle.y++;

			count++;

		}

	count = 0;

	if (flag[2])

		while (RigthPaddle.y > Roof & count < 20)

		{

			RigthPaddle.y--;

			count++;

		}

	count = 0;

	if (flag[3])

		while (RigthPaddle.y + RigthPaddle.h < winheight && count < 20)

		{

			RigthPaddle.y++;

			count++;

		}

}

void* ControLeftPaddles(void* param)

{

	SDL_Event e;

	bool flag[4] = { false };

	Uint32 sec = 0;

	Uint32 curTime, lastUpdateTime = 0;

	while (!Quit)

	{

		while (!SDL_PollEvent(&e));

		curTime = SDL_GetTicks();

		press(e, flag);

		release(e, flag);

		if (curTime - lastUpdateTime >= sec)

		{

			PaddleMove(flag);

			lastUpdateTime = SDL_GetTicks();

		}

	}

	return NULL;

}

void* pongMove(void* param)

{

	int move = 1, speed = 1;	//1=left,2=right,3=right down,4=right up, 5=left down, 6=left up.

	while (!Quit)

	{

		if (ball.x + ball.radius >= RigthPaddle.x)

		{

			if (ball.y - ball.radius <= RigthPaddle.y + RigthPaddle.h && ball.y + ball.radius >= RigthPaddle.y)

			{

				if (move == 2)

				{

					int lim1 = RigthPaddle.y + RigthPaddle.h / 3, lim2 = RigthPaddle.y + (2 * RigthPaddle.h / 3);

					if (ball.y <= lim1)

					{

						move = 6;

					}

					else if (ball.y >= lim2)

					{

						move = 5;

					}

					else

					{

						move = 1;



					}

				}

				else if (move == 3)

				{
					move = 5;
				}

				else if (move == 4)

				{
					move = 6;
				}

			}

			else if (ball.x + ball.radius - 20 >= RigthPaddle.x)

			{

				LeftPlayerScore++;

				move = 2;

				ball.x = winwidth / 2;

				ball.y = (Roof + winheight) / 2;

			}

		}

		else if (ball.x - ball.radius <= LeftPaddle.x + LeftPaddle.w)

		{

			if (ball.y - ball.radius <= LeftPaddle.y + LeftPaddle.h && ball.y + ball.radius >= LeftPaddle.y)

			{

				if (move == 1)

				{

					int lim1 = LeftPaddle.y + LeftPaddle.h / 3, lim2 = LeftPaddle.y + (2 * LeftPaddle.h / 3);

					if (ball.y <= lim1)

					{

						move = 4;

					}

					else if (ball.y >= lim2)

					{

						move = 3;

					}

					else

					{

						move = 2;

					}

				}

				else if (move == 5)

				{
					move = 3;
				}

				else if (move == 6)

				{
					move = 4;
				}

			}

			else if (ball.x - ball.radius + 20 < LeftPaddle.x + LeftPaddle.w)

			{

				rightPlayerScore++;

				move = 1;

				ball.x = winwidth / 2;

				ball.y = (Roof + winheight) / 2;

			}

		}

		if (ball.y - ball.radius <= Roof)

		{

			if (move == 4)

			{
				move = 3;
			}

			else if (move == 6)

			{
				move = 5;
			}

		}

		else if (ball.y + ball.radius >= winheight - 5)

		{

			if (move == 3)

			{
				move = 4;
			}

			else if (move == 5)

			{
				move = 6;
			}

		}

		if (move == 1)

		{
			ball.x -= speed;
		}

		else if (move == 2)

		{
			ball.x += speed;
		}

		else if (move == 3)

		{

			ball.x += speed;

			ball.y += speed;

		}

		else if (move == 4)

		{

			ball.x += speed;

			ball.y -= speed;

		}

		else if (move == 5)

		{

			ball.x -= speed;

			ball.y += speed;

		}

		else if (move == 6)

		{

			ball.x -= speed;

			ball.y -= speed;

		}

		SDL_Delay(1);

	}

	return NULL;

}



int main()

{

	pid_t pid = fork();

	if (pid == 0)

	{
		execlp("clear", "clear", NULL);
	}
	else
	{
		wait(NULL);

		cout << "\n\n \t\t\tWelcome to ZAYN'S Pong\n";







		cout << "\n\nCONTROLS: ";

		cout << "\n\nPlayer 1 : 'W' for up & 'S' for 'down'";

		cout << "\nPlayer 2 : 'Up Arrow' for up & 'Down Arrow' for 'down'";

		cout << "\nPress Any key to Start and esc to Quit!";

		cout << " \nGame will end when one of the player score 10 points\n\n";

		char n;

		cin.get(n);







		SDL_Init(SDL_INIT_VIDEO);

		TTF_Init();

		SDL_DisplayMode curDisplayMode;

		SDL_GetCurrentDisplayMode(0, &curDisplayMode);

		winheight = curDisplayMode.h;

		winwidth = curDisplayMode.w;

		SDL_Window* window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winwidth, winheight, SDL_WINDOW_FULLSCREEN_DESKTOP);

		SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		ball.x = winwidth / 2;

		ball.y = (Roof + winheight) / 2;

		RigthPaddle.x = winwidth - RigthPaddle.w - 5;

		RigthPaddle.y = (Roof + winheight) / 2 - RigthPaddle.h / 2;

		LeftPaddle.x = 5;

		LeftPaddle.y = (Roof + winheight) / 2 - LeftPaddle.h / 2;


		TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSerifBoldItalic.ttf", 130);

		if (!font)

			exit(0);





		pthread_t batID, ballID;

		pthread_create(&batID, NULL, &ControLeftPaddles, NULL);

		pthread_create(&ballID, NULL, &pongMove, NULL);



		while (rightPlayerScore < 10 && LeftPlayerScore < 10 && !Quit)

		{

			DrawIt(rend, font);

		}

		Quit = true;

		DrawIt(rend, font);

		SDL_Delay(2000);

		TTF_CloseFont(font);

		SDL_DestroyWindow(window);
		cout << "\n\t\t\t\tGAME OVER\n";
		SDL_Quit();

		pthread_join(batID, NULL);

		pthread_join(ballID, NULL);




	}
	return 0;

}


