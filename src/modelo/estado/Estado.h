#ifndef ESTADO_H
#define ESTADO_H

#include "../Trayectoria.h"
#include "../Ataque.h"
#include "../fisica/BVH.h"

#define DANIO_GANCHO 25
#define DANIO_PATADA_ALTA 10
#define DANIO_PINIA_ALTA 10
#define DANIO_PATADA_BAJA 10
#define DANIO_PINIA_BAJA 10
#define DANIO_PATADA_SALTANDO 20
#define DANIO_PINIA_SALTANDO 20
#define VECTOR_EMPUJE_DERECHA Vector2f(1,0)
#define VECTOR_EMPUJE_IZQUIERDA Vector2f(-1,0)

typedef enum estado_personaje
{
	EN_ESPERA,
	AGACHADO,
	CAMINANDO_DERECHA,
	CAMINANDO_IZQUIERDA,
	SALTANDO_VERTICAL,
    SALTANDO_OBLICUO_DERECHA,
    SALTANDO_OBLICUO_IZQUIERDA,
	PINIA_ALTA,
	PINIA_BAJA,
	PINIA_SALTANDO_VERTICAL,
	PINIA_SALTANDO_DIAGONAL_DERECHA,
	PINIA_SALTANDO_DIAGONAL_IZQUIERDA,
	PATEANDO_SALTANDO_VERTICAL,
	PATEANDO_SALTANDO_DIAGONAL_DERECHA,
	PATEANDO_SALTANDO_DIAGONAL_IZQUIERDA,
	PATEANDO_ALTO,
	PATEANDO_BAJO,
	PATEANDO_ALTO_AGACHADO,
	GANCHO,
	DEFENDIENDO,
	DEFENDIENDO_AGACHADO,
	RECIBIENDO_GOLPE,
	CAIDA_DERECHA,
	CAIDA_IZQUIERDA,
	TIRANDO_PODER,
	MUERTO,
	MUERTO_EN_PISO,
	VICTORIA,
	BLOQUEADO
} estado_personaje;

class Estado
{
    public:
        Estado(Trayectoria* trayectoriaInicial, estado_personaje id, BVH* caja);
        Estado(Trayectoria* trayectoriaInicial, float tiempoCreacion, estado_personaje id, BVH* caja);
        virtual ~Estado();
        virtual bool estaAtacando();
        virtual bool estaDefendiendo();
        virtual bool estaSaltando();
        virtual bool estaSaltandoVertical();
        virtual bool estaSaltandoDiagonalDerecha();
        virtual bool estaSaltandoDiagonalIzquierda();
        virtual bool estaAgachado();
        virtual bool estaEsperando();
        virtual bool ejecutandoMovimientoEspecial();
        virtual bool estaBloqueado();
        virtual bool estaCaminando();
        virtual bool estaEnCaida();
        virtual bool efectuandoGancho();
        virtual bool estaGolpeado();
        virtual bool estaGolpeando();
        virtual bool estaEnPiso();
        virtual bool estaDesplazandoVertical();

        Ataque* obtenerAtaque();
        Vector2f obtenerProximaPosicion();
        Vector2f obtenerVelocidad();
        estado_personaje Id();
        void actualizar(Vector2f nuevaPosicion);
        bool haySuperposicion(BVH* otraCaja);
        BVH* obtenerCajaColision();
        void agregarCajaColision(BVH* cajaColision);
        Trayectoria* getTrayectoria();
        void reducirVelocidad();
        float obtenerTiempoActual();
        float obtenerTiempoDeCreacion();
        double calcularAncho();
        double calcularAlto();
        void efectuarAtaque();
        bool ataqueFueEfectuado();
    protected:
        Ataque* ataqueEstado;
    private:
        Trayectoria* trayectoria;
        float tCreacion;
        estado_personaje id;
        BVH* cajas;
        bool ataqueEfectuado;
};

#endif // ESTADO_H
