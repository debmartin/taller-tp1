#ifndef COLISIONABLE_H
#define COLISIONABLE_H

#include "Vector2f.h"
#include "Ataque.h"
#include "fisica/BVH.h"

class Colisionable
{
    public:
        virtual void colisionar(Colisionable* otro);
        virtual bool vaAColisionar(Colisionable* otro) = 0;
        Ataque* obtenerAtaque();
        Vector2f getPosicion();
        virtual BVH* obtenerCajaColision() = 0;
    protected:
        Colisionable(Vector2f posicionIn);
        virtual ~Colisionable();
        Vector2f posicion;
        Vector2f posicionCandidata;
        Ataque* ataqueActual;
        bool estaColisionando;
    private:
};

#endif // COLISIONABLE_H
