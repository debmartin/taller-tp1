#ifndef DEFENDIENDO_H
#define DEFENDIENDO_H

#include "Estado.h"


class Defendiendo : public Estado
{
    public:
        Defendiendo(Vector2f posInicial, BVH* caja);
        virtual ~Defendiendo();
        bool estaDefendiendo();
    protected:
    private:
};

#endif // DEFENDIENDO_H
