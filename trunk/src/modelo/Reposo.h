#ifndef SRC_VISTA_REPOSO_H_
#define SRC_VISTA_REPOSO_H_

class Reposo: public Trayectoria {

private:
	Vector2f posInicial;

public:

	Reposo(Vector2f posInicial):posInicial(posInicial) {};

	Vector2f getPosicion(float tActual) {
		return this->posInicial;
	};
	virtual Vector2f getVelocidad(float tActual) {
		return Vector2f(0.0f, 0.0f);
	}
	~Reposo() {}
};

#endif /* SRC_VISTA_REPOSO_H_ */
