#include "Ataque.h"

Ataque::Ataque(int danioAtaque) :
    danio(danioAtaque) {
	ataqueEjecutado = false;
}

Ataque::~Ataque(){
}

int Ataque::obtenerDanio(){
	if(!ataqueEjecutado){
	   ataqueEjecutado = true;
	   return danio;;
	}
	   return 0;
}
