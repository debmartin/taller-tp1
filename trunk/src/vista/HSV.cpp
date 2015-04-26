/*
 * HSV.cpp
 *
 *  Created on: 25/4/2015
 *      Author: gaston
 */

#include "HSV.h"

HSV::HSV(SDL_Texture* s) {
	// TODO Auto-generated constructor stub

	/*Uint8 *colors = (Uint8*)&colorKey;

	//Aca obtener las componentes RGB;
	int R = colors[0];
	int G = colors[1];
	int B = colors[2];*/

	int R;
	int G;
	int B;

	//Hallo el máximo y el mínimo
	maxRGB = maximo(R, G, B);
	minRGB = minimo(R, G, B);

	setH(R,G,B);
	setS(R,G,B);
	setV(R,G,B);

	//Operar con los valores de HSV
	transformar_HSV_a_RGB();

	//Operar con los valores finales de RGB
}

int HSV::maximo(int R, int G, int B){
	if(R >= G || R >= B){
		return R;
	}else if(G >= R || G >= B){
		return G;
	}return B;
}

int HSV::minimo(int R, int G, int B){
	if(R <= G || R <= B){
		return R;
	}else if(G <= R || G <= B){
		return G;
	}return B;
}

void HSV::setH(int R, int G, int B){
	if(maxRGB == minRGB){
		//no definido
	}else if(maxRGB == R && G >= B){
		H = GRADOS60 * (G - B)/(maxRGB - minRGB) + GRADOS0;
	}else if(maxRGB == R && G < B){
		H = GRADOS60 * (G - B)/(maxRGB - minRGB) + GRADOS360;
	}else if(maxRGB == G){
		H = GRADOS60 * (B - R)/(maxRGB - minRGB) + GRADOS120;
	}else if(maxRGB == B){
		H = GRADOS60 * (R - G)/(maxRGB - minRGB) + GRADOS240;
	}
}

void HSV::setS(int R, int G, int B){
	if(maxRGB == 0){
		S = 0;
	}
	S = (1-minRGB/maxRGB);
}

void HSV::setV(int R, int G, int B){
	V = maxRGB;
}

/*Precondición H <= 360*/
void HSV::transformar_HSV_a_RGB(){
	int Hinicial = (H/60)%6;
	int f = ((H/60)%6) - Hinicial;
	int p = V*(1-S);
	int q = V*(1-f*S);
	int t = V*(1-(1-f)*S);

	if(Hinicial == 0){
		Rfinal = V;
		Gfinal = t;
		Bfinal = p;
	}else if(Hinicial == 1){
		Rfinal = q;
		Gfinal = V;
		Bfinal = p;
	}else if(Hinicial == 2){
		Rfinal = p;
		Gfinal = V;
		Bfinal = t;
	}else if(Hinicial == 3){
		Rfinal = p;
		Gfinal = q;
		Bfinal = V;
	}else if(Hinicial == 4){
		Rfinal = t;
		Gfinal = p;
		Bfinal = V;
	}else if(Hinicial == 5){
		Rfinal = V;
		Gfinal = p;
		Bfinal = q;
	}
}

HSV::~HSV() {
	// TODO Auto-generated destructor stub
}
