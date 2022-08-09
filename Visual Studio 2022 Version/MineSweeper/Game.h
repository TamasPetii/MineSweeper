#pragma once

#include "Text.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

#define WIDTH 600
#define HEIGHT 700

class Game
{
private:
    //SDL data members
    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;
    SDL_Texture* images = nullptr;
    SDL_Rect to;
    SDL_Rect from;
    SDL_Color ORANGE = { 255,140,0, 255 };
    SDL_Color WHITE = { 255,255,255, 255 };
    SDL_Color BLACK = { 255,255,255, 255 };
    SDL_Color RED = { 255,0,0, 255 };
    SDL_Color GREY = { 152,152,152, 255 };
    //Text
    Text* text = nullptr;
    //Vectors / Maps
    std::vector<int> map;
    std::vector<int> revealed_map;
    std::vector<int> bombs_pos;
    std::map<int, SDL_Rect> mapTexture;
    //Data members
    int bombs = 40;
    int bombsOption = 2;
    int size = 25;
    int sizeOption = 3;
    int time = 600;
    int realtime = 600;
    int timeOption = 2;
    int startOption = 1;
    int flag = 60;
    bool music = true;
    int remained = size * size - bombs;
    //Methodes
    void FillUpWithBombs();
    bool AlreadyUsed(int r);
    int NeighbourBombs(int a);
    void RevealOthers(int a);
    void DetectBombs();
public:
    //Constructor - Destructor
    Game();
    ~Game();
    //Public data members
    bool stopThread = true;
    bool option = false;
    bool start = false;
    bool end = true;
    bool load = false;
    bool quit = false;
    //Methodes
    void SetGame();
    bool TooMuchBombs(int bomb) { return size * size * 1.0 / bomb < 2; }
    void DecreaseTime() { time--; }
    void ResetMap();
    void Print();
    void Victory_Map();
    //File management
    bool LoadFile();
    bool SaveToFile();
    //Click Events
    bool Click(int x, int y);
    bool ClickRight(int x, int y);
    //Rendering
    void Render_OptionBar();
    void Render_Bar();
    void Render_Map();
    //Getter
    int Get_Bombs();
    int Get_BombsOption();
    int Get_Size();
    int Get_SizeOption();
    int Get_Time();
    int Get_RealTime();
    int Get_TimeOption();
    int Get_StartOption();
    int Get_Flag();
    bool Get_Music();
    int Get_Remained();
    //Setter
    void Set_Bombs(int bombs);
    void Set_BombsOption(int bombsOption);
    void Set_Size(int size);
    void Set_SizeOption(int sizeOption);
    void Set_Time(int time);
    void Set_RealTime(int RealTime);
    void Set_TimeOption(int timeOption);
    void Set_StartOption(int startOption);
    void Set_Flag(int flag);
    void Set_MapSize();
    void Set_Map();
    void Set_Music(bool music);
    //Exception
    class GAME_EXCEPTION : public std::exception {
    private:
        std::string msg;
    public:
        GAME_EXCEPTION(std::string msg) : msg(msg) {}
        const char* what() {
            return msg.c_str();
        }
    };
};

