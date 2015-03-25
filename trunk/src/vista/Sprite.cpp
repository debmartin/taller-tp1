#include "Sprite.h"
#include "../Game.h"
#include "GestorTexturas.h"
#include "../modelo/Vector2.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <jsoncpp/json/json.h>

Sprite::Sprite(string id_textura, Vector2 posicion, int cantidadFotogramas)
{
	int w, h;
	SDL_Texture* textura = GestorTexturas::Instance()->getTextura(id_textura);
	SDL_QueryTexture(textura, NULL, NULL, &w, &h);

	this->anchoPx = w;
	this->altoPx = h;
	this->posicion = posicion; // TODO: HACER BIEN
	this->cantidadFotogramas = cantidadFotogramas;
	this->anchoFotogramaPx = lround((double)this->anchoPx / (double)cantidadFotogramas);
	this->fotogramaActual = 0;
	this->flip = SDL_FLIP_NONE;
}

void Sprite::dibujar(){
/*
	SDL_Rect srcRect;
	srcRect.x = (fotogramaActual - 1) * this->anchoFotogramaPx;
	srcRect.y = 0;
	srcRect.w = anchoFotogramaPx;
	srcRect.h = altoPx;

	SDL_Rect destRect;
	srcRect.x = 0; //
	srcRect.y = 0;
	srcRect.w = anchoFotogramaPx;
	srcRect.h = altoPx;
*/
	SDL_RenderCopyEx(Game::Instance()->getRenderer(),GestorTexturas::Instance()->getTextura(id_textura), NULL, NULL, 0, NULL, SDL_FLIP_NONE);
}

Sprite::~Sprite() {}
