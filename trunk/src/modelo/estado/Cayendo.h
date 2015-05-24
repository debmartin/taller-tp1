#ifndef CAYENDO_H
#define CAYENDO_H

#include "Estado.h"
#include "../Vector2f.h"

class Cayendo : public Estado
{
    public:
        Cayendo(Vector2f posInicial, Vector2f velocidad, estado_personaje id, BVH* caja);
        virtual ~Cayendo();
        bool estaSaltando();
    protected:
    private:
};

#endif // CAYENDO_H
