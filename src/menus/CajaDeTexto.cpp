/*
 * CajaDeTexto.cpp
 *
 *  Created on: 10/6/2015
 *      Author: ariel
 */

#include "CajaDeTexto.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "../utils/Logger.h"
#include "../vista/Renderizador.h"
#include "Textura.h"

CajaDeTexto::CajaDeTexto() {

}

CajaDeTexto::CajaDeTexto(int cant_caracteres, int pos_x, int pos_y) {

	this->cant_caracteres = cant_caracteres;
	this->cant_caracteres_vista = 9;
	this->pos_x = pos_x;
	this->pos_y = pos_y;

	this->altoCajaDeTexto = 30;
	this->tamLetra = altoCajaDeTexto;
	this->anchoCajaDeTexto = (this->cant_caracteres_vista * tamLetra) / 2;
	this->anchoLetra = this->anchoCajaDeTexto/this->cant_caracteres_vista;
	this->textura = new Textura();
	this->textColor = { 0, 0, 0, 0xFF };
	this->enfocado = false;
	this->textoVista = "";
	this->textoMemoria = "";
	this->posicionSelector = pos_x;
	this->numeroLetraSeleccionadaVista = 0;
}

CajaDeTexto::~CajaDeTexto() {
	delete this->textura;
}

bool CajaDeTexto::manejarEvento(SDL_Event e) {
	bool renderText = false;

	this->enfocado = false;
	//Get mouse position
	int x, y;
	SDL_GetMouseState( &x, &y );

	if( x > pos_x && x < (pos_x+anchoCajaDeTexto) && y > pos_y && y < (pos_y+altoCajaDeTexto))
	{
		this->enfocado = true;
	}

	if ( this->enfocado )
	{
		//Special key input
		if( e.type == SDL_KEYDOWN )
		{
			const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);
			if(estadoTeclado[SDL_SCANCODE_LEFT]){
				cout<<"Apreto izq"<<endl;
				if(posicionSelector == pos_x && numeroLetraSeleccionadaVista == 0){
					//Acomodo los caracteres de vista:
					cout<<"debug2 scroll izquierda"<<endl;
					cout<<"num letra:"<<numeroLetraSeleccionadaVista<<endl;
					if(bufferInferior.length() != 0){
						this->bufferSuperior = textoVista.substr(textoVista.length()-1,1) + bufferSuperior;
						this->textoVista = bufferInferior.substr(bufferInferior.length()-1,1) + textoVista.substr(0,textoVista.length()-1);
						this->bufferInferior = bufferInferior.substr(0,bufferInferior.length()-1);
					}
				}
				else if(posicionSelector >= pos_x + this->anchoLetra){
					cout<<"debug3 scroll izquierda"<<endl;
					posicionSelector -= this->anchoLetra;
					this->numeroLetraSeleccionadaVista-=1;
					cout<<"num letra:"<<numeroLetraSeleccionadaVista<<endl;
				}
			}else if(estadoTeclado[SDL_SCANCODE_RIGHT]){
				cout<<"Apreto der"<<endl;

				if(posicionSelector == this->pos_x + this->anchoLetra * (this->cant_caracteres_vista) && this->numeroLetraSeleccionadaVista != cant_caracteres){
					cout<<"debug1 scroll derecha"<<endl;
					cout<<"num letra:"<<numeroLetraSeleccionadaVista<<endl;

					if(bufferSuperior.length() != 0){
						this->bufferInferior = bufferInferior + textoVista.substr(0,1);
						this->textoVista = textoVista.substr(1,textoVista.length()-1) + bufferSuperior.substr(0,1);
						this->bufferSuperior = bufferSuperior.substr(1,bufferSuperior.length()-1);
					}
				}else if(posicionSelector < this->pos_x + this->anchoLetra * (this->cant_caracteres_vista)){
					cout<<"debug2 scroll derecha"<<endl;
					posicionSelector += this->anchoLetra;
					this->numeroLetraSeleccionadaVista+=1;
					cout<<"num letra:"<<numeroLetraSeleccionadaVista<<endl;
				}
				cout<<"Texto en memoria:"<<endl;
				cout<<this->textoMemoria<<endl;

				cout<<"Vista:"<<endl;
				cout<<this->textoVista<<endl;

				cout<<"Buffer Inferior:"<<endl;
				cout<<this->bufferInferior<<endl;
				cout<<"Buffer Superior:"<<endl;
				cout<<this->bufferSuperior<<endl;
			}

			//Se borra un caracter:
			else if( e.key.keysym.sym == SDLK_BACKSPACE && this->textoMemoria.length() > 0 )
			{

				cout<<"---------------"<<endl;
				cout<<"Se borra un caracter:"<<endl;
				if(this->textoMemoria.length() < this->cant_caracteres_vista){
					cout<<"Debug1 borrado"<<endl;
					cout<<"numero letra vista:"<<numeroLetraSeleccionadaVista<<endl;
					this->textoMemoria = this->textoMemoria.substr(0,numeroLetraSeleccionadaVista-1) + this->textoMemoria.substr(numeroLetraSeleccionadaVista,textoMemoria.length()-numeroLetraSeleccionadaVista);
					this->textoVista = this->textoMemoria;

					this->numeroLetraSeleccionadaVista-=1;
					posicionSelector -= this->tamLetra/2;

				}else if(numeroLetraSeleccionadaVista <= cant_caracteres_vista && numeroLetraSeleccionadaVista != 0){
					cout<<"Debug2 borrado"<<endl;
					cout<<"numero letra vista:"<<numeroLetraSeleccionadaVista<<endl;
					this->textoVista = this->textoVista.substr(0,numeroLetraSeleccionadaVista-1) + this->textoVista.substr(numeroLetraSeleccionadaVista,cant_caracteres_vista-numeroLetraSeleccionadaVista) + bufferSuperior.substr(0,1);;
					if(bufferSuperior.length() != 0){
						this->bufferSuperior = bufferSuperior.substr(1,bufferSuperior.length()-1);
					}
					this->textoMemoria = bufferInferior + textoVista + bufferSuperior;

					this->numeroLetraSeleccionadaVista-=1;
					posicionSelector -= this->tamLetra/2;

				}else if(numeroLetraSeleccionadaVista == 0){
					cout<<"Debug3 borrado"<<endl;
					cout<<"numero letra vista:"<<numeroLetraSeleccionadaVista<<endl;
					if(bufferInferior.length() != 0){
						this->bufferInferior = bufferInferior.substr(0,bufferInferior.length()-1);
					}
					this->textoMemoria = bufferInferior + textoVista + bufferSuperior;
				}
				cout<<"Texto en memoria:"<<endl;
				cout<<this->textoMemoria<<endl;

				cout<<"Vista:"<<endl;
				cout<<this->textoVista<<endl;

				cout<<"Buffer Inferior:"<<endl;
				cout<<this->bufferInferior<<endl;
				cout<<"Buffer Superior:"<<endl;
				cout<<this->bufferSuperior<<endl;
			}
		}
		//Special text input event
		else if( e.type == SDL_TEXTINPUT )
		{
			cout<<"---------------"<<endl;
			//Se agrega un caracter:
			if ( this->textoMemoria.length() < this->cant_caracteres)
			{
				cout<<"Ingresa caracter"<<endl;
				//Agrego un caracter intermedio
				if(this->textoVista.length() < this->cant_caracteres_vista){
					cout<<"Debug1"<<endl;
					cout<<"numero letra vista:"<<numeroLetraSeleccionadaVista<<endl;
					this->textoMemoria = this->textoMemoria.substr(0, numeroLetraSeleccionadaVista) + e.text.text + this->textoMemoria.substr(numeroLetraSeleccionadaVista, textoMemoria.length()-numeroLetraSeleccionadaVista);
					this->textoVista = this->textoMemoria;
					posicionSelector = posicionSelector + this->tamLetra/2;
					this->numeroLetraSeleccionadaVista+=1;
				}
				else if(numeroLetraSeleccionadaVista < cant_caracteres_vista){
					cout<<"Debug2"<<endl;
					cout<<"numero letra vista:"<<numeroLetraSeleccionadaVista<<endl;
					this->bufferSuperior = this->textoVista.substr(cant_caracteres_vista-1, 1) + bufferSuperior;
					this->textoVista = this->textoVista.substr(0,numeroLetraSeleccionadaVista) + e.text.text + this->textoVista.substr(numeroLetraSeleccionadaVista,textoVista.length()-numeroLetraSeleccionadaVista-1);

					this->textoMemoria = bufferInferior + textoVista + bufferSuperior;

					this->numeroLetraSeleccionadaVista+=1;
					posicionSelector = posicionSelector + this->tamLetra/2;
				//Agrego un caracter al final del texto de vista:
				}else if(numeroLetraSeleccionadaVista == cant_caracteres_vista){
					cout<<"Debug3"<<endl;
					cout<<"numero letra vista:"<<numeroLetraSeleccionadaVista<<endl;
					this->bufferInferior = bufferInferior + textoVista.substr(0, 1);
					this->textoVista = textoVista.substr(1, cant_caracteres_vista-1) + e.text.text;

					this->textoMemoria = bufferInferior + textoVista + bufferSuperior;

				}
				cout<<"Texto en memoria:"<<endl;
				cout<<this->textoMemoria<<endl;

				cout<<"Vista:"<<endl;
				cout<<this->textoVista<<endl;

				cout<<"Buffer Inferior:"<<endl;
				cout<<this->bufferInferior<<endl;
				cout<<"Buffer Superior:"<<endl;
				cout<<this->bufferSuperior<<endl;
			}
		}
		renderText = true;
	}
	return renderText;
}

