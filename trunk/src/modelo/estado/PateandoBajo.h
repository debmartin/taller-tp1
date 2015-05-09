#ifndef PATEANDOBAJO_H
#define PATEANDOBAJO_H

#include "Estado.h"


class PateandoBajo : public Estado
{
    public:
        PateandoBajo(Vector2f posInicial, BVH* caja);
        virtual ~PateandoBajo();
        bool estaAtacando();
        bool estaDefendiendo();
    protected:
    private:
};

#endif // PATEANDOBAJO_H
