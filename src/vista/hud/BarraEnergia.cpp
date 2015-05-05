#include "BarraEnergia.h"

BarraEnergia::BarraEnergia(SDL_Window* gWindow, string nombre, OrientacionBarra orientacion) {
	this->porcentajeEnergia = 100.0f;
	this->gWindow           = gWindow;
	this->gRenderer         = SDL_GetRenderer(gWindow);

	this->tBarraBorde       = cargarTextura(DIR_IMG_BARRA_BORDE);
	this->tBarraInterior    = cargarTextura(DIR_IMG_BARRA_INTERIOR);
	this->tBarraCombinada   = cargarTextura(DIR_IMG_BARRA_BORDE);
	this->orientacion 	    = orientacion;
	this->nombre			= nombre;
	SDL_Color color 		= { 255, 239, 36, 255 };

	this->tNombre 			= renderText(nombre, "RECURSOS/HUD/mk2.ttf",	color, 11, gRenderer);
	SDL_Color color2 		= { 0, 0, 0, 255 };
	this->tNombreSombra		= renderText(nombre, "RECURSOS/HUD/mk2.ttf",	color2, 11, gRenderer);
}

SDL_Texture* BarraEnergia::cargarTextura(string path) {
	SDL_Surface* sAux = IMG_Load(path.c_str());

	SDL_Texture* tAux = SDL_CreateTextureFromSurface(this->gRenderer, sAux);
	SDL_Texture* tReturn = SDL_CreateTexture(this->gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sAux->w, sAux->h);
	SDL_SetTextureBlendMode(tReturn, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(this->gRenderer, tReturn);
	SDL_SetRenderDrawColor(this->gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(this->gRenderer);

	SDL_RenderCopy(this->gRenderer, tAux, NULL, NULL);

	SDL_RenderPresent(this->gRenderer);
	SDL_SetRenderTarget(this->gRenderer, NULL);

	SDL_DestroyTexture(tAux);
	SDL_FreeSurface(sAux);

	return tReturn;
}

SDL_Texture* BarraEnergia::updateTexture() {
	combinarTexturas();
	return this->tBarraCombinada;
}

void BarraEnergia::combinarTexturas() {
	SDL_SetRenderTarget(this->gRenderer, this->tBarraCombinada);

	SDL_SetRenderDrawBlendMode(this->gRenderer,SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(this->gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(this->gRenderer);

	// IMPRIMO BORDE
	SDL_RenderCopy(this->gRenderer, this->tBarraBorde, NULL, NULL);

	// IMPRIMO BARRA VERDE
	SDL_Rect srcRect, destRect;

	if (this->orientacion == BARRA_IZQUIERDA) {
		srcRect  = {0, 0, (int)(162*(porcentajeEnergia/100.0f)), 10};
		destRect = {3, 3, (int)(162*(porcentajeEnergia/100.0f)), 10};
		SDL_RenderCopy(this->gRenderer, this->tBarraInterior, &srcRect, &destRect);
	}
	else {
		srcRect  = {0, 0, (int)(162*(porcentajeEnergia/100.0f)), 10};
		destRect = {165 - (int)(162*(porcentajeEnergia/100.0f)), 3, (int)(162*(porcentajeEnergia/100.0f)), 10};
		SDL_RenderCopyEx(this->gRenderer, this->tBarraInterior, NULL, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
	}

	// IMPRIMO NOMBRE
	int w = W(this->tNombre);
	int h = H(this->tNombre);

	if (this->orientacion == BARRA_IZQUIERDA) {
		destRect = {13, 3, w, h};
		SDL_RenderCopy(this->gRenderer, this->tNombreSombra, NULL, &destRect);
		destRect = {12, 2, w, h};
		SDL_RenderCopy(this->gRenderer, this->tNombre, NULL, &destRect);
	}
	else {
		destRect = {W(this->tBarraBorde)-10-w, 3, w, h};;
		SDL_RenderCopy(this->gRenderer, this->tNombreSombra, NULL, &destRect);
		destRect = {W(this->tBarraBorde)-12-w, 2, w, h};
		SDL_RenderCopy(this->gRenderer, this->tNombre, NULL, &destRect);
	}

	// DESCARGO BUFFER
	//SDL_RenderPresent(this->gRenderer);

	SDL_SetRenderTarget(this->gRenderer, NULL);
}

Uint32 BarraEnergia::W(SDL_Texture* t) {
	int w, h;
	SDL_QueryTexture(t, NULL, NULL, &w, &h);
	return w;
}

Uint32 BarraEnergia::H(SDL_Texture* t) {
	int w, h;
	SDL_QueryTexture(t, NULL, NULL, &w, &h);
	return h;
}

void BarraEnergia::disminuirEnergia(float offset) {
	this->porcentajeEnergia -= offset;
}

void BarraEnergia::setEnergia(float nuevaEnergia) {
	this->porcentajeEnergia = nuevaEnergia;
}

float BarraEnergia::getPorcentajeEnergia() {
	return this->porcentajeEnergia;
}

SDL_Texture* BarraEnergia::renderText(
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

BarraEnergia::~BarraEnergia() {
	SDL_DestroyTexture(this->tBarraBorde);
	SDL_DestroyTexture(this->tBarraInterior);
	SDL_DestroyTexture(this->tBarraCombinada);
	SDL_DestroyTexture(this->tNombre);
	SDL_DestroyTexture(this->tNombreSombra);
}
