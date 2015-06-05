#include "Sonido.h"

#include <SDL2/SDL_mixer.h>
#include <cstring>
#include <iostream>
#include <sstream>

#include "utils/Logger.h"

Sonido::Sonido(char* idSonido, char* path, int volumen, int canal){
	this->idSonido = idSonido;
	this->path = path;
	this->sonido = cargarSonido(path);  //si hubo algun error devuelve NULL
	this->setVolumen(volumen);
	this->canal = canal;
	this->setCanalEnReproduccion(0);
	this->setCanalEnPausa(0);
}

Sonido::Sonido(const string& idSonido, const string& path, int volumen, int canal){
	this->idSonido = strdup(idSonido.c_str());
	char * pathTmp = strdup(path.c_str());
	this->path = pathTmp;
	this->sonido = this->cargarSonido(pathTmp);  //si hubo algun error devuelve NULL
	this->setVolumen(volumen);
	this->canal = canal; 
	this->setCanalEnReproduccion(0);
	this->setCanalEnPausa(0);
}

void Sonido::reproducir(int cantRepeticiones){
	std::stringstream ss;
	if(this->sonido /*&& this->getCanalEnReproduccion() == 0 && this->getCanalEnPausa() == 0 */){
		//ss<<"reproduciendo Idsonido: "<<this->idSonido<<"  nombre: "<<this->path;
		//Logger::getInstance()->info(ss.str());
		Mix_PlayChannel(this->canal, this->sonido, cantRepeticiones - 1); //le resto uno por asi funciona la funcion esta
		this->setCanalEnReproduccion(1);
		this->setCanalEnPausa(0);
	}else if (!this->sonido){
		ss<<"No reproduce Idsonido: "<<this->idSonido<<"  nombre: "<<this->path<<" por que NO EXISTE SONIDO";
		Logger::getInstance()->info(ss.str());
	}
}

void Sonido::pausar(){
	if(this->sonido && this->getCanalEnReproduccion() == 1 && this->getCanalEnPausa() == 0){
		Mix_Pause(this->canal);
		this->setCanalEnReproduccion(0);
		this->setCanalEnPausa(1);
	}
	else{
		std::stringstream ss;
		ss<<"pausa no aplicable en sonido de nombre: " <<this->path;
		Logger::getInstance()->debug(ss.str());
	}
}

void Sonido::reanudar(){
	if (this->sonido && this->getCanalEnReproduccion() == 0 && this->getCanalEnPausa() == 1){
		Mix_Resume(this->canal);
		this->setCanalEnReproduccion(1);
		this->setCanalEnPausa(0);
	}
	else {
		std::stringstream ss;
		ss<<"reanudacion no aplicable en sonido de nombre: "<<this->path;
		Logger::getInstance()->debug(ss.str());
	}
}

void Sonido::detenerReproduccionSeco(){
	if(this->sonido && this->getCanalEnReproduccion() == 1){
		int canalActual = Mix_HaltChannel(this->canal);
		this->setCanal(canalActual);
		this->setCanalEnReproduccion(0);
		this->setCanalEnPausa(0);
	}
	else{
		std::stringstream ss;
		ss<<"No aplica detener reproduccion en seco en sonido de nombre: "<<this->path;
		Logger::getInstance()->debug(ss.str());
	}
}

void Sonido::detenerReproduccionLentamente(){
	if(this->sonido && this->getCanalEnReproduccion() == 1){
		int duracionEfectoDeFade = 20; //medidos en milisegundos, asumo que tengo tiempo de sonido para hacer este efecto, sino lo loggeo. Segun pablo no prueban estas cosas, voy a averiguar mas!
		int canalActual = Mix_FadeOutChannel(this->canal, duracionEfectoDeFade);
		this->setCanal(canalActual);
		this->setCanalEnReproduccion(0);
		this->setCanalEnPausa(0);
	}
	else{
		std::stringstream ss;
		ss<<"No aplica detener reproduccion en lentamente en sonido de nombre: "<<this->path;
		Logger::getInstance()->debug(ss.str());
	}
}

Mix_Chunk* Sonido::cargarSonido(char* path){
	Mix_Chunk* sonidoAux = Mix_LoadWAV(path);
	if (sonidoAux == NULL){
		std::stringstream ss;
		ss << "No se puedo cargar el sonido de nombre " << this->path;
		Logger::getInstance()->debug(ss.str());
	}
	else {
		std::stringstream ss;
		ss << "Se cargo el sonido de nombre " << this->path;
		Logger::getInstance()->info(ss.str());
	}
	return sonidoAux;
}

char* Sonido::getIdSonido(){
	return this->idSonido;
}

Mix_Chunk* Sonido::getSonido(){
	return this->sonido;
}

char* Sonido::getPath(){
	return this->path;
}

int Sonido::getVolumen(){
	return this->volumen;
}

int Sonido::getCanal(){
	return this->canal;
}

int Sonido::getCanalEnReproduccion(){
	return this->canalEnReproduccion;
}

int Sonido::getCanalEnPausa(){
	return this->canalEnPausa;
}

void Sonido::setVolumen(int volumen){
	int volumenAux = 0;  
	if (this->sonido){
		Mix_VolumeChunk(this->sonido, volumen);
		volumenAux = volumen;
	}
	else {
		std::stringstream ss;
		ss << "volumen no seteado en sonido de nombre " << this->path;
		Logger::getInstance()->info(ss.str());
	}
	this->volumen = volumenAux;
}

void Sonido::setCanal(int nuevoCanal){
	this->canal = nuevoCanal;
}

void Sonido::setCanalEnReproduccion(int newStatus){
	this->canalEnReproduccion = newStatus;
}

void Sonido::setCanalEnPausa(int newStatus){
	this->canalEnPausa = newStatus;
}

Sonido::~Sonido(){
		if(this->sonido)
			Mix_FreeChunk(this->sonido);
	}

void Sonido::imrprimirDatos(){
	cout<<"LOS DATOS SON:"<<endl;
	if (this->getSonido() != NULL){
		cout<<"\t\tidSonido: "<<this->getIdSonido()<<endl;
		cout<<"\t\tpath: "<<this->getPath()<<endl;
		cout<<"\t\tvolumen: "<<this->getVolumen()<<endl;
		cout<<"\t\tcanal: "<<this->getCanal()<<endl;
		if (this->getCanalEnReproduccion() == 1) cout<<"\t\tcanal en reproduccion"<<endl;
		if (this->getCanalEnPausa() == 1) cout<<"\t\tcanal en pausa"<<endl;
		if (this->getCanalEnReproduccion() == 0 && this->getCanalEnPausa() == 0) cout<<"\t\tcanal detenido"<<endl;
	}
	else 
		cout<<"\t\tel sonido es nulo"<<endl;
	cout<<"\t\t\t\t\t\t\tm > MENU"<<endl;
}
