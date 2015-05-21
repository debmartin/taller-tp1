#ifndef DEFENDIENDOAGACHADO_H
#define DEFENDIENDOAGACHADO_H

#include "Estado.h"


class DefendiendoAgachado : public Estado
{
    public:
        DefendiendoAgachado(Vector2f posInicial, BVH* caja);
        virtual ~DefendiendoAgachado();
        bool estaDefendiendo();
    protected:
    private:
};

#endif // DEFENDIENDOAGACHADO_H
