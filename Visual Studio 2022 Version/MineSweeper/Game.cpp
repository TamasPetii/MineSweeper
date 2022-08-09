#include "Game.h"

//-----------------------------------------------Constructor-Destructor-----------------------------------------------//

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("MineSweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 4);
	if (!window) throw GAME_EXCEPTION("SDL couldn't create Window!");

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!render) throw GAME_EXCEPTION("SDL couldn't create Renderer!");

	images = IMG_LoadTexture(render, "./pictures/asd.png");
	if (!images) throw GAME_EXCEPTION("Couldn't load asd.png");

	text = new Text(render);

	mapTexture.insert(std::pair<int, SDL_Rect>(1, { 0, 25, 25, 25 }));
	mapTexture.insert(std::pair<int, SDL_Rect>(2, { 25, 25, 25, 25 }));
	mapTexture.insert(std::pair<int, SDL_Rect>(3, { 50, 25, 25, 25 }));
	mapTexture.insert(std::pair<int, SDL_Rect>(4, { 75, 25, 25, 25 }));
	mapTexture.insert(std::pair<int, SDL_Rect>(5, { 100, 25, 25, 25 }));
	mapTexture.insert(std::pair<int, SDL_Rect>(6, { 125, 25, 25, 25 }));
	mapTexture.insert(std::pair<int, SDL_Rect>(7, { 150, 25, 25, 25 }));
	mapTexture.insert(std::pair<int, SDL_Rect>(8, { 175, 25, 25, 25 }));
	mapTexture.insert(std::pair<int, SDL_Rect>(0, { 25, 0, 25, 25 }));
	mapTexture.insert(std::pair<int, SDL_Rect>(-1, { 75, 0, 25, 25 }));
	mapTexture.insert(std::pair<int, SDL_Rect>(-2, { 0, 0, 25, 25 }));
	mapTexture.insert(std::pair<int, SDL_Rect>(-3, { 50, 0, 25, 25 }));

	Set_MapSize();
}

Game::~Game() {
	SDL_DestroyTexture(images);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_Quit();

	delete text;

	map.~vector();
	revealed_map.~vector();
	bombs_pos.~vector();
	mapTexture.clear();
}
//--------------------------------------------Render-Text-Map--------------------------------------------//

//This function renders the option bar, including map size, bombs, time settings.
void Game::Render_OptionBar() {
	to = { 0,0,600,100 };
	SDL_SetRenderDrawColor(render, 75, 75, 75, 255);
	SDL_RenderFillRect(render, &to);

	from = { 0, 50, 600, 628 };
	to = { 540, 25, 50, 50 };
	SDL_RenderCopy(render, images, &from, &to);

	text->Render_Text_Medium("Size of Map", ORANGE, 12, 10);

	text->Render_Text_Medium("15", sizeOption == 1 ? RED : WHITE, 15, 40);

	text->Render_Text_Medium("20", sizeOption == 2 ? RED : WHITE, 57, 40);

	text->Render_Text_Medium("25", sizeOption == 3 ? RED : WHITE, 100, 40);

	text->Render_Text_Medium("30", sizeOption == 4 ? RED : WHITE, 15, 65);

	text->Render_Text_Medium("40", sizeOption == 5 ? RED : WHITE, 57, 65);

	text->Render_Text_Medium("50", sizeOption == 6 ? RED : WHITE, 100, 65);

	text->Render_Text_Medium("Number of Bombs", ORANGE, 182, 10);

	text->Render_Text_Medium("30", TooMuchBombs(30) ? GREY : bombsOption == 1 ? RED : WHITE, 185, 40);

	text->Render_Text_Medium("40", TooMuchBombs(40) ? GREY : bombsOption == 2 ? RED : WHITE, 235, 40);

	text->Render_Text_Medium("60", TooMuchBombs(60) ? GREY : bombsOption == 3 ? RED : WHITE, 280, 40);

	text->Render_Text_Medium("100", TooMuchBombs(100) ? GREY : bombsOption == 4 ? RED : WHITE, 325, 40);

	text->Render_Text_Medium("200", TooMuchBombs(200) ? GREY : bombsOption == 5 ? RED : WHITE, 185, 65);

	text->Render_Text_Medium("300", TooMuchBombs(300) ? GREY : bombsOption == 6 ? RED : WHITE, 235, 65);

	text->Render_Text_Medium("400", TooMuchBombs(400) ? GREY : bombsOption == 7 ? RED : WHITE, 280, 65);

	text->Render_Text_Medium("500", TooMuchBombs(500) ? GREY : bombsOption == 8 ? RED : WHITE, 325, 65);

	text->Render_Text_Medium("Timer (sec)", ORANGE, 395, 10);

	text->Render_Text_Medium("300", timeOption == 1 ? RED : WHITE, 400, 40);

	text->Render_Text_Medium("600", timeOption == 2 ? RED : WHITE, 450, 40);

	text->Render_Text_Medium("900", timeOption == 3 ? RED : WHITE, 400, 65);

	text->Render_Text_Medium("1200", timeOption == 4 ? RED : WHITE, 450, 65);

	SDL_RenderPresent(render);
}

