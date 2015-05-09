#ifndef PATEANDOALTO_H
#define PATEANDOALTO_H

#include "Estado.h"


class PateandoAlto : public Estado
{
    public:
        PateandoAlto(Vector2f posInicial, BVH* caja);
        virtual ~PateandoAlto();
        bool estaAtacando();
        bool ejecutandoMovimientoEspecial();
    protected:
    private:
};

#endif // PATEANDOALTO_H
