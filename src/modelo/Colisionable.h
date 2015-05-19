#ifndef COLISIONABLE_H
#define COLISIONABLE_H

#include "Vector2f.h"
#include "Ataque.h"
#include "fisica/BVH.h"

enum Direccion {
    DIR_DERECHA,
    DIR_IZQUIERDA
} typedef Direccion;

class Colisionable
{
    public:
        virtual void colisionar(Colisionable* otro);
        virtual bool vaAColisionar(Colisionable* otro, double anchoAct, double altoAct);
        Ataque* obtenerAtaque();
        Vector2f getPosicion();
        virtual BVH* obtenerCajaColision() = 0;
        virtual bool empujar(Direccion direccionEmpuje, Vector2f diferencia) = 0;
        Vector2f getPivote();

    protected:
        Colisionable(Vector2f posicionIn, double anchoIn, double altoIn);
        virtual ~Colisionable();
        Vector2f posicion;
        Vector2f posicionCandidata;
        Vector2f posicionAnterior;
        Ataque* ataqueActual;
        bool estaColisionando;
        double ancho;
        double alto;

    private:
};

#endif // COLISIONABLE_H
