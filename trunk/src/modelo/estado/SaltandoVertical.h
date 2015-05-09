#ifndef SALTANDOVERTICAL_H
#define SALTANDOVERTICAL_H

#include "Estado.h"


class SaltandoVertical : public Estado
{
    public:
        SaltandoVertical(Vector2f posInicial, BVH* caja);
        virtual ~SaltandoVertical();
        bool estaSaltando();
    protected:
    private:
};

#endif // SALTANDOVERTICAL_H
