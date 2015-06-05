#include "Sonido.h"

#include <SDL2/SDL_mixer.h>
#include <sstream>

#include "utils/Logger.h"

Sonido::Sonido(string nombre_archivo, int volumen, int canal)
{
	string path(DIR_SONIDOS);
	path.append(nombre_archivo);
	this->mix_Chunk = Mix_LoadWAV(path.c_str());
	if ( this->mix_Chunk )
	{
		Mix_VolumeChunk(this->mix_Chunk, volumen);
	} else {
		std::stringstream ss;
		ss<<"No se cargo el sonido: "<< path;
		Logger::getInstance()->error(ss.str());
	}

	this->canal = canal;
	this->canalEnReproduccion = 0;
	this->canalEnPausa = 0;
}

void Sonido::reproducir(){
	if(this->mix_Chunk){
		int cantRepeticiones = 0;
		Mix_PlayChannel(this->canal, this->mix_Chunk, cantRepeticiones);
		this->canalEnReproduccion = 1;
		this->canalEnPausa = 0;
	}
}

void Sonido::pausar(){
	if(this->mix_Chunk && this->canalEnReproduccion == 1 && this->canalEnPausa == 0){
		Mix_Pause(this->canal);
		this->canalEnReproduccion = 0;
		this->canalEnPausa = 1;
	}
}

void Sonido::reanudar(){
	if (this->mix_Chunk && this->canalEnReproduccion == 0 && this->canalEnPausa == 1){
		Mix_Resume(this->canal);
		this->canalEnReproduccion = 1;
		this->canalEnPausa = 0;
	}
}

void Sonido::detener(){
	if(this->mix_Chunk && this->canalEnReproduccion == 1){
		this->canal = Mix_HaltChannel(this->canal);
		this->canalEnReproduccion = 0;
		this->canalEnPausa = 0;
	}
}

void Sonido::detenerGradualmente(int milisegundos){
	if(this->mix_Chunk && this->canalEnReproduccion == 1){
		this->canal = Mix_FadeOutChannel(this->canal, milisegundos);
		this->canalEnReproduccion = 0;
		this->canalEnPausa = 0;
	}
}

Sonido::~Sonido(){
	if(this->mix_Chunk)
		Mix_FreeChunk(this->mix_Chunk);
}

