#ifndef SRC_VISTA_ANIMACION_H_
#define SRC_VISTA_ANIMACION_H_

#include <iostream>
#include <string>

#include "../utils/Loggeable.h"

class ColorAlternativoDef;

struct SDL_Renderer;
struct SDL_Texture;

class Animacion: public Loggeable{

    private:
        SDL_Texture* textura;
        int cantidadFotogramas;
        int fps;
        std::string id;
        std::string pathImagen;
    public:
        Animacion();
        Animacion(std::string pathImagen, int cantFotogramas, int fps, std::string id, SDL_Renderer* pRenderer);
        SDL_Texture* getTextura();
        int getCantidadFotogramas();
        int getFps();
        std::string getId();
        virtual ~Animacion();
        void cambiarColor(ColorAlternativoDef* colorAlternativoDef);
        Animacion* clonar();

    	friend ostream& operator<<(ostream &o, const Animacion &a);
    	string toString();
};

#endif /* SRC_VISTA_ANIMACION_H_ */
