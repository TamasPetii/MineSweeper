#include "Text.h"

Text::Text(SDL_Renderer*& render) {
	TTF_Init();

	this->render = render;

	this->font = TTF_OpenFont("times.ttf", 35);
	if (font == nullptr) throw TEXT_EXCEPTION("Couldn't find/init open ttf font.");

	font2 = TTF_OpenFont("times.ttf", 25);
	if (font2 == nullptr) throw TEXT_EXCEPTION("Couldn't find/init open ttf font.");
}

Text::~Text() {
	TTF_CloseFont(font);
	TTF_CloseFont(font2);
	TTF_Quit();
}

void Text::Clear_Texture_Surface() {
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Text::Get_Text_Large(std::string str, SDL_Color color) {
	surface = TTF_RenderText_Solid(font, str.c_str(), color);
	if (surface == nullptr) throw TEXT_EXCEPTION("Couldn't create Surface!");

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (texture == nullptr) throw TEXT_EXCEPTION("Couldn't create TextTexture!");
}

void Text::Get_Text_Medium(std::string str, SDL_Color color) {
	surface = TTF_RenderText_Solid(font2, str.c_str(), color);
	if (surface == nullptr) throw TEXT_EXCEPTION("Couldn't create Surface!");

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (texture == nullptr) throw TEXT_EXCEPTION("Couldn't create TextTexture!");
}

void Text::Copy_Text(int x, int y) {
	to = { x, y, surface->w, surface->h };
	SDL_RenderCopy(render, texture, NULL, &to);
}

void Text::Render_Text_Large(std::string str, SDL_Color color, int x, int y) {
	Get_Text_Large(str, color);
	Copy_Text(x, y);
	Clear_Texture_Surface();
}

void Text::Render_Text_Medium(std::string str, SDL_Color color, int x, int y) {
	Get_Text_Medium(str, color);
	Copy_Text(x, y);
	Clear_Texture_Surface();
}