#ifndef POSICIONADOR_H
#define POSICIONADOR_H

enum Direccion {DERECHA, IZQUIERDA, ARRIBA, ABAJO};

class Posicionador
{
    public:
        Posicionador();
        virtual ~Posicionador();
//        void puedePosicionar(Posicionable pos, Direccion nuevaDir) = 0;
    protected:
    private:
};

#endif // POSICIONADOR_H
