#include "EscenarioGrafico.h"

#define LIMITE_IZQUIERDO 0

using std::list;

EscenarioGrafico::EscenarioGrafico() {

}

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

	for (list<Capa*>::iterator it = capas->begin(); it != capas->end(); ++it){
		Vector2f posActual = (*it)->getSprite()->getPosicion();
		Vector2f posNueva(posActual.X(), VentanaGrafica::Instance()->getLimiteLogicoSuperior() * VentanaGrafica::Instance()->relacion_de_aspectoY());
		(*it)->getSprite()->setPosicion(posNueva);
	}
}

void EscenarioGrafico::centrar_en(Vector2f posicion, float limiteLogicoIzquierdoVentana, float relacion_de_aspectoX){

}

void EscenarioGrafico::centrar_dibujables(int zindexPersonaje){
	//Centro las capas
	float posicionInicialY = 0.0f;

	Vector2f vec(this->getAnchoLogico()/2.0, posicionInicialY);
	for (list<Capa*>::iterator it = capas->begin(); it != capas->end(); ++it){
		(*it)->centrar_en(vec, VentanaGrafica::Instance()->getLimiteLogicoIzquierdo(), VentanaGrafica::Instance()->relacion_de_aspectoX());
	}

	//Centro el personaje
	int z_index_capa = 1;
	int veces_encontrado = 0;

	for (list<Capa*>::iterator it = capas->begin(); it != capas->end(); ++it) {

		if (z_index_capa == zindexPersonaje) veces_encontrado++;

		if (veces_encontrado == 2)
		{
			Vector2f vec2((float)this->ancho_logico/4.0, (float)getYPisoLogico());
			(*it)->centrar_en(vec2, VentanaGrafica::Instance()->getLimiteLogicoIzquierdo(), VentanaGrafica::Instance()->relacion_de_aspectoX());
			break;
		}

		z_index_capa++;
	}

	Logger::getInstance()->debug("Centrado de capas correcto.");
}

void EscenarioGrafico::scrollear_capas(){
	size_t poslListaVelocidades = 0;
	for (list<Capa*>::iterator it = capas->begin(); it != capas->end(); ++it){
		float nuevaPosicionXCapa = this->listaVelocidades[poslListaVelocidades] * VentanaGrafica::Instance()->getLimiteLogicoIzquierdo();
		(*it)->setPosicionX(nuevaPosicionXCapa);
		float posicionXRespectoAVentana = nuevaPosicionXCapa - VentanaGrafica::Instance()->getLimiteLogicoIzquierdo();
		Vector2f posPXSprite(posicionXRespectoAVentana * VentanaGrafica::Instance()->relacion_de_aspectoX(), 0.0f);
		(*it)->getSprite()->setPosicion(posPXSprite);
		poslListaVelocidades++;
	}
}

bool EscenarioGrafico::esValida(Vector2f posicion, double ancho_personaje){
//    cout << "ESCENARIO: " << this->ancho_logico << " ~ " << (posicion.X() + ancho_personaje) << endl;
    if ((posicion.X() - ancho_personaje)  <= LIMITE_IZQUIERDO || (posicion.X() + ancho_personaje) >= ancho_logico)
        return false;
    if (posicion.Y() < y_piso_logico || posicion.Y() >= alto_logico)
        return false;
    return true;
}

