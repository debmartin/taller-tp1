#ifndef ENESPERA_H
#define ENESPERA_H

#include "Estado.h"
#include "../../utils/Logger.h"


class EnEspera : public Estado
{
    public:
        EnEspera(Vector2f posInicial, BVH* caja);
        virtual ~EnEspera();
        bool estaEsperando();
        bool estaAtacando();
    protected:
    private:
};

#endif // ENESPERA_H
