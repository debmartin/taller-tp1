/*
 * Personaje.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Personaje.h"

#include <sstream>

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_HORIZONTAL_CAMINANDO 215.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_VELOCIDAD_NULA Vector2f(0, 0)
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

Personaje::Personaje(
		string idIn,
		double anchoIn,
		double altoIn,
		Vector2f posInicial,
		Posicionable* posc,
		int numJugador,
		map<estado_personaje, BVH*>* cajas_orientacion_derecha, // LA ORIENTACION DEL BVH DEBE SER DERECHA EN EL CONSTRUCTOR
		DireccionObjeto orientacionInicialPersonaje):

    Colisionable(posInicial, anchoIn, altoIn),
	id(idIn),
	posicionInicial(posInicial),
	ancho(anchoIn),
	alto(altoIn),
	estado(new EnEspera(posInicial,(*cajas_orientacion_derecha)[EN_ESPERA])),
	posicionable(posc),
	numeroJugador(numJugador),
	cajasPorEstado(cajas_orientacion_derecha)

{
	this->energia = ENERGIA_INICIAL;
	this->tiempoBloqueo = 0;

	// ORIENTACION INICIAL DE BVH - POR DEFECTO LA ORIENTACION ES DERECHA
	this->direccion = DIRECCION_DERECHA;
}

double Personaje::getAlto() const {
	return alto;
}

double Personaje::getAncho() const {
	return ancho;
}

int Personaje::getNumeroJugador(){
	return numeroJugador;
}

Vector2f Personaje::getDimensionesLogicas() const {
	return Vector2f(this->getAncho(), this->getAlto());
}

void Personaje::setPosicion(double x, double y) {
	this->posicion.setCoordenada(x,y);
}

Vector2f Personaje::getPosicion(){
	return this->posicion;
}

estado_personaje Personaje::getEstado(){
	return ((estado_personaje) estado->Id());
}

int Personaje::getEnergia(){
	return this->energia;
}

void Personaje::agregarArma(Objeto* unArma){
	this->arma = unArma;
	Vector2f posicionObjeto(posicion.X()+ancho,alto);
	arma->posicionar(posicionObjeto);
}

Objeto* Personaje::getArma(){
	return arma;
}

//Devuelve un vector posicion referenciado desde el eje con origen de coordenadas arriba izquierda.
Vector2f Personaje::obtenerPosicionEnVentana(){
	//Vector2f P1(getPivote().X(), getPivote().Y());
	//Vector2f P1(posicion.X(), posicion.Y() + getAlto()); // TODO: ESTE ES EL ORIGINAL, EL DE ABAJO USA PIVOTE.
	Vector2f P1(getPivote().X(), posicion.Y() + getAlto()); // TODO: ESTA MODIFICACION UTILIZA LA COMPONENTE X DEL PIVOTE SOLAMENTE, ESTA INCOMPLETA
	Vector2f P2 = VentanaGrafica::Instance()->calcularPosicionEnVentana(P1);
	return P2;
}

bool Personaje::llegoAlLimiteIzquierdo(){
	return VentanaGrafica::Instance()->llegoAlLimiteIzquierdo(this->posicion.X()-this->getAnchoEnvolvente()/2);
	//return VentanaGrafica::Instance()->llegoAlLimiteIzquierdo(this->getPivote().X() - this->getAnchoEnvolvente()/2);
}

bool Personaje::llegoAlLimiteDerecho(){
	return VentanaGrafica::Instance()->llegoAlLimiteDerecho(Vector2f(this->posicion.X()+this->getAnchoEnvolvente()/2,this->posicion.Y()));
}

void Personaje::caminarDerecha(){
    cambiarEstado(new CaminandoDerecha(posicion, llegoAlLimiteDerecho(), (*cajasPorEstado)[CAMINANDO_DERECHA], direccion));
    Logger::getInstance()->debug("Personaje: caminando derecha. Se setea trayectoria.");
}

void Personaje::caminarIzquierda(){
    cambiarEstado(new CaminandoIzquierda(posicion, llegoAlLimiteIzquierdo(), (*cajasPorEstado)[CAMINANDO_IZQUIERDA], direccion));
    Logger::getInstance()->debug("Personaje: caminando izquierda. Se setea trayectoria.");
}

void Personaje::saltarVertical(){
    cambiarEstado(new SaltandoVertical(posicion, (*cajasPorEstado)[SALTANDO_VERTICAL]));
    Logger::getInstance()->debug("Personaje: salto vertical. Se setea trayectoria.");
}

void Personaje::saltarOblicuoDerecha(){
    cambiarEstado(new SaltandoOblicuoDerecha(posicion, (*cajasPorEstado)[SALTANDO_OBLICUO_DERECHA]));
    Logger::getInstance()->debug("Personaje: salto oblicuo derecha. Se setea trayectoria.");
}

void Personaje::saltarOblicuoIzquierda(){
    cambiarEstado(new SaltandoOblicuoIzquierda(posicion, (*cajasPorEstado)[SALTANDO_OBLICUO_IZQUIERDA]));
    Logger::getInstance()->debug("Personaje: salto oblicuo izquierda. Se setea trayectoria.");
}

void Personaje::agacharse(){
    cambiarEstado(new Agachado(posicion, (*cajasPorEstado)[AGACHADO]));
    Logger::getInstance()->debug("Personaje: agachado.");
}

void Personaje::piniaAlta(){
    cambiarEstado(new PiniaAlta(posicion, (*cajasPorEstado)[PINIA_ALTA]));
    bloquearPersonaje(25);
	Logger::getInstance()->debug("Personaje: golpe alto.");
	//VentanaGrafica::Instance()->vibrar();
}

void Personaje::piniaBaja(){
    cambiarEstado(new PiniaBaja(posicion, (*cajasPorEstado)[PINIA_BAJA]));
    bloquearPersonaje(25);
	Logger::getInstance()->debug("Personaje: golpe bajo.");
}

void Personaje::piniaSaltandoDiagonalDerecha(){
    cambiarEstado(new PiniaSaltandoDiagonalDerecha(estado->getTrayectoria(), estado->obtenerTiempoDeCreacion(), (*cajasPorEstado)[PINIA_SALTANDO_DIAGONAL_DERECHA]));
	Logger::getInstance()->debug("Personaje: piña saltando.");
}

void Personaje::piniaSaltandoDiagonalIzquierda(){
    cambiarEstado(new PiniaSaltandoDiagonalIzquierda(estado->getTrayectoria(), estado->obtenerTiempoDeCreacion() , (*cajasPorEstado)[PINIA_SALTANDO_DIAGONAL_IZQUIERDA]));
	Logger::getInstance()->debug("Personaje: piña saltando.");
}

void Personaje::piniaSaltandoVertical(){
    cambiarEstado(new PiniaSaltandoVertical(estado->getTrayectoria(), estado->obtenerTiempoDeCreacion(), (*cajasPorEstado)[PINIA_SALTANDO_VERTICAL]));
	Logger::getInstance()->debug("Personaje: piña saltando.");
}

void Personaje::patadaAlta(){
	cambiarEstado(new PatadaAlta(posicion, (*cajasPorEstado)[PATEANDO_ALTO]));
	bloquearPersonaje(35);
	Logger::getInstance()->debug("Personaje: patada alta.");
}

void Personaje::patadaBaja(){
    cambiarEstado(new PatadaBaja(posicion, (*cajasPorEstado)[PATEANDO_BAJO]));
    bloquearPersonaje(35);
	Logger::getInstance()->debug("Personaje: patada baja.");
}

void Personaje::patadaAltaAgachado(){
	cambiarEstado(new PateandoAltoAgachado(posicion, (*cajasPorEstado)[PATEANDO_ALTO_AGACHADO]));
	Logger::getInstance()->debug("Personaje: patada alta agachado.");
}

void Personaje::patadaSaltandoVertical(){
    cambiarEstado(new PateandoSaltandoVertical(estado->getTrayectoria(), estado->obtenerTiempoDeCreacion(), (*cajasPorEstado)[PATEANDO_SALTANDO_VERTICAL]));
	Logger::getInstance()->debug("Personaje: patada.");
}

void Personaje::patadaSaltandoDiagonalDerecha(){
    cambiarEstado(new PateandoSaltandoDiagonalDerecha(estado->getTrayectoria(), estado->obtenerTiempoDeCreacion(), (*cajasPorEstado)[PATEANDO_SALTANDO_DIAGONAL_DERECHA]));
	Logger::getInstance()->debug("Personaje: patada.");
}

void Personaje::patadaSaltandoDiagonalIzquierda(){
    cambiarEstado(new PateandoSaltandoDiagonalIzquierda(estado->getTrayectoria(), estado->obtenerTiempoDeCreacion(), (*cajasPorEstado)[PATEANDO_SALTANDO_DIAGONAL_IZQUIERDA]));
	Logger::getInstance()->debug("Personaje: patada.");
}

void Personaje::gancho(){
	cambiarEstado(new Gancho(posicion, (*cajasPorEstado)[GANCHO]));
    Logger::getInstance()->debug("Personaje: gancho.");
}

void Personaje::defender(){
    cambiarEstado(new Defendiendo(posicion, (*cajasPorEstado)[DEFENDIENDO]));
	Logger::getInstance()->debug("Personaje: defensa.");
}

void Personaje::defenderAgachado(){
    cambiarEstado(new DefendiendoAgachado(posicion, (*cajasPorEstado)[DEFENDIENDO_AGACHADO]));
	Logger::getInstance()->debug("Personaje: defensa.");
}

void Personaje::recibirGolpe(){
	if(estaSaltando() && this->direccion == DIRECCION_IZQUIERDA){
	    cambiarEstado(new CaidaDerecha(posicion, (*cajasPorEstado)[RECIBIENDO_GOLPE]));
	}else if(estaSaltando() && this->direccion == DIRECCION_DERECHA){
	    cambiarEstado(new CaidaIzquierda(posicion, (*cajasPorEstado)[RECIBIENDO_GOLPE]));
	}else{
	    cambiarEstado(new Golpeado(posicion, (*cajasPorEstado)[RECIBIENDO_GOLPE]));
        Vector2f vectorEmpuje = (direccion == DIRECCION_DERECHA) ? VECTOR_EMPUJE_IZQUIERDA : VECTOR_EMPUJE_DERECHA;
	    empujar(vectorEmpuje);
	}
    Logger::getInstance()->debug("Personaje: recibiendo golpe.");
}


void Personaje::mantenerReposo(){
    cambiarEstado(new EnEspera(posicion, (*cajasPorEstado)[EN_ESPERA]));
    Logger::getInstance()->debug("Personaje: en reposo.");
}

void Personaje::cambiarEstado(Estado* nuevo) {
    //delete estado;
    estado = nuevo;
}

void Personaje::agregarObservador(Observador* unObservador){
	Observable::agregarObservador(unObservador);
}

void Personaje::notificarObservadores(){
	Observable::notificarObservadores();
}

void Personaje::caer(){
    Vector2f velocActual = estado->obtenerVelocidad();
    estado_personaje id = estado->Id();
    cambiarEstado(new Cayendo(posicion, Vector2f(0, velocActual.Y()), id, (*cajasPorEstado)[id]));
//    cambiarEstado(new SaltandoVertical(posicion, (*cajasPorEstado)[id]));
}

void Personaje::arrastrar(Colisionable* otro){
    cout << "arrastra" << endl;
//    Vector2f diferencia = posicionCandidata - posicionAnterior - Vector2f(estado->calcularAncho(), 0);
    Vector2f diferencia = posicionCandidata - posicionAnterior;
    if (diferencia.Y() != 0)
        diferencia.setCoordenada(diferencia.X(), 0);
//    cout << "dir " << dir
    if ((posicion.X() < otro->getPosicion().X() && estado->Id() == CAMINANDO_IZQUIERDA) ||
        (posicion.X() > otro->getPosicion().X() && estado->Id() == CAMINANDO_DERECHA)) {
        posicion = posicionCandidata;
        return;
    }

    if (otro->empujar(diferencia))
        posicion = posicion + diferencia;
}

bool Personaje::empujar(Vector2f& diferencia) {
    if (! (estaEnReposo() || estaAgachado() || estaDefendiendo()))
        return false;

    estado_personaje proxEstado = (diferencia.X() >= 0) ? CAMINANDO_DERECHA : CAMINANDO_IZQUIERDA;
    if (estado->Id() == CAMINANDO_DERECHA && proxEstado == CAMINANDO_IZQUIERDA)
        return false;
    if (estado->Id() == CAMINANDO_IZQUIERDA && proxEstado == CAMINANDO_DERECHA)
        return false;

    if (estaDefendiendo())
        diferencia.setCoordenada(diferencia.X() / 2.0, diferencia.Y());

    posicionCandidata = posicion + diferencia;
    if (posicionable->esValida(posicionCandidata, estado->calcularAncho())){
        posicion = posicionCandidata;
        return true;
    }
    return false;
}

void Personaje::colisionar(Colisionable* otro){
    if (estaAtacando()) {
        ataqueActual = estado->obtenerAtaque();
        Colisionable::colisionar(otro);
        return;
    }
    if (! otro->estaAtacando()) return;

    if (estaDefendiendo()){
    	recibirDanio(otro->obtenerDanio() / 4);
    } else if (estaEnReposo() || estaCaminando()) {
    	recibirGolpe();
        recibirDanio(otro->obtenerDanio());
    } else if (estaSaltando()){
    	recibirGolpe();
        recibirDanio(otro->obtenerDanio());
    } else{
        recibirDanio(otro->obtenerDanio());
    }
    Colisionable::colisionar(otro);
}

bool Personaje::vaAColisionar(Colisionable* enemigo){
	double anchoFict = estado->calcularAncho();
	double altoFict = estado->calcularAlto();

	if (Colisionable::vaAColisionar(enemigo, anchoFict, altoFict)){
//		cout<<"vaAColisionar"<<endl;
		return true;
	}
    return estado->haySuperposicion(enemigo->obtenerCajaColision());
}

void Personaje::volverAlPiso(float distanciaAObjetivo){
    if (! posicionable->enExtremos(distanciaAObjetivo, estado->calcularAncho())) {
        posicion = Vector2f(posicionCandidata.X(), posicionInicial.Y());
    } else {
        posicion = Vector2f(posicion.X(), posicionInicial.Y());
    }
    mantenerReposo();
}

float calcularDistancia(float pos1, float pos2, float ancho) {
	float distancia = pos1 - pos2;
	if (distancia < 0) distancia = -distancia;

    return distancia + ancho;
}

void Personaje::calcularPosicionSinColision(Colisionable* enemigo){
	float distanciaAObjetivo = calcularDistancia(posicionCandidata.X(), enemigo->getPosicion().X(), estado->calcularAncho());

    if (posicionable->esValida(posicionCandidata, estado->calcularAncho()) && posicionCandidata.Y() >= posicionInicial.Y()) {

        if (! posicionable->enExtremos(distanciaAObjetivo, estado->calcularAncho())){
            posicion = posicionCandidata;
        }else{
            posicion = Vector2f(posicion.X(), posicionCandidata.Y());
        }
	} else if (posicionCandidata.Y() < posicionInicial.Y()) {
	    volverAlPiso(distanciaAObjetivo);
    } else if (posicionCandidata.Y() > posicionInicial.Y()) {
        caer();
    } else {
        mantenerReposo();
    }
}

void Personaje::espejarBVH() {
	int i = 1;
	//cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
    for (map<estado_personaje, BVH*>::iterator it = this->cajasPorEstado->begin() ; it != this->cajasPorEstado->end(); ++it)
    {
    	(it)->second->espejarBVH();
    	//cout << ">>>>>>>>>>>>>>>>>>>>>>>>" << i++ << endl;
    }
}

void Personaje::orientar(DireccionObjeto nuevaOrientacion) {
	//cout << "?????????????????PIVOTE-INI:" << this->obtenerCajaColision()->getPivote() << endl;
	if (this->direccion == nuevaOrientacion)
		return;

	this->direccion = nuevaOrientacion;
	this->arma->orientar(nuevaOrientacion);
	espejarBVH();
	//cout << "?????????????????PIVOTE-FIN:" << this->obtenerCajaColision()->getPivote() << endl;
}

void Personaje::calcularNuevaPosicion(Colisionable* enemigo){
    posicionCandidata = estado->obtenerProximaPosicion();

    if (! vaAColisionar(enemigo)) {
        calcularPosicionSinColision(enemigo);
        return;
    }
    if (estaCaminando()){
        arrastrar(enemigo);
    } else if (estaSaltando()) {
        posicionCandidata = estado->obtenerProximaPosicion();

        float distanciaAObjetivo = calcularDistancia(posicionCandidata.X(), enemigo->getPosicion().X(), estado->calcularAncho());
        if (posicionCandidata.Y() <= posicionInicial.Y()) {
            volverAlPiso(distanciaAObjetivo);
        //arrastrar(enemigo);
        } else if(posicionable->esValida(posicionCandidata, estado->calcularAncho())){
            posicion = posicionCandidata;
        } else {
            caer();
      }
    } else {
        colisionar(enemigo);
    }
 }

void Personaje::update(Colisionable* enemigo){
	Logger::getInstance()->debug("Personaje: update.");

	//cout << *this->obtenerCajaColision() << endl;

    if(estaBloqueado()){
        if(tiempoBloqueo <= 0){
           mantenerReposo();
        }
        tiempoBloqueo -= 1.0;
    }

    posicionAnterior = posicion;
    calcularNuevaPosicion(enemigo);
//    corregirPorColision(enemigo);
    cout << "personaje" << this->numeroJugador << " ~ " << posicion << endl;
    estado->actualizar(posicion);
	arma->update(enemigo);

	notificarObservadores();
}

Personaje::~Personaje(){
//    delete trayectoria;
}

bool Personaje::estaSaltando(){
    return (estado->estaSaltando());
}

bool Personaje::estaSaltandoVertical(){
    return (estado->estaSaltandoVertical());
}

bool Personaje::estaSaltandoDiagonalDerecha(){
    return (estado->estaSaltandoDiagonalDerecha());
}

bool Personaje::estaSaltandoDiagonalIzquierda(){
    return (estado->estaSaltandoDiagonalIzquierda());
}

bool Personaje::ejecutandoMovimientoEspecial(){
	return estado->ejecutandoMovimientoEspecial();
}

bool Personaje::estaAgachado(){
    return (estado->estaAgachado());
}

bool Personaje::estaEnReposo(){
    return (estado->estaEsperando());
}

bool Personaje::estaBloqueado(){
	return (estado->estaBloqueado());
}

bool Personaje::estaCaminando(){
	return (estado->estaCaminando());
}

bool Personaje::estaAtacando(){
    return (estado->estaAtacando());
}

bool Personaje::estaDefendiendo(){
    return (estado->estaDefendiendo());
}

bool Personaje::estaEnCaida(){
    return (estado->estaEnCaida());
}

void Personaje::arrojarArma(){
	//Posiciono el poder respecto a la posicion del personaje
	cout << "LANZADA" << endl;
	Vector2f posicionObjeto;
	if(this->direccion == DIRECCION_DERECHA){
		posicionObjeto.setCoordenada(posicion.X()+ancho/2, alto * 5/6);
	}else{
		posicionObjeto.setCoordenada(posicion.X()-ancho/2, alto * 5/6);
	}

	arma->posicionar(posicionObjeto);
	arma->arrojar();
}

void Personaje::recibirDanio(int danio){
	this->energia -= danio;
}


BVH* Personaje::obtenerCajaColision(){
    return estado->obtenerCajaColision();
}


void Personaje::bloquearPersonaje(float segundos){
	cambiarEstado(new Bloqueado(estado));
	this->tiempoBloqueo = segundos;
}


ostream& operator <<(ostream &o, const Personaje &p) {

        o<<"Personaje -> [ancho, alto, posInicial]=["<<p.ancho<<", "<<p.alto<<", "<<p.posicionInicial<<"]";
        return o;
}

string Personaje::getId() const {
	return id;
}

string Personaje::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}

void Personaje::definirPosicionIncial_enX(double x)
{
	double y = this->posicion.Y();
	Vector2f posicionIncial(x,y);
	this->posicion = posicionIncial;
	this->posicionInicial = posicionIncial;
}

void Personaje::cambiarNumeroPersonaje(){
	if(this->numeroJugador == NUMERO_DE_PERSONAJE_1){
		this->numeroJugador = NUMERO_DE_PERSONAJE_2;
	}else{
		this->numeroJugador = NUMERO_DE_PERSONAJE_1;
	}
}
//void Personaje::agregarCajasColisiones(BVH* caja, estado_personaje estadoCaja){
//    cajasPorEstado[estadoCaja] = caja;
//}

bool Personaje::estaMuerto(){
    return (this->energia <= 0);
}

float Personaje::getAnchoEnvolvente() {
	return this->estado->calcularAncho();
}

float Personaje::getAltoEnvolvente() {
	return this->estado->calcularAlto();
}

Estado* Personaje::verEstado(){
	return estado;
}
