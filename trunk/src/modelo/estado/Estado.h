#ifndef ESTADO_H
#define ESTADO_H

#include "../Trayectoria.h"
#include "../Ataque.h"
#include "../fisica/BVH.h"

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
	BLOQUEADO
} estado_personaje;

class Estado
{
    public:
        Estado(Trayectoria* trayectoriaInicial, estado_personaje id, BVH* caja);
        virtual ~Estado();
        virtual bool estaAtacando();
        virtual bool estaDefendiendo();
        virtual bool estaSaltando();
        virtual bool estaAgachado();
        virtual bool estaEsperando();
        virtual bool ejecutandoMovimientoEspecial();
        virtual bool estaBloqueado();

        Ataque* obtenerAtaque();
        Vector2f obtenerProximaPosicion();
        Vector2f obtenerVelocidad();
        estado_personaje Id();
        Vector2f actualizar();
        bool haySuperposicion(BVH* otraCaja);
        BVH* obtenerCajaColision();
        void agregarCajaColision(BVH* cajaColision);
        Trayectoria* getTrayectoria();
    protected:
        Ataque* ataqueEstado;
    private:
        Trayectoria* trayectoria;
        float tCreacion;
        estado_personaje id;
        BVH* cajas;
};

#endif // ESTADO_H
