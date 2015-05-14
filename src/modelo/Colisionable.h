#ifndef COLISIONABLE_H
#define COLISIONABLE_H

#include "Vector2f.h"
#include "Ataque.h"
#include "fisica/BVH.h"

class Colisionable
{
    public:
        virtual void colisionar(Colisionable* otro);
        virtual bool vaAColisionar(Colisionable* otro, double anchoAct, double altoAct);
        Ataque* obtenerAtaque();
        Vector2f getPosicion();
        virtual BVH* obtenerCajaColision() = 0;

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
