#include "Animacion.h"

Animacion::Animacion(

		SDL_Renderer* pRenderer,
		string pathImagen,
		int cantidadFotogramas,
		int fps,
		string id):

		pRenderer(pRenderer),
		pathImagen(pathImagen),
		cantidadFotogramas(cantidadFotogramas),
		fps(fps),
		id(id)

{

    SDL_Surface* pTempSurface = IMG_Load(pathImagen.c_str());

    if (!pTempSurface) {
		//Logger::getInstance()->error("No se pudo cargar la imagen " + pathImagen);
		return;
	}

	textura = SDL_CreateTextureFromSurface(this->pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	//if (!textura)
		//Logger::getInstance()->error("No se pudo crear la textura SDL para " + pathImagen);

}

SDL_Texture* Animacion::getTextura() {
	return this->textura;
}

int Animacion::getCantidadFotogramas() {
	return this->cantidadFotogramas;
}

int Animacion::getFps() {
	return this->fps;
}

Animacion::~Animacion() {
	SDL_DestroyTexture(textura);
}

string Animacion::getId(){
    return id;
}

void Animacion::cambiarColor(Uint16 Hinicial, Uint16 Hfinal, Uint16 desplazamiento)
{
	// SE VUELVE A CARGAR LA IMAGEN A UNA SUPERFICIE AUXILIAR
	SDL_Surface* superficie_tempotal = IMG_Load(this->pathImagen.c_str());

    if ( superficie_tempotal )
    {
    	// SE REALIZA EL CAMBIO DE COLOR SOBRE LA SUPERFICIE AUXILIAR
    	Desplazar::H(superficie_tempotal, Hinicial, Hfinal, desplazamiento);

    	// SE CONVIERTE LA SUPERFICIE A UNA TEXTURA AUXILIAR
    	SDL_Texture* texturaAuxiliar = SDL_CreateTextureFromSurface(this->pRenderer, superficie_tempotal);

    	// SE LIBERA LA SUPERFICIE AUXILIAR
    	SDL_FreeSurface(superficie_tempotal);

    	if ( !texturaAuxiliar )
    		//Logger::getInstance()->error("Animacion::cambiarColor(): No se pudo crear la textura SDL para la imagen " + pathImagen + " en su cambio de color.");

    	// SE SOBRESCRIBE LA TEXTURA LOCAL CON LA AUXILIAR
    	SDL_DestroyTexture(this->textura);
    	this->textura = texturaAuxiliar;
	}
    else
    {
    	//Logger::getInstance()->error("Animacion::cambiarColor(): No se pudo cargar la imagen " + pathImagen + " para el cambio de color.");
    }
}

void Animacion::cambiarColor(ColorAlternativoDef* colorAlternativoDef) {
	this->cambiarColor(colorAlternativoDef->getHfinal(), colorAlternativoDef->getHfinal(), colorAlternativoDef->getDesplazamiento());
}
ostream& operator <<(ostream &o, const Animacion &a)
{
	o<<"Animacion -> [cantFotog, fps, id, pathImagen]=[";
	o<<a.cantidadFotogramas<<", "<<a.fps<<", "<<a.id<<", "<<a.pathImagen<<"]";
	return o;
}

string Animacion::toString()
{
    ostringstream stream;
    stream <<*this;
	return stream.str();
}
