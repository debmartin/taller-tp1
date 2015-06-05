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

Musica::Musica(string nombre_archivo, int volumen){

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
		Logger::getInstance()->error("error en Mix_OpenAudio ");
	}

	string path(DIR_SONIDOS);
	path.append(nombre_archivo);

	this->mix_Music = Mix_LoadMUS(path.c_str());
	if(!this->mix_Music){
		std::stringstream ss;
		ss<<"No se cargo la musica: "<< path;
		Logger::getInstance()->error(ss.str());
	}

	Mix_VolumeMusic(volumen);
}

void Musica::reproducir(){
	if (this->mix_Music){
		if (Mix_PlayMusic(this->mix_Music, -1) == -1){
			Logger::getInstance()->error("error en Mix_PlayMusic de musica de fondo");
		}
	}
}

void Musica::detener(){
	if (this->mix_Music) {
		Mix_HaltMusic();
		Mix_FreeMusic(this->mix_Music);
	}
}
void Musica::detenerGradualmente(int milisegundos){
	if (this->mix_Music) {
		Mix_FadeOutMusic(milisegundos);
		Mix_FreeMusic(this->mix_Music);
	}

}

Musica::~Musica(){
	Mix_CloseAudio();
}
