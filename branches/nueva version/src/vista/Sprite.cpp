#include "Sprite.h"
#include "../modelo/Vector2.h"
#include "VentanaGrafica.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <iostream>

#include "GestorAnimaciones.h"

Sprite::Sprite(string id_animacion, Vector2 posicion, int zIndex)
{
	this->id_animacion = id_animacion;
	this->factorEscalaX = 1.0f;
	this->factorEscalaY = 1.0f;
	this->zIndex = zIndex;
	this->fps = GestorAnimaciones::Instance()->getAnimacion(id_animacion)->getFps();
	this->tCreacion = 0; //ARREGLAR

	int w, h;
	SDL_Texture* textura = GestorAnimaciones::Instance()->getAnimacion(id_animacion)->getTextura();
	SDL_QueryTexture(textura, NULL, NULL, &w, &h);

	this->anchoPx = w;
	this->altoPx = h;
	this->posicion = posicion;
	this->cantidadFotogramas = GestorAnimaciones::Instance()->getAnimacion(id_animacion)->getCantidadFotogramas();
	this->anchoFotogramaPx = lround((double)this->anchoPx / (double)cantidadFotogramas);
	this->fotogramaActual = 1;
	this->flip = SDL_FLIP_NONE;

	this->sentidoReproduccion = HACIA_ADELANTE;
	this->trayectoria = new Reposo(Vector2f(posicion));
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

	SDL_RenderCopyEx(VentanaGrafica::Instance()->getRenderer(),	GestorAnimaciones::Instance()->getAnimacion(id_animacion)->getTextura(), &srcRect, &destRect, 0,	NULL,this->flip);

	cout << "Sprite::dibujar(" << this->id_animacion << ")fotogramaActual:" << fotogramaActual << endl;

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


	// RECALCULA LA POSICION EN BASE AL OBJETO TRAYECTORIA
	float tActual = ((float)(SDL_GetTicks())/1000.0f) - tCreacion;
	this->posicion = this->trayectoria->getPosicion(tActual);
	//cout << "SPRITE->UPDATE:" << this->id_textura << " - poiscion:[" << posicion.getCoordenadaX() << "," << posicion.getCoordenadaY() << "],tiempo:[" << tActual << "]" << endl;
	//cout << "nº fotogarma:" << this->fotogramaActual << endl; TODO: para test
}

void Sprite::setSentidoReproduccion(SentidoReproduccion sr) {
	this->sentidoReproduccion = sr;
}

void Sprite::setTrayectoria(Trayectoria* t) {
	this->trayectoria = t;
	tCreacion = ((float)(SDL_GetTicks()))/1000.0f; //TODO: Solo funciona en el caso particular de este video juego porque anda lo suficientemente rapido
}

void Sprite::cambiarAnimacion(string id_animacion) {

	this->id_animacion = id_animacion;
	this->fps = GestorAnimaciones::Instance()->getAnimacion(id_animacion)->getFps();

	int w, h;
	SDL_Texture* textura = GestorAnimaciones::Instance()->getAnimacion(id_animacion)->getTextura();
	SDL_QueryTexture(textura, NULL, NULL, &w, &h);
	this->anchoPx = w;
	this->altoPx = h;

	this->cantidadFotogramas = GestorAnimaciones::Instance()->getAnimacion(id_animacion)->getCantidadFotogramas();
	this->anchoFotogramaPx = lround((double)this->anchoPx / (double)cantidadFotogramas);

	this->fotogramaActual = 1;
	cout << "Sprite::cambiarAnimacion" << endl;
}

Vector2 Sprite::getPosicion() {
	return this->posicion;
}

Sprite::~Sprite() {
	delete(trayectoria); // TODO: borrar trayectoria usando setTrayectoria pude traer problemas, gestionar bien la memoria.
}
