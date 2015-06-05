#ifndef __SONIDO_H__
#define __SONIDO_H__

#include <string>

struct Mix_Chunk;

using namespace std;

class Sonido{

private:
	char* idSonido;
	Mix_Chunk* sonido;  //basicamente un chunk es un sonido
	char* path;
	int volumen;
	/*
	 * canal por el que se reproduce el sonido, importante, sino no se va a poder reproducir sinodos simultanos.
	 * tenia otro comportamiento SDL_mixer, entonces me facilite las cosas.
	 */
	int canal;
	int canalEnReproduccion;
	int canalEnPausa;

public: 
	Sonido(char* idSonido, char* path, int volumen, int canal);
	Sonido(const string& idSonido, const string& path, int volumen, int canal);
	//cantRepeticiones: cantidad de veces que se repetira el sonido.
	//-1 = infinito
	void reproducir(int cantRepeticiones);
	void pausar();
	void reanudar();
	void detenerReproduccionSeco();  
	void detenerReproduccionLentamente(); 
	char* getIdSonido();
	Mix_Chunk* getSonido(); //para test
	char* getPath();
	int getVolumen();
	int getCanal();
	int getCanalEnReproduccion(); 
	int getCanalEnPausa(); 
	void imrprimirDatos(); //para test

	~Sonido();

private: 
	Mix_Chunk* cargarSonido(char* path);
	void setVolumen(int volumen);//volumen: entre 0 y 128.
	void setCanal(int nuevoCanal);
	void setCanalEnReproduccion(int newStatus);
	void setCanalEnPausa(int newStatus);
};
#endif
