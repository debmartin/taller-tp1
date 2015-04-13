#include "EscenarioGrafico.h"

#define LIMITE_IZQUIERDO 0

using std::list;

EscenarioGrafico::EscenarioGrafico(double ancho, double alto, double y_piso, list<Dibujable*>* dibujables, list<Capa*>* capas) :
    ancho_logico(ancho),
	alto_logico(alto),
	y_piso_logico(y_piso),
	dibujables(dibujables),
	capas(capas) {

	float velocidadCapa;

	for (list<Capa*>::iterator it = capas->begin(); it != capas->end(); ++it){
		velocidadCapa = this->getAnchoLogico() - (*it)->getAnchoLogico();
		velocidadCapa /= this->getAnchoLogico() - VentanaGrafica::Instance()->getAnchoLogico();

		this->listaVelocidades.push_back(velocidadCapa);
		cout << "VELOCIDAD DE CAPA:" << velocidadCapa << endl;
	}
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

void EscenarioGrafico::centrar_en(Vector2f v){

}

void EscenarioGrafico::centrar_dibujables(){
	//Centro las capas
	float posicionInicialY = 0.0f;
	Vector2f vec(VentanaGrafica::Instance()->getAnchoPx()/2.0, posicionInicialY);
	for (list<Capa*>::iterator it = capas->begin(); it != capas->end(); ++it){
		(*it)->centrar_en(vec);
	}

	//Centro el personaje
	Vector2f vec2(this->ancho_logico/2.0, getYPisoLogico());
	this->dibujables->back()->centrar_en(vec);
	//((PersonajeDibujable*)(this->dibujables))->centrar_en(vec);
}

void EscenarioGrafico::scrollear_capas(){
	size_t poslListaVelocidades = 0;
	for (list<Capa*>::iterator it = capas->begin(); it != capas->end(); ++it){
		/*
		Vector2f v(VentanaGrafica::Instance()->getLimiteLogicoIzquierdo() * VentanaGrafica::Instance()->relacion_de_aspectoX(), 0.0f);
		v*=-1;
		Sprite* sprite = (*it)->getSprite();
	    sprite->setPosicion(v);
	    */
		float nuevaPosicionXCapa = this->listaVelocidades[poslListaVelocidades] * VentanaGrafica::Instance()->getLimiteLogicoIzquierdo();
		(*it)->setPosicionX(nuevaPosicionXCapa);
		float posicionXRespectoAVentana = nuevaPosicionXCapa - VentanaGrafica::Instance()->getLimiteLogicoIzquierdo();
		Vector2f posPXSprite(posicionXRespectoAVentana * VentanaGrafica::Instance()->relacion_de_aspectoX(), 0.0f);
		(*it)->getSprite()->setPosicion(posPXSprite);
		poslListaVelocidades++;
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