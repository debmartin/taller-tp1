#ifndef SALTANDOOBLICUOIZQUIERDA_H
#define SALTANDOOBLICUOIZQUIERDA_H

#include "Estado.h"


class SaltandoOblicuoIzquierda : public Estado
{
    public:
        SaltandoOblicuoIzquierda(Vector2f posInicial, BVH* caja);
        virtual ~SaltandoOblicuoIzquierda();
        bool estaSaltando();
    protected:
    private:
};

#endif // SALTANDOOBLICUOIZQUIERDA_H
