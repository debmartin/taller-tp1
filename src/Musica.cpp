/*
 * Musica.cpp
 *
 *  Created on: 5/6/2015
 *      Author: ariel
 */

#include "Musica.h"

#include <SDL2/SDL_mixer.h>
#include <sstream>
#include <string>

#include "utils/Logger.h"

Musica::Musica(string path, int volumen){

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
		Logger::getInstance()->error("error en Mix_OpenAudio ");
	}

	this->musicaDeFondo = Mix_LoadMUS(path.c_str());
	if(!this->musicaDeFondo){
		std::stringstream ss;
		ss << "No se puedo cargar la musica de fondo de nombre. " <<  Mix_GetError();
		Logger::getInstance()->error(ss.str());
	}

	Mix_VolumeMusic(volumen);
}

void Musica::play(){
	if (this->musicaDeFondo){
		if (Mix_PlayMusic(this->musicaDeFondo, -1) == -1){
			Logger::getInstance()->error("error en Mix_PlayMusic de musica de fondo");
		}
	}
}

void Musica::stop(){
	if (this->musicaDeFondo) {
		Mix_HaltMusic();
		Mix_FreeMusic(this->musicaDeFondo);
	}
}
void Musica::stopGradualmente(int milisegundos){
	if (this->musicaDeFondo) {
		Mix_FadeOutMusic(milisegundos);
		Mix_FreeMusic(this->musicaDeFondo);
	}

}

Musica::~Musica(){
	Mix_CloseAudio();
}
