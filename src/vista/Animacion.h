#ifndef SRC_VISTA_ANIMACION_H_
#define SRC_VISTA_ANIMACION_H_

#include <string>

struct SDL_Renderer;
struct SDL_Texture;

class ColorAlternativoDef;

class Animacion {

    private:
        SDL_Texture* textura;
        int cantidadFotogramas;
        int fps;
        std::string id;
        std::string pathImagen;
    public:
        Animacion(std::string pathImagen, int cantFotogramas, int fps, std::string id, SDL_Renderer* pRenderer);
        SDL_Texture* getTextura();
        int getCantidadFotogramas();
        int getFps();
        std::string getId();
        virtual ~Animacion();
        void cambiarColor(ColorAlternativoDef* colorAlternativoDef);
};

#endif /* SRC_VISTA_ANIMACION_H_ */
