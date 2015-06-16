#ifndef PERSONAJEINTELIGENTE_H
#define PERSONAJEINTELIGENTE_H

#include "Personaje.h"
#include <utility>

class PersonajeInteligente : public Personaje {
    public:
        PersonajeInteligente(std::string id,
			double ancho,
			double alto,
			Vector2f posInicial,
			Posicionable* posc,
			int numJugador,
			std::map<estado_personaje, BVH*>* cajas_orientacion_derecha,
			DireccionObjeto orientacionInicialPersonaje = DIRECCION_DERECHA);
        virtual ~PersonajeInteligente();
        void calcularProximoMovimiento(Personaje* otro);
    protected:
    private:
        void caminarHaciaEnemigo(Colisionable* enemigo);
        void caminarLejosEnemigo(Colisionable* enemigo);
        bool ataquesEnemigoRepetidos();

        int contadorReposo;
        int contadorAtaque;
        int turno;
        std::pair<estado_personaje, estado_personaje> estados_anteriores;
};

#endif // PERSONAJEINTELIGENTE_H
