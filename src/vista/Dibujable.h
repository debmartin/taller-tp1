#ifndef DIBUJABLE_H
#define DIBUJABLE_H
#include "../modelo/Vector2f.h"

class Dibujable
{
    public:
        /** Default constructor */
        Dibujable();
        /** Default destructor */
        virtual ~Dibujable();
        virtual void dibujar() = 0;
        virtual void actualizar() = 0;
        virtual void centrar_en(Vector2f posicion) = 0;
    protected:
    private:
};

#endif // DIBUJABLE_H
