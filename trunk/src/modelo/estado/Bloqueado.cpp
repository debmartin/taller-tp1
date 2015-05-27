#include "Bloqueado.h"

#include "Estado.h"

Bloqueado::Bloqueado(Estado* estadoActual) :
    Estado(estadoActual->getTrayectoria(), estadoActual->Id(), estadoActual->obtenerCajaColision()){
	if(estadoActual->estaAtacando()){
		ataqueEstado = new Ataque(estadoActual->obtenerAtaque()->obtenerDanio());
	}
	estadoDeBloqueo = estadoActual;
}

Bloqueado::~Bloqueado(){
}

bool Bloqueado::estaBloqueado(){
    return true;
}

bool Bloqueado::estaAtacando(){
	return (estadoDeBloqueo->estaAtacando());
}

bool Bloqueado::ejecutandoMovimientoEspecial(){
	return (estadoDeBloqueo->ejecutandoMovimientoEspecial());
}
