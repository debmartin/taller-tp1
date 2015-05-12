#ifndef PINIABAJA_H
#define PINIABAJA_H

#include "Estado.h"


class PiniaBaja : public Estado
{
    public:
        PiniaBaja(Vector2f posInicial, BVH* caja);
        virtual ~PiniaBaja();
        bool estaAtacando();
        bool estaDefendiendo();
    protected:
    private:
};

#endif // PINIABAJA_H
