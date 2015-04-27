#ifndef SRC_VISTA_PIXELCOLOR_H_
#define SRC_VISTA_PIXELCOLOR_H_
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream> //TODO: BORRAR
using namespace std; //TODO: BORRAR

#define GRADOS60 60.0f
#define GRADOS120 120.0f
#define GRADOS240 240.0f
#define GRADOS360 360.0f
#define GRADOS0 0.0f

class PixelColor {

private:
	PixelColor();
	static Uint8  maximo(Uint8  R, Uint8  G, Uint8  B);
	static Uint8  minimo(Uint8  R, Uint8  G, Uint8  B);
	static Uint16 RGBtoH(Uint8  R, Uint8  G, Uint8  B);
	static Uint16 RGBtoS(Uint8  R, Uint8  G, Uint8  B);
	static Uint16 RGBtoV(Uint8  R, Uint8  G, Uint8  B);
	static Uint8  HSVtoR(Uint16 H, Uint16 S, Uint16 V);
	static Uint8  HSBtoG(Uint16 H, Uint16 S, Uint16 V);
	static Uint8  HSBtoB(Uint16 H, Uint16 S, Uint16 V);

public:
	static void RGBtoHSV(Uint8  R, Uint8  G, Uint8  B, Uint16& H, Uint16& S, Uint16& V);
	static void HSVtoRGB(Uint16 H, Uint16 S, Uint16 V, Uint8&  R, Uint8&  G, Uint8&  B);
	virtual ~PixelColor();

};

#endif /* SRC_VISTA_PIXELCOLOR_H_ */