void CajaDeTexto::dibujar(bool renderText) {

	if( renderText )
	{
		if( this->textoVista != "" )
		{
			this->textura->loadFromRenderedText( this->textoVista.c_str(), this->textColor );
		}else{
			this->textura->loadFromRenderedText( " ", this->textColor );
		}
	}

	//dibujar un cuadro blanco y despues el texto
	SDL_Rect fillRect = { this->pos_x, this->pos_y, this->anchoCajaDeTexto, this->altoCajaDeTexto };
	SDL_SetRenderDrawColor( Renderizador::Instance()->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderFillRect( Renderizador::Instance()->getRenderer(), &fillRect );

	SDL_Rect fillRect2 = { this->posicionSelector, this->pos_y, this->anchoLetra/4 , this->altoCajaDeTexto };
	SDL_SetRenderDrawColor( Renderizador::Instance()->getRenderer(), 32, 178, 170, 0 );
	SDL_RenderFillRect( Renderizador::Instance()->getRenderer(), &fillRect2 );
	//Render text textures
	this->textura->render(this->pos_x, this->pos_y);

}

bool CajaDeTexto::loadMedia() {
	//Loading success flag
	bool success = true;

	//Open the font
	//TTF_Font* gFont = TTF_OpenFont( "RECURSOS/HUD/mk2.ttf", this->tamLetra );
	TTF_Font* gFont = TTF_OpenFont( "RECURSOS/lazy.ttf", this->tamLetra );
	this->textura->setFont(gFont);

	if( gFont == NULL )
	{
		Logger::getInstance()->error("Failed to load lazy font! SDL_ttf Error");
		success = false;
	}

	return success;
}

string CajaDeTexto::getTexto() const {
	return textoMemoria;
}

bool CajaDeTexto::estoyEnfocado() {
	return this->enfocado;
}

void CajaDeTexto::setTexto(string texto) {
	this->textoVista = texto;
	this->textoMemoria = texto;
	this->posicionSelector += this->textoVista.length()*this->tamLetra/2;
	this->numeroLetraSeleccionadaVista = textoMemoria.length();
	this->bufferInferior = "";
	this->bufferSuperior = "";
	cout<<"Debug letra seleccionada:"<<numeroLetraSeleccionadaVista<<endl;
}
