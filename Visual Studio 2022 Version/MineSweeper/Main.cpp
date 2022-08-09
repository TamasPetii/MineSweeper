#define SDL_MAIN_HANDLED
#define _CRTDBG_MAP_ALLOC
#include "Functions.h"

int main() {
	SDL_SetMainReady();
	srand(time(NULL));

	Game* game;
	Sound* sound;

	try {
		game = new Game();
		sound = new Sound();

		std::thread th(thread, game);
		th.detach();

		sound->playBackgroundMusic();

		game->SetGame();
		game->Render_Bar();
		game->Render_Map();
		game->Print();

		int x;
		int y;
		SDL_Event event;
		while (!game->quit) {
			while (SDL_PollEvent(&event)) {
				switch (event.type)
				{
				case SDL_QUIT:
					game->quit = true;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						game->quit = true;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					x = event.button.x;
					y = event.button.y;
					if (event.button.button == SDL_BUTTON_LEFT) {
						if (y < 100) {
							//Option wheel							
							if (rangeXY(540, x, 590, 25, y, 75)) {
								Change_Bar(game, sound);
							}
							//SizeOfMap -> 15
							else if (game->option && !game->start && rangeXY(18, x, 39, 46, y, 63)) {
								Change_MapSize(game, sound, 15, 1);
							}
							//SizeOfMap -> 20
							else if (game->option && !game->start && rangeXY(58, x, 82, 46, y, 63)) {
								Change_MapSize(game, sound, 20, 2);
							}
							//SizeOfMap -> 25
							else if (game->option && !game->start && rangeXY(101, x, 124, 46, y, 63)) {
								Change_MapSize(game, sound, 25, 3);
							}
							//SizeOfMap -> 30
							else if (game->option && !game->start && rangeXY(16, x, 40, 71, y, 88)) {
								Change_MapSize(game, sound, 30, 4);
							}
							//SizeOfMap -> 40
							else if (game->option && !game->start && rangeXY(58, x, 81, 71, y, 88)) {
								Change_MapSize(game, sound, 40, 5);
							}
							//SizeOfMap -> 50
							else if (game->option && !game->start && rangeXY(100, x, 125, 71, y, 88)) {
								Change_MapSize(game, sound, 50, 6);
							}
							//NumberOfBombs -> 30
							else if (game->option && !game->start && rangeXY(185, x, 210, 46, y, 63) && !game->TooMuchBombs(30)) {
								Change_BombsNumber(game, sound, 30, 1);
							}
							//NumberOfBombs -> 40
							else if (game->option && !game->start && rangeXY(235, x, 260, 46, y, 63) && !game->TooMuchBombs(40)) {
								Change_BombsNumber(game, sound, 40, 2);
							}
							//NumberOfBombs -> 60
							else if (game->option && !game->start && rangeXY(281, x, 305, 46, y, 63) && !game->TooMuchBombs(60)) {
								Change_BombsNumber(game, sound, 60, 3);
							}
							//NumberOfBombs -> 100
							else if (game->option && !game->start && rangeXY(328, x, 363, 46, y, 63) && !game->TooMuchBombs(100)) {
								Change_BombsNumber(game, sound, 100, 4);
							}
							//NumberOfBombs -> 200
							else if (game->option && !game->start && rangeXY(186, x, 223, 71, y, 88) && !game->TooMuchBombs(200)) {
								Change_BombsNumber(game, sound, 200, 5);
							}
							//NumberOfBombs -> 300
							else if (game->option && !game->start && rangeXY(236, x, 272, 71, y, 88) && !game->TooMuchBombs(300)) {
								Change_BombsNumber(game, sound, 300, 6);
							}
							//NumberOfBombs -> 400
							else if (game->option && !game->start && rangeXY(280, x, 318, 71, y, 88) && !game->TooMuchBombs(400)) {
								Change_BombsNumber(game, sound, 400, 7);
							}
							//NumberOfBombs -> 500
							else if (game->option && !game->start && rangeXY(326, x, 362, 71, y, 88) && !game->TooMuchBombs(500)) {
								Change_BombsNumber(game, sound, 500, 8);
							}
							//Time -> 300
							else if (game->option && !game->start && rangeXY(401, x, 438, 46, y, 63)) {
								Change_Timer(game, sound, 300, 1);
							}
							//Time -> 600
							else if (game->option && !game->start && rangeXY(451, x, 488, 46, y, 63)) {
								Change_Timer(game, sound, 600, 2);
							}
							//Time -> 900
							else if (game->option && !game->start && rangeXY(401, x, 438, 71, y, 88)) {
								Change_Timer(game, sound, 900, 3);
							}
							//Time -> 1200
							else if (game->option && !game->start && rangeXY(453, x, 501, 71, y, 88)) {
								Change_Timer(game, sound, 1200, 4);
							}
							//Music
							else if (!game->option && rangeXY(425, x, 475, 50, y, 85)) {
								Change_Music(game, sound);
							}
							//Start
							else if (!game->start && !game->option && rangeXY(245, x, 355, 35, y, 65)) {
								Click_Start(game, sound);
							}
							//Reset
							else if (game->start && !game->option && game->Get_StartOption() == 2 && rangeXY(245, x, 355, 35, y, 65)) {
								Click_Reset(game, sound);
							}
							//Save game
							else if (!game->option && !game->end && rangeXY(268, x, 327, 72, y, 89)) {
								Click_Save(game, sound);
							}
							//Load game
							else if (!game->option && rangeXY(265, x, 333, 12, y, 29)) {
								Click_Load(game, sound);
							}
						}
						//Click on the map
						else {
							if (game->start && !game->end) {
								Click_Map(game, sound, x, y);
							}
						}
					}
					else if (event.button.button == SDL_BUTTON_RIGHT) {
						if (!game->end && game->start && y >= 100) {
							Click_Map_Right(game, sound, x, y);
						}
					}
					break;
				}
			}
			if (game->Get_Remained() == 0 && !game->end) {
				Victory(game, sound);
			}
			Sleep(10);
		}
	}
	catch (Game::GAME_EXCEPTION& exception) {
		std::cout << exception.what() << std::endl;
		exit(1);
	}
	catch (Text::TEXT_EXCEPTION& exception) {
		std::cout << exception.what() << std::endl;
		exit(1);
	}
	catch (Sound::SOUND_EXCEPTION& exception) {
		std::cout << exception.what() << std::endl;
		exit(1);
	}
	delete game;
	delete sound;
	_CrtDumpMemoryLeaks();

	return 0;
}