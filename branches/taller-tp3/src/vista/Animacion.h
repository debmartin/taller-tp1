#ifndef SRC_VISTA_ANIMACION_H_
#define SRC_VISTA_ANIMACION_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>
#include "Desplazar.h"
#include "../json/ColorAlternativoDef.h"

using namespace std;

class Animacion: public Loggeable{

    private:
		SDL_Renderer* pRenderer;
		SDL_Texture* textura;
		std::string pathImagen;
		int cantidadFotogramas;
		int fps;
		std::string id;

    public:
        Animacion(SDL_Renderer* pRenderer, std::string pathImagen, int cantFotogramas, int fps, std::string id);
        SDL_Texture* getTextura();
        int getCantidadFotogramas();
        int getFps();
        std::string getId();
        virtual ~Animacion();
        void cambiarColor(Uint16 Hinicial, Uint16 Hfinal, Uint16 desplazamiento);
        void cambiarColor(ColorAlternativoDef* colorAlternativoDef);

    	friend ostream& operator<<(ostream &o, const Animacion &a);
    	string toString();
};

#endif /* SRC_VISTA_ANIMACION_H_ */
