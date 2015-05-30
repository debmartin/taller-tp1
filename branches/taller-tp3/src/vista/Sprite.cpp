#include "Sprite.h"

Sprite::Sprite(
		Animacion* animacion,
		SDL_Renderer* pRenderer,
		Vector2f posicionIni,
		OrientacionSprite orientacion,
		UbicacionPivote ubicacion) :

	animacionAct(animacion),
	pRenderer(pRenderer),
	posicion(posicionIni),
	orientacion(orientacion),
	ubicacionDibujado(ubicacion),
	factorEscala(FACTOR_ESCALA_INICIAL),
	fps(animacion->getFps()),
	sentidoReproduccion(HACIA_ADELANTE),
	loopMode(LOOP_MOD),
	tInicial(SDL_GetTicks()){

	// DIMENSIONES DE IMAGEN
	int w, h;
	SDL_Texture* textura = animacion->getTextura();
	SDL_QueryTexture(textura, NULL, NULL, &w, &h);
	dimensionesImagen = Vector2f(w, h);

	// FOTORGAMAS
	double cantidadFotogramas = animacion->getCantidadFotogramas();
	this->anchoFotogramaPx = lround((double) this->dimensionesImagen.X() / cantidadFotogramas);
	this->fotogramaActual = FOTOGRAMA_INICIAL;

	//Logger::getInstance()->debug("Sprite::Sprite() - Construccion exitosa");
}