//This function renders the top bar, including Start, Load, Save, Music, Timer, etc...
void Game::Render_Bar() {
	to = { 0,0,600,100 };
	SDL_SetRenderDrawColor(render, 75, 75, 75, 255);
	SDL_RenderFillRect(render, &to);

	from = { 0, 50, 600, 628 };
	to = { 540, 25, 50, 50 };
	SDL_RenderCopy(render, images, &from, &to);

	text->Render_Text_Large(startOption == 1 ? "START" : "RESET", ORANGE, 250, 30);

	text->Render_Text_Medium("LOAD", ORANGE, 265, 5);

	text->Render_Text_Medium("SAVE", ORANGE, 266, 65);

	text->Render_Text_Medium("Timer:", RED, 15, 10);

	text->Render_Text_Medium(std::to_string(time), WHITE, 90, 10);

	text->Render_Text_Medium("Flags:", RED, 18, 38);

	text->Render_Text_Medium(std::to_string(flag), WHITE, 90, 38);

	text->Render_Text_Medium("Remained:", RED, 18, 65);

	text->Render_Text_Medium(std::to_string(remained), WHITE, 135, 65);

	text->Render_Text_Medium("Music", ORANGE, 420, 10);

	music ? from = { 5, 667, 140, 100 } : from = { 215, 667, 123, 100 };
	music ? to = { 425, 50, 49, 35 } : to = { 425, 50, 43, 35 };
	SDL_RenderCopy(render, images, &from, &to);

	SDL_RenderPresent(render);
}

void Game::Render_Map() {
	int l = 600 / size;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			to = { j * l,100 + i * l,l,l };
			SDL_RenderCopy(render, images, &mapTexture[revealed_map[j + i * size]], &to);
		}
	}
	SDL_RenderPresent(render);
}

//--------------------------------------------Data-Setter-Getter--------------------------------------------//

void Game::Set_Bombs(int bombs) { this->bombs = bombs; }
void Game::Set_BombsOption(int bombsOption) { this->bombsOption = bombsOption; }
void Game::Set_Size(int size) { this->size = size; }
void Game::Set_SizeOption(int sizeOption) { this->sizeOption = sizeOption; }
void Game::Set_Time(int time) { this->time = time; }
void Game::Set_RealTime(int realtime) { this->realtime = realtime; }
void Game::Set_TimeOption(int timeOption) { this->timeOption = timeOption; }
void Game::Set_StartOption(int startOption) { this->startOption = startOption; }
void Game::Set_Flag(int flag) { this->flag = flag; }
void Game::Set_MapSize() { map.clear(); revealed_map.clear(); map.resize(size * size); revealed_map.resize(size * size, -2); }
void Game::Set_Music(bool music) { this->music = music; }

