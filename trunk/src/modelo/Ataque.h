#ifndef ATAQUE_H
#define ATAQUE_H


class Ataque
{
    public:
        Ataque(int danio);
        virtual ~Ataque();
        int obtenerDanio();
    protected:
    private:
        int danio;
};

#endif // ATAQUE_H
