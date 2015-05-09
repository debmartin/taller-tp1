#ifndef GOLPEANDOALTO_H
#define GOLPEANDOALTO_H

#include "Estado.h"


class GolpeandoAlto : public Estado
{
    public:
        GolpeandoAlto(Vector2f posInicial, BVH* caja);
        virtual ~GolpeandoAlto();
        bool estaAtacando();
        bool ejecutandoMovimientoEspecial();
    protected:
    private:
};

#endif // GOLPEANDOALTO_H
