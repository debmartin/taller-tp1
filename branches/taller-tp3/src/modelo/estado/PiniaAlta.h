#ifndef PINIAALTA_H
#define PINIAALTA_H

#include "Estado.h"


class PiniaAlta : public Estado
{
    public:
        PiniaAlta(Vector2f posInicial, BVH* caja);
        virtual ~PiniaAlta();
        bool estaAtacando();
        bool estaDefendiendo();
        bool estaGolpeando();
    protected:
    private:
};

#endif // PINIAALTA_H
