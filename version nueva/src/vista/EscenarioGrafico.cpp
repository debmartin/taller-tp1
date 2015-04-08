#include "EscenarioGrafico.h"

using std::list;

EscenarioGrafico::EscenarioGrafico(double ancho, double alto, double y_piso, list<Dibujable*>* dibujables) :
    ancho_logico(ancho), alto_logico(alto), capas(dibujables) {
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
    for (list<Dibujable*>::iterator it = capas->begin(); it != capas->end(); ++it){
        (*it)->dibujar();
    }
}

void EscenarioGrafico::actualizar(){
    for (list<Dibujable*>::iterator it = capas->begin(); it != capas->end(); ++it){
        (*it)->actualizar();
    }
}

void EscenarioGrafico::scrollear_capas(Sentido sentido){

}

//ostream& operator <<(ostream &o, const Escenario &e) {
//
//        o<<"escenario -> [ancho, alto, ypiso]=["<<e.ancho<<", "<<e.alto<<", "<<e.ypiso<<"]";
//        return o;
//}
