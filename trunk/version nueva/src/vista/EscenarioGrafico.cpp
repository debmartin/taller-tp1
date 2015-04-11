#include "EscenarioGrafico.h"

#define LIMITE_IZQUIERDO 0

using std::list;

EscenarioGrafico::EscenarioGrafico(double ancho, double alto, double y_piso, list<Dibujable*>* dibujables, list<Capa*>* capas) :
    ancho_logico(ancho), alto_logico(alto), dibujables(dibujables), capas(capas) {
}

double EscenarioGrafico::getAltoLogico() const {
	return alto_logico;
}

double EscenarioGrafico::getAnchoLogico() const {
	return ancho_logico;
}


double EscenarioGrafico::getYPisoLogico() const {
	return y_piso_logico;
}

EscenarioGrafico::~EscenarioGrafico() {
	// TODO Auto-generated destructor stub
}

void EscenarioGrafico::dibujar(){
    for (list<Dibujable*>::iterator it = dibujables->begin(); it != dibujables->end(); ++it){
        (*it)->dibujar();
    }
}

void EscenarioGrafico::actualizar(){
    for (list<Dibujable*>::iterator it = dibujables->begin(); it != dibujables->end(); ++it){
        (*it)->actualizar();
    }
}

void EscenarioGrafico::centrar_capas(){
	float posicionInicialY = 0.0f;
	Vector2f vec(this->ancho_logico/2.0, posicionInicialY);
	for (list<Capa*>::iterator it = capas->begin(); it != capas->end(); ++it){
		(*it)->centrar_en(vec);
	}
}

void EscenarioGrafico::scrollear_capas(){
/*	Dibujable* dib = this->capas->front();
	Capa* capa = (Capa*) dib;
	Sprite* sprite = capa->getSprite();*/

	for (list<Capa*>::iterator it = capas->begin(); it != capas->end(); ++it){
		Vector2f v(VentanaGrafica::Instance()->getLimiteLogicoIzquierdo() * VentanaGrafica::Instance()->relacion_de_aspectoX(), 0.0f);
		v*=-1;
		Sprite* sprite = (*it)->getSprite();
	    sprite->setPosicion(v);
	}
}

bool EscenarioGrafico::esValida(Vector2f posicion){
    if (posicion.X() < LIMITE_IZQUIERDO || posicion.X() >= ancho_logico)
        return false;
    if (posicion.Y() < y_piso_logico || posicion.Y() >= alto_logico)
        return false;
    return true;
}
//ostream& operator <<(ostream &o, const Escenario &e) {
//
//        o<<"escenario -> [ancho, alto, ypiso]=["<<e.ancho<<", "<<e.alto<<", "<<e.ypiso<<"]";
//        return o;
//}
