#include "Animacion.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <sstream>

#include "../json/ColorAlternativoDef.h"
#include "../utils/Logger.h"
#include "Desplazar.h"
#include "Renderizador.h"

using std::string;
using std::cout;

Animacion::Animacion() {
}

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
	SDL_Surface* superficie_tempotal = IMG_Load(pathImagen.c_str());
    if ( superficie_tempotal )
    {
    	// se realiza el cambio de color
    	Desplazar::H(superficie_tempotal, color->getHinicial(), color->getHfinal(), color->getDesplazamiento());

    	textura = SDL_CreateTextureFromSurface(Renderizador::Instance()->getRenderer(), superficie_tempotal);

    	//se libera la superficie temporal recien utilizada.
    	SDL_FreeSurface(superficie_tempotal);

    	if ( !textura )
    		Logger::getInstance()->error("No se pudo crear la textura SDL para la imagen "+pathImagen+" ene su cambio de color.");
	}
    else
    {
    	Logger::getInstance()->error("No se pudo cargar la imagen "+pathImagen+ " para el cambio de color.");
    }
}

Animacion* Animacion::clonar()
{
	Animacion* animacion_clon = new Animacion();
	animacion_clon->textura = textura;
	animacion_clon->cantidadFotogramas = cantidadFotogramas;
	animacion_clon->fps = fps;
	animacion_clon->id = id;
	animacion_clon->pathImagen = pathImagen;

	return animacion_clon;
}

ostream& operator <<(ostream &o, const Animacion &a)
{
	o<<"Animacion -> [cantFotog, fps, id, pathImagen]=[";
	o<<a.cantidadFotogramas<<", "<<a.fps<<", "<<a.id<<", "<<a.pathImagen<<"]";
	return o;
}

string Animacion::toString()
{
    ostringstream stream;
    stream <<*this;
	return stream.str();
}
