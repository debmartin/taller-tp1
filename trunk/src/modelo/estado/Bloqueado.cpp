#include "Bloqueado.h"

#include "Estado.h"

Bloqueado::Bloqueado(Estado* estadoActual) :
    Estado(estadoActual->getTrayectoria(), estadoActual->Id(), estadoActual->obtenerCajaColision()){
	ataqueEstado = new Ataque(estadoActual->obtenerAtaque()->obtenerDanio());
	bandera = estadoActual->estaAtacando();
}

Bloqueado::~Bloqueado(){
}

bool Bloqueado::estaBloqueado(){
    return true;
}

bool Bloqueado::estaAtacando(){
	cout<<"Entro a chequear Bloqueado::estaAtacando()"<<endl;
	if (bandera){
		cout<<"Chequea esta atacando: bandera True"<<endl;
		return true;
	}
	return false;
}
