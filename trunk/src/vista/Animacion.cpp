#include "Animacion.h"

Animacion::Animacion(SDL_Texture* t, int cantidadFotogramas, int fps):
	textura(t), cantidadFotogramas(cantidadFotogramas), fps(fps) {}

SDL_Texture* Animacion::getTextura() {
	return this->textura;
}

int Animacion::getCantidadFotogramas() {
	return this->cantidadFotogramas;
}

int Animacion::getFps() {
	return this->fps;
}

Animacion::~Animacion() {
	// TODO Auto-generated destructor stub
}