void Sprite::dibujar() {

	SDL_Rect srcRect;
	srcRect.x = (fotogramaActual - 1) * this->anchoFotogramaPx;
	srcRect.y = 0;
	srcRect.w = anchoFotogramaPx;
	srcRect.h = this->dimensionesImagen.Y();

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

	if (this->ubicacionDibujado == SPR_ARRIBA_IZQUIERDA)
		SDL_RenderCopyEx(this->pRenderer, animacionAct->getTextura(), &srcRect, &destRect, 0, NULL, flip);
	if (this->ubicacionDibujado == SPR_ARRIBA_CENTRO) {
		destRect.x -= destRect.w / 2;
		SDL_RenderCopyEx(this->pRenderer, animacionAct->getTextura(), &srcRect, &destRect, 0, NULL, flip);
	}
	if (this->ubicacionDibujado == SPR_ABAJO_IZQUIERDA) {
		destRect.y -= destRect.h;
		SDL_RenderCopyEx(this->pRenderer, animacionAct->getTextura(), &srcRect, &destRect, 0, NULL, flip);
	}
	if (this->ubicacionDibujado == SPR_ABAJO_CENTRO) {
		destRect.y -= destRect.h;
		destRect.x -= destRect.w / 2;
		SDL_RenderCopyEx(this->pRenderer, animacionAct->getTextura(), &srcRect, &destRect, 0, NULL, flip);
	}

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

int Sprite::getAnchoPx() {
	return this->anchoFotogramaPx * factorEscala.X();
}

int Sprite::getAltoPx() {
	return this->dimensionesImagen.Y() * factorEscala.Y();
}

Vector2f Sprite::getDimensionesPx() {
	return Vector2f(this->getAnchoPx(), this-> getAltoPx());
}

void Sprite::escalarConFactor(Vector2f factor){
	this->factorEscala = factor;
}

void Sprite::escalarConTamanio(int anchoNuevoPx, int altoNuevoPx) {
	this->factorEscala.X(((float) anchoNuevoPx) / ((float) anchoFotogramaPx));
	this->factorEscala.Y(((float) altoNuevoPx) / ((float) this->dimensionesImagen.Y()));
}

void Sprite::escalarConTamanio(Vector2f nuevoTamanioPx) {
	this->escalarConTamanio(nuevoTamanioPx.X(), nuevoTamanioPx.Y());
}

void Sprite::setFotogramaActual(int nroFotograma){
	this->fotogramaActual = nroFotograma;
}

void Sprite::update() {

	if (this->loopMode == LOOP_MOD) {
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
	}

	if (this->loopMode == LOOP_NO_REPEAT) {
		if (this->fotogramaActual == this->animacionAct->getCantidadFotogramas())
			return;
		else {
			int delayTime = 1000.0f / fps;

			int tActual = SDL_GetTicks();
			int tTranscurrido = tActual - this->tInicial;

			int cantidadFotogramas = animacionAct->getCantidadFotogramas();
			int nuevoFotograma = (int(tTranscurrido/delayTime) % cantidadFotogramas) + 1;

			if (this->orientacion == ORIENTACION_DERECHA && this->sentidoReproduccion == HACIA_ADELANTE)
				this->setFotogramaActual(nuevoFotograma);
			else if (this->orientacion == ORIENTACION_DERECHA && this->sentidoReproduccion == HACIA_ATRAS)
				this->setFotogramaActual(cantidadFotogramas + 1 - nuevoFotograma);
			else if (this->orientacion == ORIENTACION_IZQUIERDA && this->sentidoReproduccion == HACIA_ADELANTE)
				this->setFotogramaActual(nuevoFotograma);
			else if (this->orientacion == ORIENTACION_IZQUIERDA && this->sentidoReproduccion == HACIA_ATRAS)
				this->setFotogramaActual(cantidadFotogramas + 1 - nuevoFotograma);
		}
	}

	if (this->loopMode == LOOP_REPEAT) {
		int delayTime = 1000.0f / fps;

		int tActual = SDL_GetTicks();
		int tTranscurrido = tActual - this->tInicial;

		int cantidadFotogramas = animacionAct->getCantidadFotogramas();
		int nuevoFotograma = (int(tTranscurrido/delayTime) % cantidadFotogramas) + 1;

		if (this->orientacion == ORIENTACION_DERECHA && this->sentidoReproduccion == HACIA_ADELANTE)
			this->setFotogramaActual(nuevoFotograma);
		else if (this->orientacion == ORIENTACION_DERECHA && this->sentidoReproduccion == HACIA_ATRAS)
			this->setFotogramaActual(cantidadFotogramas + 1 - nuevoFotograma);
		else if (this->orientacion == ORIENTACION_IZQUIERDA && this->sentidoReproduccion == HACIA_ADELANTE)
			this->setFotogramaActual(nuevoFotograma);
		else if (this->orientacion == ORIENTACION_IZQUIERDA && this->sentidoReproduccion == HACIA_ATRAS)
			this->setFotogramaActual(cantidadFotogramas + 1 - nuevoFotograma);
	}

	//Logger::getInstance()->debug("Sprite::update()");
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
	dimensionesImagen = Vector2f(w, h);

	double cantidadFotogramas = animacionAct->getCantidadFotogramas();
	this->anchoFotogramaPx = lround((double)this->dimensionesImagen.X() / cantidadFotogramas);

	this->fotogramaActual = 1;
	this->escalarConTamanio(tamPx.X(), tamPx.Y());

	// LOOP
	this->tInicial = SDL_GetTicks();
	//Logger::getInstance()->debug("Sprite::cambiarAnimacion() - La animacion a sido cambiada");
}

void Sprite::setLoopMode(LoopMode loopMode) {
	this->loopMode = loopMode;
}

Vector2f Sprite::getPosicion() {
	return posicion;
}

Sprite::~Sprite() {
}

void Sprite::cambiarOrientacionHaciaDerecha() {

		orientacion = ORIENTACION_DERECHA;
}

void Sprite::cambiarOrientacionHaciaIzquierda() {

		orientacion = ORIENTACION_IZQUIERDA;

}

ostream& operator <<(ostream &o, const Sprite &s)
{
	o<<"Sprite -> [animacion, posicion, anchoPx, altoPx]=[";
	o<<*s.animacionAct<<", "<<s.posicion<<", "<< s.dimensionesImagen.X() <<", "<<s.dimensionesImagen.Y()<<"]";

	return o;
}

string Sprite::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}
