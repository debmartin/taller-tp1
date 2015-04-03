#include "EscenarioGrafico.h"

using std::list;

EscenarioGrafico::EscenarioGrafico(double ancho, double alto, list<Dibujable*>* dibujables) :
    ancho(ancho), alto(alto), dibujables(dibujables) {
}

double EscenarioGrafico::getAlto() const {
	return alto;
}

double EscenarioGrafico::getAncho() const {
	return ancho;
}

//int EscenarioGrafico::getYpiso() const {
//	return ypiso;
//}

EscenarioGrafico::~EscenarioGrafico() {
	// TODO Auto-generated destructor stub
}

void EscenarioGrafico::dibujar(){
    for (list<Dibujable*>::iterator it = dibujables->begin(); it != dibujables->end(); ++it){
        (*it)->dibujar();
    }
}
//ostream& operator <<(ostream &o, const Escenario &e) {
//
//        o<<"escenario -> [ancho, alto, ypiso]=["<<e.ancho<<", "<<e.alto<<", "<<e.ypiso<<"]";
//        return o;
//}
