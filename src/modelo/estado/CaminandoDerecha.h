#ifndef CAMINANDODERECHA_H
#define CAMINANDODERECHA_H

#include "Estado.h"


class CaminandoDerecha : public Estado
{
    public:
        CaminandoDerecha(Vector2f posInicial, bool enLimite, BVH* caja);
        virtual ~CaminandoDerecha();
        bool estaCaminando();
    protected:
    private:
};

#endif // CAMINANDODERECHA_H