int Game::Get_Bombs() { return bombs; }
int Game::Get_BombsOption() { return bombsOption; }
int Game::Get_Size() { return size; }
int Game::Get_SizeOption() { return sizeOption; }
int Game::Get_Time() { return time; }
int Game::Get_RealTime() { return realtime; }
int Game::Get_TimeOption() { return timeOption; }
int Game::Get_StartOption() { return startOption; }
int Game::Get_Flag() { return flag; }
bool Game::Get_Music() { return music; }
int Game::Get_Remained() { return remained; }
//--------------------------------------------MineSweeper-Algorithms--------------------------------------------//

//This function detects the number of the neighbour bombs of a given map slot.
int Game::NeighbourBombs(int a) {
	int c = 0;
	int x = a % size;
	int y = a / size;
	if (x - 1 >= 0 && map[a - 1] == -1) c++;
	if (x + 1 < size && map[a + 1] == -1) c++;
	if (y - 1 >= 0 && map[a - size] == -1) c++;
	if (y - 1 >= 0 && x - 1 >= 0 && map[a - size - 1] == -1) c++;
	if (y - 1 >= 0 && x + 1 < size && map[a - size + 1] == -1) c++;
	if (y + 1 < size && map[a + size] == -1) c++;
	if (y + 1 < size && x - 1 >= 0 && map[a + size - 1] == -1) c++;
	if (y + 1 < size && x + 1 < size && map[a + size + 1] == -1) c++;
	return c;
}

//This function sets the map. Every map slot will have the number of neighbour bombs.
void Game::Set_Map() {
	for (unsigned int i = 0; i < map.size(); i++) {
		if (map[i] != -1) {
			map[i] = NeighbourBombs(i);
		}
	}
}

//This function fills up the map with a given quantity of bombs.
void Game::FillUpWithBombs() {
	if (bombs == 0) throw GAME_EXCEPTION("Bombs number is not yet set!");
	if (bombs >= size * size) throw GAME_EXCEPTION("Too much bombs!");

	int r = 0;
	for (int i = 0; i < bombs; i++) {
		do {
			r = rand() % map.size();
		} while (AlreadyUsed(r));
		bombs_pos.push_back(r);
		map[r] = -1;
	}
}

//This function detects that a given map position is occupied by bomb or not.
bool Game::AlreadyUsed(int r) {
	bool l = false;
	for (unsigned int i = 0; i < bombs_pos.size() && !l; i++) {
		l = l || (bombs_pos[i] == r);
	}
	return l;
}

//This function reveals all the bombs of the map (by clicking on a bomb spot)
void Game::DetectBombs() {
	for (unsigned int i = 0; i < map.size(); i++) {
		if (map[i] == -1) {
			revealed_map[i] = -1;
		}
	}
}

//This recursive function reveals the revealable map spots by clicking.
void Game::RevealOthers(int a) {
	int x = a % size;
	int y = a / size;
	if (x >= 0 && x < size && y >= 0 && y < size && map[a] != -1 && revealed_map[a] == -2) {
		remained--;
		revealed_map[a] = map[a];
		if (map[a] == 0) {
			if (x - 1 >= 0) RevealOthers(a - 1);
			if (x + 1 < size) RevealOthers(a + 1);
			if (y - 1 >= 0) RevealOthers(a - size);
			if (y - 1 >= 0 && x - 1 >= 0) RevealOthers(a - size - 1);
			if (y - 1 >= 0 && x + 1 < size) RevealOthers(a - size + 1);
			if (y + 1 < size) RevealOthers(a + size);
			if (y + 1 < size && x - 1 >= 0) RevealOthers(a + size - 1);
			if (y + 1 < size && x + 1 < size) RevealOthers(a + size + 1);
		}
	}
}

//--------------------------------------------Click-Events--------------------------------------------//

bool Game::Click(int x, int y) {
	int s = 600 / size;
	int k = x / s + ((y - 100) / s) * size;
	if (map[k] == -1 && revealed_map[k] != -3) {
		DetectBombs();
		return true;
	}
	else {
		if (revealed_map[k] == -2) {
			RevealOthers(k);
		}
	}
	return false;
}

