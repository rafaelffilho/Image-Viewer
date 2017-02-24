#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <array>

using namespace std;

int main(int argc, char **argv){

	SDL_Init(SDL_INIT_EVERYTHING);

	if(argc > 1){
		if(strstr(argv[1], ".jpg"))
			IMG_Init(IMG_INIT_JPG);
		if(strstr(argv[1], ".png"))
			IMG_Init(IMG_INIT_PNG);
	}

	SDL_Window *w;
	SDL_Renderer *r;

	SDL_CreateWindowAndRenderer(500, 800, SDL_WINDOW_RESIZABLE, &w, &r);

	const char *buffer = argv[1];

	SDL_Texture *t = IMG_LoadTexture(r, buffer);

	SDL_Event e;
	bool running = true;

	SDL_SetRenderDrawColor(r, 0x00, 0xff, 0x00, 0xff);

	FILE *pwd = popen("pwd", "r");
	char buf[256];
	fgets(buf, 256, pwd);
	char lscmd[512];
	strcpy(lscmd, "ls ");
	strcat(lscmd, buf);
	FILE *ls = popen(lscmd, "r");
	vector<string> Files;
	vector<string> Images;
	char j[256];
	while ((fgets(j, 256, ls)) != NULL) {
		Files.push_back(j);
	}

	cout << buf << endl;

	for (unsigned int i = 0; i < Files.size(); i++) {
		cout << Files[i] << " ";
		char Bug[256];
		strcpy(Bug, Files[i].c_str());
		if(strstr(Bug, ".jpg"))
			Images.push_back(Files[i]);
		if(strstr(Bug, ".png"))
			Images.push_back(Files[i]);
	}
	for (unsigned int i = 0; i < Images.size(); i++) {
		cout << Images[i] << " ";
	}

	while (running) {
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT){
			running = false;
			continue;
		}
		SDL_RenderClear(r);
		SDL_RenderCopy(r, t, NULL, NULL);
		SDL_RenderPresent(r);
	}


	IMG_Quit();
	SDL_Quit();
	return 0;
}
