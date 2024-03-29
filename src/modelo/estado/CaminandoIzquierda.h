#ifndef CAMINANDOIZQUIERDA_H
#define CAMINANDOIZQUIERDA_H

#include "Estado.h"
#include "../Vector2f.h"

class CaminandoIzquierda : public Estado
{
    public:
        CaminandoIzquierda(Vector2f posInicial, BVH* caja, bool direccion);
        virtual ~CaminandoIzquierda();
        bool estaCaminando();
    protected:
    private:
};

#endif // CAMINANDOIZQUIERDA_H
