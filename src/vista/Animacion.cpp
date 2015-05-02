#include "Animacion.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <iostream>

#include "Desplazar.h"

using std::string;
using std::cout;

Animacion::Animacion(string pathImagen, int cantFotogramas, int fpsIn, string idIn, SDL_Renderer* pRenderer):
	cantidadFotogramas(cantFotogramas), fps(fpsIn), id(idIn) {
    SDL_Surface* pTempSurface = IMG_Load(pathImagen.c_str());
	if (!pTempSurface) {
		return;//agregar error
	}
	textura = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (!textura)
		cout << "ERROR";//agregar error

}

Animacion::Animacion(
        		std::string pathImagen,
				int cantFotogramas,
				int fpsIn,
				std::string idIn,
				SDL_Renderer* pRenderer,
				Uint16 Hinicial, Uint16 Hfinal, Uint16 desplazamiento):
					cantidadFotogramas(cantFotogramas),
					fps(fpsIn),
					id(idIn)
{
    SDL_Surface* pTempSurface = IMG_Load(pathImagen.c_str());
	if (!pTempSurface) {
		return;//agregar error
	}

	Desplazar::H(pTempSurface, Hinicial, Hfinal, desplazamiento);

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

void Animacion::cambiarColor(ColorAlternativoDef* colorAlternativoDef) {
	// TODO aplicarle este color a la textura;
}
