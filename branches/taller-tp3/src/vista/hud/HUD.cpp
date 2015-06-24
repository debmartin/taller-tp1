#include "HUD.h"

HUD* HUD::instancia_unica = NULL;

HUD* HUD::Instance()
{
	if (instancia_unica == NULL)
	{
		instancia_unica = new HUD();
	}
	return instancia_unica;
}

HUD::HUD() {}

bool HUD::init(
	SDL_Window* gWindow,
	string nombre_personaje1,
	string nombre_personaje2,
	ColaEventos* colaDeTeclas,
	bool combosVisibles)
{

	this->gWindow         = gWindow;

	this->gRenderer       = SDL_GetRenderer(gWindow);

	this->barraDeEnergia1 = new BarraEnergia(gWindow, nombre_personaje1, BARRA_IZQUIERDA);
	this->barraDeEnergia2 = new BarraEnergia(gWindow, nombre_personaje2, BARRA_DERECHA);
	this->tHUD = crearTexturaTransparente(640, 480);


	this->colaDeTeclas = colaDeTeclas;

	this->combosVisibles = combosVisibles;

	// CARGA DE ANIMACIONES
	this->mAnimaciones = new map<string, Animacion*>;
    (*this->mAnimaciones)["JOY_PINIA_ALTA"]  = new Animacion(this->gRenderer, "RECURSOS/HUD/BOTONES/Δ.png" , 1, 1, "JOY_PINIA_ALTA");
    (*this->mAnimaciones)["JOY_PATADA_ALTA"] = new Animacion(this->gRenderer, "RECURSOS/HUD/BOTONES/O.png" , 1, 1, "JOY_PATADA_ALTA");
    (*this->mAnimaciones)["JOY_PINIA_BAJA"]  = new Animacion(this->gRenderer, "RECURSOS/HUD/BOTONES/X.png" , 1, 1, "JOY_PINIA_BAJA");
    (*this->mAnimaciones)["JOY_PATADA_BAJA"] = new Animacion(this->gRenderer, "RECURSOS/HUD/BOTONES/□.png" , 1, 1, "JOY_PATADA_BAJA");
    (*this->mAnimaciones)["JOY_DEFENSA"]     = new Animacion(this->gRenderer, "RECURSOS/HUD/BOTONES/R2.png", 1, 1, "JOY_DEFENSA");
    (*this->mAnimaciones)["JOY_PODER"]       = new Animacion(this->gRenderer, "RECURSOS/HUD/BOTONES/L2.png", 1, 1, "JOY_PODER");

    (*this->mAnimaciones)["JOY_ARRIBA"]      = new Animacion(this->gRenderer, "RECURSOS/HUD/BOTONES/ARRIBA.png"   , 1, 1, "JOY_ARRIBA");
    (*this->mAnimaciones)["JOY_ABAJO"]       = new Animacion(this->gRenderer, "RECURSOS/HUD/BOTONES/ABAJO.png"    , 1, 1, "JOY_ABAJO");
    (*this->mAnimaciones)["JOY_IZQUIERDA"]   = new Animacion(this->gRenderer, "RECURSOS/HUD/BOTONES/IZQUIERDA.png", 1, 1, "JOY_IZQUIERDA");
    (*this->mAnimaciones)["JOY_DERECHA"]     = new Animacion(this->gRenderer, "RECURSOS/HUD/BOTONES/DERECHA.png"  , 1, 1, "JOY_DERECHA");

    // CARGA DE SPRITES
	this->mBotones = new map<string, Sprite*>;
    (*this->mBotones)["JOY_PINIA_ALTA"]  = new Sprite((*this->mAnimaciones)["JOY_PINIA_ALTA"] , this->gRenderer, Vector2f(0.0f, 0.0f));
    (*this->mBotones)["JOY_PATADA_ALTA"] = new Sprite((*this->mAnimaciones)["JOY_PATADA_ALTA"], this->gRenderer, Vector2f(0.0f, 0.0f));
    (*this->mBotones)["JOY_PINIA_BAJA"]  = new Sprite((*this->mAnimaciones)["JOY_PINIA_BAJA"] , this->gRenderer, Vector2f(0.0f, 0.0f));
    (*this->mBotones)["JOY_PATADA_BAJA"] = new Sprite((*this->mAnimaciones)["JOY_PATADA_BAJA"], this->gRenderer, Vector2f(0.0f, 0.0f));
    (*this->mBotones)["JOY_DEFENSA"]     = new Sprite((*this->mAnimaciones)["JOY_DEFENSA"]    , this->gRenderer, Vector2f(0.0f, 0.0f));
    (*this->mBotones)["JOY_PODER"]       = new Sprite((*this->mAnimaciones)["JOY_PODER"]      , this->gRenderer, Vector2f(0.0f, 0.0f));

    (*this->mBotones)["JOY_ARRIBA"]      = new Sprite((*this->mAnimaciones)["JOY_ARRIBA"]   , this->gRenderer, Vector2f(0.0f, 0.0f));
    (*this->mBotones)["JOY_ABAJO"]       = new Sprite((*this->mAnimaciones)["JOY_ABAJO"]    , this->gRenderer, Vector2f(0.0f, 0.0f));
    (*this->mBotones)["JOY_IZQUIERDA"]   = new Sprite((*this->mAnimaciones)["JOY_IZQUIERDA"], this->gRenderer, Vector2f(0.0f, 0.0f));
    (*this->mBotones)["JOY_DERECHA"]     = new Sprite((*this->mAnimaciones)["JOY_DERECHA"]  , this->gRenderer, Vector2f(0.0f, 0.0f));

    (*this->mBotones)["JOY_PINIA_ALTA"]->escalarConTamanio(64,64);
    (*this->mBotones)["JOY_PATADA_ALTA"]->escalarConTamanio(64,64);
    (*this->mBotones)["JOY_PINIA_BAJA"]->escalarConTamanio(64,64);
    (*this->mBotones)["JOY_PATADA_BAJA"]->escalarConTamanio(64,64);
    (*this->mBotones)["JOY_DEFENSA"]->escalarConTamanio(64,64);
    (*this->mBotones)["JOY_PODER"]->escalarConTamanio(64,64);

    (*this->mBotones)["JOY_ARRIBA"]->escalarConTamanio(64,64);
    (*this->mBotones)["JOY_ABAJO"]->escalarConTamanio(64,64);
    (*this->mBotones)["JOY_IZQUIERDA"]->escalarConTamanio(64,64);
    (*this->mBotones)["JOY_DERECHA"]->escalarConTamanio(64,64);

   	this->aCaja = new Animacion(this->gRenderer, "RECURSOS/HUD/metal-oxidado.png"  , 1, 1, "metal-oxidado");
   	this->sCaja = new Sprite(this->aCaja , this->gRenderer, Vector2f(0.0f, 0.0f), ORIENTACION_DERECHA, SPR_ARRIBA_CENTRO);

	this->aFondoBoton = new Animacion(this->gRenderer, "RECURSOS/HUD/BOTONES/fondo-boton.png"  , 1, 1, "RECUADRO");
	this->sFondoBoton = new Sprite(this->aFondoBoton , this->gRenderer, Vector2f(0.0f, 0.0f), ORIENTACION_DERECHA, SPR_ARRIBA_IZQUIERDA);
	this->sFondoBoton->escalarConTamanio(64, 64);

	// RELOJ
	this->relojFuncionando = false;
	this->tiempoTranscurrido = 0;
	this->tiempoInicial = 0; // ESTE VALOR NO SE UTILIZA
	this->tiempoMostrado = 0;
	this->arrancarReloj();

    return true;

}

