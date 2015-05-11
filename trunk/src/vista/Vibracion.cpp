#include "Vibracion.h"

Vibracion::Vibracion() {
	this->amplitud = 10;
	this->vibrando = false;
	this->tInicial = 0.0;
}
Vibracion::Vibracion(float amplitud) {
	this->amplitud = amplitud;
	this->vibrando = false;
	this->tInicial = 0.0;
}
void Vibracion::iniciar() {
	this->vibrando = true;
	this->tInicial = SDL_GetTicks();
}

Vector2f Vibracion::getOffset() {

	if (!estaVibrando())
		return Vector2f(0,0);

	if (T() >  0.00 && T() < 0.05)
		return Vector2f(0, -amplitud);
	if (T() >= 0.05 && T() < 0.10)
		return Vector2f(0, 0);
	if (T() >= 0.10 && T() < 0.15)
		return Vector2f(0, -amplitud);
	if (T() >= 0.15 && T() < 0.20)
		return Vector2f(0, 0);
	if (T() >= 0.20 && T() < 0.25)
		return Vector2f(0, -amplitud);
	if (T() >= 0.25 && T() < 0.30)
		return Vector2f(0, 0);

	if (T() >= 0.60)
		this->vibrando = false;

	return Vector2f(0,0);
}
double Vibracion::T() {
	double t = (SDL_GetTicks() - this->tInicial)/1000.0;
	//cout << t << endl;
	return t;
}

bool Vibracion::estaVibrando() {
	return this->vibrando;
}

Vibracion::~Vibracion() {
	// TODO Auto-generated destructor stub
}

