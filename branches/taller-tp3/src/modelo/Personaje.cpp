/*
 * Personaje.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Personaje.h"

#include <map>
#include <sstream>
#include <utility>

#include "../Sonidos.h"
#include "estado/Estado.h"
#include "fisica/BVH.h"

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_HORIZONTAL_CAMINANDO 215.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_VELOCIDAD_NULA Vector2f(0, 0)
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)
#define VELOCIDAD_CAIDA_SUAVE 200
#define VELOCIDAD_ARROJADO Vector2f(400.0f, 800.0f)
#define VELOCIDAD_HORIZONTAL_ANIMALITY 300
#define VELOCIDAD_VERTICAL_ANIMALITY 650
#define AJUSTE_ALTURA_ARMA 0.67

#define TIEMPO_BLOQUEO_PATADA 35
#define TIEMPO_BLOQUEO_GOLPE 25
#define TIEMPO_BLOQUEO_DERRIBADO 55
#define TIEMPO_BLOQUEO_GANCHO 15
#define TIEMPO_BLOQUEO_PATADA_GIRATORIA 45
#define TIEMPO_BLOQUEO_TIJERA 80
#define TIEMPO_BLOQUEO_ANIMALITY_SUBZERO_PARTE1 30
#define TIEMPO_BLOQUEO_ANIMALITY_SUBZERO_PARTE2 20
#define TIEMPO_BLOQUEO_ANIMALITY_SUBZERO_PARTE3 60
#define TIEMPO_BLOQUEO_ANIMALITY_SUBZERO_PARTE4 60
#define TIEMPO_FESTEJO_VICTORIA 200
#define DISTANCIA_MINIMA 125
#define DISTANCIA_ANIMALITY_SUBZERO 110
#define DISTANCIA_ANIMALITY_SONYA 300
#define AJUSTE_ALTO_EXPLOSION_SANGRE 30

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
	this->enFatality = false;

	// ORIENTACION INICIAL DE BVH - POR DEFECTO LA ORIENTACION ES DERECHA
	this->direccion = DIRECCION_DERECHA;
}

Personaje::~Personaje(){
//    delete trayectoria;
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

Vector2f Personaje::getPosicion(){
	return this->posicion;
}

void Personaje::setPosicion(double x, double y) {
	this->posicion.setCoordenada(x,y);
}

void Personaje::agregarArma(Objeto* unArma){
	this->arma = unArma;
	Vector2f posicionObjeto(posicion.X()+ancho,alto);
	arma->posicionar(posicionObjeto);
}

int Personaje::getEnergia(){
	return this->energia;
}

Objeto* Personaje::getArma(){
	return arma;
}

void Personaje::agregarObservador(Observador* unObservador){
	Observable::agregarObservador(unObservador);
}

void Personaje::notificarObservadores(){
	Observable::notificarObservadores();
}

//Devuelve un vector posicion referenciado desde el eje con origen de coordenadas arriba izquierda.
Vector2f Personaje::obtenerPosicionEnVentana(){
	//Vector2f P1(getPivote().X(), getPivote().Y());
	//Vector2f P1(posicion.X(), posicion.Y() + getAlto()); // TODO: ESTE ES EL ORIGINAL, EL DE ABAJO USA PIVOTE.
	Vector2f P1(getPivote().X(), posicion.Y() + getAlto());
	Vector2f P2 = VentanaGrafica::Instance()->calcularPosicionEnVentana(P1);
	return P2;
}

void Personaje::cambiarNumeroPersonaje(){
	if(this->numeroJugador == NUMERO_DE_PERSONAJE_1){
		this->numeroJugador = NUMERO_DE_PERSONAJE_2;
	}else{
		this->numeroJugador = NUMERO_DE_PERSONAJE_1;
	}
}

bool Personaje::llegoAlLimiteIzquierdo(){
	return VentanaGrafica::Instance()->llegoAlLimiteIzquierdo(Vector2f(posicion.X() - getAnchoEnvolvente()/2, posicion.Y()));
}

bool Personaje::llegoAlLimiteDerecho(){
	return VentanaGrafica::Instance()->llegoAlLimiteDerecho(Vector2f(posicion.X() + getAnchoEnvolvente()/2, posicion.Y()));
}

////////Estados////////
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

bool Personaje::estaEnPiso(){
    return (estado->estaEnPiso());
}

bool Personaje::haciendoFatality(){
	return (estado->haciendoFatality());
}

bool Personaje::recibioFatality(){
	return (estado->recibioFatality());
}

bool Personaje::estaSinEnergia(){
    return (this->energia <= 0);
}

bool Personaje::estaMareado(){
	 return (estado->estaMareado());
}

bool Personaje::estaMuerto(){
	 return (estado->estaMuerto());
}

bool Personaje::estaHaciendoToma(){
	return (estado->estaHaciendoToma());
}

bool Personaje::ejecutandoMovimientoEspecial(){
	return (estado->ejecutandoMovimientoEspecial());
}

bool Personaje::efectuandoPatadaGiratoria(){
	return (estado->efectuandoPatadaGiratoria());
}

bool Personaje::estaVolandoVertical(){
	return(estado->estaVolandoVertical());
}

bool Personaje::esGanador(){
	return(estado->esGanador());
}

bool Personaje::estaEnFatality(){
	return(this->enFatality);
}

bool Personaje::estaInhabilitado(){
    return (estado->Id() == PINIA_ALTA) || (estado->Id() == PINIA_BAJA) || (estado->Id() == GANCHO);
}

void Personaje::cambiarEstado(Estado* nuevo) {
    //delete estado;
    estado = nuevo;
}

estado_personaje Personaje::getEstado(){
	return ((estado_personaje) estado->Id());
}

Estado* Personaje::verEstado(){
	return estado;
}

////Movimientos y poderes////
void Personaje::caminarDerecha(){
    cambiarEstado(new CaminandoDerecha(posicion, (*cajasPorEstado)[CAMINANDO_DERECHA], direccion));
    Logger::getInstance()->debug("Personaje: caminando derecha. Se setea trayectoria.");
}

void Personaje::caminarIzquierda(){
    cambiarEstado(new CaminandoIzquierda(posicion, (*cajasPorEstado)[CAMINANDO_IZQUIERDA], direccion));
    Logger::getInstance()->debug("Personaje: caminando izquierda. Se setea trayectoria.");
}

void Personaje::saltarVertical(){
    cambiarEstado(new SaltandoVertical(posicion, (*cajasPorEstado)[SALTANDO_VERTICAL]));
    // TODO by ariel: tomarlo desde un hash de sonidos para no cargar el archivo de sonido
    if(id == "sonya"){
       	Sonidos::getInstancia()->reproducirSonido("sonido_saltar_sonya");
    }
    Logger::getInstance()->debug("Personaje: salto vertical. Se setea trayectoria.");
}

void Personaje::saltarOblicuoDerecha(){
    cambiarEstado(new SaltandoOblicuoDerecha(posicion, (*cajasPorEstado)[SALTANDO_OBLICUO_DERECHA]));
    if(id == "sonya"){
       Sonidos::getInstancia()->reproducirSonido("sonido_saltar_sonya");
    }
    Logger::getInstance()->debug("Personaje: salto oblicuo derecha. Se setea trayectoria.");
}

void Personaje::saltarOblicuoIzquierda(){
    cambiarEstado(new SaltandoOblicuoIzquierda(posicion, (*cajasPorEstado)[SALTANDO_OBLICUO_IZQUIERDA]));
    if(id == "sonya"){
        Sonidos::getInstancia()->reproducirSonido("sonido_saltar_sonya");
    }
    Logger::getInstance()->debug("Personaje: salto oblicuo izquierda. Se setea trayectoria.");
}

void Personaje::agacharse(){
    cambiarEstado(new Agachado(posicion, (*cajasPorEstado)[AGACHADO]));
    Logger::getInstance()->debug("Personaje: agachado.");
}

void Personaje::piniaAlta(){
    cambiarEstado(new PiniaAlta(posicion, (*cajasPorEstado)[PINIA_ALTA]));
    bloquearPersonaje(TIEMPO_BLOQUEO_GOLPE);
    if(id == "sonya"){
    	Sonidos::getInstancia()->reproducirSonido("sonido_golpe_sonya");
    }else{
    	Sonidos::getInstancia()->reproducirSonido("sonido_pinia");
    }
	Logger::getInstance()->debug("Personaje: golpe alto.");
}

void Personaje::piniaBaja(){
    cambiarEstado(new PiniaBaja(posicion, (*cajasPorEstado)[PINIA_BAJA]));
    bloquearPersonaje(TIEMPO_BLOQUEO_GOLPE);
    if(id == "sonya"){
    	Sonidos::getInstancia()->reproducirSonido("sonido_golpe_sonya");
    }else{
    	Sonidos::getInstancia()->reproducirSonido("sonido_pinia");
    }
	Logger::getInstance()->debug("Personaje: golpe bajo.");
}

void Personaje::piniaSaltandoDiagonalDerecha(){
    cambiarEstado(new PiniaSaltandoDiagonalDerecha(estado->getTrayectoria(), estado->obtenerTiempoDeCreacion(), (*cajasPorEstado)[PINIA_SALTANDO_DIAGONAL_DERECHA]));
    if(id == "sonya"){
      Sonidos::getInstancia()->reproducirSonido("sonido_golpe_sonya");
    }else{
      Sonidos::getInstancia()->reproducirSonido("sonido_pinia");
    }
	Logger::getInstance()->debug("Personaje: piña saltando.");
}

void Personaje::piniaSaltandoDiagonalIzquierda(){
    cambiarEstado(new PiniaSaltandoDiagonalIzquierda(estado->getTrayectoria(), estado->obtenerTiempoDeCreacion() , (*cajasPorEstado)[PINIA_SALTANDO_DIAGONAL_IZQUIERDA]));
    if(id == "sonya"){
      Sonidos::getInstancia()->reproducirSonido("sonido_golpe_sonya");
    }else{
      Sonidos::getInstancia()->reproducirSonido("sonido_pinia");
    }
	Logger::getInstance()->debug("Personaje: piña saltando.");
}

void Personaje::piniaSaltandoVertical(){
    cambiarEstado(new PiniaSaltandoVertical(estado->getTrayectoria(), estado->obtenerTiempoDeCreacion(), (*cajasPorEstado)[PINIA_SALTANDO_VERTICAL]));
    if(id == "sonya"){
       Sonidos::getInstancia()->reproducirSonido("sonido_golpe_sonya");
    }else{
       Sonidos::getInstancia()->reproducirSonido("sonido_pinia");
    }
	Logger::getInstance()->debug("Personaje: piña saltando.");
}

void Personaje::patadaAlta(){
	cambiarEstado(new PatadaAlta(posicion, (*cajasPorEstado)[PATEANDO_ALTO]));
	bloquearPersonaje(TIEMPO_BLOQUEO_PATADA);
	 if(id == "sonya"){
	    Sonidos::getInstancia()->reproducirSonido("sonido_golpe_sonya");
	}else{
	    Sonidos::getInstancia()->reproducirSonido("sonido_pinia");
	}
	Logger::getInstance()->debug("Personaje: patada alta.");
}

void Personaje::patadaBaja(){
    cambiarEstado(new PatadaBaja(posicion, (*cajasPorEstado)[PATEANDO_BAJO]));
    bloquearPersonaje(TIEMPO_BLOQUEO_PATADA);
    if(id == "sonya"){
       	Sonidos::getInstancia()->reproducirSonido("sonido_golpe_sonya");
    }else{
       Sonidos::getInstancia()->reproducirSonido("sonido_pinia");
    }
	Logger::getInstance()->debug("Personaje: patada baja.");
}

void Personaje::patadaAltaAgachado(){
	cambiarEstado(new PateandoAltoAgachado(posicion, (*cajasPorEstado)[PATEANDO_ALTO_AGACHADO]));
	Logger::getInstance()->debug("Personaje: patada alta agachado.");
}

void Personaje::patadaGiratoria(){
	cambiarEstado(new PatadaGiratoria(posicion, (*cajasPorEstado)[PATEANDO_ALTO_AGACHADO]));
	bloquearPersonaje(TIEMPO_BLOQUEO_PATADA_GIRATORIA);
	Logger::getInstance()->debug("Personaje: patada giratoria.");
}

void Personaje::patadaSaltandoVertical(){
    cambiarEstado(new PateandoSaltandoVertical(estado->getTrayectoria(), estado->obtenerTiempoDeCreacion(), (*cajasPorEstado)[PATEANDO_SALTANDO_VERTICAL]));
    Sonidos::getInstancia()->reproducirSonido("sonido_patada");
	Logger::getInstance()->debug("Personaje: patada.");
}

void Personaje::patadaSaltandoDiagonalDerecha(){
    cambiarEstado(new PateandoSaltandoDiagonalDerecha(estado->getTrayectoria(), estado->obtenerTiempoDeCreacion(), (*cajasPorEstado)[PATEANDO_SALTANDO_DIAGONAL_DERECHA]));
    Sonidos::getInstancia()->reproducirSonido("sonido_patada");
	Logger::getInstance()->debug("Personaje: patada.");
}

void Personaje::patadaSaltandoDiagonalIzquierda(){
    cambiarEstado(new PateandoSaltandoDiagonalIzquierda(estado->getTrayectoria(), estado->obtenerTiempoDeCreacion(), (*cajasPorEstado)[PATEANDO_SALTANDO_DIAGONAL_IZQUIERDA]));
    Sonidos::getInstancia()->reproducirSonido("sonido_patada");
	Logger::getInstance()->debug("Personaje: patada.");
}

void Personaje::gancho(){
	cambiarEstado(new Gancho(posicion, (*cajasPorEstado)[GANCHO]));
	Sonidos::getInstancia()->reproducirSonido("sonido_gancho");
	bloquearPersonaje(TIEMPO_BLOQUEO_GANCHO);
    Logger::getInstance()->debug("Personaje: gancho.");
}

void Personaje::ganchoFatality(){
	hacerFatality(FATALITY1);
	Sonidos::getInstancia()->reproducirSonido("sonido_gancho");
	bloquearPersonaje(TIEMPO_BLOQUEO_GANCHO);
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

void Personaje::caidaDerecha(){
    Estado* caida = new CaidaDerecha(posicion, (*cajasPorEstado)[CAIDA_DERECHA]);

	if (! posicionable->esValida(posicion, caida->calcularAncho()))
        caida->agregarCajaColision((*cajasPorEstado)[SALTANDO_VERTICAL]);

	cambiarEstado(caida);
}

void Personaje::caidaIzquierda(){
    Estado* caida = new CaidaIzquierda(posicion, (*cajasPorEstado)[CAIDA_IZQUIERDA]);
    if (! posicionable->esValida(posicion, caida->calcularAncho()))
        caida->agregarCajaColision((*cajasPorEstado)[SALTANDO_VERTICAL]);

	cambiarEstado(caida);
}

void Personaje::ser_arrojado_derecha(){
    Estado* caida = new CaidaDerecha(posicion, ARROJADO, (*cajasPorEstado)[CAIDA_DERECHA], VELOCIDAD_ARROJADO);

	if (! posicionable->esValida(posicion, caida->calcularAncho()))
        caida->agregarCajaColision((*cajasPorEstado)[SALTANDO_VERTICAL]);

	cambiarEstado(caida);
}

void Personaje::ser_arrojado_izquierda(){
    Estado* caida = new CaidaIzquierda(posicion, ARROJADO, (*cajasPorEstado)[CAIDA_IZQUIERDA], VELOCIDAD_ARROJADO);
    if (! posicionable->esValida(posicion, caida->calcularAncho()))
        caida->agregarCajaColision((*cajasPorEstado)[SALTANDO_VERTICAL]);

	cambiarEstado(caida);
}
void Personaje::golpeado(){
	cambiarEstado(new Golpeado(posicion, (*cajasPorEstado)[RECIBIENDO_GOLPE]));
	bloquearPersonaje(TIEMPO_BLOQUEO_GOLPE);
	sangrar();
}

void Personaje::derribado(){
	cambiarEstado(new Golpeado(posicion, DERRIBADO,(*cajasPorEstado)[RECIBIENDO_GOLPE]));
	bloquearPersonaje(TIEMPO_BLOQUEO_DERRIBADO);
}

void Personaje::mareado(){
	cambiarEstado(new Mareado(posicion, (*cajasPorEstado)[RECIBIENDO_GOLPE]));
	Sonidos::getInstancia()->reproducirSonido("sonido_finish");
}

void Personaje::sangrar(){
	//Posiciono el poder respecto a la posicion del personaje

	if(estado->Id() == MUERTO_EN_PISO){
		//Ejecuto explosion de sangre
		Vector2f posicionEfecto;
		if(this->direccion == DIRECCION_DERECHA){
			posicionEfecto.setCoordenada(posicion.X() - estado->calcularAncho()/2, posicion.Y()+40);
		}else{
			posicionEfecto.setCoordenada(posicion.X() + estado->calcularAncho()/2, posicion.Y()+40);
		}
		EfectosEspeciales::Instance()->ejecutarEfecto("explosion-sangre", posicionEfecto, direccion);
	}else if(estado->Id() == MUERTO_DECAPITADO){
		//Ejecuto explosion de sangre
		Vector2f posicionEfecto;
		if(this->direccion == DIRECCION_DERECHA){
			posicionEfecto.setCoordenada(posicion.X() + estado->calcularAncho()*2, posicion.Y()-60);
			EfectosEspeciales::Instance()->ejecutarEfecto("sangre", posicionEfecto, DIRECCION_IZQUIERDA);
		}else{
			posicionEfecto.setCoordenada(posicion.X() - estado->calcularAncho()*2, posicion.Y()-60);
			EfectosEspeciales::Instance()->ejecutarEfecto("sangre", posicionEfecto, DIRECCION_DERECHA);
		}
	}else if(estado->Id() == DECAPITADO){
		//Ejecuto explosion de sangre
		Vector2f posicionEfecto;
		if(this->direccion == DIRECCION_DERECHA){
			posicionEfecto.setCoordenada(posicion.X() - estado->calcularAncho()/3, posicion.Y()+ estado->calcularAlto()-AJUSTE_ALTO_EXPLOSION_SANGRE);
		}else{
			posicionEfecto.setCoordenada(posicion.X() + estado->calcularAncho()/3, posicion.Y() + estado->calcularAlto()-AJUSTE_ALTO_EXPLOSION_SANGRE);
		}
		EfectosEspeciales::Instance()->ejecutarEfecto("explosion-sangre", posicionEfecto, direccion);
	}else if(estado->Id() != CAIDA_DERECHA){
		Vector2f posicionEfecto;
		if(this->direccion == DIRECCION_DERECHA){
			posicionEfecto.setCoordenada(posicion.X() - estado->calcularAncho()/2, posicion.Y()+ estado->calcularAlto()/2);
		}else{
			posicionEfecto.setCoordenada(posicion.X() + estado->calcularAncho()/2, posicion.Y() + estado->calcularAlto()/2);
		}
		EfectosEspeciales::Instance()->ejecutarEfecto("sangre", posicionEfecto, direccion);
	}
}

void Personaje::retroceder(){
	cambiarEstado(new Golpeado(posicion, RECIBIENDO_PINIA_RETROCEDIENDO, (*cajasPorEstado)[RECIBIENDO_GOLPE]));
	bloquearPersonaje(TIEMPO_BLOQUEO_GOLPE);
}

void Personaje::victoria(){
	if(estado->Id() == ANIMALITY2){
		cambiarEstado(new EnEspera(posicion, ANIMALITY2, (*cajasPorEstado)[EN_ESPERA]));
	}else{
		cambiarEstado(new EnEspera(posicion, VICTORIA, (*cajasPorEstado)[EN_ESPERA]));
	}
	if(id == "sonya"){
		Sonidos::getInstancia()->reproducirSonido("sonido_sonya_win");
	}else{
		Sonidos::getInstancia()->reproducirSonido("sonido_subzero_win");
	}
	bloquearPersonaje(TIEMPO_FESTEJO_VICTORIA);
}

void Personaje::morir(){
	if(recibioFatality()){
		cambiarEstado(new Muerto(posicion, estado->Id(), (*cajasPorEstado)[EN_ESPERA]));
	}else{
		cambiarEstado(new EnEspera(posicion, MUERTO, (*cajasPorEstado)[EN_ESPERA]));
	}
	bloquearPersonaje(TIEMPO_FESTEJO_VICTORIA);
}

void Personaje::deslizar(){
	cambiarEstado(new Deslizar(posicion, SLIDE, (*cajasPorEstado)[SALTANDO_VERTICAL], direccion));
	if(id == "sonya"){
		Sonidos::getInstancia()->reproducirSonido("sonido_golpe2_sonya");
	}else{
		Sonidos::getInstancia()->reproducirSonido("sonido_subzero_win");
	}
	bloquearPersonaje(50);
}

void Personaje::volar_horizontal(estado_personaje id_estado){
	cambiarEstado(new Deslizar(posicion, id_estado, (*cajasPorEstado)[estado->Id()], direccion, VELOCIDAD_HORIZONTAL_ANIMALITY));
	bloquearPersonaje(50);
}

void Personaje::volar_vertical(estado_personaje id_estado, estado_personaje id_estado_caja){
	cambiarEstado(new VueloVertical(posicion, id_estado, (*cajasPorEstado)[id_estado_caja]));
}

void Personaje::volar_vertical(estado_personaje id_estado){
	cambiarEstado(new VueloVertical(posicion, id_estado, (*cajasPorEstado)[id_estado]));
}


void Personaje::tijera(){
	cambiarEstado(new TomandoOponente(posicion, TIJERA, (*cajasPorEstado)[EN_ESPERA]));
	Sonidos::getInstancia()->reproducirSonido("sonido_deslizar");
	bloquearPersonaje(TIEMPO_BLOQUEO_TIJERA);
}

void Personaje::morirEnPiso(){
	VentanaGrafica::Instance()->vibrar();
	if(estado->Id() == RECIBIENDO_GOLPE){
		cambiarEstado(new Muerto(posicion, MUERTO_EN_PISO,(*cajasPorEstado)[EN_ESPERA]));
		sangrar();
	}else{
		cambiarEstado(new Muerto(posicion, MUERTO_EN_PISO,(*cajasPorEstado)[EN_ESPERA]));
	}
    bloquearPersonaje(TIEMPO_FESTEJO_VICTORIA);
}

void Personaje::morirEnPiso(estado_personaje id_estado){
    cambiarEstado(new Muerto(posicion, id_estado,(*cajasPorEstado)[EN_ESPERA]));
    bloquearPersonaje(TIEMPO_FESTEJO_VICTORIA);
}

void Personaje::mantenerReposo(){
    cambiarEstado(new EnEspera(posicion, (*cajasPorEstado)[EN_ESPERA]));
    Logger::getInstance()->debug("Personaje: en reposo.");
}

void Personaje::bebe(){
	cambiarEstado(new Fatality(posicion, BEBE, (*cajasPorEstado)[EN_ESPERA]));
	Sonidos::getInstancia()->reproducirSonido("sonido_bebe");
	//bloquearPersonaje(TIEMPO_FESTEJO_VICTORIA);
}

void Personaje::animality(){
	if(id == "sonya"){
		cambiarEstado(new Fatality(posicion, ANIMALITY, (*cajasPorEstado)[ANIMALITY]));
		bloquearPersonaje(50);
	}else{
		cambiarEstado(new Fatality(posicion, OSO, (*cajasPorEstado)[OSO]));
		bloquearPersonaje(TIEMPO_BLOQUEO_ANIMALITY_SUBZERO_PARTE1);
	}
}

void Personaje::tirar_beso(){
	hacerFatality(FATALITY1);
	bloquearPersonaje(25);
}

void Personaje::decapitar(){
	cambiarEstado(new RecibiendoFatality(posicion, DECAPITADO, (*cajasPorEstado)[EN_ESPERA]));
	bloquearPersonaje(50);
	sangrar();
	VentanaGrafica::Instance()->vibrar();
}

void Personaje::mantenerFatality(estado_personaje id_estado){
	if(id_estado == MUERTO_EN_PISO){
		sangrar();
	}
	cambiarEstado(new RecibiendoFatality(posicion, id_estado, (*cajasPorEstado)[EN_ESPERA]));
}

void Personaje::hacerFatality(){
	cambiarEstado(new Fatality(posicion, estado->Id(), (*cajasPorEstado)[estado->Id()]));
}

void Personaje::hacerFatality(estado_personaje id_estado){
	cambiarEstado(new Fatality(posicion, id_estado, (*cajasPorEstado)[estado->Id()]));
}

void Personaje::updateFatality(Colisionable* enemigo){
	if(estado->Id()== ANIMALITY){
		if(!estaBloqueado()){
			volar_horizontal(ANIMALITY2);
		}
	}else if(estado->Id()== ANIMALITY2 && !estaVolandoVertical()){
		if(!estaBloqueado()){
			volar_vertical(ANIMALITY2, ANIMALITY);
		}
	}else if(estado->Id()== OSO){
		if(!estaBloqueado()){
			hacerFatality(OSO2);
			bloquearPersonaje(TIEMPO_BLOQUEO_ANIMALITY_SUBZERO_PARTE2);
		}
	}else if(estado->Id()== OSO2){
		if(!estaBloqueado()){
			hacerFatality(OSO_ATACANDO);
			bloquearPersonaje(TIEMPO_BLOQUEO_ANIMALITY_SUBZERO_PARTE3);
		}
	}else if(estado->Id()== OSO_ATACANDO){
		if(!estaBloqueado()){
			hacerFatality(OSO3);
			bloquearPersonaje(TIEMPO_BLOQUEO_ANIMALITY_SUBZERO_PARTE4);
		}
	}else if(recibioFatality() && estado->Id() == CAIDA_DERECHA && !estaBloqueado()){
		mantenerFatality(MUERTO_EN_PISO);
		sangrar();
		bloquearPersonaje(TIEMPO_BLOQUEO_ANIMALITY_SUBZERO_PARTE3+TIEMPO_BLOQUEO_ANIMALITY_SUBZERO_PARTE4);
	}else if(!estaMuerto() && recibioFatality() && estado->Id() == MUERTO_EN_PISO && !estaBloqueado()){
		morirEnPiso(MUERTO_EN_PISO);
	}else if(estado->Id() == DECAPITADO && !estaBloqueado()){
		morirEnPiso(MUERTO_DECAPITADO);
		sangrar();
	}else if(estado->Id()== FATALITY1){
		if(!estaBloqueado() && id == "sonya"){

		}else if(!estaBloqueado()){
			hacerFatality(GANCHO_FATALITY);
			bloquearPersonaje(50);
		}
	}
}

void Personaje::recibirFatality(Colisionable* enemigo){
	if(enemigo->verEstado()->estaVolandoVertical()){
		volar_vertical(RECIBIENDO_GOLPE);
		enFatality = true;
	}else if(enemigo->verEstado()->Id() == GANCHO_FATALITY){
		decapitar();
		enFatality = true;
	}else if(enemigo->verEstado()->Id() == OSO2){
		caida_animality();
		enFatality = true;
		bloquearPersonaje(TIEMPO_BLOQUEO_ANIMALITY_SUBZERO_PARTE2);
	}
}

void Personaje::caer(){
	if(haciendoFatality()){
		mantenerFatality(estado->Id());
	}else{
		Vector2f velocActual = estado->obtenerVelocidad();
		estado_personaje id = estado->Id();
		BVH* cajas = estado->obtenerCajaColision();
		cambiarEstado(new Cayendo(posicion, Vector2f(0, velocActual.Y()), id, cajas));
	}
}

void Personaje::caida_animality(){
	cambiarEstado(new RecibiendoFatality(posicion, CAIDA_DERECHA,(*cajasPorEstado)[EN_ESPERA]));
	bloquearPersonaje(50);
}

void Personaje::arrastrar(Colisionable* otro){
    Vector2f diferencia = posicionCandidata - posicion;
    if (diferencia.Y() != 0)
        diferencia.setCoordenada(diferencia.X(), 0);
    if ((posicion.X() < otro->getPosicion().X() && estado->Id() == CAMINANDO_IZQUIERDA) ||
        (posicion.X() > otro->getPosicion().X() && estado->Id() == CAMINANDO_DERECHA)) {
        if (posicionable->esValida(posicionCandidata, getAnchoEnvolvente()))
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

void Personaje::bloquearPersonaje(float segundos){
	cambiarEstado(new Bloqueado(estado));
	this->tiempoBloqueo = segundos;
}

void Personaje::recibirDanio(int danio){
	this->energia -= danio;
}

void Personaje::recibirGolpe(Colisionable* otro){
	if(otro->ejecutandoMovimientoEspecial()){
		if(otro->verEstado()->estaTomandoAlOponente()){
			if(this->direccion == DIRECCION_IZQUIERDA){
				ser_arrojado_izquierda();
			}else if(this->direccion == DIRECCION_DERECHA){
				ser_arrojado_derecha();
			}
		}else if(otro->verEstado()->efectuandoGancho() || otro->verEstado()->estaSaltando()){
			if(this->direccion == DIRECCION_IZQUIERDA){
				caidaDerecha();
			}else if(this->direccion == DIRECCION_DERECHA){
				caidaIzquierda();
			}
			VentanaGrafica::Instance()->vibrar();
		//Si el oponente pega una patada:
		}else if(otro->verEstado()->efectuandoPatadaGiratoria()){
			derribado();
		}else if(otro->verEstado()->estaTomandoAlOponente()){
			//ser_arrojado();
			if(this->direccion == DIRECCION_IZQUIERDA){
				caidaIzquierda();
			}else if(this->direccion == DIRECCION_DERECHA){
				caidaDerecha();
			}
		}else if(!estaSaltando()){
			golpeado();
			Vector2f vectorEmpuje = (direccion == DIRECCION_DERECHA) ? VECTOR_EMPUJE_IZQUIERDA : VECTOR_EMPUJE_DERECHA;
			if (! (llegoAlLimiteDerecho() || llegoAlLimiteIzquierdo()))
				empujar(vectorEmpuje);
		}else if(estaSaltando() && this->direccion == DIRECCION_IZQUIERDA){
		    caidaDerecha();
		    VentanaGrafica::Instance()->vibrar();
		}else if(estaSaltando() && this->direccion == DIRECCION_DERECHA){
		    caidaIzquierda();
		    VentanaGrafica::Instance()->vibrar();
		}
	}else if(estaSaltando() && this->direccion == DIRECCION_IZQUIERDA){
		caidaDerecha();
		VentanaGrafica::Instance()->vibrar();
	}else if(estaSaltando() && this->direccion == DIRECCION_DERECHA){
		caidaIzquierda();
		VentanaGrafica::Instance()->vibrar();
	}else{
		if(pegadoAlOponente(otro)){
			golpeado();
		}else{
			golpeado();
		}
	}
    Logger::getInstance()->debug("Personaje: recibiendo golpe.");
}

void Personaje::arrojarArma(){
	if(!estaSaltando()){
		cambiarEstado(new EnEspera(posicion, TIRANDO_PODER,(*cajasPorEstado)[TIRANDO_PODER]));
		bloquearPersonaje(50);
	}

	//Posiciono el poder respecto a la posicion del personaje
	Vector2f posicionObjeto;
	if(this->direccion == DIRECCION_DERECHA){
		posicionObjeto.setCoordenada(posicion.X(), posicion.Y()+ estado->calcularAlto() * AJUSTE_ALTURA_ARMA);
	}else{
		posicionObjeto.setCoordenada(posicion.X()-ancho/2, posicion.Y() + estado->calcularAlto() * AJUSTE_ALTURA_ARMA);
	}

	if(id == "sonya"){
		Sonidos::getInstancia()->reproducirSonido("sonido_arma_sonya");
	}else{
		Sonidos::getInstancia()->reproducirSonido("sonido_arma");
	}
	arma->posicionar(posicionObjeto);
	arma->arrojar();
}

void Personaje::ejecutarCombo(string nombreCombo, Personaje* enemigo){
		if(nombreCombo == "Ring Toss"){
			arrojarArma();
		}else if(nombreCombo == "Leg Grab"){
			tijera();
		}else if(nombreCombo == "Patada Giratoria"){
			patadaGiratoria();
		}else if(nombreCombo == "Ice Freeze"){
			arrojarArma();
		}else if(nombreCombo == "Slide"){
			deslizar();
		}else if(nombreCombo == "Patada Voladora"){
			deslizar();
		//FATALITY//
		}else if(enemigo->estaMareado()){
			if(nombreCombo == "Animality" && calcularProximaDistancia(enemigo) <= DISTANCIA_ANIMALITY_SONYA){
				if(id == "sonya"){
					animality();
					enFatality = true;
				}else if(id == "sub-zero" && calcularProximaDistancia(enemigo) <= DISTANCIA_ANIMALITY_SUBZERO){
					animality();
					enFatality = true;
				}
			}else if(nombreCombo == "Fatality"){
				if(id == "sonya"){
					tirar_beso();

				}else{
					if(pegadoAlOponente(enemigo)){
						ganchoFatality();
						enFatality = true;
					}
				}
			}
		}
}

////////Colision////////
void Personaje::colisionar(Colisionable* otro){
    if (estaAtacando()) {
        ataqueActual = estado->obtenerAtaque();
        if (! estado->ataqueFueEfectuado()) {
            Colisionable::colisionar(otro);
            estado->efectuarAtaque();
        }
        return;
    }
    if (! otro->estaAtacando()) return;

    int danio = otro->obtenerDanio();
    if (! danio) return;

    if (estaDefendiendo()){
    	recibirDanio(danio / 4);
    } else if (estaAgachado() && otro->estaInhabilitado()) {
    } else if (estaEnReposo() || estaCaminando()) {
    	recibirDanio(danio);
    	recibirGolpe(otro);
    } else if (estaSaltando()){
        recibirDanio(danio);
    	recibirGolpe(otro);
    } else{
        recibirDanio(danio);
    }
}

BVH* Personaje::obtenerCajaColision(){
    return estado->obtenerCajaColision();
}

bool Personaje::vaAColisionar(Colisionable* enemigo){
	double anchoFict = estado->calcularAncho();
	double altoFict = estado->calcularAlto();

	if (Colisionable::vaAColisionar(enemigo, anchoFict, altoFict)){
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
    if(estaSinEnergia()){
        morirEnPiso();
    }else{
        mantenerReposo();
    }
}

void Personaje::calcularPosicionSinColision(Colisionable* enemigo){
	float distanciaAObjetivo = calcularProximaDistancia(enemigo);

		if ((estado->Id() == SALTANDO_VERTICAL || posicionable->esValida(posicionCandidata, estado->calcularAncho())) && posicionCandidata.Y() >= posicionInicial.Y()) {
		if (! posicionable->enExtremos(distanciaAObjetivo, estado->calcularAncho())){
			posicion = posicionCandidata;
		}else{
			posicion = Vector2f(posicion.X(), posicionCandidata.Y());
		}
		} else if (posicionCandidata.Y() < posicionInicial.Y()) {
            volverAlPiso(distanciaAObjetivo);
	} else if (estado->estaDesplazandoVertical()) {
		posicion = posicionCandidata;
    } else if (posicionCandidata.Y() > posicionInicial.Y()) {
        caer();
    } else {
    	if(!haciendoFatality()){
    		mantenerReposo();
    	}
    }
}

void Personaje::espejarBVH() {
    for (map<estado_personaje, BVH*>::iterator it = this->cajasPorEstado->begin() ; it != this->cajasPorEstado->end(); ++it)
    {
    	(it)->second->espejarBVH();
    }
}

void Personaje::orientar(DireccionObjeto nuevaOrientacion) {
	if (this->direccion == nuevaOrientacion)
		return;

	this->direccion = nuevaOrientacion;
	this->arma->orientar(nuevaOrientacion);
	espejarBVH();
}

void Personaje::calcularNuevaPosicion(Colisionable* enemigo){
    posicionCandidata = estado->obtenerProximaPosicion();

    if (! vaAColisionar(enemigo)) {
        calcularPosicionSinColision(enemigo);
        return;
    }

    if(estaHaciendoToma()){
    	posicion = posicionCandidata;
    }
    else if (estaCaminando()){
        arrastrar(enemigo);
    } else if (estaSaltando()) {
        float distanciaAObjetivo = calcularDistancia(enemigo);

        if (posicionable->esValida(posicionCandidata, estado->calcularAncho())){
            posicion = posicionCandidata;
        } else if (posicionCandidata.Y() <= posicionInicial.Y()) {
            volverAlPiso(distanciaAObjetivo);
        } else if (estado->estaDesplazandoVertical()) {
        	posicion = posicionCandidata;
        } else {
            caer();
        }
        if (estaAtacando())
            colisionar(enemigo);
    } else {
    	//cout<<"COLISIONAR"<<endl;
        colisionar(enemigo);
    }
 }

void Personaje::update(Colisionable* enemigo){
    Logger::getInstance()->debug("Personaje: update.");
    if(estaEnPiso() ){
       return;

	}else if((haciendoFatality() || recibioFatality()) && !estaBloqueado()){
		updateFatality(enemigo);
	}
	else if(estaMareado() && !recibioFatality()){
    	if(enemigo->verEstado()->haciendoFatality()){
    		recibirFatality(enemigo);
    	}
    }

    else if(estaSinEnergia() && !estaMuerto() && !estaSaltando() && !estaEnPiso() && !haciendoFatality() && !estaMareado() && !recibioFatality() && !estaVolandoVertical()){
    	mareado();
    }

    if(estaBloqueado()){
        if(tiempoBloqueo <= 0){
        	if(haciendoFatality()){
        		hacerFatality();
        	}else if(recibioFatality()){
        		mantenerFatality(estado->Id());
        	}else{
        		mantenerReposo();
        	}
        }
        tiempoBloqueo -= 1.0;
    }

    posicionAnterior = posicion;
    calcularNuevaPosicion(enemigo);
    estado->actualizar(posicion);
    arma->update(enemigo);

    notificarObservadores();
}


float Personaje::getAnchoEnvolvente() {
	return this->estado->calcularAncho();
}

float Personaje::getAltoEnvolvente() {
	return this->estado->calcularAlto();
}

bool Personaje::pegadoAlOponente(Colisionable* enemigo){
	float distanciaAObjetivo = calcularProximaDistancia(enemigo);
	if(distanciaAObjetivo <= DISTANCIA_MINIMA)
		return true;
	return false;
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

void Personaje::obtenerAntidoto(Personaje* otro){
	if(haciendoFatality() || otro->recibioFatality() || otro->estaVolandoVertical() || otro->estaMareado())
		return;
    switch(estado->obtenerEstadoContrario()) {
        case CAMINANDO_DERECHA:
            return (otro->caminarDerecha());
        case CAMINANDO_IZQUIERDA:
            return (otro->caminarIzquierda());
        case EN_ESPERA:
        	return (otro->mantenerReposo());
        case SALTANDO_VERTICAL:
            return (otro->saltarVertical());
        case SALTANDO_OBLICUO_DERECHA:
            return (otro->saltarOblicuoDerecha());
        case SALTANDO_OBLICUO_IZQUIERDA:
            return (otro->saltarOblicuoIzquierda());
        case AGACHADO:
            return (otro->agacharse());
        case DEFENDIENDO:
            return (otro->defender());
        case DEFENDIENDO_AGACHADO:
            return (otro->defenderAgachado());
        case PINIA_ALTA:
            return (otro->piniaAlta());
        case PINIA_BAJA:
            return (otro->piniaBaja());
        case PINIA_SALTANDO_DIAGONAL_DERECHA:
            return (otro->piniaSaltandoDiagonalDerecha());
        case PINIA_SALTANDO_DIAGONAL_IZQUIERDA:
            return (otro->piniaSaltandoDiagonalIzquierda());
        case PINIA_SALTANDO_VERTICAL:
            return (otro->piniaSaltandoVertical());
        case PATEANDO_ALTO:
            return (otro->patadaAlta());
        case PATEANDO_BAJO:
            return (otro->patadaBaja());
        case PATEANDO_SALTANDO_DIAGONAL_DERECHA:
            return (otro->patadaSaltandoDiagonalDerecha());
        case PATEANDO_SALTANDO_DIAGONAL_IZQUIERDA:
            return (otro->patadaSaltandoDiagonalIzquierda());
        case PATEANDO_SALTANDO_VERTICAL:
            return (otro->patadaSaltandoVertical());
        case PATEANDO_ALTO_AGACHADO:
            return (otro->patadaAltaAgachado());
        case GANCHO:
            return (otro->gancho());
        case CAIDA_DERECHA:
            return (otro->caidaDerecha());
        case CAIDA_IZQUIERDA:
            return (otro->caidaIzquierda());
        case VICTORIA:
            return (otro->victoria());
        default:
            otro->mantenerReposo();
    }
}
