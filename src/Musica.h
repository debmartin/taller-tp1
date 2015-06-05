#ifndef __MUSICA_H__
#define __MUSICA_H__

#include <SDL2/SDL_mixer.h>
#include <string>


using namespace std;

#define DIR_SONIDOS "RECURSOS/SONIDOS/"


class Musica{
private:
	Mix_Music* mix_Music;
public:
	//rango del volumen va desde 0 hasta 128
	Musica(string nombre_archivo, int volumen);
	void reproducir();
	void detener();
	void detenerGradualmente(int milisegundos);
	~Musica();
};
#endif
