#ifndef BLOQUEADO_H
#define BLOQUEADO_H

#include "Estado.h"

class Bloqueado : public Estado
{
    public:
        Bloqueado(Estado* estadoActual);
        virtual ~Bloqueado();
        bool estaBloqueado();
        bool estaAtacando();
    protected:
    private:
        bool bandera;
};

#endif // BLOQUEADO_H
