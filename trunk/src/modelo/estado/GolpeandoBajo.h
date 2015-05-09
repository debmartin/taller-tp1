#ifndef GOLPEANDOBAJO_H
#define GOLPEANDOBAJO_H

#include "Estado.h"


class GolpeandoBajo : public Estado
{
    public:
        GolpeandoBajo(Vector2f posInicial, BVH* caja);
        virtual ~GolpeandoBajo();
        bool estaAtacando();
        bool estaDefendiendo();
    protected:
    private:
};

#endif // GOLPEANDOBAJO_H
