#ifndef SRC_VISTA_ANIMACION_H_
#define SRC_VISTA_ANIMACION_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Desplazar.h"

class Animacion {

    private:
        SDL_Texture* textura;
        int cantidadFotogramas;
        int fps;
        std::string id;
    public:
        Animacion(std::string pathImagen, int cantFotogramas, int fps, std::string id, SDL_Renderer* pRenderer);
        Animacion(
        		std::string pathImagen,
				int cantFotogramas,
				int fps,
				std::string id,
				SDL_Renderer* pRenderer,
				Uint16 Hinicial, Uint16 Hfinal, Uint16 desplazamiento);
        SDL_Texture* getTextura();
        int getCantidadFotogramas();
        int getFps();
        std::string getId();
        virtual ~Animacion();
};

#endif /* SRC_VISTA_ANIMACION_H_ */
