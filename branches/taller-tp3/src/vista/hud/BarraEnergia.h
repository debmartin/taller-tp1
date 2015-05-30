#ifndef BARRAENERGIA_H_
#define BARRAENERGIA_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;

#define DIR_IMG_BARRA_BORDE    "RECURSOS/HUD/barra-borde.png"
#define DIR_IMG_BARRA_INTERIOR "RECURSOS/HUD/barra-interior3.png"

typedef enum OrientacionBarra
{
    BARRA_IZQUIERDA,
    BARRA_DERECHA
} OrientacionBarra;

class BarraEnergia {
public:
	BarraEnergia() {};
	BarraEnergia(SDL_Window* gWindow, string nombre, OrientacionBarra orientacion);
	void disminuirEnergia(float offset);
	void setEnergia(float nuevaEnergia);
	float getPorcentajeEnergia();
	SDL_Texture* updateTexture();
	virtual ~BarraEnergia();

private:
	SDL_Texture* renderText(
			const std::string &message,
			const std::string &fontFile,
			SDL_Color color,
			int fontSize,
			SDL_Renderer *renderer);
	SDL_Texture* cargarTextura(string path);
	void combinarTexturas();
	Uint32 W(SDL_Texture* t);
	Uint32 H(SDL_Texture* t);
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	SDL_Texture* tBarraBorde;
	SDL_Texture* tBarraInterior;
	SDL_Texture* tBarraCombinada;
	SDL_Texture* tNombre;
	SDL_Texture* tNombreSombra;
	string nombre;
	OrientacionBarra orientacion;

	float porcentajeEnergia;
};

#endif /* BARRAENERGIA_H_ */
