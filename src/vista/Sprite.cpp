#include "Sprite.h"
#include "../Game.h"
#include "GestorTexturas.h"
#include "../modelo/Vector2.h"
#include "VentanaGrafica.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <jsoncpp/json/json.h>

Sprite::Sprite(string id_textura, Vector2 posicion, int cantidadFotogramas, int zIndex, int fps)
{
	this->factorEscalaX = 1.0f;
	this->factorEscalaY = 1.0f;
	this->zIndex = zIndex;

	int w, h;
	SDL_Texture* textura = GestorTexturas::Instance()->getTextura(id_textura);
	SDL_QueryTexture(textura, NULL, NULL, &w, &h);

	this->anchoPx = w;
	this->altoPx = h;
	this->posicion = posicion; // TODO: HACER BIEN
	this->cantidadFotogramas = cantidadFotogramas;
	this->anchoFotogramaPx = lround((double)this->anchoPx / (double)cantidadFotogramas);
	this->fotogramaActual = 0;
	this->flip = SDL_FLIP_NONE;
}

void Sprite::dibujar(){

	SDL_Rect srcRect;
	srcRect.x = (fotogramaActual - 1) * this->anchoFotogramaPx;
	srcRect.y = 0;
	srcRect.w = anchoFotogramaPx;
	srcRect.h = altoPx;

	SDL_Rect destRect;
	srcRect.x = posicion.getCoordenadaX();
	srcRect.y = posicion.getCoordenadaY();
	srcRect.w = (int)(anchoFotogramaPx * factorEscalaX);
	srcRect.h = (int)(altoPx * factorEscalaY);

	SDL_RenderCopyEx(VentanaGrafica::Instance()->getRenderer(),GestorTexturas::Instance()->getTextura(id_textura),&srcRect,&destRect,	0,NULL,SDL_FLIP_NONE);
}

void Sprite::setPosicion(Vector2 nuevaPosicion) {
	posicion = nuevaPosicion;
}

void Sprite::setFlip(SDL_RendererFlip f) {
	this->flip = f;
}

void Sprite::avanzarFotograma() {
	if (fotogramaActual < cantidadFotogramas)
		fotogramaActual++;
	else
		fotogramaActual = 1;
}

void Sprite::escalar(float factor_x, float factor_y){
	this->factorEscalaX = factor_x;
	this->factorEscalaY = factor_y;
}

void Sprite::escalar(int anchoNuevoPx, int altoNuevoPx){
	this->factorEscalaX = (float) anchoNuevoPx / (float) anchoPx;
	this->factorEscalaY = (float) altoNuevoPx / (float) altoPx;
}

void Sprite::setFotogramaActual(int nroFotograma){
	this->fotogramaActual = nroFotograma;
}

void Sprite::setZindex(int z_index){
	this->zIndex = z_index;
}

Sprite::~Sprite() {}
