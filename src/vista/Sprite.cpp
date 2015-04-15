#include "Sprite.h"
#include "../modelo/Vector2f.h"
#include "VentanaGrafica.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <iostream>

#define FACTOR_ESCALA_INICIAL_X 1.0f
#define FACTOR_ESCALA_INICIAL_Y 1.0f
#define TIEMPO_INICIAL 0
#define FOTOGRAMA_INICIAL 1

Sprite::Sprite(Animacion* animacion, Vector2f& posicionIni, OrientacionSprite orientacion) :
    animacionAct(animacion), posicion(posicionIni), factorEscalaX (FACTOR_ESCALA_INICIAL_X),
	factorEscalaY(FACTOR_ESCALA_INICIAL_Y), fps(animacion->getFps()), tCreacion(TIEMPO_INICIAL) {
    //ARREGLAR tCreacion
	int w, h;
	SDL_Texture* textura = animacion->getTextura();
	SDL_QueryTexture(textura, NULL, NULL, &w, &h);

	this->anchoPx = w;
	this->altoPx = h;

	double cantidadFotogramas = animacion->getCantidadFotogramas();
	this->anchoFotogramaPx = lround((double) anchoPx / cantidadFotogramas);
	this->fotogramaActual = FOTOGRAMA_INICIAL;

	if (orientacion == ORIENTACION_DERECHA)
		this->flip = SDL_FLIP_NONE;
	else
		this->flip = SDL_FLIP_HORIZONTAL;

	this->sentidoReproduccion = HACIA_ADELANTE;

}

void Sprite::dibujar(){

	SDL_Rect srcRect;
	srcRect.x = (fotogramaActual - 1) * this->anchoFotogramaPx;
	srcRect.y = 0;
	srcRect.w = anchoFotogramaPx;
	srcRect.h = altoPx;

	SDL_Rect destRect;
	destRect.x = (int) posicion.X();
	destRect.y = (int) posicion.Y();
	destRect.w = (int)(anchoFotogramaPx * factorEscalaX);
	destRect.h = (int)(altoPx * factorEscalaY);

	cout << "ññññññw" << factorEscalaX << endl;
	cout << "ññññññh" << anchoFotogramaPx <<endl;
	SDL_RenderCopyEx(Renderizador::Instance()->getRenderer(), animacionAct->getTextura(), &srcRect, &destRect, 0, NULL, flip);

	//cout << "Sprite::dibujar(" << animacionAct->getId() << ")fotogramaActual:" << fotogramaActual << endl;

}

void Sprite::setPosicion(Vector2f& nuevaPosicion) {
	posicion = nuevaPosicion;
}

void Sprite::desplazar(Vector2f& p) {
	posicion += p;
}

void Sprite::setFlip(SDL_RendererFlip f) {
	this->flip = f;
}

int Sprite::getAnchoPx(){
	return this->anchoFotogramaPx * factorEscalaX;
}

int Sprite::getAltoPx(){
	return this->altoPx * factorEscalaY;
}
/*
void Sprite::avanzarFotograma() {
	if (fotogramaActual < cantidadFotogramas)
		fotogramaActual++;
	else
		fotogramaActual = 1;
}
*/
void Sprite::escalarConFactor(Vector2f& factor){
	this->factorEscalaX = factor.X();
	this->factorEscalaY = factor.Y();
}

void Sprite::escalarConTamanio(int anchoNuevoPx, int altoNuevoPx){

	cout<<"++++++++++++++++++AnchoNuevoPx"<<anchoNuevoPx<<endl;
	cout<<"+++++++++++++++++++++AltoNuevoPx"<<altoNuevoPx<<endl;
	this->factorEscalaX = (float) anchoNuevoPx / (float) anchoFotogramaPx;
	this->factorEscalaY = (float) altoNuevoPx / (float) altoPx;
}

void Sprite::setFotogramaActual(int nroFotograma){
	this->fotogramaActual = nroFotograma;
}

void Sprite::update() {
	int delayTime = 1000.0f / fps;

    int cantidadFotogramas = animacionAct->getCantidadFotogramas();
	int nuevoFotograma = (int(SDL_GetTicks()/delayTime) % cantidadFotogramas) + 1;

	if (this->flip == SDL_FLIP_NONE && this->sentidoReproduccion == HACIA_ADELANTE)
		this->setFotogramaActual(nuevoFotograma);
	else if (this->flip == SDL_FLIP_NONE && this->sentidoReproduccion == HACIA_ATRAS)
		this->setFotogramaActual(cantidadFotogramas + 1 - nuevoFotograma);
	else if (this->flip == SDL_FLIP_HORIZONTAL && this->sentidoReproduccion == HACIA_ADELANTE)
		this->setFotogramaActual(cantidadFotogramas + 1 - nuevoFotograma);
	else if (this->flip == SDL_FLIP_HORIZONTAL && this->sentidoReproduccion == HACIA_ATRAS)
		this->setFotogramaActual(nuevoFotograma);

	cout<<"Sprite: update()"<<endl;


	//cout << "SPRITE->UPDATE:" << this->id_textura << " - poiscion:[" << posicion.getCoordenadaX() << "," << posicion.getCoordenadaY() << "],tiempo:[" << tActual << "]" << endl;
	//cout << "nº fotogarma:" << this->fotogramaActual << endl; TODO: para test
    //cout << "sprite update: ok" << endl;

}

void Sprite::setSentidoReproduccion(SentidoReproduccion sr) {
	this->sentidoReproduccion = sr;
}

void Sprite::cambiarAnimacion(Animacion* nuevaAnim) {

	animacionAct = nuevaAnim;
	this->fps = animacionAct->getFps();

	int w, h;
	SDL_Texture* textura = animacionAct->getTextura();
	SDL_QueryTexture(textura, NULL, NULL, &w, &h);
	this->anchoPx = w;
	this->altoPx = h;

	double cantidadFotogramas = animacionAct->getCantidadFotogramas();
	this->anchoFotogramaPx = lround((double)this->anchoPx / cantidadFotogramas);

	this->fotogramaActual = 1;
	cout << "Sprite::cambiarAnimacion" << endl;
}

Vector2f Sprite::getPosicion() {
	return posicion;
}

Sprite::~Sprite() {
}
