#include "Animacion.h"
#include <iostream>

using std::string;
using std::cout;

Animacion::Animacion(string pathImagen, int cantFotogramas, int fps, string id, SDL_Renderer* pRenderer):
	cantidadFotogramas(cantFotogramas), fps(fps), id(id) {
    SDL_Surface* pTempSurface = IMG_Load(pathImagen.c_str());
    cout << pathImagen;
	if (!pTempSurface)
        cout<<"errorTextura";
		return;//agregar error

	textura = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (!textura)
		cout << "ERROR";//agregar error

}

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
	SDL_DestroyTexture(textura);
}

string Animacion::getId(){
    return id;
}
