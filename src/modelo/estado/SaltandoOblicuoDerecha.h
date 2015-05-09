#ifndef SALTANDOOBLICUODERECHA_H
#define SALTANDOOBLICUODERECHA_H

#include "Estado.h"


class SaltandoOblicuoDerecha : public Estado
{
    public:
        SaltandoOblicuoDerecha(Vector2f posInicial, BVH* caja);
        virtual ~SaltandoOblicuoDerecha();
        bool estaSaltando();
    protected:
    private:
};

#endif // SALTANDOOBLICUODERECHA_H
