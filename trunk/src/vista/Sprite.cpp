#include "Sprite.h"
#include "GestorTexturas.h"
#include "../modelo/Vector2.h"
#include "VentanaGrafica.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <iostream>

Sprite::Sprite(string id_textura, Vector2 posicion, int cantidadFotogramas, int zIndex, int fps)
{
	this->id_textura = id_textura;
	this->factorEscalaX = 1.0f;
	this->factorEscalaY = 1.0f;
	this->zIndex = zIndex;
	this->fps = fps;

	int w, h;
	SDL_Texture* textura = GestorTexturas::Instance()->getTextura(id_textura);
	SDL_QueryTexture(textura, NULL, NULL, &w, &h);

	this->anchoPx = w;
	this->altoPx = h;
	this->posicion = posicion; // TODO: HACER BIEN
	this->cantidadFotogramas = cantidadFotogramas;
	this->anchoFotogramaPx = lround((double)this->anchoPx / (double)cantidadFotogramas);
	this->fotogramaActual = 1;
	this->flip = SDL_FLIP_NONE;

	this->sentidoReproduccion = HACIA_ADELANTE;
}

void Sprite::dibujar(){

	SDL_Rect srcRect;
	srcRect.x = (fotogramaActual - 1) * this->anchoFotogramaPx;
	srcRect.y = 0;
	srcRect.w = anchoFotogramaPx;
	srcRect.h = altoPx;

	SDL_Rect destRect;
	destRect.x = posicion.getCoordenadaX();
	destRect.y = posicion.getCoordenadaY();
	destRect.w = (int)(anchoFotogramaPx * factorEscalaX);
	destRect.h = (int)(altoPx * factorEscalaY);

	SDL_RenderCopyEx(VentanaGrafica::Instance()->getRenderer(),	GestorTexturas::Instance()->getTextura(id_textura), &srcRect, &destRect, 0,	NULL,this->flip);

}

void Sprite::setPosicion(Vector2 nuevaPosicion) {
	posicion = nuevaPosicion;
}
void Sprite::desplazar(Vector2 p) {
	posicion += p;
}
void Sprite::setFlip(SDL_RendererFlip f) {
	this->flip = f;
}
/*
void Sprite::avanzarFotograma() {
	if (fotogramaActual < cantidadFotogramas)
		fotogramaActual++;
	else
		fotogramaActual = 1;
}
*/
void Sprite::escalarConFactor(float factor_x, float factor_y){
	this->factorEscalaX = factor_x;
	this->factorEscalaY = factor_y;
}

void Sprite::escalarConTamanio(int anchoNuevoPx, int altoNuevoPx){
	this->factorEscalaX = (float) anchoNuevoPx / (float) anchoPx;
	this->factorEscalaY = (float) altoNuevoPx / (float) altoPx;
}

void Sprite::setFotogramaActual(int nroFotograma){
	this->fotogramaActual = nroFotograma;
}

void Sprite::setZindex(float z_index){
	this->zIndex = z_index;
}

void Sprite::update() {
	int delayTime = 1000.0f / fps;

	int nuevoFotograma = (int(SDL_GetTicks()/delayTime) % this->cantidadFotogramas) + 1;

	if (this->sentidoReproduccion == HACIA_ADELANTE)
		this->setFotogramaActual(nuevoFotograma);
	else
		this->setFotogramaActual(cantidadFotogramas + 1 - nuevoFotograma);

	//cout << "nº fotogarma:" << this->fotogramaActual << endl; TODO: para test
}

void Sprite::setSentidoReproduccion(SentidoReproduccion sr) {
	this->sentidoReproduccion = sr;
}

Sprite::~Sprite() {}
