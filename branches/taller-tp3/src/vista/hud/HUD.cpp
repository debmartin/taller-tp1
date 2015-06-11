#include "HUD.h"

HUD::HUD(SDL_Window* gWindow, string nombre_personaje1, string nombre_personaje2, bool combosVisibles) {

	this->gWindow         = gWindow;

	this->gRenderer       = SDL_GetRenderer(gWindow);

	this->barraDeEnergia1 = new BarraEnergia(gWindow, nombre_personaje1, BARRA_IZQUIERDA);
	this->barraDeEnergia2 = new BarraEnergia(gWindow, nombre_personaje2, BARRA_DERECHA);
	this->tHUD = crearTexturaTransparente(640, 480);

	this->colaDeTeclas1 = new deque<string>;
	this->colaDeTeclas2 = new deque<string>;

	this->combosVisibles = combosVisibles;
	this->colaDeTeclas1->push_back("EVENTO 1");
	this->colaDeTeclas1->push_back("EVENTO 2");
	this->colaDeTeclas1->push_back("EVENTO 3");

	this->colaDeTeclas2->push_back("EVENTO A");
	this->colaDeTeclas2->push_back("EVENTO B");
	this->colaDeTeclas2->push_back("EVENTO C");

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
}

void HUD::dibujar(){
	this->tHUD = updateTexture();
	SDL_RenderCopy(this->gRenderer, this->tHUD, NULL, NULL);

	if(this->combosVisibles){
		//IMPRIMO COLA DE COMBOS 1
		int x = 30; int y = 70;
		std::deque<string>::iterator it = colaDeTeclas1->begin();
		while (it != colaDeTeclas1->end()) {
			SDL_Texture* combos = renderText(*it++, "RECURSOS/HUD/mk2.ttf", { 255, 239, 36, 255 }, 11, gRenderer);
			SDL_Rect destRect = {x, y, 100, 20}; y += 15;
			SDL_RenderCopy(this->gRenderer, combos, NULL, &destRect);
			SDL_DestroyTexture(combos);
		}

		//IMPRIMO COLA DE COMBOS 2
		x = 500; y = 70;
		it = colaDeTeclas1->begin();
		while (it != colaDeTeclas1->end()) {
			SDL_Texture* combos = renderText(*it++, "RECURSOS/HUD/mk2.ttf", { 255, 239, 36, 255 }, 11, gRenderer);
			SDL_Rect destRect = {x, y, 100, 20}; y += 15;
			SDL_RenderCopy(this->gRenderer, combos, NULL, &destRect);
			SDL_DestroyTexture(combos);
		}
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
		const std::string& mensaje,
		const std::string& pathFuente,
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

