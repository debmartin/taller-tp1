#include "HUD.h"

HUD::HUD(
	SDL_Window* gWindow,
	string nombre_personaje1,
	string nombre_personaje2,
	deque<string>* colaDeTeclas,
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
    (*this->mBotones)["JOY_PATADA_ALTA"] = new Sprite((*this->mAnimaciones)["JOY_PATADA_ALTA"], this->gRenderer, Vector2f(0.0f, 10.0f));
    (*this->mBotones)["JOY_PINIA_BAJA"]  = new Sprite((*this->mAnimaciones)["JOY_PINIA_BAJA"] , this->gRenderer, Vector2f(0.0f, 20.0f));
    (*this->mBotones)["JOY_PATADA_BAJA"] = new Sprite((*this->mAnimaciones)["JOY_PATADA_BAJA"], this->gRenderer, Vector2f(0.0f, 30.0f));
    (*this->mBotones)["JOY_DEFENSA"]     = new Sprite((*this->mAnimaciones)["JOY_DEFENSA"]    , this->gRenderer, Vector2f(0.0f, 40.0f));
    (*this->mBotones)["JOY_PODER"]       = new Sprite((*this->mAnimaciones)["JOY_PODER"]      , this->gRenderer, Vector2f(0.0f, 50.0f));

    (*this->mBotones)["JOY_ARRIBA"]      = new Sprite((*this->mAnimaciones)["JOY_ARRIBA"]   , this->gRenderer, Vector2f(0.0f, 60.0f));
    (*this->mBotones)["JOY_ABAJO"]       = new Sprite((*this->mAnimaciones)["JOY_ABAJO"]    , this->gRenderer, Vector2f(0.0f, 70.0f));
    (*this->mBotones)["JOY_IZQUIERDA"]   = new Sprite((*this->mAnimaciones)["JOY_IZQUIERDA"], this->gRenderer, Vector2f(0.0f, 80.0f));
    (*this->mBotones)["JOY_DERECHA"]     = new Sprite((*this->mAnimaciones)["JOY_DERECHA"]  , this->gRenderer, Vector2f(0.0f, 90.0f));
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

SDL_Texture* HUD::updateTexture() {

	SDL_Texture* b1 = this->barraDeEnergia1->updateTexture();
	SDL_Texture* b2 = this->barraDeEnergia2->updateTexture();

	SDL_SetRenderTarget(this->gRenderer, this->tHUD);

	SDL_SetRenderDrawBlendMode(this->gRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(this->gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(this->gRenderer);

	SDL_Rect destRect1 = {30 , 43, 270, 26};
	SDL_Rect destRect2 = {340, 43, 270, 26};

	SDL_RenderCopy(this->gRenderer, b1, NULL, &destRect1);
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

	/*
	if (this->combosVisibles) {
		//IMPRIMO COLA DE COMBOS 1
		int x = 30; int y = 70;
		std::deque<string>::iterator it1 = colaDeTeclas->begin();
		while (it1 != colaDeTeclas->end()) {
			SDL_Color color1 = { 255, 239, 36, 255 };
			SDL_Texture* combos = renderText(*it1++, "RECURSOS/HUD/mk2.ttf", color1, 11, gRenderer);
			SDL_Rect destRect = {x, y, 100, 20}; y += 15;
			SDL_RenderCopy(this->gRenderer, combos, NULL, &destRect);
			SDL_DestroyTexture(combos);
		}
	}
	*/


	if (this->combosVisibles) {
		//IMPRIMO COLA DE COMBOS 1
		int x = 30; int y = 70;
		std::deque<string>::iterator it1 = colaDeTeclas->begin();
		while (it1 != colaDeTeclas->end()) {
			//SDL_Color color1 = { 255, 239, 36, 255 };
			//SDL_Texture* combos = renderText(*it1++, "RECURSOS/HUD/mk2.ttf", color1, 11, gRenderer);
			SDL_Rect destRect = {x, y, 100, 20}; y += 15;

			//cout << *it1++ << endl;
			//Botones->
			//SDL_RenderCopy(this->gRenderer, mBotones[*it1++], NULL, &destRect);
			//SDL_DestroyTexture(combos);
		}
	}
	/*
    for (map<std::string, Sprite*>::iterator it = this->mBotones->begin() ; it != this->mBotones->end(); ++it)
    {
    	//cout << it->first << endl;
    	//this->mBotones[it->first]
    }
	*/
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
		std::string& mensaje,
		std::string& pathFuente,
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

