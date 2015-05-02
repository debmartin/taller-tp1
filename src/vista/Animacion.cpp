#include "Animacion.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <iostream>

#include "../json/ColorAlternativoDef.h"
#include "../utils/Logger.h"
#include "Desplazar.h"
#include "Renderizador.h"

using std::string;
using std::cout;

Animacion::Animacion(string pathImg, int cantFotogramas, int fpsIn, string idIn, SDL_Renderer* pRenderer)
{
	pathImagen = pathImg;
	cantidadFotogramas = cantFotogramas;
	fps = fpsIn;
	id = idIn;

    SDL_Surface* pTempSurface = IMG_Load(pathImagen.c_str());
    if (!pTempSurface) {
		Logger::getInstance()->error("No se pudo cargar la imagen "+pathImagen);
		return;
	}

	textura = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (!textura)
		Logger::getInstance()->error("No se pudo crear la textura SDL para "+pathImagen);

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

void Animacion::cambiarColor(ColorAlternativoDef* color)
{
	SDL_Surface* pTempSurface = IMG_Load(pathImagen.c_str());
	Desplazar::H(pTempSurface, color->getHinicial(), color->getHfinal(), color->getDesplazamiento());
	textura = SDL_CreateTextureFromSurface(Renderizador::Instance()->getRenderer(), pTempSurface);
	//¿no falta liberar la surface?
	//SDL_FreeSurface(pTempSurface);
}
