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
	if (bandera){
		return true;
	}
	return false;
}
