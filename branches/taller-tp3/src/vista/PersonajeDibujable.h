/*
 * PersonajeDibujable.h
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#ifndef SRC_VISTA_PERSONAJEDIBUJABLE_H_
#define SRC_VISTA_PERSONAJEDIBUJABLE_H_

#include <map>
#include <string>

#include "../modelo/Observador.h"
#include "../modelo/Personaje.h"
#include "../modelo/Vector2f.h"
#include "Animacion.h"
#include "Dibujable.h"
#include "Sprite.h"

class ArmaDibujable;

#define ID_FONDO "screen-pit"
#define ID_PERSONAJE_REPOSO "reposo"
#define ID_PERSONAJE_CAMINANDO "caminando"
#define ID_PERSONAJE_AGACHADO "agachado"
#define ID_PERSONAJE_SALTANDO_VERTICAL "saltando-vertical"
#define ID_PERSONAJE_SALTANDO_DIAGONAL "saltando-diagonal"
#define ID_PERSONAJE_PINIA_ALTA "pinia-alta"
#define ID_PERSONAJE_PINIA_BAJA "pinia-baja"
#define ID_PERSONAJE_PINIA_SALTANDO_DIAGONAL "pinia-saltando-diagonal"
#define ID_PERSONAJE_PINIA_SALTANDO_VERTICAL "salto-pinia"
#define ID_PERSONAJE_PATEANDO_ALTO "patada-alta"
#define ID_PERSONAJE_PATEANDO_BAJO "patada-baja"
#define ID_PERSONAJE_PATEANDO_ALTO_AGACHADO "patada-alta-agachado"
#define ID_PERSONAJE_PATEANDO_SALTANDO_VERTICAL "salto-vertical-patada"
#define ID_PERSONAJE_PATEANDO_SALTANDO_DIAGONAL "salto-diagonal-patada"
#define ID_PERSONAJE_GANCHO "gancho"
#define ID_PERSONAJE_DEFENDIENDO "defensa-parado"
#define ID_PERSONAJE_DEFENDIENDO_AGACHADO "defensa-agachado"
#define ID_PERSONAJE_RECIBIENDO_GOLPE "recibiendo-golpe"
#define ID_PERSONAJE_RECIBIENDO_PINIA_RETROCEDIENDO "recibiendo-pinia-retrocediendo"
#define ID_PERSONAJE_CAIDA "caida"
#define ID_PERSONAJE_MAREADO "mareado"
#define ID_PERSONAJE_TIRANDO_PODER "tirando-poder"
#define ID_PERSONAJE_BEBE "bebe"
#define ID_PERSONAJE_VICTORIA "victoria"
#define ID_PERSONAJE_MUERTO "muerto"
#define ID_PERSONAJE_SLIDE "deslizamiento"
#define ID_PERSONAJE_TIJERA "tijera"
#define ID_PERSONAJE_FATALITY1 "fatality1"
#define ID_PERSONAJE_DECAPITADO "decapitado"

class PersonajeDibujable : public Dibujable, public Observador {
private:
	Sprite* spritePersonaje;
	estado_personaje estado;
	std::string nombre;
    std::map<std::string, Animacion*> animaciones;
    ColorAlternativoDef* colorAlternativo;
    ArmaDibujable* armaDibujable;
    estado_personaje estadoAnterior;

    // ENVOLVENTE
    Animacion* animacionEnvolvente;
    Sprite* spriteEnvolvente;
public:
    PersonajeDibujable();
	PersonajeDibujable(Animacion* animIni, Vector2f posicionIni, Vector2f tamanioPx, OrientacionSprite orientacion,
						ColorAlternativoDef* colorAlternativo);
	virtual ~PersonajeDibujable();
	void seleccionarSprite();
	void setEstado(estado_personaje unEstado);
	void agregarAnimacion(Animacion* nuevaAnimacion);
	void agregarArma(ArmaDibujable* unArma);
	ArmaDibujable* getArma();
	void centrar_en(Vector2f v, float limiteLogicoIzquierdoVentana, float relacion_de_aspectoX) { }
	void dibujar();
	void actualizar();
	void recibirNotificacion(Observable* unObservable);
	Sprite* _getSprite() { return spritePersonaje; }
	void cambiarOrientacionHaciaDerecha();
	void cambiarOrientacionHaciaIzquierda();
	void cambiarColor(ColorAlternativoDef* colorAlternativo);
	ColorAlternativoDef* getColorAlternativo() const;
};

#endif /* SRC_VISTA_PERSONAJEDIBUJABLE_H_ */
