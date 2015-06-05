#ifndef __MUSICA_H__
#define __MUSICA_H__

#include <string.h>
#include <SDL2/SDL_mixer.h>
#include <sstream>
#include <string>

#include "utils/Logger.h"

using namespace std;

//para crear instancias de esta clase de acuerdo a la pantalla en que estemos parados, por ejempla la pantalla de juego
class Musica{
private:
	Mix_Music* musicaDeFondo;
	char* path;
	int volumen; //rango valido: 0-128

private: 
		void openAudio(){ 
			if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
				std::stringstream ss;
				ss << "error en Mix_OpenAudio ";
				Logger::getInstance()->error(ss.str());
			}
		}

		void cargarMusica(char* path){
			this->musicaDeFondo = Mix_LoadMUS(path);
			if(!this->musicaDeFondo){
				std::stringstream ss;
				ss << "No se puedo cargar la musica de fondo de nombre " << path << "ERROR: " <<  Mix_GetError();
				Logger::getInstance()->error(ss.str());
			}
		}

public: 

		Musica(const string& path, int volumen){
			this->openAudio();
			char * tmp = strdup(path.c_str());
			this->path = tmp;
			this->cargarMusica(tmp);	
			this->setVolumen(volumen);
		}

		Musica(Mix_Music* musica, int volumen){
			this->openAudio();
			this->path = path;
			this->musicaDeFondo = musica;
			this->setVolumen(volumen);
		}


		Mix_Music* getMusicaDeFondo(){
			return this->musicaDeFondo;
		}

		void setMusicaDeFondo(Mix_Music* otraMusicaDeFondo){
			this->musicaDeFondo = otraMusicaDeFondo;
		}

		char* getPath(){
			return this->path;
		}

		void play(){
			if (this->musicaDeFondo){
				if (Mix_PlayMusic(this->musicaDeFondo, -1) == -1){
					std::stringstream ss;
					ss << "error en Mix_PlayMusic de musica de fondo de nombre " <<this->path;
					Logger::getInstance()->error(ss.str());
				}
			}
		}

		void stop(){
			if (this->musicaDeFondo) {
				Mix_HaltMusic();
				Mix_FreeMusic(this->musicaDeFondo);
			}
		}
		void stopGradualmente(int milisegundos){
			if (this->musicaDeFondo) {
				Mix_FadeOutMusic(milisegundos);
				Mix_FreeMusic(this->musicaDeFondo);
			}
		
		}

		void setVolumen(int volumen){  //es publico porque talvez lo necesite modifcar en algun momento
			this->volumen = volumen;
			Mix_VolumeMusic(volumen);
		}

		~Musica(){
			Mix_CloseAudio();
		}

};
#endif
