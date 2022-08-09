#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <exception>
#include <string>
class Text
{
private:
    //SDL/TTF data members
    SDL_Renderer* render = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = nullptr;
    TTF_Font* font = nullptr;
    TTF_Font* font2 = nullptr;
    SDL_Rect to;
public:
    //Constructor
    Text(SDL_Renderer*& render);
    ~Text();
    //Methodes
    void Get_Text_Large(std::string str, SDL_Color color);
    void Get_Text_Medium(std::string str, SDL_Color color);
    void Clear_Texture_Surface();
    void Copy_Text(int x, int y);
    void Render_Text_Large(std::string str, SDL_Color color, int x, int y);
    void Render_Text_Medium(std::string str, SDL_Color color, int x, int y);
    //Exception
    class TEXT_EXCEPTION : public std::exception {
    private:
        std::string msg;
    public:
        TEXT_EXCEPTION(std::string msg) : msg(msg) {}
        const char* what() {
            return msg.c_str();
        }
    };
};

