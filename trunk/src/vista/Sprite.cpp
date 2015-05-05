#include "Sprite.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <cmath>
#include <sstream>

#include "../utils/Logger.h"
#include "Animacion.h"
#include "Renderizador.h"

#define FACTOR_ESCALA_INICIAL_X 1.0f
#define FACTOR_ESCALA_INICIAL_Y 1.0f
#define FOTOGRAMA_INICIAL 1

Sprite::Sprite(Animacion* animacion, Vector2f& posicionIni, OrientacionSprite orientacion) :
    animacionAct(animacion),
	posicion(posicionIni),
	factorEscalaX(FACTOR_ESCALA_INICIAL_X),
	factorEscalaY(FACTOR_ESCALA_INICIAL_Y),
	fps(animacion->getFps()),
	orientacion(orientacion),
	sentidoReproduccion(HACIA_ADELANTE){

	int w, h;
	SDL_Texture* textura = animacion->getTextura();
	SDL_QueryTexture(textura, NULL, NULL, &w, &h);

	this->anchoPx = w;
	this->altoPx = h;

	double cantidadFotogramas = animacion->getCantidadFotogramas();
	this->anchoFotogramaPx = lround((double) anchoPx / cantidadFotogramas);
	this->fotogramaActual = FOTOGRAMA_INICIAL;

	Logger::getInstance()->debug("Sprite::Sprite() - Construccion exitosa");
}

void Sprite::dibujar() {

	SDL_Rect srcRect;
	srcRect.x = (fotogramaActual - 1) * this->anchoFotogramaPx;
	srcRect.y = 0;
	srcRect.w = anchoFotogramaPx;
	srcRect.h = altoPx;

	SDL_Rect destRect;
	destRect.x = (int) posicion.X();
	destRect.y = (int) posicion.Y();
	destRect.w = (int) getAnchoPx();
	destRect.h = (int) getAltoPx();

	SDL_RendererFlip flip;
	if (orientacion == ORIENTACION_DERECHA)
		flip = SDL_FLIP_NONE;
	else
		flip = SDL_FLIP_HORIZONTAL;

	SDL_RenderCopyEx(Renderizador::Instance()->getRenderer(), animacionAct->getTextura(), &srcRect, &destRect, 0, NULL, flip);
}

void Sprite::setPosicion(Vector2f& nuevaPosicion) {
	posicion = nuevaPosicion;
}

void Sprite::desplazar(Vector2f& p) {
	posicion += p;
}

void Sprite::setOrientacion(OrientacionSprite o) {
	this->orientacion = o;
}

int Sprite::getAnchoPx(){
	return this->anchoFotogramaPx * factorEscalaX;
}

int Sprite::getAltoPx(){
	return this->altoPx * factorEscalaY;
}

Vector2f Sprite::getDimensionesPx() {
	return Vector2f(this->getAnchoPx(), this-> getAltoPx());
}

void Sprite::escalarConFactor(Vector2f& factor){
	this->factorEscalaX = factor.X();
	this->factorEscalaY = factor.Y();
}

void Sprite::escalarConTamanio(int anchoNuevoPx, int altoNuevoPx) {
	this->factorEscalaX = ((float) anchoNuevoPx) / ((float) anchoFotogramaPx);
	this->factorEscalaY = ((float) altoNuevoPx) / ((float) altoPx);
}

void Sprite::setFotogramaActual(int nroFotograma){
	this->fotogramaActual = nroFotograma;
}

void Sprite::update() {
	int delayTime = 1000.0f / fps;

    int cantidadFotogramas = animacionAct->getCantidadFotogramas();
	int nuevoFotograma = (int(SDL_GetTicks()/delayTime) % cantidadFotogramas) + 1;

	if (this->orientacion == ORIENTACION_DERECHA && this->sentidoReproduccion == HACIA_ADELANTE)
		this->setFotogramaActual(nuevoFotograma);
	else if (this->orientacion == ORIENTACION_DERECHA && this->sentidoReproduccion == HACIA_ATRAS)
		this->setFotogramaActual(cantidadFotogramas + 1 - nuevoFotograma);
	else if (this->orientacion == ORIENTACION_IZQUIERDA && this->sentidoReproduccion == HACIA_ADELANTE)
		this->setFotogramaActual(cantidadFotogramas + 1 - nuevoFotograma);
	else if (this->orientacion == ORIENTACION_IZQUIERDA && this->sentidoReproduccion == HACIA_ATRAS)
		this->setFotogramaActual(nuevoFotograma);

	Logger::getInstance()->debug("Sprite::update()");
}

void Sprite::setSentidoReproduccion(SentidoReproduccion sr) {
	this->sentidoReproduccion = sr;
}

void Sprite::cambiarAnimacion(Animacion* nuevaAnim) {
	Vector2f tamPx = this->getDimensionesPx();
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
	this->escalarConTamanio(tamPx.X(), tamPx.Y());
	Logger::getInstance()->debug("Sprite::cambiarAnimacion() - La animacion a sido cambiada");
}

Vector2f Sprite::getPosicion() {
	return posicion;
}

Sprite::~Sprite() {
}

//TODO ver el atributo sentidoReproduccion ...

void Sprite::cambiarOrientacionHaciaDerecha() {
	if (orientacion == ORIENTACION_IZQUIERDA)
	{
		orientacion = ORIENTACION_DERECHA;
	}
}

void Sprite::cambiarOrientacionHaciaIzquierda() {
	if (orientacion == ORIENTACION_DERECHA)
	{
		orientacion = ORIENTACION_IZQUIERDA;
	}
}

ostream& operator <<(ostream &o, const Sprite &s)
{
	//TODO terminar de implementar ...
	o<<"Sprite -> [animacion, posicion, anchoPx, altoPx]=[";
	o<<*s.animacionAct<<", "<<s.posicion<<", "<<s.anchoPx<<", "<<s.altoPx<<"]";

	return o;
}

string Sprite::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}
