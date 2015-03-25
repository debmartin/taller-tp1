#include "Sprite.h"
#include "GestorTexturas.h"
#include "../modelo/Vector2.h"
#include <SDL2/SDL.h>

Sprite::Sprite(string id_textura, Vector2 posicion, int anchoFotogramaPx)
{
	int w, h;
	SDL_Texture* textura = GestorTexturas::Instance()->getTextura(id_textura);
	SDL_QueryTexture(textura, NULL, NULL, &w, &h);

	this->anchoPx = w;
	this->altoPx = h;
	this->anchoFotogramaPx = anchoFotogramaPx;
	this->fotogramaActual = 0;
}
/*
void Sprite::dibujar(){

}
*/
Sprite::~Sprite() {}
