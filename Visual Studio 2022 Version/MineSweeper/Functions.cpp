#include "Functions.h"

void thread(Game* game) {
	while (!game->quit) {
		while (!game->stopThread) {
			game->DecreaseTime();
			//game->Print();
			Sleep(1000);
			if (!game->option) {
				game->Render_Bar();
			}
		}
		Sleep(10);
	}
}

bool range(int from, int n, int to) {
	return n >= from && n < to;
}

bool rangeXY(int fromx, int x, int tox, int fromy, int y, int toy) {
	return range(fromx, x, tox) && range(fromy, y, toy);
}

void Change_MapSize(Game*& game, Sound*& sound, int size, int sizeOption) {
	sound->playOptionClickSound();
	game->Set_Size(size);
	game->Set_MapSize();
	game->Set_SizeOption(sizeOption);
	game->Render_OptionBar();
	game->Render_Map();
}

void Change_BombsNumber(Game*& game, Sound*& sound, int bombs, int bombsOption) {
	sound->playOptionClickSound();
	game->Set_Bombs(bombs);
	game->Set_Flag(bombs);
	game->Set_BombsOption(bombsOption);
	game->Render_OptionBar();
}

void Change_Timer(Game*& game, Sound*& sound, int time, int timeOption) {
	sound->playOptionClickSound();
	game->Set_Time(time);
	game->Set_RealTime(time);
	game->Set_TimeOption(timeOption);
	game->Render_OptionBar();
}

void Change_Music(Game*& game, Sound*& sound) {
	sound->playOptionClickSound();
	if (game->Get_Music()) {
		Mix_HaltMusic();
		game->Set_Music(false);
		game->Render_Bar();
	}
	else {
		sound->playBackgroundMusic();
		game->Set_Music(true);
		game->Render_Bar();
	}
}

void Change_Bar(Game*& game, Sound*& sound) {
	sound->playOptionClickSound();
	if (game->option) {
		game->option = false;
		game->Render_Bar();
	}
	else {
		game->option = true;
		game->Render_OptionBar();
	}
}

void Click_Start(Game*& game, Sound*& sound) {
	if (game->TooMuchBombs(game->Get_Bombs())) {
		sound->playErrorSound();
	}
	else {
		sound->playOptionClickSound();
		if (!game->load) game->SetGame();
		game->Set_StartOption(2);
		game->Render_Bar();
		game->Render_Map();
		game->stopThread = false;
		game->start = true;
		game->end = false;
		game->load = false;
	}
}

void Click_Reset(Game*& game, Sound*& sound) {
	sound->playOptionClickSound();
	game->Set_StartOption(1);
	game->ResetMap();
	game->Render_Bar();
	game->Render_Map();
	game->stopThread = true;
	game->start = false;
	game->end = true;
}

void Click_Save(Game*& game, Sound*& sound) {
	if (game->start && game->SaveToFile()) {
		sound->playOptionClickSound();
	}
	else {
		sound->playErrorSound();
	}
}

void Click_Load(Game*& game, Sound*& sound) {
	if (game->LoadFile()) {
		sound->playOptionClickSound();
		game->Set_StartOption(1);
		game->Render_Bar();
		game->Render_Map();
		game->stopThread = true;
		game->start = false;
		game->end = true;
		game->load = true;
	}
	else {
		sound->playErrorSound();
	}
}

void Click_Map(Game*& game, Sound*& sound, int x, int y) {
	if (game->Click(x, y)) {
		sound->playDuckSound();
		game->end = true;
		game->stopThread = true;
	}
	else {
		sound->playClickSound();
	}
	game->Render_Map();
	game->Render_Bar();
}

void Click_Map_Right(Game*& game, Sound*& sound, int x, int y) {
	game->ClickRight(x, y) ? sound->playClickSound() : sound->playErrorSound();
	game->Render_Bar();
	game->Render_Map();
}

void Victory(Game*& game, Sound*& sound) {
	sound->playVictorySound();
	game->Victory_Map();
	game->Render_Map();
	game->end = true;
	game->stopThread = true;
}