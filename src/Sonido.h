#ifndef __SONIDO_H__
#define __SONIDO_H__

#include <string>

struct Mix_Chunk;

using namespace std;

#define DIR_SONIDOS "RECURSOS/SONIDOS/"

class Sonido{
private:
	Mix_Chunk* mix_Chunk;
	int canal;
	int canalEnReproduccion;
	int canalEnPausa;

public: 
	Sonido(string nombre_archivo, int volumen, int canal);
	void reproducir();
	void pausar();
	void reanudar();
	void detener();
	void detenerGradualmente(int milisegundos);
	~Sonido();
};
#endif
