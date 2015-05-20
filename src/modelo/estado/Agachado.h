#ifndef AGACHADO_H
#define AGACHADO_H

#include "Estado.h"


class Agachado : public Estado
{
    public:
        Agachado(Vector2f posInicial, BVH* caja);
        virtual ~Agachado();
        bool estaAgachado();
        bool estaAtacando();
    protected:
    private:
};

#endif // AGACHADO_H
