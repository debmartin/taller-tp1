#include "Bloqueado.h"

#include "Estado.h"

Bloqueado::Bloqueado(Estado* estadoActual) :
    Estado(estadoActual->getTrayectoria(), estadoActual->Id(), estadoActual->obtenerCajaColision(), EN_ESPERA){
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

bool Bloqueado::estaGolpeando(){
	return (estadoDeBloqueo->estaGolpeando());
}

bool Bloqueado::estaEnPiso(){
	return (estadoDeBloqueo->estaEnPiso());
}

bool Bloqueado::efectuandoPatadaGiratoria(){
	return (estadoDeBloqueo->efectuandoPatadaGiratoria());
}

bool Bloqueado::efectuandoGancho(){
	return (estadoDeBloqueo->efectuandoGancho());
}

bool Bloqueado::estaMareado(){
	return (estadoDeBloqueo->estaMareado());
}

bool Bloqueado::estaTomandoAlOponente(){
	return (estadoDeBloqueo->estaTomandoAlOponente());
}

bool Bloqueado::estaHaciendoToma(){
	return (estadoDeBloqueo->estaHaciendoToma());
}

bool Bloqueado::haciendoFatality(){
	return (estadoDeBloqueo->haciendoFatality());
}
