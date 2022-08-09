#pragma once

#include "Game.h"
#include "Sound.h"

#include <Windows.h>
#include <Time.h>
#include <thread>

void thread(Game* game);
bool range(int from, int n, int to);
bool rangeXY(int fromx, int x, int tox, int fromy, int y, int toy);
void Change_MapSize(Game*& game, Sound*& sound, int size, int sizeOption);
void Change_BombsNumber(Game*& game, Sound*& sound, int bombs, int bombsOption);
void Change_Timer(Game*& game, Sound*& sound, int time, int timeOption);
void Change_Music(Game*& game, Sound*& sound);
void Change_Bar(Game*& game, Sound*& sound);
void Click_Start(Game*& game, Sound*& sound);
void Click_Reset(Game*& game, Sound*& sound);
void Click_Save(Game*& game, Sound*& sound);
void Click_Load(Game*& game, Sound*& sound);
void Click_Map(Game*& game, Sound*& sound, int x, int y);
void Click_Map_Right(Game*& game, Sound*& sound, int x, int y);
void Victory(Game*& game, Sound*& sound);
