#include "HUD.h"

HUD::HUD(SDL_Window* gWindow, string nombre_personaje1, string nombre_personaje2) {

	this->gWindow         = gWindow;

	this->gRenderer       = SDL_GetRenderer(gWindow);

	this->barraDeEnergia1 = new BarraEnergia(gWindow, nombre_personaje1, BARRA_IZQUIERDA);
	this->barraDeEnergia2 = new BarraEnergia(gWindow, nombre_personaje2, BARRA_DERECHA);
	this->tHUD = crearTexturaTransparente(640, 480);

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
