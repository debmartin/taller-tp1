#ifndef SRC_VISTA_ANIMACION_H_
#define SRC_VISTA_ANIMACION_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Animacion {

    private:
        SDL_Texture* textura;
        int cantidadFotogramas;
        int fps;
        std::string id;
    public:
        Animacion(std::string pathImagen, int cantFotogramas, int fps, std::string id, SDL_Renderer* pRenderer);
        SDL_Texture* getTextura();
        int getCantidadFotogramas();
        int getFps();
        std::string getId();
        virtual ~Animacion();
};

#endif /* SRC_VISTA_ANIMACION_H_ */
