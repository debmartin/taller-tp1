#ifndef DIBUJABLE_H
#define DIBUJABLE_H


class Dibujable
{
    public:
        /** Default constructor */
        Dibujable();
        /** Default destructor */
        virtual ~Dibujable();
        virtual void dibujar() = 0;
        virtual void actualizar() = 0;
    protected:
    private:
};

#endif // DIBUJABLE_H