SDL_Texture* HUD::crearTexturaTransparente(int ancho, int alto) {
	SDL_Texture* tReturn = SDL_CreateTexture(this->gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, ancho, alto);
	SDL_SetTextureBlendMode(tReturn, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(this->gRenderer, tReturn);
	SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(this->gRenderer,0,0,0,0);
	SDL_RenderClear(this->gRenderer);
	SDL_RenderPresent(this->gRenderer);
	SDL_SetRenderTarget(this->gRenderer, NULL);

	return tReturn;
}

void HUD::arrancarReloj() {
	this->resetReloj();
	this->playReloj();
}

void HUD::pausarReloj() {
	this->relojFuncionando = false;
}

// Reloj regresa a cero y queda en pausa
void HUD::resetReloj() {
	this->tiempoInicial = SDL_GetTicks() / 1000.0f;
	this->relojFuncionando = false;
}

void HUD::playReloj() {
	this->relojFuncionando = true;
}

bool HUD::seAcaboElTiempo() {
	return (this->tiempoTranscurrido >= TIEMPO_INICIAL_RELOJ_SEGUNDOS);
}

SDL_Texture* HUD::updateTexture() {

	SDL_Texture* b1 = this->barraDeEnergia1->updateTexture();
	SDL_Texture* b2 = this->barraDeEnergia2->updateTexture();

	SDL_SetRenderTarget(this->gRenderer, this->tHUD);

	SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(this->gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(this->gRenderer);

	SDL_Rect destRect1 = {30 , 43, 270, 26};
	SDL_RenderCopy(this->gRenderer, b1, NULL, &destRect1);

	SDL_Rect destRect2 = {340, 43, 270, 26};
	SDL_RenderCopy(this->gRenderer, b2, NULL, &destRect2);

	//SDL_RenderPresent(this->gRenderer);
	SDL_SetRenderTarget(this->gRenderer, NULL);

	return this->tHUD;
}

void HUD::disminuirEnergia1(float offset) {
	this->barraDeEnergia1->disminuirEnergia(offset);
}

void HUD::disminuirEnergia2(float offset) {
	this->barraDeEnergia2->disminuirEnergia(offset);
}

void HUD::setEnergia1(float nuevaEnergia) {
	this->barraDeEnergia1->setEnergia(nuevaEnergia);
}

void HUD::setEnergia2(float nuevaEnergia) {
	this->barraDeEnergia2->setEnergia(nuevaEnergia);
}

HUD::~HUD() {
	delete(barraDeEnergia1);
	delete(barraDeEnergia2);

	this->mAnimaciones->clear();
	delete(this->mAnimaciones);

	this->mBotones->clear();
	delete(this->mBotones);
}

void HUD::dibujar(){
	this->tHUD = updateTexture();
	SDL_RenderCopy(this->gRenderer, this->tHUD, NULL, NULL);
	SDL_SetRenderTarget(this->gRenderer, NULL);

	if (this->combosVisibles) {

		// IMPRIMO COLA DE COMBOS
		Vector2f posicion(320.0f - (colaDeTeclas->size() * 70) / 2 , 90.0f);
		std::deque<Evento*>::iterator it = colaDeTeclas->begin();

		while (it != colaDeTeclas->end()) {

			if ((*it)->estaColoreado()) {
				//cout << (*it)->getNombre() << endl;
				this->sFondoBoton->setPosicion(posicion);
				this->sFondoBoton->dibujar();
			}

			(*this->mBotones)[(*it)->getNombre()]->setPosicion(posicion);
			(*this->mBotones)[(*it)->getNombre()]->dibujar();
			posicion += Vector2f(70.0f, 0.0f);
			*it++;

		}


		// IMPRIMO NOMBRE DE COMBO
		if (this->mostrandoNombreCombo) {

			SDL_Color color = { 255, 239, 36, 255 };

			SDL_Texture* texturaCombo = renderText(nombreComboActual, "RECURSOS/HUD/mk2.ttf",color,25,this->gRenderer);


			//IMPRIMO CAJA COMBO
			this->sCaja->escalarConTamanio(this->W(texturaCombo) + 25, this->H(texturaCombo) * 1.10 );
			Vector2f posCaja(320, 399);
			this->sCaja->setPosicion(posCaja);
			this->sCaja->dibujar();

			// IMPRIMO NOMBRE COMBO
			SDL_Rect destRect1 = {320 - (this->W(texturaCombo) / 2) , 400, this->W(texturaCombo), this->H(texturaCombo)};
			SDL_RenderCopy(this->gRenderer, texturaCombo, NULL, &destRect1);
		}
	}

	// IMPRIMO RELOJ
	char tiempoReloj[256];
	if (this->tiempoMostrado > 9)
		sprintf (tiempoReloj,"%d", this->tiempoMostrado);
	else
		sprintf (tiempoReloj,"0%d", this->tiempoMostrado);

	SDL_Color color = { 255, 239, 36, 255 };
	SDL_Texture* tTiempo = renderText(tiempoReloj, "RECURSOS/HUD/mk2.ttf",	color, 30, gRenderer);
	SDL_Rect destRect3 = {320 - this->W(tTiempo) / 2, 28, this->W(tTiempo), this->H(tTiempo) * 1.6};

	color = { 0, 0, 0, 255 };
	SDL_Texture* tTiempo2 = renderText(tiempoReloj, "RECURSOS/HUD/mk2.ttf",	color, 30, gRenderer);
	SDL_Rect destRect4 = {320 - this->W(tTiempo) / 2, 30, this->W(tTiempo2), this->H(tTiempo2) * 1.6};


	SDL_RenderCopy(this->gRenderer, tTiempo2, NULL, &destRect4);
	SDL_RenderCopy(this->gRenderer, tTiempo, NULL, &destRect3);
}

void HUD::mostrarMensajeCombo(string nombreCombo) {

	this->nombreComboActual = nombreCombo;
	this->mostrandoNombreCombo = true;
	this->tiempoInicioMostrar = SDL_GetTicks();
}

void HUD::update() {
	if (SDL_GetTicks() - this->tiempoInicioMostrar > TIEMPO_LIMITE_MOSTRAR_NOMBRE_COMBO)
		this->mostrandoNombreCombo = false;

	if (this->relojFuncionando && this->tiempoTranscurrido < TIEMPO_INICIAL_RELOJ_SEGUNDOS) {
		this->tiempoTranscurrido = SDL_GetTicks() / 1000.0f - this->tiempoInicial;
		this->tiempoMostrado = TIEMPO_INICIAL_RELOJ_SEGUNDOS - this->tiempoTranscurrido;
	}
}

void HUD::recibirNotificacion(Observable* unObservable){
	Personaje* unPersonaje = (Personaje*) unObservable;
	if(unPersonaje->getNumeroJugador() == 1){
		if(barraDeEnergia2->getPorcentajeEnergia() != unPersonaje->getEnergia()){
			setEnergia2(unPersonaje->getEnergia());
		}
	}else{
		if(barraDeEnergia1->getPorcentajeEnergia() != unPersonaje->getEnergia()){
			setEnergia1(unPersonaje->getEnergia());
		}
	}
}


SDL_Texture* HUD::renderText(
		std::string mensaje,
		std::string pathFuente,
		SDL_Color 		   color,
		int 			   tamanioFuentePx,
		SDL_Renderer*      renderer)
{

	TTF_Font *fuente = TTF_OpenFont(pathFuente.c_str(), tamanioFuentePx);
	if (fuente == NULL){
		std::cout << "ERROR: TTF_OpenFont" << endl;
		std::cout << TTF_GetError() << std::endl;
		return NULL;
	}

	SDL_Surface *surf = TTF_RenderText_Blended(fuente, mensaje.c_str(), color);
	if (surf == NULL){
		TTF_CloseFont(fuente);
		std::cout << "ERROR: TTF_RenderText" << endl;
		return NULL;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == NULL){
		std::cout << "CreateTexture" << endl;
	}

	SDL_FreeSurface(surf);
	TTF_CloseFont(fuente);
	return texture;
}


Uint32 HUD::W(SDL_Texture* t) {
	int w, h;
	SDL_QueryTexture(t, NULL, NULL, &w, &h);
	return w;
}

Uint32 HUD::H(SDL_Texture* t) {
	int w, h;
	SDL_QueryTexture(t, NULL, NULL, &w, &h);
	return h;
}

