#pragma once
#include <SDL_mixer.h>
#include <exception>
#include <string>
class Sound
{
private:
	Mix_Music* backgroundMusic = nullptr;
	Mix_Chunk* clickSound = nullptr;
	Mix_Chunk* optionClickSound = nullptr;
	Mix_Chunk* duckSound = nullptr;
	Mix_Chunk* errorSound = nullptr;
	Mix_Chunk* victorySound = nullptr;
public:
	Sound();
	~Sound();
	//Methodes
	void playBackgroundMusic();
	void playClickSound();
	void playDuckSound();
	void playOptionClickSound();
	void playErrorSound();
	void playVictorySound();
	//Exception
	class SOUND_EXCEPTION : public std::exception {
	private:
		std::string msg;
	public:
		SOUND_EXCEPTION(std::string msg) : msg(msg) {}
		const char* what() {
			return msg.c_str();
		}
	};
};