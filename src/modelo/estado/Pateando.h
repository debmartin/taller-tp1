#ifndef PATEANDO_H
#define PATEANDO_H

#include "Estado.h"


class Pateando : public Estado
{
    public:
        Pateando(Vector2f posInicial, BVH* caja);
        virtual ~Pateando();
        bool estaAtacando();
        bool estaDefendiendo();
    protected:
    private:
};

#endif // PATEANDO_H