bool Game::ClickRight(int x, int y) {
	int s = 600 / size;
	int k = x / s + ((y - 100) / s) * size;
	if (revealed_map[k] == -3) {
		revealed_map[k] = -2;
		flag++;
	}
	else if (revealed_map[k] == -2) {
		if (flag == 0) {
			return false;
		}
		revealed_map[k] = -3;
		flag--;
	}
	return true;
}

//--------------------------------------------File-Management--------------------------------------------//

/*
This function loads a saved minesweeper file.
File must be named as "Map.txt"
The function sets the class data members properly, and decrypts the encrypted map.
*/
bool Game::LoadFile() {
	std::ifstream f("Map.txt");
	if (f.fail()) {
		return false;
	}

	map.clear();
	revealed_map.clear();

	f >> size >> sizeOption >> bombs >> flag >> bombsOption >> time >> realtime >> timeOption >> startOption >> remained;

	std::string line;
	int x;

	std::getline(f, line, '\n');
	std::getline(f, line, '\n');
	std::stringstream ss(line);
	map.clear();
	int i = 0;
	while (ss >> x) {
		map.push_back(x - (bombsOption + 1) * (sizeOption + 1) * (++i));
	}

	std::getline(f, line, '\n');
	std::stringstream sss(line);
	revealed_map.clear();

	while (sss >> x) {
		revealed_map.push_back(x);
	}

	f.close();
	return true;
}

/*
This function creates a minesweeper file named as "Map.txt".
The function saves all the necessary data members, and map positions.
In order to the player would not be able to cheat with reading the file, the function encrypts the map.
*/
bool Game::SaveToFile() {
	std::ofstream f("Map.txt");
	if (f.fail()) {
		return false;
	}

	f << size << " " << sizeOption << " " << bombs << " " << flag << " " << bombsOption << " " << time << " " << realtime << " " << timeOption << " " << startOption << " " << remained << std::endl;

	for (unsigned int i = 0; i < map.size(); i++) {
		f << map[i] + (bombsOption + 1) * (sizeOption + 1) * (i + 1) << " ";
	}

	f << "\n";

	for (unsigned int i = 0; i < revealed_map.size(); i++) {
		f << revealed_map[i] << " ";
	}

	f.close();

	return true;
}



void Game::SetGame() {
	this->remained = size * size - bombs;
	this->FillUpWithBombs();
	this->Set_Map();
}


void Game::ResetMap() {
	Set_MapSize();
	bombs_pos.clear();
	time = realtime;
	flag = bombs;
	remained = size * size - bombs;
}

void Game::Print() {
	std::cout << "Size:\t\t" << size << std::endl;
	std::cout << "SizeOption:\t" << sizeOption << std::endl;
	std::cout << "Bombs:\t\t" << bombs << std::endl;
	std::cout << "Flags:\t\t" << flag << std::endl;
	std::cout << "BombsOption:\t" << bombsOption << std::endl;
	std::cout << "Time:\t\t" << time << std::endl;
	std::cout << "RealTime:\t" << realtime << std::endl;
	std::cout << "TimeOption:\t" << timeOption << std::endl;
	std::cout << "StartOption:\t" << startOption << std::endl;
	std::cout << "Remained:\t" << remained << std::endl;
	std::cout << "Map:\t\t" << map.size() << std::endl;
	std::cout << "RevealdMap:\t" << revealed_map.size() << std::endl;
	std::cout << "Used:\t\t" << bombs_pos.size() << std::endl;
	for (unsigned int i = 0; i < map.size(); i++) {
		if (i % size == 0) std::cout << std::endl;
		std::cout << (map[i] >= 0 ? (" " + std::to_string(map[i]) + " ") : (std::to_string(map[i]) + " "));
	}
	std::cout << std::endl << "----------------------------------------" << std::endl;
}

void Game::Victory_Map() {
	for (unsigned int i = 0; i < map.size(); i++) {
		if (map[i] == -1) {
			revealed_map[i] = -3;
		}
	}
}