#ifndef BLOQUEADO_H
#define BLOQUEADO_H

#include "Estado.h"


class Bloqueado : public Estado
{
    public:
        Bloqueado(Trayectoria* trayActual, BVH* caja);
        Bloqueado(estado_personaje estadoInicial, Trayectoria* trayActual, BVH* caja);
        virtual ~Bloqueado();
        bool estaBloqueado();
    protected:
    private:
};

#endif // BLOQUEADO_H
