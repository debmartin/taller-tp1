/*
 * Personaje.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Personaje.h"

#include <sstream>

#include "../utils/Logger.h"
#include "../vista/VentanaGrafica.h"
#include "Ataque.h"
#include "estado/Agachado.h"
#include "estado/Bloqueado.h"
#include "estado/CaminandoDerecha.h"
#include "estado/CaminandoIzquierda.h"
#include "estado/Cayendo.h"
#include "estado/Defendiendo.h"
#include "estado/DefendiendoAgachado.h"
#include "estado/EnEspera.h"
#include "estado/PatadaAlta.h"
#include "estado/PatadaBaja.h"
#include "estado/PateandoAltoAgachado.h"
#include "estado/PateandoSaltandoVertical.h"
#include "estado/PateandoSaltandoDiagonalDerecha.h"
#include "estado/PateandoSaltandoDiagonalIzquierda.h"
#include "estado/Gancho.h"
#include "estado/PiniaAlta.h"
#include "estado/PiniaBaja.h"
#include "estado/PiniaSaltandoDiagonalDerecha.h"
#include "estado/PiniaSaltandoDiagonalIzquierda.h"
#include "estado/PiniaSaltandoVertical.h"
#include "estado/SaltandoOblicuoDerecha.h"
#include "estado/SaltandoOblicuoIzquierda.h"
#include "estado/SaltandoVertical.h"
#include "Objeto.h"

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_HORIZONTAL_CAMINANDO 215.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_VELOCIDAD_NULA Vector2f(0, 0)
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

Personaje::Personaje(string idIn, double anchoIn, double altoIn, Vector2f posInicial, Posicionable* posc, int numJugador, map<estado_personaje, BVH*>* cajas) :
    Colisionable(posInicial, anchoIn, altoIn), id(idIn), posicionInicial(posInicial), ancho(anchoIn), alto(altoIn),
	estado(new EnEspera(posInicial, (*cajas)[EN_ESPERA])), posicionable(posc), numeroJugador(numJugador), cajasPorEstado(cajas){
	this->energia = ENERGIA_INICIAL;
	this->tiempoBloqueo = 0;
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
	Vector2f P1(posicion.X(), posicion.Y() + getAlto());
	Vector2f P2 = VentanaGrafica::Instance()->calcularPosicionEnVentana(P1);
	return P2;
}

bool Personaje::llegoAlLimiteIzquierdo(){
	return VentanaGrafica::Instance()->llegoAlLimiteIzquierdo(this->posicion.X()-this->getAncho()*0.05);
}

bool Personaje::llegoAlLimiteDerecho(){
	return VentanaGrafica::Instance()->llegoAlLimiteDerecho(Vector2f(this->posicion.X()+this->getAncho()*1.05,this->posicion.Y()));
}

void Personaje::caminarDerecha(){
    cambiarEstado(new CaminandoDerecha(posicion, llegoAlLimiteDerecho(), (*cajasPorEstado)[CAMINANDO_DERECHA]));
    Logger::getInstance()->debug("Personaje: caminando derecha. Se setea trayectoria.");
}

void Personaje::caminarIzquierda(){
    cambiarEstado(new CaminandoIzquierda(posicion, llegoAlLimiteIzquierdo(), (*cajasPorEstado)[CAMINANDO_IZQUIERDA]));
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
    //recibirDanio(10);
}

void Personaje::piniaAlta(){
    cambiarEstado(new PiniaAlta(posicion, (*cajasPorEstado)[PINIA_ALTA]));
	Logger::getInstance()->debug("Personaje: golpe alto.");
	//VentanaGrafica::Instance()->vibrar();
}

void Personaje::piniaBaja(){
    cambiarEstado(new PiniaBaja(posicion, (*cajasPorEstado)[PINIA_BAJA]));
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
	bloquearPersonaje(50);
	Logger::getInstance()->debug("Personaje: patada alta.");
}

void Personaje::patadaBaja(){
    cambiarEstado(new PatadaBaja(posicion, (*cajasPorEstado)[PATEANDO_BAJO]));
    bloquearPersonaje(50);
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
    cambiarEstado(new Cayendo(posicion, Vector2f(0.0f, velocActual.Y()), id, (*cajasPorEstado)[id]));
}

void Personaje::arrastrar(Colisionable* otro){
//    estado->reducirVelocidad();
    Vector2f diferencia(posicionCandidata.X() - posicionAnterior.X(), posicionCandidata.Y() - posicionAnterior.Y());
    Direccion direccionEmpuje = (estado->Id() == CAMINANDO_DERECHA) ? DIR_DERECHA : DIR_IZQUIERDA;
    if (otro->empujar(direccionEmpuje, diferencia))
        posicion = posicionCandidata;
}

bool Personaje::empujar(Direccion direccionEmpuje, Vector2f diferencia) {
    if (estaAtacando())
        return false;

    estado_personaje proxEstado = (direccionEmpuje == DIR_DERECHA) ? CAMINANDO_DERECHA : CAMINANDO_IZQUIERDA;
    if (estado->Id() == CAMINANDO_DERECHA && proxEstado == CAMINANDO_IZQUIERDA)
        return false;
    if (estado->Id() == CAMINANDO_IZQUIERDA && proxEstado == CAMINANDO_DERECHA)
        return false;

    posicionCandidata.setCoordenada(posicion.X() + diferencia.X(), posicion.Y() + diferencia.Y());
    if (estaEnReposo() && posicionable->esValida(posicionCandidata, estado->calcularAncho())){
        posicion = posicionCandidata;
        return true;
    }
    return false;
}

void Personaje::colisionar(Colisionable* otro){
    if (estaAtacando()) {
        ataqueActual = estado->obtenerAtaque();
        cout << "atacando"<<endl;
    } else if (estaDefendiendo()) {
        recibirDanio(otro->obtenerAtaque()->obtenerDanio() / 2);
    } else if (estaCaminando()) {
        arrastrar(otro);
    } else {
        recibirDanio(otro->obtenerAtaque()->obtenerDanio());
        cout << "recibiendo ataque"<<endl;
    }
    Colisionable::colisionar(otro);
}

bool Personaje::vaAColisionar(Colisionable* enemigo){
	double anchoFict = estado->calcularAncho();
	double altoFict = estado->calcularAncho();
    if (Colisionable::vaAColisionar(enemigo, anchoFict, altoFict))
        return true;
    return estado->haySuperposicion(enemigo->obtenerCajaColision());
}

void Personaje::calcularPosicionSinColision(Colisionable* enemigo){
	float distanciaAObjetivo = posicionCandidata.X() - enemigo->getPosicion().X();
	if (distanciaAObjetivo < 0) distanciaAObjetivo = -distanciaAObjetivo;

    if (posicionable->esValida(posicionCandidata, estado->calcularAncho()) && posicionCandidata.Y() >= posicionInicial.Y()) {

        if (! posicionable->enExtremos(distanciaAObjetivo, ancho)){
            posicion = posicionCandidata;
        }else{
            posicion = Vector2f(posicion.X(), posicionCandidata.Y());
        }
	} else if (posicionCandidata.Y() < posicionInicial.Y()) {
	    if (! posicionable->enExtremos(distanciaAObjetivo, ancho)) {
            posicion = Vector2f(posicionCandidata.X(), posicionInicial.Y());
	    } else {
            posicion = Vector2f(posicion.X(), posicionInicial.Y());
	    }
	    mantenerReposo();
    } else if (posicionCandidata.Y() > posicionInicial.Y()) {
        caer();
    } else {
        mantenerReposo();
    }
}

void Personaje::calcularNuevaPosicion(Colisionable* enemigo){
    posicionCandidata = estado->obtenerProximaPosicion();

    if (! vaAColisionar(enemigo)) {
        calcularPosicionSinColision(enemigo);
        return;
    }
    if (! estaAtacando() && ! estaSaltando()){
        arrastrar(enemigo);
    } else if (! estaAtacando()) {
        caer();
    } else {
        colisionar(enemigo);
    }
}

void Personaje::update(Colisionable* enemigo){
	Logger::getInstance()->debug("Personaje: update.");

    if(estaBloqueado()){
        cout << "entrar" << endl;
        if(tiempoBloqueo <= 0){
           mantenerReposo();
        }
        tiempoBloqueo -= 1.0;
    }

    arma->update();
    posicionAnterior = posicion;
    calcularNuevaPosicion(enemigo);
//    corregirPorColision(enemigo);
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
void Personaje::arrojarArma(){
	//Posiciono el poder respecto a la posicion del personaje
	Vector2f posicionObjeto(posicion.X()+ancho,alto);
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
	cambiarEstado(new Bloqueado(estado->Id(), estado->getTrayectoria(), estado->obtenerCajaColision()));
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
//	this->trayectoria = new Reposo(this->posicion);
}

//void Personaje::agregarCajasColisiones(BVH* caja, estado_personaje estadoCaja){
//    cajasPorEstado[estadoCaja] = caja;
//}
