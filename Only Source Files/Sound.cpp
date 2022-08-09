#include "Sound.h"

Sound::Sound() {
	Mix_Init(0);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	backgroundMusic = Mix_LoadMUS("./sounds/BG.wav"); if (!backgroundMusic) throw SOUND_EXCEPTION("Couldn't load BG.wav");
	clickSound = Mix_LoadWAV("./sounds/Click.wav"); if (!clickSound) throw SOUND_EXCEPTION("Couldn't load Click.wav");
	optionClickSound = Mix_LoadWAV("./sounds/OptionClick.wav"); if (!clickSound) throw SOUND_EXCEPTION("Couldn't load OptonClick.wav");
	duckSound = Mix_LoadWAV("./sounds/Duck.wav"); if (!duckSound) throw SOUND_EXCEPTION("Couldn't load Duck.wav");
	errorSound = Mix_LoadWAV("./sounds/Error.wav"); if (!duckSound) throw SOUND_EXCEPTION("Couldn't load Error.wav");
	victorySound = Mix_LoadWAV("./sounds/Victory.wav"); if (!victorySound) throw SOUND_EXCEPTION("Couldn't load Victory.wav");
}

Sound::~Sound() {
	Mix_FreeMusic(backgroundMusic);
	Mix_FreeChunk(clickSound);
	Mix_FreeChunk(optionClickSound);
	Mix_FreeChunk(duckSound);
	Mix_FreeChunk(errorSound);
	Mix_FreeChunk(victorySound);
	Mix_Quit();
}

void Sound::playBackgroundMusic() {
	Mix_HaltMusic();
	Mix_PlayMusic(backgroundMusic, -1);
	Mix_VolumeMusic(5);
}

void Sound::playClickSound() {
	Mix_HaltChannel(-1);
	Mix_PlayChannel(-1, clickSound, 0);
	Mix_VolumeChunk(clickSound, 5);
}

void Sound::playOptionClickSound() {
	Mix_HaltChannel(-1);
	Mix_PlayChannel(-1, optionClickSound, 0);
	Mix_VolumeChunk(optionClickSound, 5);
}

void Sound::playDuckSound() {
	Mix_HaltChannel(-1);
	Mix_PlayChannel(-1, duckSound, 0);
	Mix_VolumeChunk(duckSound, 5);
}

void Sound::playErrorSound() {
	Mix_HaltChannel(-1);
	Mix_PlayChannel(-1, errorSound, 0);
	Mix_VolumeChunk(errorSound, 5);
}

void Sound::playVictorySound() {
	Mix_HaltChannel(-1);
	//Mix_HaltMusic();
	Mix_PlayChannel(-1, victorySound, 0);
	Mix_VolumeChunk(victorySound, 5);
}