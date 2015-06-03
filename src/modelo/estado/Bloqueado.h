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
        bool estaGolpeando();
        bool ejecutandoMovimientoEspecial();
        bool estaEnPiso();
    protected:
    private:
        Estado* estadoDeBloqueo;
};

#endif // BLOQUEADO_H
