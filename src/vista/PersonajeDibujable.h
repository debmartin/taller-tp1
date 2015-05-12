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
#define ID_SUBZERO_REPOSO "reposo"
#define ID_SUBZERO_CAMINANDO "caminando"
#define ID_SUBZERO_AGACHADO "agachado"
#define ID_SUBZERO_SALTANDO_VERTICAL "saltando-vertical"
#define ID_SUBZERO_SALTANDO_DIAGONAL "saltando-diagonal"
#define ID_SUBZERO_PINIA_ALTA "pinia-alta"
#define ID_SUBZERO_PINIA_BAJA "pinia-baja"
#define ID_SUBZERO_PINIA_SALTANDO_DIAGONAL "salto-diagonal-pinia"
#define ID_SUBZERO_PATEANDO_ALTO "patada-alta"
#define ID_SUBZERO_PATEANDO_BAJO "patada-baja"
#define ID_SUBZERO_PATEANDO_ALTO_AGACHADO "patada-alta-agachado"
#define ID_SUBZERO_PATEANDO_SALTANDO_VERTICAL "patada-saltando-vertical"
#define ID_SUBZERO_PATEANDO_SALTANDO_DIAGONAL "salto-diagonal-patada"
#define ID_SUBZERO_GANCHO "gancho"
#define ID_SUBZERO_DEFENDIENDO "defendiendo"
#define ID_SUBZERO_DEFENDIENDO_AGACHADO "defendiendo_agachado"


class PersonajeDibujable : public Dibujable, public Observador {
private:
	Sprite* spritePersonaje;
	estado_personaje estado;
	std::string nombre;
    std::map<std::string, Animacion*> animaciones;
    ColorAlternativoDef* colorAlternativo;
    ArmaDibujable* armaDibujable;

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
